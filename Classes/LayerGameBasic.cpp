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
    myMap["Pause"] = &LayerGameBasic::Pause;
    myMap["Unpause"] = &LayerGameBasic::Unpause;
    
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
        quad[i]->setDuration(0.1);
        addChild(quad[i], 2);
    }
    
    workflows[POST_TOUCH].setMaxStage(6);
    
    return true;
}
void LayerGameBasic::MoveLeft(Ref *sender,Control::EventType controlEvent)
{
    game->MoveLeft();
    
}
void LayerGameBasic::MoveRight(Ref *sender,Control::EventType controlEvent)
{
    game->MoveRight();
}
void LayerGameBasic::Rotate(Ref *sender,Control::EventType controlEvent)
{
    game->Rotate();
}
void LayerGameBasic::Pause(Ref *sender,Control::EventType controlEvent)
{
    Director::getInstance()->pause();
}
void LayerGameBasic::Unpause(Ref *sender,Control::EventType controlEvent)
{
    Director::getInstance()->resume();
}
void LayerGameBasic::update(float dt)
{
//    std::cout<<"update  ----:"<<count ++<<" isolated:"<<isIsolated()<<endl;

    for(int i = 0; i < POOL_WIDTH; i ++)
    {
        for(int j = 0; j < POOL_HEIGHT; j ++)
        {
            if(!game->isPoolBlockEmpty(i, j)) pool[i][j]->setVisible(true);
            else pool[i][j]->setVisible(false);
        }
    }
    
    if(game->isMoverActive())
    {
        for(int i = 0; i < BLOCK_COMP; i ++ )
        {
            mover[i]->setPosition(getMoverPosition(i));
        }
    }
    else
        for(auto block : mover) block->setPosition(Vec2(-100, -100));
    
}
void LayerGameBasic::DropDown(float dt)
{
    if(!game->isMoverActive()) return;
    
    if(game->DropDown())
    {
        PostWorkFlow(POST_TOUCH);
    }
}
void LayerGameBasic::MoveDown(Ref *sender,Control::EventType controlEvent)
{
    if(!game->isMoverActive()) return;
    
    if(game->DropDown())    // multi actions may happen in 1 frame. Make sure no redundant post-processing
    {
        PostWorkFlow(POST_TOUCH);
    }
}
void LayerGameBasic::MoveToBottom(Ref *sender,Control::EventType controlEvent)
{
    if(!game->isMoverActive()) return;
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
    
    PostWorkFlow(POST_TOUCH);
}
void LayerGameBasic::labelMenuCallback(Ref* pSender)
{
    auto scene = LayerMenu::createScene();
    //Director::getInstance()->replaceScene( TransitionFade::create(2, scene));
    Director::getInstance()->replaceScene(scene);
    //释放
    //scene->release();
}    
void LayerGameBasic::EffectMoveDown(float dt)
{
    for(auto effect : effect_MoveDown)
    {
        ParticleFire* quad = ParticleFire::create();
        quad->setPosition(effect);
        quad->setDuration(0.1);
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
void LayerGameBasic::PostWorkFlow(int workflow)
{
    switch(workflow)
    {
        case POST_TOUCH:
            if(workflows[POST_TOUCH].isActive()) return;
            else
            {
                workflows[POST_TOUCH].setActive(true);
                scheduleOnce(schedule_selector(LayerGameBasic::TouchProcessing), 0);
            }
            break;
            
        default:
            break;
    }
}
void LayerGameBasic::TouchProcessing(float dt)
{
    switch(workflows[POST_TOUCH].getStage())
    {
        case 0:
            scheduleOnce(schedule_selector(LayerGameBasic::PostTouchMerge), 0);
            workflows[POST_TOUCH].gotoNextStage();
            
            break;
        case 1:
            scheduleOnce(schedule_selector(LayerGameBasic::PostTouchClear), 0);
            workflows[POST_TOUCH].gotoNextStage();
            
            break;
        case 2:
            scheduleOnce(schedule_selector(LayerGameBasic::PostTouchFall), 0);
            workflows[POST_TOUCH].gotoNextStage();
            
            break;
        case 3:
            scheduleOnce(schedule_selector(LayerGameBasic::PostTouchDig), 0);
            workflows[POST_TOUCH].gotoNextStage();
            break;
        case 4:
            scheduleOnce(schedule_selector(LayerGameBasic::PostTouchGenerate), 0);
            workflows[POST_TOUCH].gotoNextStage();
            
            break;
        case 5:
            workflows[POST_TOUCH].gotoNextStage();
            workflows[POST_TOUCH].setActive(false);
            
            break;
            
        default: break;
    }
}
Vec2 LayerGameBasic::getMoverPosition(int n)
{
    pair<int, int> pos = game->getMoverPosition(n);
//    return pool[pos.first][pos.second]->getPosition();
    return Vec2(POOL_LEFT_BORDER + BLOCK_SIZE_F * pos.first, POOL_BOTTOM_BORDER + BLOCK_SIZE_F * pos.second);
}
void LayerGameBasic::EnableIsolation(float dt)
{
    b_isolation ++;
}
void LayerGameBasic::DisableIsolation(float dt)
{
    b_isolation --;
}
void LayerGameBasic::PostTouchMerge(float dt)
{
    game->MergeMover();
    scheduleOnce(schedule_selector(LayerGameBasic::TouchProcessing), 0);
}
void LayerGameBasic::PostTouchClear(float dt)
{
    if(game->EliminateRow())
    {
        effect_Eliminate.clear();
        effect_Eliminate = game->getEliminatedRow();
        scheduleOnce(schedule_selector(LayerGameBasic::EffectRowClear), 0);
    }
    else  workflows[POST_TOUCH].setStage(4);
    
    scheduleOnce(schedule_selector(LayerGameBasic::TouchProcessing), 0);
}
void LayerGameBasic::PostTouchFall(float dt)
{
    float speed = 0.5;
    // calculate which row the pool pointer should point to after some rows gone and shrink shift
    // newRow[0] = 3 means  now the pointer pointed row 0 should points row 3 before cleared rows gone.
    int newRow[POOL_HEIGHT];    int n_new = 0;
    int delta[POOL_HEIGHT];     int n_delta = 0;
    vector<int> rows = game->getEliminatedRow();
    
    for(int i = 0; i < POOL_HEIGHT; i ++)
    {
        if(game->isRowCleared(i))
        {
            n_delta ++ ;
        }
        else
        {
            newRow[n_new] = i;
            delta[n_new] = n_delta;
            n_new ++;
        }
    }
    
    int threshold = n_new;
    int count = 0;
    while(n_new < POOL_HEIGHT)
    {
        newRow[n_new] = rows[count ++];
        delta[n_new] = n_delta;
        n_new ++;
    }
    // switch pointers
    
    int reverse[POOL_HEIGHT];
    for(int i = 0; i < POOL_HEIGHT; i ++) reverse[newRow[i]] = i;
    bool done[POOL_HEIGHT] = {false};           // if this row got modified pointer points to
//    GameSprite *t_row[POOL_WIDTH];              // temp row pointers
    int n_t_row;                                // and which old row it stores
    
    for(int i = 0; i < POOL_HEIGHT; i ++)
    {
        if(done[i]) continue;
        
        n_t_row = reverse[i];
        setRowPointerTemp(reverse[i]);           // t_row = reverse[i];
        setRowPointer(reverse[i], i);       //newRow[reverse[i]] = i;
        done[i] = true; // got a pointer points to this
        
        while(!done[n_t_row])
        {
            setRowPointerSwitch(reverse[n_t_row]);       //newRow[reverse[t_row]] = t_row;
//            setRowPointer(reverse[n_t_row]);               //t_row = reverse[t_row];
            done[n_t_row] = true;
            n_t_row = reverse[n_t_row];
        }
    }
    
    // fall
    for(int j = 0; j < POOL_HEIGHT; j ++)
    {
        if(j < threshold)
        {
            for(int i = 0; i < POOL_WIDTH; i ++)
            {
                ActionInterval *moveto = MoveBy::create(speed, Vec2(0, - BLOCK_SIZE * delta[j]));
                pool[i][j]->runAction(moveto);
            }
        }
        else
        {
            for(int i = 0; i < POOL_WIDTH; i ++)
            {
                ActionInterval *moveto = MoveTo::create(0, Vec2(i * BLOCK_SIZE_F + POOL_LEFT_BORDER, j * BLOCK_SIZE_F + POOL_BOTTOM_BORDER));
                pool[i][j]->runAction(moveto);
            }
        }
    }
    
    game->ShrinkRow();
    
    scheduleOnce(schedule_selector(LayerGameBasic::TouchProcessing), speed);
}
void LayerGameBasic::PostTouchDig(float dt)
{
    float speed = 1.0;
    
    int delta = effect_Eliminate.size();
    
    delta = game->DigDown(delta);
    
    if(delta > 0)
    {
        bool done[POOL_HEIGHT] = {false};
        int n_t_row;
        
        for(int j = 0; j < POOL_HEIGHT; j ++)
        {
            if(done[j]) continue;
            
            n_t_row = (delta + j) % POOL_HEIGHT;
            setRowPointerTemp((delta + j) % POOL_HEIGHT);
            setRowPointer((delta + j) % POOL_HEIGHT, j);
            done[j] = true;
            
            while(!done[n_t_row])
            {
                setRowPointerSwitch((delta + n_t_row) % POOL_HEIGHT);
                done[n_t_row] = true;
                n_t_row = (delta + n_t_row) % POOL_HEIGHT;
            }
        }
        
        // move top to bottom
        for(int j = 0; j < delta; j ++)
        {
            for(int i = 0; i < POOL_WIDTH; i ++)
            {
                pool[i][j]->setPosition(cocos2d::Point{
                    pool[i][j]->getPositionX(),
                    pool[i][j]->getPositionY() - BLOCK_SIZE_F * (POOL_HEIGHT)
                });
            }
            
        }
        
        // riseup
        for(int i = 0; i < POOL_WIDTH; i ++)
        {
            for(int j = 0; j < POOL_HEIGHT; j ++)
            {
                ActionInterval *moveto = MoveBy::create(speed, Vec2(0, BLOCK_SIZE_F * delta));
                pool[i][j]->runAction(moveto);
            }
        }
        
        scheduleOnce(schedule_selector(LayerGameBasic::TouchProcessing), speed);
    }
    else
        scheduleOnce(schedule_selector(LayerGameBasic::TouchProcessing), 0);
}

void LayerGameBasic::setRowPointerTemp(int from)
{
    for(int i = 0; i < POOL_WIDTH; i ++) t_row[i] = pool[i][from];
}
void LayerGameBasic::setRowPointer(int to, int from)
{
    for(int i = 0; i < POOL_WIDTH; i ++) pool[i][to] = pool[i][from];
}
void LayerGameBasic::setRowPointerSwitch(int from)
{
    GameSprite *t;
    for(int i = 0; i < POOL_WIDTH; i ++)
    {
        t = t_row[i];
        t_row[i] = pool[i][from];
        pool[i][from] = t;
    }
}
void LayerGameBasic::PostTouchGenerate(float dt)
{
    game->Generate();
    scheduleOnce(schedule_selector(LayerGameBasic::TouchProcessing), 0);
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
