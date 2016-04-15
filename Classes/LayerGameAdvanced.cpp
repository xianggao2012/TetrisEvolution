#include "LayerGameAdvanced.h"
#include "LayerMenu.h"
#include "TEHeader.h"
#include "ConfigFactory.h"

USING_NS_CC;

Scene* LayerGameAdvanced::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LayerGameAdvanced::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LayerGameAdvanced::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerGameBasic::init() )
    {
        return false;
    }

    game->setPoolDepth(3);
    
    // Dynamic buttons
    unordered_map<string, unordered_map<string, string>> config;
    config = ConfigFactory::getInstance()->LoadLayer("LayerGameAdvanced");
    
    typedef void (LayerGameAdvanced::*FnPtr)(Ref *sender,Control::EventType controlEvent);
    std::map<std::string, FnPtr> myMap;
    myMap["ItemLightning"] = &LayerGameAdvanced::ItemLightning;
    
    for(unordered_map<string, unordered_map<string, string> >::iterator iter = config.begin(); iter != config.end(); iter++)
    {
        if(iter->second["type"] != "2") continue;
        
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
    
    
    // 3.8 Item
    ItemStatus[ITEM_LIGHTNING] = false;
    
    workflows[POST_TOUCH].setMaxStage(6);
    
 
    return true;
}
void LayerGameAdvanced::onEnter()
{
    cocos2d::Layer::onEnter();
    
    auto listener = cocos2d::EventListenerTouchAllAtOnce::create();
    
    listener->onTouchesBegan = CC_CALLBACK_2(LayerGameBasic::onTouchesBegan, this);
    
    auto dispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
void LayerGameAdvanced::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event)
{
    std::cout<<"Touch--------"<<endl;
    cocos2d::Point tap;
    for (const auto& touch : touches) {
        tap = touch->getLocation();
        
        // Out of pool, warning
        
        
        // in the pool
        for(int i = 0; i < POOL_WIDTH; i ++)
        {
            for(int j = 0; j < POOL_HEIGHT; j ++)
            {
                if(pool[i][j]->getBoundingBox().containsPoint(tap))
                {
                    ItemStatus[ITEM_LIGHTNING] = false;
                    ItemLightningAction(i, j);
                }
            }
        }
    }
}
void LayerGameAdvanced::PostWorkFlow(int workflow)
{
    LayerGameBasic::PostWorkFlow(workflow);
    
    switch(workflow)
    {
        case POST_LIGHTENING:
            
            break;
            
        default:
            break;
    }
}

void LayerGameAdvanced::ItemLightning(Ref *sender,Control::EventType controlEvent)
{
    cout<<"ItemLightning-----"<<endl;
    ItemStatus[ITEM_LIGHTNING] = true;
}
void LayerGameAdvanced::ItemLightningAction(int x, int y)
{
    game->RemoveBlock(x, y);
    // pointer shift
    
    //schedule moveby 1
    
    ItemLightningEffect(x, y);
}
void LayerGameAdvanced::ItemLightningEffect(int x, int y)
{
    std::cout<<"EffectRowClear  ----"<<endl;
    
    quad[0]->resetSystem();
    quad[0]->setPosition(pool[x][y]->getPosition());
    
}