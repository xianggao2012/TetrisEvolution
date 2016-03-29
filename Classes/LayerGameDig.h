

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

class LayerGameDig : public LayerGameBasic
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // implement the "static create()" method manually
    CREATE_FUNC(LayerGameDig);

};

#endif // __LAYER_GAME_DIG_H__
