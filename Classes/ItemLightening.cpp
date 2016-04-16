
#include "ItemLightening.h"
#include<iostream>
using namespace std;

ItemLightening::ItemLightening()
{
    quad = cocos2d::ParticleSystemQuad::create("fire.plist");
    quad->setDuration(0.1);
    addChild(quad, 3);
}
ItemLightening::~ItemLightening()
{
    
}

void ItemLightening::setPoolPosition(cocos2d::Vec2 pos)
{
    poolPosition = pos;
}

void ItemLightening::setArrayPosition(pair<int ,int> pos)
{
    arrayPosition = pos;
}

pair<int, int> ItemLightening::getArrayPosition()
{
    return arrayPosition;
}

cocos2d::Vec2 ItemLightening::getPoolPosition()
{
    return poolPosition;
}

void ItemLightening::startEffect()
{
    std::cout<<"ItemLightening  startEffect----"<<endl;
    
    quad->resetSystem();
    quad->setPosition(getPoolPosition());
    
}