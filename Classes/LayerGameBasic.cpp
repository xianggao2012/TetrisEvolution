#include "LayerGameBasic.h"
#include "LayerMenu.h"
#include "TEHeader.h"
#include "ConfigFactory.h"

//#include "ui/CocosGUI.h"
//#include "extensions/cocos-ext.h"

USING_NS_CC;

Scene* LayerGameBasic::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LayerGameBasic::create();

    // add layer as a child to scene
    scene->addChild(layer, 2);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LayerGameBasic::init()
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
                                           CC_CALLBACK_1(LayerGameBasic::menuCloseCallback, this));
    
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
                                               CC_CALLBACK_1(LayerGameBasic::labelMenuCallback, this));
    //创建一个菜单,并设置位置
    auto labelMenu = Menu::create(labelItem,NULL);
    labelMenu->setPosition(Vec2(100, 100));
    //将文本菜单加入到HelloWorld布景中,第二个参数表示在Z轴的层次，屏幕由里到外从小到大
    addChild(labelMenu,2);

    // 3.2 game logic object
    game = new GameLogicBasic();
    game->Initialize();

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
            addChild(pool[i][j], 2);
        }
    }
    
     // 3. add your codes below...
    unordered_map<string, unordered_map<string, string>> config;
    config = ConfigFactory::getInstance()->LoadLayer("LayerGameBasic");
    
    // 3.3 background
    cocos2d::Size _screenSize = cocos2d::Director::getInstance()->getWinSize();
    //    auto court = Sprite::create("court.png");
    
    auto court = Sprite::create(config[LGB_BG][LGB_BG_IMG]);
    court->setPosition(cocos2d::Point{
        _screenSize.width * stof(config["Background"]["px"]),
        _screenSize.height * stof(config["Background"]["py"])
    });
    addChild(court, 1);
    
    // 3.4 mover
    for(int i = 0; i < BLOCK_COMP; i ++)
    {
        mover[i] = GameSprite::gameSpriteWithFile("ActiveBlock.png");
        mover[i]->setVisible(true);
        addChild(mover[i], 2);
    }
    
    // 3.5 buttons
    typedef void (LayerGameBasic::*FnPtr)(Ref *sender,Control::EventType controlEvent);
    
    std::map<std::string, FnPtr> myMap;
    myMap["LeftButton"] = &LayerGameBasic::MoveLeft;
    myMap["RightButton"] = &LayerGameBasic::MoveRight;
    myMap["DownButton"] = &LayerGameBasic::MoveDown;
    myMap["RotateButton"] = &LayerGameBasic::Rotate;
    myMap["BottomButton"] = &LayerGameBasic::MoveToBottom;
    
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
    
    // 3.6 schedule: UPDATE
    scheduleUpdate();  // first priority before other schedulers which makes change
    
    // 3.7 schedule: UPDATE
    schedule( schedule_selector(LayerGameBasic::DropDown), DROP_INTERVAL);
    
    //
    for(int i = 0; i < POOL_WIDTH; i ++)
    {
        quad[i] = ParticleSystemQuad::create("fire.plist");
        quad[i]->setDuration(0.5);
        addChild(quad[i], 2);
    }
    
    return true;
}

void LayerGameBasic::update(float dt) {

    for(int i = 0; i < POOL_WIDTH; i ++)
    {
        for(int j = 0; j < POOL_HEIGHT; j ++)
        {
            if(game->getPoolStatus(i, j) != POOL_BLO_EMPTY) pool[i][j]->setVisible(true);
            else pool[i][j]->setVisible(false);
        }
    }
    
    for(int i = 0; i < BLOCK_COMP; i ++ )
    {
        mover[i]->setPosition(getMoverPosition(i));
    }
}

void LayerGameBasic::DropDown(float dt)
{
    if(game->DropDown())
    {
        MergeEliminateGenerate();
    }
}

void LayerGameBasic::MoveLeft(Ref *sender,Control::EventType controlEvent)
{
    game->MoveLeft();
}

void LayerGameBasic::MoveRight(Ref *sender,Control::EventType controlEvent)
{
    game->MoveRight();
}

void LayerGameBasic::MoveDown(Ref *sender,Control::EventType controlEvent)
{
    if(game->DropDown())
    {
        MergeEliminateGenerate();
    }
}

void LayerGameBasic::Rotate(Ref *sender,Control::EventType controlEvent)
{
    game->Rotate();
}

void LayerGameBasic::MoveToBottom(Ref *sender,Control::EventType controlEvent)
{
    bool touched = false;
    while(!touched)
    {
        touched = game->DropDown();
    }
    
    for(int i = 0; i < game->getMoverLength(); i ++)
    {
        
        effect_MoveDown.push_back(getMoverPosition(i));
    }

    // effect
    scheduleOnce(schedule_selector(LayerGameBasic::EffectMoveDown), 0);
    
    MergeEliminateGenerate();
}

void LayerGameBasic::labelMenuCallback(Ref* pSender)
{
    auto scene = LayerMenu::createScene();
    Director::getInstance()->replaceScene( TransitionFade::create(2, scene));
    //释放
    //scene->release();
}

void LayerGameBasic::EffectMoveDown(float dt)
{
    for(auto effect : effect_MoveDown)
    {
        ParticleFire* quad = ParticleFire::create();
        quad->setPosition(effect);
        quad->setDuration(0.5);
        quad->setAutoRemoveOnFinish(true);
        this->addChild(quad,2,1);
    }
    effect_MoveDown.clear();
}

void LayerGameBasic::EffectRowClear(float dt)
{
    for(auto row : effect_Eliminate)
    {
        for(int i = 0; i < POOL_WIDTH; i ++)
        {
            quad[i]->resetSystem();
            quad[i]->setPosition(pool[i][row]->getPosition());
        }
    }
}

void LayerGameBasic::RowClear()
{
    game->EliminateRow();
}

void LayerGameBasic::MergeEliminateGenerate()
{
    game->MergeMover();
    if(game->EliminateRow())
    {
        effect_Eliminate.clear();
        effect_Eliminate = game->getEliminatedRow();
        scheduleOnce(schedule_selector(LayerGameBasic::EffectRowClear), 0);
        game->ShrinkRow();
    }
    game->Generate();
}


Vec2 LayerGameBasic::getMoverPosition(int n)
{
    pair<int, int> pos = game->getMoverPosition(n);
    return pool[pos.first][pos.second]->getPosition();
}


void LayerGameBasic::menuCloseCallback(Ref* pSender)
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
