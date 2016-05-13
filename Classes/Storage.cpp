#include "Storage.hpp"
#include "ConfigFactory.h"
#include<iostream>
using namespace std;


Storage* Storage::p_Storage = NULL;


Storage::Storage()
{

}

Storage::~Storage()
{
    
}

void Storage::Initialize()
{
    
    if(cocos2d::UserDefault::getInstance()->getStringForKey("Storage_Initialized") == "YES") return;
    else cocos2d::UserDefault::getInstance()->setStringForKey("Storage_Initialized", "YES");
    
    cocos2d::UserDefault::getInstance()->setIntegerForKey(LIGHTENING_WHITE_LEVEL, 5);
    cocos2d::UserDefault::getInstance()->setIntegerForKey(LIGHTENING_WHITE_PROGRESS, 2);
    cocos2d::UserDefault::getInstance()->setIntegerForKey(LIGHTENING_BLACK_LEVEL, 1);
    cocos2d::UserDefault::getInstance()->setIntegerForKey(LIGHTENING_BLACK_PROGRESS, 3);
    
    cocos2d::UserDefault::getInstance()->setIntegerForKey(FORKLIGHTENING_WHITE_LEVEL, 15);
    cocos2d::UserDefault::getInstance()->setIntegerForKey(FORKLIGHTENING_WHITE_PROGRESS, 12);
    cocos2d::UserDefault::getInstance()->setIntegerForKey(FORKLIGHTENING_BLACK_LEVEL, 11);
    cocos2d::UserDefault::getInstance()->setIntegerForKey(FORKLIGHTENING_BLACK_PROGRESS, 13);
    
    cocos2d::UserDefault::getInstance()->setIntegerForKey(WHITE_GEAR, 10);
    cocos2d::UserDefault::getInstance()->setIntegerForKey(BLACK_GEAR, 20);
    
    cocos2d::UserDefault::getInstance()->flush();
}

Storage* Storage::getInstance()
{
    
    if(p_Storage == NULL)
    {
        p_Storage = new Storage();
    }
    return p_Storage;
}

int Storage::getStorageStatus(string s)
{
    int len = (int)s.length();
    char c[len + 1];
    for(int i = 0; i < len; i ++)
    {
        c[i] = s[i];
    }
    c[len] = '\0';
    
    return cocos2d::UserDefault::getInstance()->getIntegerForKey(c);
}

//void Storage::setStorageStatus(string s, int n)
void Storage::setStorageStatus(const char* c, int n)
{ 
    cocos2d::UserDefault::getInstance()->setIntegerForKey(c, n);
    cocos2d::UserDefault::getInstance()->flush();
}