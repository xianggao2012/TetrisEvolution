

#ifndef __LAYER_GAME_CLASSIC_H__
#define __LAYER_GAME_CLASSIC_H__

#include "cocos2d.h"
#include "GameLogicBasic.hpp"
#include "GameSprite.h"
#include <vector>
using namespace std;
#include "cocos-ext.h"
using namespace cocos2d::extension;

class LayerGameClassic : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void labelMenuCallback(Ref* pSender);

    GameLogicBasic *game;
    
    // implement the "static create()" method manually
    CREATE_FUNC(LayerGameClassic);


    // Added code

    cocos2d::Size _screenSize;
    //std::vector<std::vector<GameSprite*> > pool;
    GameSprite *pool[POOL_WIDTH][POOL_HEIGHT];
    GameSprite *left, *right, *rotate;
    GameSprite *mover[BLOCK_COMP];
//    void AddMoverToPool();
//    void AddActiveMover();
//    bool CheckTouched();
//    bool CheckFull();
//    void Eliminate();
//    void GenerateMover();
//        bool isFullRow(int r);
//        void MoveRowTo(int from, int dest);
    void update(float dt);
    void DropDown(float dt);
    void MoveLeft(Ref *sender,Control::EventType controlEvent);
    void MoveRight(Ref *sender,Control::EventType controlEvent);
    void Rotate(Ref *sender,Control::EventType controlEvent);
    void MoveDown(Ref *sender,Control::EventType controlEvent);
    
    vector<cocos2d::Vec2> effect_MoveDown;
    void EffectMoveDown(float dt);
};

#endif // __LAYER_GAME_CLASSIC_H__
