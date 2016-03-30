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

enum {POOL_BLO_EMPTY = 0, POOL_BLO_SETTLED};
enum {MOV_STA_NORMAL = 0};
enum {MOV_BLO_NORMAL = 0, MOV_BLO_WHITE, MOV_BLO_BLACK};

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
};
class GameLogicBasic
{
private:
public:   
    Pool pool;
    Mover mover;
    Mover candidates[CANDIDATES];
    bool rowEmpty[POOL_HEIGHT];
    void MoveRowTo(int from, int to);
public:
    void Generate();
    void MergeMover();
    
    bool Initialize();
    bool DropDown();
    bool MoveLeft();
    bool MoveRight();
    bool MoveDown();
    bool Rotate();
    bool EliminateRow();
    void ShrinkRow();
    vector<int> getEliminatedRow();
    bool DigDown(int);
    bool GenerateRow(int);
};

#endif /* GameLogicBasic_hpp */
