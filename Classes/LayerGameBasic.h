

#ifndef __LAYER_GAME_BASIC_H__
#define __LAYER_GAME_BASIC_H__

#include "cocos2d.h"
#include "GameLogicBasic.hpp"
#include "GameSprite.h"
#include <vector>
using namespace std;
#include "cocos-ext.h"
using namespace cocos2d::extension;

class LayerGameBasic : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void labelMenuCallback(Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(LayerGameBasic);

    // Added code
    GameLogicBasic *game;
    
    GameSprite *pool[POOL_WIDTH][POOL_HEIGHT];
    GameSprite *left, *right, *rotate;
    GameSprite *mover[BLOCK_COMP];
    
    void update(float dt);
    void DropDown(float dt);
    void MoveLeft(Ref *sender,Control::EventType controlEvent);
    void MoveRight(Ref *sender,Control::EventType controlEvent);
    void MoveDown(Ref *sender,Control::EventType controlEvent);
    void Rotate(Ref *sender,Control::EventType controlEvent);
    void RowClear();
    void MergeEliminateGenerate();
    
    //Particle effects
    vector<cocos2d::Vec2> effect_MoveDown;
    vector<int> effect_Eliminate;
    void EffectMoveDown(float dt);
    void EffectRowClear(float dt);
    
    cocos2d::ParticleSystem *quad[POOL_WIDTH];
};

#endif // __LAYER_GAME_BASIC_H__
