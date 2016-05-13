#include "Personal.hpp"
#include "ConfigFactory.h"
#include<iostream>
using namespace std;


Personal* Personal::p_Personal = NULL;


Personal::Personal()
{

}

Personal::~Personal()
{
    
}

void Personal::Initialize()
{
    
    if(cocos2d::UserDefault::getInstance()->getStringForKey("Personal_Initialized") == "YES") return;
    else cocos2d::UserDefault::getInstance()->setStringForKey("Personal_Initialized", "YES");
    
    cocos2d::UserDefault::getInstance()->setIntegerForKey(LIGHTENING_WHITE_LEVEL, 5);
    cocos2d::UserDefault::getInstance()->setIntegerForKey(LIGHTENING_WHITE_PROGRESS, 2);
    cocos2d::UserDefault::getInstance()->setIntegerForKey(LIGHTENING_BLACK_LEVEL, 1);
    cocos2d::UserDefault::getInstance()->setIntegerForKey(LIGHTENING_BLACK_PROGRESS, 3);
    
    cocos2d::UserDefault::getInstance()->flush();
}

Personal* Personal::getInstance()
{
    
    if(p_Personal == NULL)
    {
        p_Personal = new Personal();
    }
    return p_Personal;
}

int Personal::getPersonalStatus(string s)
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

//void Personal::setPersonalStatus(string s, int n)
void Personal::setPersonalStatus(const char* c, int n)
{ 
    cocos2d::UserDefault::getInstance()->setIntegerForKey(c, n);
    cocos2d::UserDefault::getInstance()->flush();
}