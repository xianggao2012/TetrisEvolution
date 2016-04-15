
#include "PostWorkFlow.h"

PostWorkFlow::PostWorkFlow()
{
    active = false;
    cur_stage = 0;
    stage = 99;
}
PostWorkFlow::~PostWorkFlow()
{
    
}
bool PostWorkFlow::isActive()
{
    return active;
}
void PostWorkFlow::setActive(bool b)
{
    active = b;
}
int PostWorkFlow::getStage()
{
    return cur_stage;
}
void PostWorkFlow::gotoNextStage()
{
    cur_stage = ++ cur_stage % stage;
}
void PostWorkFlow::setMaxStage(int n)
{
    stage = n;
}
void PostWorkFlow::setStage(int n)
{
    cur_stage = n;
}