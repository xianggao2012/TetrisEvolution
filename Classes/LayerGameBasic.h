

#ifndef __LAYER_GAME_BASIC_H__
#define __LAYER_GAME_BASIC_H__

#include "cocos2d.h"
#include "GameLogicBasic.hpp"
#include "GameSprite.h"
#include <vector>
using namespace std;
#include "cocos-ext.h"
using namespace cocos2d::extension;
USING_NS_CC;

#include "PostWorkFlow.h"

class LayerGameBasic : public cocos2d::Layer
{
public:
    /*
     ** basics
     */
    static cocos2d::Scene* createScene();
    
    // implement the "static create()" method manually
    CREATE_FUNC(LayerGameBasic);
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    void update(float dt);
    /*
     ** callbacks
     */
    void menuCloseCallback(cocos2d::Ref* pSender);
    void labelMenuCallback(Ref* pSender);
    
    /*
     ** actions
     */
    void MoveLeft(Ref *sender,Control::EventType controlEvent);
    void MoveRight(Ref *sender,Control::EventType controlEvent);
    void MoveDown(Ref *sender,Control::EventType controlEvent);
    void MoveToBottom(Ref *sender,Control::EventType controlEvent);
    void Rotate(Ref *sender,Control::EventType controlEvent);
    void Pause(Ref *sender,Control::EventType controlEvent);
    void Unpause(Ref *sender,Control::EventType controlEvent);
    
    void DropDown(float dt);
    /*
     ** support
     */
    Vec2 getMoverPosition(int);
    
    
    int count = 0;
protected:
    
    GameLogicBasic *game;
    GameSprite *pool[POOL_WIDTH][POOL_HEIGHT];
    GameSprite *left, *right, *rotate;
    GameSprite *mover[BLOCK_COMP];
    int b_isolation = 0;
    
    GameSprite *t_row[POOL_WIDTH];
    bool isIsolated();
    /*
     ** game operations; detail controll
     */
public:
    virtual void TouchProcessing(float dt);
    
    /*
     **Particle effects
     */
    vector<cocos2d::Vec2> effect_MoveDown;


    vector<int> effect_Eliminate;
    void EffectMoveDown(float dt);
    
public:
    void EffectRowClear(float dt);
    void EnableIsolation(float dt);
    void DisableIsolation(float dt);
    
    void PostTouchMerge(float dt);
    void PostTouchClear(float dt);
    void PostTouchFall(float dt);
    void PostTouchDig(float dt);
    void PostTouchGenerate(float dt);
    
    
    void setRowPointer(int to, int from);
    void setRowPointerSwitch(int from);
    void setRowPointerTemp(int from);
    
protected:
    cocos2d::ParticleSystem *quad[POOL_WIDTH];
    int postTouchStage = 0;
    
    
    virtual void PostWorkFlow(int workflow);
    
    
    enum postWorkFlowList{POST_TOUCH = 0};
    class PostWorkFlow workflows[20];
    
    
    CCTexture2D *ActiveBlack, *StayedBlack, *ActiveWhite, *StayedWhite;
};

#endif // __LAYER_GAME_BASIC_H__
