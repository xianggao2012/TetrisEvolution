
#ifndef __ITEM_LIGHTENING__
#define __ITEM_LIGHTENING__

#include <stdio.h>
#include "cocos2d.h"
#include "ItemBase.h"
#include<iostream>
using namespace std;

class ItemLightening : public ItemBase
{
public:
    ItemLightening();
    ~ItemLightening();
    
    // sprite & position
    
    // effect
    
    // position/point/row
    cocos2d::Vec2 poolPosition;
    pair<int, int> arrayPosition;
    void setPoolPosition(cocos2d::Vec2 pos);
    void setArrayPosition(pair<int, int>);
    pair<int, int> getArrayPosition();
    cocos2d::Vec2 getPoolPosition();
    
    
    cocos2d::ParticleSystem *quad;
    void startEffect();
};

#endif
