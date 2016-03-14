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


class GameLogicBasic
{
private:
    
    int candidates[CANDIDATES][BLOCK_COMP][2];
    
    void Generate();
    void MergeMover();
    
public:

    bool pool[POOL_WIDTH][POOL_HEIGHT];
    int mover[BLOCK_COMP][2];
    
    bool Initialize();
    void DropDown();
    bool MoveLeft();
    bool MoveRight();
    bool Rotate();
    
};

#endif /* GameLogicBasic_hpp */
