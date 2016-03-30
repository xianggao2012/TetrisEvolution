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
    
    // 3. add your codes below...
    unordered_map<string, unordered_map<string, string>> config;
    config = ConfigFactory::getInstance()->LoadLayer("LayerGameClassic");
    
    // 3.3 background
    cocos2d::Size _screenSize = cocos2d::Director::getInstance()->getWinSize();
    //    auto court = Sprite::create("court.png");
    
    auto court = Sprite::create(config[LGC_BG][LGC_BG_IMG]);
    court->setPosition(cocos2d::Point{
        _screenSize.width * stof(config["Background"]["px"]),
        _screenSize.height * stof(config["Background"]["py"])
    });
    addChild(court, 1);
    
    
    // 3.5 buttons
    //ControlButton *lblBtn = ControlButton::create("zhouyunxuan", "fonts/PaintBoy.ttf", 30);
    ControlButton *lblBtn = ControlButton::create();
    lblBtn->setPosition(Vec2(stof(config[LGC_LB][LGC_LB_X]), stof(config[LGC_LB][LGC_LB_Y])));
    auto backgroundButton = Scale9Sprite::create(config[LGC_LB][LGC_LB_IMG_CLICKED]);    // no event
    auto backgroundHighlightedButton = Scale9Sprite::create(config[LGC_LB][LGC_LB_IMG_DEFAULT]); // clicked
    lblBtn->setBackgroundSpriteForState(backgroundButton, Control::State::NORMAL);
    lblBtn->setBackgroundSpriteForState(backgroundHighlightedButton, Control::State::HIGH_LIGHTED);
    lblBtn->setPreferredSize(Sprite::create(config[LGC_LB][LGC_LB_IMG_DEFAULT])->getContentSize());
    //绑定点击事件
    lblBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(LayerGameBasic::MoveLeft),
                                                Control::EventType::TOUCH_DOWN);
    addChild(lblBtn, 2);
    
    
    lblBtn = ControlButton::create();
    lblBtn->setPosition(Vec2(stof(config[LGC_RB][LGC_RB_X]), stof(config[LGC_RB][LGC_RB_Y])));
    backgroundButton = Scale9Sprite::create(config[LGC_RB][LGC_RB_IMG_CLICKED]);    // no event
    backgroundHighlightedButton = Scale9Sprite::create(config[LGC_RB][LGC_RB_IMG_DEFAULT]); // clicked
    lblBtn->setBackgroundSpriteForState(backgroundButton, Control::State::NORMAL);
    lblBtn->setBackgroundSpriteForState(backgroundHighlightedButton, Control::State::HIGH_LIGHTED);
    lblBtn->setPreferredSize(Sprite::create(config[LGC_RB][LGC_RB_IMG_DEFAULT])->getContentSize());
    //绑定点击事件
    lblBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(LayerGameBasic::MoveRight),
                                                Control::EventType::TOUCH_DOWN);
    addChild(lblBtn, 2);
    
    
    lblBtn = ControlButton::create();
    lblBtn->setPosition(Vec2(stof(config[LGC_RTB][LGC_RTB_X]), stof(config[LGC_RTB][LGC_RTB_Y])));
    backgroundButton = Scale9Sprite::create(config[LGC_RTB][LGC_RTB_IMG_CLICKED]);    // no event
    backgroundHighlightedButton = Scale9Sprite::create(config[LGC_RTB][LGC_RTB_IMG_DEFAULT]); // clicked
    lblBtn->setBackgroundSpriteForState(backgroundButton, Control::State::NORMAL);
    lblBtn->setBackgroundSpriteForState(backgroundHighlightedButton, Control::State::HIGH_LIGHTED);
    lblBtn->setPreferredSize(Sprite::create(config[LGC_RTB][LGC_RTB_IMG_DEFAULT])->getContentSize());
    //绑定点击事件
    lblBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(LayerGameBasic::Rotate),
                                                Control::EventType::TOUCH_DOWN);
    addChild(lblBtn, 2);
    
    
    lblBtn = ControlButton::create();
    lblBtn->setPosition(Vec2(stof(config[LGC_DB][LGC_DB_X]), stof(config[LGC_DB][LGC_DB_Y])));
    backgroundButton = Scale9Sprite::create(config[LGC_DB][LGC_DB_IMG_CLICKED]);    // no event
    backgroundHighlightedButton = Scale9Sprite::create(config[LGC_DB][LGC_DB_IMG_DEFAULT]); // clicked
    lblBtn->setBackgroundSpriteForState(backgroundButton, Control::State::NORMAL);
    lblBtn->setBackgroundSpriteForState(backgroundHighlightedButton, Control::State::HIGH_LIGHTED);
    lblBtn->setPreferredSize(Sprite::create(config[LGC_DB][LGC_DB_IMG_DEFAULT])->getContentSize());
    //绑定点击事件
    lblBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(LayerGameBasic::MoveDown),
                                                Control::EventType::TOUCH_DOWN);
    addChild(lblBtn, 2);
    
    game->pool.depth = 3;
    
    return true;
}

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
