#include "LayerGameClassic.h"
#include "LayerMenu.h"
#include "TEHeader.h"

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
    //cocos2d::Sprite *court = cocos2d::Sprite::create("court.png");
    auto court = Sprite::create("court.png");
    court->setPosition(cocos2d::Point{
        _screenSize.width * 0.5f,
        _screenSize.height * 0.5f
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
    lblBtn->setPosition(Vec2(100.0, 500.0));
    auto backgroundButton = Scale9Sprite::create("ActiveBlock.png");    // no event
    auto backgroundHighlightedButton = Scale9Sprite::create("StayedBlock.png"); // clicked
    lblBtn->setBackgroundSpriteForState(backgroundButton, Control::State::NORMAL);
    lblBtn->setBackgroundSpriteForState(backgroundHighlightedButton, Control::State::HIGH_LIGHTED);
    lblBtn->setPreferredSize(Sprite::create("ActiveBlock.png")->getContentSize());
    //绑定点击事件
    lblBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(LayerGameClassic::MoveLeft),
                                                Control::EventType::TOUCH_DOWN);
    addChild(lblBtn);


    lblBtn = ControlButton::create();
    lblBtn->setPosition(Vec2(1400.0, 500.0));
    backgroundButton = Scale9Sprite::create("ActiveBlock.png");    // no event
    backgroundHighlightedButton = Scale9Sprite::create("StayedBlock.png"); // clicked
    lblBtn->setBackgroundSpriteForState(backgroundButton, Control::State::NORMAL);
    lblBtn->setBackgroundSpriteForState(backgroundHighlightedButton, Control::State::HIGH_LIGHTED);
    lblBtn->setPreferredSize(Sprite::create("ActiveBlock.png")->getContentSize());
    //绑定点击事件
    lblBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(LayerGameClassic::MoveRight),
                                                Control::EventType::TOUCH_DOWN);
    addChild(lblBtn);


    lblBtn = ControlButton::create();
    lblBtn->setPosition(Vec2(1400.0, 700.0));
    backgroundButton = Scale9Sprite::create("ActiveBlock.png");    // no event
    backgroundHighlightedButton = Scale9Sprite::create("StayedBlock.png"); // clicked
    lblBtn->setBackgroundSpriteForState(backgroundButton, Control::State::NORMAL);
    lblBtn->setBackgroundSpriteForState(backgroundHighlightedButton, Control::State::HIGH_LIGHTED);
    lblBtn->setPreferredSize(Sprite::create("ActiveBlock.png")->getContentSize());
    //绑定点击事件
    lblBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(LayerGameClassic::Rotate),
                                                Control::EventType::TOUCH_DOWN);
    addChild(lblBtn);

    
    // 3.6 schedule: UPDATE
    schedule(schedule_selector(LayerGameClassic::Update));  // first priority before other schedulers which makes change
    
    // 3.7 schedule: UPDATE
    schedule( schedule_selector(LayerGameClassic::DropDown), DROP_INTERVAL);
    
    return true;
}

void LayerGameClassic::Update(float dt) {

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
    game->DropDown();
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

void LayerGameClassic::labelMenuCallback(Ref* pSender)
{
    auto scene = LayerMenu::createScene();
    Director::getInstance()->replaceScene( TransitionFade::create(2, scene));
    //释放
    //scene->release();
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