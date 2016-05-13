
#include "ItemForkLightening.h"
#include "Storage.hpp"

ItemForkLightening::ItemForkLightening()
{
    
}
ItemForkLightening::~ItemForkLightening()
{
    
}

void ItemForkLightening::setPoolPosition(cocos2d::Vec2 pos)
{
    poolPosition = pos;
}

cocos2d::Vec2 ItemForkLightening::getPoolPosition()
{
    return poolPosition;
}

void ItemForkLightening::IncreaseWhitePrg(int n)
{
    int cur = Storage::getInstance()->getStorageStatus(FORKLIGHTENING_WHITE_PROGRESS);
    Storage::getInstance()->setStorageStatus(FORKLIGHTENING_WHITE_PROGRESS, cur + 1);
}
void ItemForkLightening::IncreaseBlackPrg(int n)
{
    int cur = Storage::getInstance()->getStorageStatus(FORKLIGHTENING_BLACK_PROGRESS);
    Storage::getInstance()->setStorageStatus(FORKLIGHTENING_BLACK_PROGRESS, cur + 1);
}