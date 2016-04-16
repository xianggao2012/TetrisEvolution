
#ifndef __ITEM_LIGHTENING__
#define __ITEM_LIGHTENING__

#include <stdio.h>
#include "cocos2d.h"
#include "ItemBase.h"

class ItemLightening : public ItemBase
{
public:
    ItemLightening();
    ~ItemLightening();
    
    // sprite & position
    
    // effect
    
    // position/point/row
    cocos2d::Vec2 poolPosition;
    
    void setPoolPosition(cocos2d::Vec2 pos);
    cocos2d::Vec2 getPoolPosition();
};

#endif
