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


struct Pool         // left bottom cornor (0, 0)
{
    int height, width, depth;       // depth = how many rows still below bottom of pool
    int status[POOL_WIDTH][POOL_HEIGHT];    // 0-empty
};

struct Mover
{
    int len;                    // the 7 regular shapes with length 4;
    int shapes[BLOCK_COMP][2];
    int status;                   // speciality. 0-normal
    
    int block_status[BLOCK_COMP];       // 0-default, 1-white 2-black 3-white bomb 4-black bomb
    pair<int, int> positions[BLOCK_COMP];
    
    bool isActive;
};
class GameLogicBasic
{
    enum poolBlockStatus{POOL_BLOCK_EMPTY, POOL_BLOCK_BLACK, POOL_BLOCK_WHITE};
    enum moverStatus{MOVER_STATUS_NORMAL};
    enum moverBlockStatus{MOVER_BLOCK_NORMAL, MOVER_BLOCK_WHITE, MOVER_BLOCK_BLACK};

private:
    
    Pool pool;
    Mover mover;
    Mover candidates[CANDIDATES];
    bool rowEmpty[POOL_HEIGHT];
    
    
    void MoveRowTo(int from, int to);
public:
    
    // basic
    bool Initialize();
    
    // game operations; basic behaviors taken, commonly used
    bool DropDown();
    bool MoveLeft();
    bool MoveRight();
    bool MoveDown();
    bool Rotate();
    
    // game operations; detail controll
    void Generate();
    void MergeMover();
    bool EliminateRow();
    int DigDown(int rows);
    bool GenerateRow(int rows);
    void ShrinkRow();
    
    // customer support, get info & set info
    vector<int> getEliminatedRow();
    pair<int, int> getMoverPosition(int n);    // each block in the mover
    bool isPoolBlockEmpty(int x, int y);
    int getMoverLength();

    void setPoolDepth(int depth);
    bool isRowCleared(int row);
    bool isMoverActive();
    bool isMoverBlack(int);
    bool isMoverWhite(int);
    bool isPoolBlockWhite(int, int);
    bool isPoolBlockBlack(int, int);
    
    void RemoveBlock(pair<int, int> pos);
};

#endif /* GameLogicBasic_hpp */
