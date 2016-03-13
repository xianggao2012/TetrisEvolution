

#ifndef  _CONFIG_FACTORY_H_
#define  _CONFIG_FACTORY_H_

#include "TEHeader.h"
#include <iostream>
using namespace std;

/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by Director.
*/
class  ConfigFactory
{
private:
    static ConfigFactory* p_ConfigFactory;

public:
    ~ConfigFactory();

    static ConfigFactory* getInstance();

    // loading methods
    bool LoadScene();
    bool LoadStage();

    string a[10];

    // get methods

private:
    ConfigFactory();

    // map object to match the scene name and scene config object
    
};

#endif // _CONFIG_FACTORY_H_

