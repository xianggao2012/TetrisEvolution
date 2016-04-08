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

    game->pool.depth = 3;
    
    return true;
}

// overwrite parent class. add logic for dig check
void LayerGameDig::MergeEliminateGenerate()
{
    game->MergeMover();
    bool eliminate = game->EliminateRow();
    if(eliminate)
    {
        effect_Eliminate.clear();
        effect_Eliminate = game->getEliminatedRow();
        scheduleOnce(schedule_selector(LayerGameBasic::EffectRowClear), 0);
        game->ShrinkRow();
    }
    game->Generate();
    
    if(eliminate) game->DigDown(effect_Eliminate.size());
}