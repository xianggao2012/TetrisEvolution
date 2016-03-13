//
//  GameLogicBasic.hpp
//  TetrisEvolution
//
//  Created by Xiang Gao on 3/10/16.
//
//

#include "TEHeader.h"

#ifndef GameLogicBasic_hpp
#define GameLogicBasic_hpp

#include <stdio.h>
#include "cocos2d.h"


class GameLogicBasic: public cocos2d::Node
{
private:
    
    int candidates[CANDIDATES][BLOCK_COMP][2];
//    int dropInterval;
//    int genInterval;
//    int blockSet[BLOCK_TYPES][BLOCK_COMP][2];
    
//    void Update(float dt);
    bool CheckTouched();
    void Generate();
    void MergeMover();
//    
//    CC_SYNTHESIZE(int, _nextType, NextType);
//    CC_SYNTHESIZE(int, _Type, Type);
public:
    
    bool pool[POOL_WIDTH][POOL_HEIGHT];
    
    bool Initialize();
    int mover[BLOCK_COMP][2];
    
    void DropDown();
    bool MoveLeft();
    bool MoveRight();
    bool Rotate();
//    bool GoDown();
    
};







#endif /* GameLogicBasic_hpp */
