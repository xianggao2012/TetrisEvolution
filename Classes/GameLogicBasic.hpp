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

#include<vector>
using namespace std;

class GameLogicBasic
{
private:
    
    int candidates[CANDIDATES][BLOCK_COMP][2];
    bool rowEmpty[POOL_HEIGHT];
    void MoveRowTo(int from, int to);
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
    bool EliminateRow();
    void ShrinkRow();
    vector<int> getEliminatedRow();
    
};

#endif /* GameLogicBasic_hpp */
