
#ifndef __POSTWORKFLOW__
#define __POSTWORKFLOW__

#include <stdio.h>
#include "cocos2d.h"

class PostWorkFlow{
public:
    PostWorkFlow();
    ~PostWorkFlow();
    
    int cur_stage;
    int stage;
    bool active;
    
    void setMaxStage(int n);
    bool isActive();
    void setActive(bool);
    int getStage();
    void gotoNextStage();
    void setStage(int n);
};

#endif