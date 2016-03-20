#include "LayerGameClassic.h"
#include "LayerMenu.h"
#include "TEHeader.h"
#include "ConfigFactory.h"

//#include "ui/CocosGUI.h"
//#include "extensions/cocos-ext.h"

USING_NS_CC;

Scene* LayerGameClassic::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LayerGameClassic::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LayerGameClassic::init()
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
                                           CC_CALLBACK_1(LayerGameClassic::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...
    unordered_map<string, unordered_map<string, string>> config;
    config = ConfigFactory::getInstance()->LoadLayer("LayerGameClassic");

    // 3.1 return back to menu
    auto size = Director::getInstance()->getWinSize();
    
    auto labelText = LabelTTF::create("Go back", "Arial",30);
    auto labelItem = MenuItemLabel::create(labelText,
                                               CC_CALLBACK_1(LayerGameClassic::labelMenuCallback, this));
    //创建一个菜单,并设置位置
    auto labelMenu = Menu::create(labelItem,NULL);
    labelMenu->setPosition(Vec2(100, 100));
    //将文本菜单加入到HelloWorld布景中,第二个参数表示在Z轴的层次，屏幕由里到外从小到大
    addChild(labelMenu,2);

    // 3.2 game logic object
    game = new GameLogicBasic();
    game->Initialize();

    // 3.3 background
    _screenSize = cocos2d::Director::getInstance()->getWinSize();
//    auto court = Sprite::create("court.png");
    
    auto court = Sprite::create(config[LGC_BG][LGC_BG_IMG]);
    court->setPosition(cocos2d::Point{
        _screenSize.width * stof(config["Background"]["px"]),
        _screenSize.height * stof(config["Background"]["py"])
    });
    addChild(court);

    // 3.4 pool
    for(int i = 0; i < POOL_WIDTH; i ++)
    {
        std::vector<GameSprite*> v;
        for(int j = 0; j < POOL_HEIGHT; j ++)
        {
            pool[i][j] = GameSprite::gameSpriteWithFile("StayedBlock.png");
            pool[i][j]->setPosition(cocos2d::Point{
                i * BLOCK_SIZE_F + POOL_LEFT_BORDER,
                j * BLOCK_SIZE_F + POOL_BOTTOM_BORDER
            });
            pool[i][j]->setPoolPositionX(i);
            pool[i][j]->setPoolPositionY(j);
            pool[i][j]->isSettled = false;
            pool[i][j]->setVisible(false);
            addChild(pool[i][j]);
        }
    }

    // 3.4 mover
    for(int i = 0; i < BLOCK_COMP; i ++)
    {
        mover[i] = GameSprite::gameSpriteWithFile("ActiveBlock.png");
        mover[i]->setVisible(true);
        addChild(mover[i]);
    }

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
    lblBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(LayerGameClassic::MoveLeft),
                                                Control::EventType::TOUCH_DOWN);
    addChild(lblBtn);


    lblBtn = ControlButton::create();
    lblBtn->setPosition(Vec2(stof(config[LGC_RB][LGC_RB_X]), stof(config[LGC_RB][LGC_RB_Y])));
    backgroundButton = Scale9Sprite::create(config[LGC_RB][LGC_RB_IMG_CLICKED]);    // no event
    backgroundHighlightedButton = Scale9Sprite::create(config[LGC_RB][LGC_RB_IMG_DEFAULT]); // clicked
    lblBtn->setBackgroundSpriteForState(backgroundButton, Control::State::NORMAL);
    lblBtn->setBackgroundSpriteForState(backgroundHighlightedButton, Control::State::HIGH_LIGHTED);
    lblBtn->setPreferredSize(Sprite::create(config[LGC_RB][LGC_RB_IMG_DEFAULT])->getContentSize());
    //绑定点击事件
    lblBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(LayerGameClassic::MoveRight),
                                                Control::EventType::TOUCH_DOWN);
    addChild(lblBtn);


    lblBtn = ControlButton::create();
    lblBtn->setPosition(Vec2(stof(config[LGC_RTB][LGC_RTB_X]), stof(config[LGC_RTB][LGC_RTB_Y])));
    backgroundButton = Scale9Sprite::create(config[LGC_RTB][LGC_RTB_IMG_CLICKED]);    // no event
    backgroundHighlightedButton = Scale9Sprite::create(config[LGC_RTB][LGC_RTB_IMG_DEFAULT]); // clicked
    lblBtn->setBackgroundSpriteForState(backgroundButton, Control::State::NORMAL);
    lblBtn->setBackgroundSpriteForState(backgroundHighlightedButton, Control::State::HIGH_LIGHTED);
    lblBtn->setPreferredSize(Sprite::create(config[LGC_RTB][LGC_RTB_IMG_DEFAULT])->getContentSize());
    //绑定点击事件
    lblBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(LayerGameClassic::Rotate),
                                                Control::EventType::TOUCH_DOWN);
    addChild(lblBtn);
    
    
    lblBtn = ControlButton::create();
    lblBtn->setPosition(Vec2(stof(config[LGC_DB][LGC_DB_X]), stof(config[LGC_DB][LGC_DB_Y])));
    backgroundButton = Scale9Sprite::create(config[LGC_DB][LGC_DB_IMG_CLICKED]);    // no event
    backgroundHighlightedButton = Scale9Sprite::create(config[LGC_DB][LGC_DB_IMG_DEFAULT]); // clicked
    lblBtn->setBackgroundSpriteForState(backgroundButton, Control::State::NORMAL);
    lblBtn->setBackgroundSpriteForState(backgroundHighlightedButton, Control::State::HIGH_LIGHTED);
    lblBtn->setPreferredSize(Sprite::create(config[LGC_DB][LGC_DB_IMG_DEFAULT])->getContentSize());
    //绑定点击事件
    lblBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(LayerGameClassic::MoveDown),
                                                Control::EventType::TOUCH_DOWN);
    addChild(lblBtn);
    
    // 3.6 schedule: UPDATE
    scheduleUpdate();  // first priority before other schedulers which makes change
    
    // 3.7 schedule: UPDATE
    schedule( schedule_selector(LayerGameClassic::DropDown), DROP_INTERVAL);
    
    return true;
}

void LayerGameClassic::update(float dt) {

    CCLOG("%f",dt);
    for(int i = 0; i < POOL_WIDTH; i ++)
    {
        std::vector<GameSprite*> v;
        for(int j = 0; j < POOL_HEIGHT; j ++)
        {
            if(game->pool[i][j]) pool[i][j]->setVisible(true);
            else pool[i][j]->setVisible(false);
        }
    }
    
    for(int i = 0; i < BLOCK_COMP; i ++ )
    {
        mover[i]->setPosition((pool[game->mover[i][0]][game->mover[i][1]])->getPosition());
    }
}

void LayerGameClassic::DropDown(float dt)
{
    if(game->DropDown())
    {
        game->MergeMover();
        game->Generate();
    }
}

void LayerGameClassic::MoveLeft(Ref *sender,Control::EventType controlEvent)
{
    game->MoveLeft();
}

void LayerGameClassic::MoveRight(Ref *sender,Control::EventType controlEvent)
{
    game->MoveRight();
}

void LayerGameClassic::Rotate(Ref *sender,Control::EventType controlEvent)
{
    game->Rotate();
}

void LayerGameClassic::MoveDown(Ref *sender,Control::EventType controlEvent)
{
    bool touched = false;
    while(!touched)
    {
        touched = game->DropDown();
    }
    for(auto block : game->mover)
    {
        effect_MoveDown.push_back(pool[block[0]][block[1]]->getPosition());
    }
    
    scheduleOnce(schedule_selector(LayerGameClassic::EffectMoveDown), 0);
    
    game->MergeMover();
    game->Generate();
}

void LayerGameClassic::labelMenuCallback(Ref* pSender)
{
    auto scene = LayerMenu::createScene();
    Director::getInstance()->replaceScene( TransitionFade::create(2, scene));
    //释放
    //scene->release();
}

void LayerGameClassic::EffectMoveDown(float dt)
{
    ///----------
    CCPoint mysize = CCDirector::sharedDirector()->getVisibleSize();
    
    
    CCParticleSystemQuad* quad = CCParticleSystemQuad::create();
    this->addChild(quad,1,1);
    
    
    //纹理图片
    quad->setTexture( CCTextureCache::sharedTextureCache()->addImage("HelloWorld.png") );
    
    
    //混合模式
    ccBlendFunc cbl = { GL_SRC_ALPHA , GL_ONE};
    quad->setBlendFunc(cbl);
    
    
    /********************/
    /*     粒子属性     */
    /********************/
    
    //粒子生命，单位：秒
    quad->setLife(0.2);
    quad->setLifeVar(0);
    
    //大小，-1表示和初始大小一致
    quad->setStartSize(100);
    quad->setStartSizeVar(5);
    quad->setEndSize(200);
    quad->setEndSizeVar(0);
    
    //颜色，ccc4f：取值0~1
    quad->setStartColor( ccc4f(192/255.0, 63/255.0, 63/255.0, 63/255.0) );
    quad->setStartColorVar(  ccc4f(192/255.0, 63/255.0, 63/255.0, 63/255.0));
    quad->setEndColor( ccc4f(0, 0, 0, 0) );
    quad->setEndColorVar( ccc4f(0, 0, 0, 0) );
    
    //旋转角度
    quad->setStartSpin(0);
    quad->setStartSpinVar(60);
    quad->setEndSpin(180);
    quad->setEndSpinVar(30);
    
    //发射角度
    quad->setAngle(180);
    quad->setAngleVar(30);
    
    
    /********************/
    /*  发射器子属性    */
    /********************/
    
    //最大粒子个数
    quad->setTotalParticles(500);
    
    //粒子发射器持续时间，-1为永久
    quad->setDuration(0.2);
    
    //发射速率
    quad->setEmissionRate( quad->getTotalParticles() /  quad->getDuration());
    
    //发射器位置
    quad->setPosition( effect_MoveDown[0]);
    quad->setPosVar( ccp(0,0) );
    
    effect_MoveDown.clear();
    
    //重力模式
    quad->setEmitterMode(kCCParticleModeGravity);
    
    //粒子位置模式
    quad->setPositionType(kCCPositionTypeFree);
    
    //粒子速度
    quad->setSpeed(0);
    quad->setSpeedVar(0);
    
    //重力加速度
    quad->setGravity( ccp(0, 5) );
    
    //径向加速度
    quad->setRadialAccel(0);
    quad->setRadialAccelVar(100);
    
    //切向加速度
    quad->setTangentialAccel(0);
    quad->setTangentialAccelVar(0);
    ///-----------
}

void LayerGameClassic::menuCloseCallback(Ref* pSender)
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
