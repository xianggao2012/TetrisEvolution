#ifndef __Layer_MENU_H__
#define __Layer_MENU_H__

#include "cocos2d.h"
#include "LayerGameClassic.h"

class LayerMenu : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void imageMenuCallback(cocos2d::CCObject* pSender);
    
    void labelMenuCallback(cocos2d::CCObject* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(LayerMenu);
};

#endif // __Layer_MENU_H__
