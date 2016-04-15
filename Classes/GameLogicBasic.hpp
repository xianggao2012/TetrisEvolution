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
    int type;                   // speciality. 0-normal
    
    int status[BLOCK_COMP];       // 0-default, 1-white 2-black 3-white bomb 4-black bomb
    pair<int, int> positions[BLOCK_COMP];
    
    bool isActive;
};
class GameLogicBasic
{
private:
    
    enum poolBlockStatus{POOL_BLO_EMPTY, POOL_BLO_SETTLED};
    enum moverStatus{MOV_STA_NORMAL};
    enum moverBlockStatus{MOV_BLO_NORMAL, MOV_BLO_WHITE, MOV_BLO_BLACK};
    
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
    
    void RemoveBlock(int x, int y);
};

#endif /* GameLogicBasic_hpp */
