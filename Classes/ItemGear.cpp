
#include "ItemGear.h"
#include "Storage.hpp"

ItemGear::ItemGear()
{
    
}
ItemGear::~ItemGear()
{
    
}

void ItemGear::setPoolPosition(cocos2d::Vec2 pos)
{
    poolPosition = pos;
}

cocos2d::Vec2 ItemGear::getPoolPosition()
{
    return poolPosition;
}

void ItemGear::IncreaseWhiteGear(int n)
{
    int cur = Storage::getInstance()->getStorageStatus(WHITE_GEAR);
    Storage::getInstance()->setStorageStatus(WHITE_GEAR, cur + 1);
}
void ItemGear::IncreaseBlackGear(int n)
{
    int cur = Storage::getInstance()->getStorageStatus(BLACK_GEAR);
    Storage::getInstance()->setStorageStatus(BLACK_GEAR, cur + 1);
}

void ItemGear::DecreaseWhiteGear(int n)
{
    int cur = Storage::getInstance()->getStorageStatus(WHITE_GEAR);
    Storage::getInstance()->setStorageStatus(WHITE_GEAR, cur - 1);
}
void ItemGear::DecreaseBlackGear(int n)
{
    int cur = Storage::getInstance()->getStorageStatus(BLACK_GEAR);
    Storage::getInstance()->setStorageStatus(BLACK_GEAR, cur - 1);
}
bool ItemGear::WhiteEmpty()
{
    if(Storage::getInstance()->getStorageStatus(WHITE_GEAR) == 0) return true;
    
    return false;
}
bool ItemGear::BlackEmpty()
{
    if(Storage::getInstance()->getStorageStatus(BLACK_GEAR) == 0) return true;
    
    return false;
}