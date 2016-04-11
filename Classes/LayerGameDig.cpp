#include "LayerGameDig.h"
#include "LayerMenu.h"
#include "TEHeader.h"
#include "ConfigFactory.h"

USING_NS_CC;

Scene* LayerGameDig::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LayerGameDig::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LayerGameDig::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerGameBasic::init() )
    {
        return false;
    }

    game->setPoolDepth(3);
    
//    gs = GameSprite::gameSpriteWithFile("ActiveBlock.png");
//    gs->setPosition(Vec2(400, 1800));
//    gs->setVisible(true);
//    addChild(gs, 1);
    
    
    return true;
}

// overwrite parent class. add logic for dig check
//void LayerGameDig::TouchProcessing(float dt)
//{std::cout<<"TouchProcessing----"<<endl;
//    
//
//    std::cout<<"TouchProcessing beging ----"<<postTouchStage<<endl;
//    switch(postTouchStage)
//    {
//        case 0:
//            scheduleOnce(schedule_selector(LayerGameBasic::PostTouchMerge), 0);
//            postTouchStage ++;
//            
//            break;
//        case 1:
//            scheduleOnce(schedule_selector(LayerGameBasic::PostTouchClear), 0);
//            postTouchStage ++;
//            
//            break;
//        case 2:
//            scheduleOnce(schedule_selector(LayerGameBasic::PostTouchFall), 0);
//            postTouchStage ++;
//            
//            break;
//        case 3:
//            scheduleOnce(schedule_selector(LayerGameBasic::PostTouchDig), 0);
//            postTouchStage ++;
//            
//            break;
//        case 4:
//            scheduleOnce(schedule_selector(LayerGameBasic::PostTouchGenerate), 0);
//            postTouchStage ++;
//            
//            break;
//        case 5:
//            scheduleOnce(schedule_selector(LayerGameBasic::DisableIsolation), 0);
//            postTouchStage = 0;
//            
//            break;
//        default: break;
//    }
//   
//
////
//    
//
//    // 创建移动动作
//    ActionInterval *moveto = MoveTo::create(5, Vec2(600, 1800));
//    
//    CallFunc * func = CallFunc::create(CC_CALLBACK_0(LayerGameDig::Resume,this));
////    Sequence * sequenece = Sequence::create(moveto, func, NULL);
//    Sequence * sequenece = Sequence::create(func, NULL);
//    
//    scheduleOnce(schedule_selector(LayerGameBasic::EnableIsolation), 0);
//    gs->runAction(sequenece);
//}
void LayerGameDig::Resume()
{
//    gs->setPosition(Vec2(400, 1800));
    gs->setPosition(Vec2(600, 1800));
//    scheduleOnce(schedule_selector(LayerGameBasic::DisableIsolation), 0);
}
