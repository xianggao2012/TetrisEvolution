#include "LayerMenu.h"
#include "LayerGameClassic.h"
#include "LayerGameDig.h"
USING_NS_CC;

Scene* LayerMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LayerMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LayerMenu::init()
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
                                           CC_CALLBACK_1(LayerMenu::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...
    //获得屏幕的大小
    auto size = Director::getInstance()->getWinSize();
    //创建一个图片菜单项。
    //四个参数代表：正常显示的图片，选中菜单项后显示的图片，关闭时显示的图片，菜单项的回调函数。
    auto imageItem = MenuItemImage::create("btn-play-normal.png",
                                           "btn-play-selected.png",
                                           CC_CALLBACK_1(LayerMenu::imageMenuCallback, this));
    //创建一个菜单,并设置位置
    auto imageMenu = Menu::create(imageItem,NULL);
    imageMenu->setPosition(Vec2(size.width/2,size.height/2));
    //将图片菜单加入到HelloWorld布景中,第二个参数表示在Z轴的层次，屏幕由里到外从小到大
    addChild(imageMenu,2);
    
    //创建一个行文本参数代表：显示内容，字体，大小
    auto labelText = LabelTTF::create("Classic Mode", "Arial",30);
    //创建一个文本项,参数代表：要显示的文本内容，目标对象，回调函数
    auto labelItem = MenuItemLabel::create(labelText,
                                           CC_CALLBACK_1(LayerMenu::labelMenuCallback, this));
    //创建一个菜单,并设置位置
    auto labelMenu = Menu::create(labelItem,NULL);
    labelMenu->setPosition(Vec2(size.width/2,size.height/2+50));
    //将文本菜单加入到HelloWorld布景中,第二个参数表示在Z轴的层次，屏幕由里到外从小到大
    addChild(labelMenu,2);
   
    
//
//    // add a label shows "Hello World"
//    // create and initialize a label
//    
//    auto label = LabelTTF::create("Hello World", "Arial", 24);
//    
//    // position the label on the center of the screen
//    label->setPosition(Vec2(origin.x + visibleSize.width/2,
//                            origin.y + visibleSize.height - label->getContentSize().height));
//
//    // add the label as a child to this layer
//    this->addChild(label, 1);
//
//    // add "HelloWorld" splash screen"
//    auto sprite = Sprite::create("HelloWorld.png");
//
//    // position the sprite on the center of the screen
//    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//
//    // add the sprite as a child to this layer
//    this->addChild(sprite, 0);
    
    return true;
}

void LayerMenu::imageMenuCallback(Ref* pSender)
{
    //在输出台打印一句话
//    cocos2d::log("ImageMenu");
//    CCLOG("ImageMenu");
}
void LayerMenu::labelMenuCallback(Ref* pSender)
{
    auto scene = LayerGameDig::createScene();
    Director::getInstance()->replaceScene( TransitionFade::create(0, scene));
//    auto scene = LayerGameClassic::createScene();
//    Director::getInstance()->replaceScene( TransitionFade::create(2, scene));
//    //释放
//    //scene->release();
}

void LayerMenu::menuCloseCallback(Ref* pSender)
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
