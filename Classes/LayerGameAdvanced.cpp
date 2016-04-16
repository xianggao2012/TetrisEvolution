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
    
    
    // item
    item_lightening.setCount(3);
    
    
    
    // post workflow
    workflows[POST_TOUCH].setMaxStage(6);
    workflows[POST_LIGHTENING].setMaxStage(3);
    
 
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
    
    // return if none item is active
    
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
                    // depending on which item is active
                    if(item_lightening.isActive() && !workflows[POST_LIGHTENING].isActive())
                    {
                        item_lightening.setPoolPosition(Vec2(i, j));
                        workflows[POST_LIGHTENING].setActive(true);
                        PostWorkFlow(POST_LIGHTENING);
                    }
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
            PostItemLightening(0);
            
            break;
            
        default:
            break;
    }
}

void LayerGameAdvanced::PostItemLightening(float dt)
{
    switch(workflows[POST_LIGHTENING].getStage())
    {
        case 0: // change momdel; make effect
            game->RemoveBlock(item_lightening.getPoolPosition().x, item_lightening.getPoolPosition().y);
            EffectItemLightning();

            workflows[POST_LIGHTENING].gotoNextStage();
            
            scheduleOnce(schedule_selector(LayerGameAdvanced::PostItemLightening), 0);
            
            break;
        case 1: // action of fall down
            scheduleOnce(schedule_selector(LayerGameAdvanced::ItemLightningAction), 0);
            workflows[POST_LIGHTENING].gotoNextStage();
            
            break;
        case 2:
            workflows[POST_LIGHTENING].gotoNextStage();
            workflows[POST_LIGHTENING].setActive(false);
            item_lightening.setActive(false);
            item_lightening.DecreaseCount();
            
            break;
            
        default: break;
    }
}

void LayerGameAdvanced::ItemLightning(Ref *sender,Control::EventType controlEvent)
{
    cout<<"ItemLightning-----"<<endl;
    if(item_lightening.getCount() <= 0 || item_lightening.isActive()) return;
    
    item_lightening.setActive(true);
}
void LayerGameAdvanced::ItemLightningAction(float dt)
{
    cout<<"ItemLightningAction-----"<<endl;
    float speed = 0.5;
    int x = item_lightening.getPoolPosition().x;
    int y = item_lightening.getPoolPosition().y;
    GameSprite *temp = pool[x][y];
    for(int j = y; j < POOL_HEIGHT - 1; j ++)
    {
        pool[x][j] = pool[x][j + 1];
    }
    pool[x][POOL_HEIGHT - 1] = temp;
    
    
    for(int j = y; j < POOL_HEIGHT - 1; j ++)
    {
        ActionInterval *moveto = MoveBy::create(speed, Vec2(0, - BLOCK_SIZE));
        pool[x][j]->runAction(moveto);
    }
    ActionInterval *moveto = MoveTo::create(0, Vec2(0, (POOL_HEIGHT - 1) * BLOCK_SIZE_F + POOL_BOTTOM_BORDER));
    pool[x][POOL_HEIGHT - 1]->runAction(moveto);
    
    scheduleOnce(schedule_selector(LayerGameAdvanced::PostItemLightening), speed);
}
void LayerGameAdvanced::EffectItemLightning()
{
    std::cout<<"EffectItemLightning  ----"<<endl;
    
    quad[0]->resetSystem();
    quad[0]->setPosition(pool[(int)item_lightening.getPoolPosition().x][(int)item_lightening.getPoolPosition().y]->getPosition());
    
}