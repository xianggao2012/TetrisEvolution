#include "TEHeader.h"

#ifndef __PERSONAL_hpp_
#define __PERSONAL_hpp_

#include <stdio.h>
#include "cocos2d.h"
#include <vector>
using namespace std;

#include "ItemLightening.h"
#include "ItemForkLightening.h"

class Personal
{

private:
    static Personal* p_Personal;

public:
    Personal();
    ~Personal();

    static Personal* getInstance();
    void Initialize();

    int getPersonalStatus(string s);
    //    void setPersonalStatus(string s, int n);
    void setPersonalStatus(const char* c, int n);
};

#endif