

#ifndef __LAYER_GAME_DIG_H__
#define __LAYER_GAME_DIG_H__

#include "cocos2d.h"
#include "GameLogicBasic.hpp"
#include "LayerGameBasic.h"
#include "GameSprite.h"
#include <vector>
using namespace std;
#include "cocos-ext.h"
using namespace cocos2d::extension;

#include "PostWorkFlow.h"


class LayerGameDig : public LayerGameBasic
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // implement the "static create()" method manually
    CREATE_FUNC(LayerGameDig);

    
    
    void Resume();
    
    
    
    enum postWorkFlowList{POST_TOUCH, POST_LIGHTENING};

    void PostWorkFlow(int workflow);
    
    enum ItemInUse{ITEM_LIGHTNING = 0};
    void ItemLightning(Ref *sender,Control::EventType controlEvent);
    void ItemLightningAction(int, int);
    void ItemLightningEffect(int, int);
    virtual void onEnter() override;
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
    
    class PostWorkFlow workflows[20];
};

#endif // __LAYER_GAME_DIG_H__
