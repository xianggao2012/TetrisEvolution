#include "LayerMenu.h"
#include "TEHeader.h"
#include "ConfigFactory.h"
#include "LayerPersonal.h"
#include "Storage.hpp"
#include "ItemLightening.h"
#include "ItemForkLightening.h"
#include "ItemGear.h"
//#include "ui/CocosGUI.h"
//#include "extensions/cocos-ext.h"

USING_NS_CC;
Scene* LayerPersonal::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LayerPersonal::create();

    // add layer as a child to scene
    scene->addChild(layer, 2);

    // return the scene
    return scene;
}
// on "init" you need to initialize your instance
bool LayerPersonal::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(LayerPersonal::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 2);

    /////////////////////////////
    // 3. add your codes below...

    // 3.1 return back to menu
    auto size = Director::getInstance()->getWinSize();
    
    auto labelText = LabelTTF::create("Go back", "Arial",30);
    auto labelItem = MenuItemLabel::create(labelText,
                                               CC_CALLBACK_1(LayerPersonal::labelMenuCallback, this));
    //创建一个菜单,并设置位置
    auto labelMenu = Menu::create(labelItem,NULL);
    labelMenu->setPosition(Vec2(100, 100));
    //将文本菜单加入到HelloWorld布景中,第二个参数表示在Z轴的层次，屏幕由里到外从小到大
    addChild(labelMenu,2);

    // 3. add your codes below...
    unordered_map<string, unordered_map<string, string>> config;
    config = ConfigFactory::getInstance()->LoadLayer("LayerPersonal");
    
    // 3.3 background
    cocos2d::Size _screenSize = cocos2d::Director::getInstance()->getWinSize();
    //    auto court = Sprite::create("court.png");
    
    auto court = Sprite::create(config[LGB_BG][LGB_BG_IMG]);
    court->setPosition(cocos2d::Point{
        _screenSize.width * stof(config["Background"]["px"]),
        _screenSize.height * stof(config["Background"]["py"])
    });
    addChild(court, 1);
    
    
    // 3.5 buttons
    typedef void (LayerPersonal::*FnPtr)(Ref *sender,Control::EventType controlEvent);
    
    std::map<std::string, FnPtr> myMap;
    myMap["IncreaseLighteningWhitePrg"] = &LayerPersonal::IncreaseLighteningWhitePrg;
    myMap["IncreaseLighteningBlackPrg"] = &LayerPersonal::IncreaseLighteningBlackPrg;
    myMap["IncreaseForkLighteningWhitePrg"] = &LayerPersonal::IncreaseForkLighteningWhitePrg;
    myMap["IncreaseForkLighteningBlackPrg"] = &LayerPersonal::IncreaseForkLighteningBlackPrg;
    myMap["IncreaseWithWhite"] = &LayerPersonal::IncreaseWithWhite;
    myMap["IncreaseWithBlack"] = &LayerPersonal::IncreaseWithBlack;
    
    int type3 = 0;
    for(unordered_map<string, unordered_map<string, string> >::iterator iter = config.begin(); iter != config.end(); iter++)
    {
        if(iter->second["type"] == "2")
        {
            
            ControlButton *lblBtn = ControlButton::create();
            lblBtn->setPosition(Vec2(stof(iter->second["px"]), stof(iter->second["py"])));
            auto backgroundButton = Scale9Sprite::create(iter->second["imageDefault"]);    // no event
            auto backgroundHighlightedButton = Scale9Sprite::create(iter->second["imageClicked"]); // clicked
            
            lblBtn->setBackgroundSpriteForState(backgroundButton, Control::State::NORMAL);
            lblBtn->setBackgroundSpriteForState(backgroundHighlightedButton, Control::State::HIGH_LIGHTED);
            lblBtn->setPreferredSize(Sprite::create(iter->second["imageDefault"])->getContentSize());
            
            lblBtn->addTargetWithActionForControlEvents(this, static_cast<cocos2d::extension::Control::Handler>(myMap[iter->first]),
                                                        Control::EventType::TOUCH_DOWN);
            
            addChild(lblBtn, 2);
        }
        else if(iter->second["type"] == "3")
        {
            pLabel[type3] = CCLabelTTF::create("default", "Arial", 30);//要显示的内容，字体，字号
            int a = Storage::getInstance()->getStorageStatus(iter->second["labelname"]);
            CCString* ns = CCString::createWithFormat("%s%d", iter->first.c_str(), a);
            string s = ns->_string;
            pLabel[type3]->setString(s);
            pLabel[type3]->setPosition(Vec2(stof(iter->second["px"]), stof(iter->second["py"])));
            this->addChild(pLabel[type3], 1);
            
            tempkey[type3] = iter->second["labelname"];
            cout<<"label:"<<type3<<":"<<iter->second["labelname"]<<endl;
            type3 ++;
        }
    }
    
    // 3.6 schedule: UPDATE
    scheduleUpdate();  // first priority before other schedulers which makes change
    
    Storage::getInstance()->Initialize();
    
    return true;
}
void LayerPersonal::update(float dt)
{
    for(int i = 0; i < 7; i ++)
    {
        int a = Storage::getInstance()->getStorageStatus(tempkey[i]);      // enum
        CCString* ns=CCString::createWithFormat("%s%d", tempkey[i].c_str(), a);
        string s=ns->_string;
        pLabel[i]->setString(s);
    }
}

void LayerPersonal::labelMenuCallback(Ref* pSender)
{
    auto scene = LayerMenu::createScene();
    //Director::getInstance()->replaceScene( TransitionFade::create(2, scene));
    Director::getInstance()->replaceScene(scene);
    //释放
    //scene->release();
}

void LayerPersonal::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void LayerPersonal::IncreaseLighteningWhitePrg(Ref *sender,Control::EventType controlEvent)
{
    if(ItemGear::WhiteEmpty()) return;
    ItemLightening::IncreaseWhitePrg(1);
    ItemGear::DecreaseWhiteGear(1);
}

void LayerPersonal::IncreaseLighteningBlackPrg(Ref *sender,Control::EventType controlEvent)
{
    if(ItemGear::BlackEmpty()) return;
    ItemLightening::IncreaseBlackPrg(1);
    ItemGear::DecreaseBlackGear(1);
}

void LayerPersonal::IncreaseForkLighteningWhitePrg(Ref *sender,Control::EventType controlEvent)
{
    if(ItemGear::WhiteEmpty()) return;
    ItemForkLightening::IncreaseWhitePrg(1);
    ItemGear::DecreaseWhiteGear(1);
}

void LayerPersonal::IncreaseForkLighteningBlackPrg(Ref *sender,Control::EventType controlEvent)
{
    if(ItemGear::BlackEmpty()) return;
    ItemForkLightening::IncreaseBlackPrg(1);
    ItemGear::DecreaseBlackGear(1);
}
void LayerPersonal::IncreaseWithWhite(Ref *sender,Control::EventType controlEvent)
{
    if(ItemGear::WhiteEmpty()) return;
    ItemLightening::IncreaseCount(1);
    ItemGear::DecreaseWhiteGear(1);
}
void LayerPersonal::IncreaseWithBlack(Ref *sender,Control::EventType controlEvent)
{
    if(ItemGear::BlackEmpty()) return;
    ItemLightening::IncreaseCount(1);
    ItemGear::DecreaseBlackGear(1);
}
