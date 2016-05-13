
#ifndef __ITEM_GEAR__
#define __ITEM_GEAR__

#include <stdio.h>
#include "cocos2d.h"
#include "ItemBase.h"

class ItemGear : public ItemBase
{
public:
    ItemGear();
    ~ItemGear();
    
    // sprite & position
    
    // effect
    
    // position/point/row
    cocos2d::Vec2 poolPosition;
    
    void setPoolPosition(cocos2d::Vec2 pos);
    cocos2d::Vec2 getPoolPosition();


    int black;
    int white;
    
    static void IncreaseWhiteGear(int n);
    static void IncreaseBlackGear(int n);
    static void DecreaseWhiteGear(int n);
    static void DecreaseBlackGear(int n);
    static bool WhiteEmpty();
    static bool BlackEmpty();
};

#endif
