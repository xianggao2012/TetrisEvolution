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
    
public:
    void Generate();
    void MergeMover();
    

    bool pool[POOL_WIDTH][POOL_HEIGHT];
    int mover[BLOCK_COMP][2];
    
    bool Initialize();
    bool DropDown();
    bool MoveLeft();
    bool MoveRight();
    bool MoveDown();
    bool Rotate();
    
};

#endif /* GameLogicBasic_hpp */
