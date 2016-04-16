

#ifndef __LAYER_GAME_ADVANCED_H__
#define __LAYER_GAME_ADVANCED_H__

#include "cocos2d.h"
#include "GameLogicBasic.hpp"
#include "LayerGameBasic.h"
#include "GameSprite.h"
#include <vector>
using namespace std;
#include "cocos-ext.h"
using namespace cocos2d::extension;

#include "PostWorkFlow.h"
#include "ItemLightening.h"

class LayerGameAdvanced : public LayerGameBasic
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // implement the "static create()" method manually
    CREATE_FUNC(LayerGameAdvanced);

    
    virtual void onEnter() override;
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
    
    void PostWorkFlow(int workflow) override;
    enum postWorkFlowList{POST_TOUCH = 0, POST_LIGHTENING = 1};
    
    ItemLightening item_lightening;
    void ItemLightning(Ref *sender,Control::EventType controlEvent);
    void PostItemLightening(float dt);
    void ItemLightningAction(float dt);
};

#endif // __LAYER_GAME_ADVANCED_H__
