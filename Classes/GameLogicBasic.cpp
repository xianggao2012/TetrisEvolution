//
//  GameLogicBasic.cpp
//  TetrisEvolution
//
//  Created by Xiang Gao on 3/10/16.
//
//

#include "GameLogicBasic.hpp"
int blockSet[BLOCK_TYPES][BLOCK_COMP][2] =
{
    {{0,0},{1,0},{1,1},{1,2}},  // 7
    {{0,0},{1,0},{0,1},{0,2}},
    {{0,0},{1,0},{2,0},{3,0}},  // --
    {{0,0},{1,0},{0,1},{1,1}},  // [ ]
    {{0,0},{1,0},{2,0},{1,1}},  // _|_
    {{0,0},{1,0},{1,1},{2,1}},
    {{1,0},{2,0},{1,1},{0,1}}
};

bool GameLogicBasic::Initialize()
{
    srand (time(NULL));
    int n = rand() % BLOCK_TYPES;

    // 1. empty pool
    for(int i = 0; i < POOL_WIDTH; i ++)
    {
        for(int j = 0; j < POOL_HEIGHT; j ++) pool[i][j] = false;
    }
    // 2. mover
    n = rand() % BLOCK_TYPES;
    CCLOG("n:%i",n);
    for(int i = 0; i < BLOCK_COMP; i ++)
    {
        mover[i][0] = blockSet[n][i][0];
        mover[i][1] = blockSet[n][i][1];
    }

    // 3. candidates
    for(int i = 0; i < CANDIDATES; i ++)
    {
        n = rand() % BLOCK_TYPES;
        CCLOG("n:%i",n);
        for(int j = 0; j < BLOCK_COMP; j ++)
        {
            candidates[i][j][0] = blockSet[n][j][0];
            candidates[i][j][1] = blockSet[n][j][1];
        }
    } 
    
    // 4. add mover to the pool; real position, not shape
    int x = POOL_WIDTH / 2 - 1;
    int y = POOL_HEIGHT - 1;
    for(int i = 0; i < BLOCK_COMP; i ++)
    {
        mover[i][0] = x + mover[i][0];
        mover[i][1] = y - mover[i][1];
    }

    return true;
}

void GameLogicBasic::DropDown()
{
    // if can't drop anymore, merge it to the pool and generate another
    bool touched = false;
    
    for(auto block : mover){
        
        if(block[1] == 0 || pool[block[0]][block[1] - 1]) touched = true;
    }
    
    if(touched)
    {
        MergeMover();
        Generate();
    }
    else for(auto block : mover) block[1] -= 1;
}

void GameLogicBasic::MergeMover()
{
    for(auto block : mover) pool[block[0]][block[1]] = true;
}

void GameLogicBasic::Generate()
{
    // 1. copy mover shape from first candidate
    for(int i = 0; i < BLOCK_COMP; i++)
    {
        mover[i][0] = candidates[0][i][0];
        mover[i][1] = candidates[0][i][1];
    }
    // 2. adjust remained candidates
    for(int i = 0; i < CANDIDATES - 1; i ++)
    {
        for(int j = 0; j < BLOCK_COMP; j++)
        {
            candidates[i][j][0] = candidates[i + 1][j][0];
            candidates[i][j][1] = candidates[i + 1][j][1];
        }
    }
    // 3. randomize a new candidate
    int n = rand() % BLOCK_TYPES;
    for(int i = 0; i < BLOCK_COMP; i ++)
    {
        candidates[CANDIDATES - 1][i][0] = blockSet[n][i][0];
        candidates[CANDIDATES - 1][i][1] = blockSet[n][i][1];
    }
    // 4. add mover to the pool; real position, not shape
    int x = POOL_WIDTH / 2 - 1;
    int y = POOL_HEIGHT - 1;
    CCLOG("new mover:");
    for(int i = 0; i < BLOCK_COMP; i ++)
    {
        mover[i][0] = x + mover[i][0];
        mover[i][1] = y - mover[i][1];
        
        CCLOG("(%i, %i)",mover[i][0], mover[i][1]);
    }
}

bool GameLogicBasic::MoveLeft()
{
    for(auto block : mover) if(block[0] == 0 || pool[block[0] - 1][block[1]]) return false;

    for(auto block : mover) block[0] -= 1;
    
    return true;
}

bool GameLogicBasic::MoveRight()
{
    for(auto block : mover) if(block[0] == (POOL_WIDTH - 1) || pool[block[0] + 1][block[1]]) return false;

    for(auto block : mover) block[0] += 1;
    
    return true;
}

bool GameLogicBasic::Rotate()
{
    int hmax = 0, h = POOL_HEIGHT, w = POOL_WIDTH;

    int px, py;
    for(auto block : mover)
    {
        px = block[0];
        py = block[1];
        hmax = (hmax >= py ? hmax : py);
        h = (h <= py ? h : py);
        w = (w <= px ? w : px);
    }
    hmax = hmax - h;
    
    // nx=hmax - y,ny=x
    int x, y;
    for(auto block : mover)
    {
        px = block[0];
        py = block[1];
        x = hmax - (py - h) + w;
        y = (px - w) + h;
        
        px = x;
        py = y;
        block[0] = px;
        block[1] = py;
    }
    
    return true;
}