
#include "ItemBase.h"

ItemBase::ItemBase()
{
    count = 0;
    active = false;
}
ItemBase::~ItemBase()
{
    
}

void ItemBase::setCount(int n)
{
    count = n;
}

void ItemBase::IncreaseCount()
{
    count ++;
}

void ItemBase::DecreaseCount()
{
    count --;
}

bool ItemBase::isActive()
{
    return active;
}

void ItemBase::setActive(bool b)
{
    active = b;
}
int ItemBase::getCount()
{
    return count;
}
