#ifndef  _CONFIG_FACTORY_H_
#define  _CONFIG_FACTORY_H_

#include "cocos-ext.h"
#include "tinyxml2/tinyxml2.h"
using namespace tinyxml2;

#include "iostream"
using namespace std;
/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by Director.
*/
class  ConfigFactory
{
public:
    ConfigFactory();
    virtual ~ConfigFactory();
};

#endif // _CONFIG_FACTORY_H_

