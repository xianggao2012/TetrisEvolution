#include "TEHeader.h"

#ifndef __STORAGE_hpp_
#define __STORAGE_hpp_

#include <stdio.h>
#include "cocos2d.h"
#include <vector>
using namespace std;


class Storage
{

private:
    static Storage* p_Storage;

public:
    Storage();
    ~Storage();

    static Storage* getInstance();
    void Initialize();

    int getStorageStatus(string s);
    //    void setStorageStatus(string s, int n);
    void setStorageStatus(const char* c, int n);
};

#endif