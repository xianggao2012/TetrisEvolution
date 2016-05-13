
#ifndef __ITEM_BASE__
#define __ITEM_BASE__

#include <stdio.h>
#include "cocos2d.h"

class ItemBase : public cocos2d::Sprite
{
public:
    ItemBase();
    ~ItemBase();
    
    bool active;
    
    void setCount(int n);
    void IncreaseCount();
    void DecreaseCount();
    int getCount();
    bool isActive();
    void setActive(bool b);
    
    // status
    int lvlB, lvlW, count;
    int prgB, prgW, prgCount;
    static const int maxLvl = 10;
};

#endif
