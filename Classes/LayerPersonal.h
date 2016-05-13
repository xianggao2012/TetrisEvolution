

#ifndef __LAYER_PERSONAL_H__
#define __LAYER_PERSONAL_H__

#include "cocos2d.h"
#include "GameSprite.h"
#include "cocos-ext.h"
using namespace cocos2d::extension;
USING_NS_CC;


class LayerPersonal : public cocos2d::Layer
{
public:
    /*
     ** basics
     */
    static cocos2d::Scene* createScene();
    
    // implement the "static create()" method manually
    CREATE_FUNC(LayerPersonal);
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    void update(float dt);
    /*
     ** callbacks
     */
    void menuCloseCallback(cocos2d::Ref* pSender);
    void labelMenuCallback(Ref* pSender);
    
    void IncreaseLighteningWhitePrg(Ref *sender,Control::EventType controlEvent);
    void IncreaseLighteningBlackPrg(Ref *sender,Control::EventType controlEvent);
    void IncreaseForkLighteningWhitePrg(Ref *sender,Control::EventType controlEvent);
    void IncreaseForkLighteningBlackPrg(Ref *sender,Control::EventType controlEvent);
    void IncreaseWithWhite(Ref *sender,Control::EventType controlEvent);
    void IncreaseWithBlack(Ref *sender,Control::EventType controlEvent);
    
    CCLabelTTF* pLabel[7];
    string tempkey[7];
};

#endif // __LAYER_GAME_BASIC_H__
