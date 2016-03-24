//
//  GameLogicBasic.cpp
//  TetrisEvolution
//
//  Created by Xiang Gao on 3/10/16.
//
//

#include "GameLogicBasic.hpp"

static const int blockSet[BLOCK_TYPES][BLOCK_COMP][2] =
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
    srand(time(NULL));
    int n = rand() % BLOCK_TYPES;

    // 1. empty pool
    for(int i = 0; i < POOL_WIDTH; i ++)
    {
        for(int j = 0; j < POOL_HEIGHT; j ++) pool[i][j] = false;
    }
    // 2. mover
    n = rand() % BLOCK_TYPES;

    for(int i = 0; i < BLOCK_COMP; i ++)
    {
        mover[i][0] = blockSet[n][i][0];
        mover[i][1] = blockSet[n][i][1];
    }

    // 3. candidates
    for(int i = 0; i < CANDIDATES; i ++)
    {
        n = rand() % BLOCK_TYPES;

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

    // 5. row set to not full
    for(int i = 0; i < POOL_HEIGHT; i ++) rowEmpty[i] = false;
    
    // test:
    for(int i = 0; i < POOL_WIDTH; i ++) pool[i][0] = true;
    pool[4][0] = false;
    pool[1][1] = true;
    
    return true;
}

bool GameLogicBasic::DropDown()
{
    bool touched = false;
    
    for(auto block : mover){
        
        if(block[1] == 0 || pool[block[0]][block[1] - 1]) touched = true;
    }
    
    if(touched) return touched;
    else for(auto block : mover) block[1] -= 1;
    
    return touched;
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

    for(int i = 0; i < BLOCK_COMP; i ++)
    {
        mover[i][0] = x + mover[i][0];
        mover[i][1] = y - mover[i][1];
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
    int tx, ty, ax, ay; //temp, availability

    for(auto block : mover)
    {
        hmax = (hmax >= block[1] ? hmax : block[1]);
        h = (h <= block[1] ? h : block[1]);
        w = (w <= block[0] ? w : block[0]);
    }
    hmax = hmax - h;

    // check rotate availability
    for(auto block : mover)
    {
        tx = block[0];
        ty = block[1];
        ax = hmax - (ty - h) + w;
        ay = (tx - w) + h;
        if(ax <=0 || ax >= (POOL_WIDTH - 1) || ay <= 0 || ay >= (POOL_HEIGHT - 1) || pool[ax][ay]) return false;
    }
    
    // newx=hmax - y,newy=x
    for(auto block : mover)
    {
        tx = block[0];
        ty = block[1];
        block[0] = hmax - (ty - h) + w;
        block[1] = (tx - w) + h;
    }
    
    return true;
}

bool GameLogicBasic::MoveDown()
{
    bool touched = false;
    while(!touched)
    {
        touched = DropDown();
    }
    
    return touched;
}

bool GameLogicBasic::EliminateRow()
{
    bool foundRowFull = false;
    
    bool rowFull;
    for(int j = 0; j < POOL_HEIGHT; j ++)
    {
        rowFull = true;
        for(int i = 0; i < POOL_WIDTH; i ++)
        {
            if(!pool[i][j]) rowFull = false;
        }
        if(rowFull)
        {
            foundRowFull = true;
            for(int i = 0; i < POOL_WIDTH; i ++) pool[i][j] = false;
            rowEmpty[j] = true;
        }
    }
    
    return foundRowFull;
}

void GameLogicBasic::ShrinkRow()
{
    int last = 0, cur = 0;
    while(cur < POOL_HEIGHT)
    {
        if(cur == last && rowEmpty[cur] == false)
        {
            last ++;
            cur ++;
        }
        else if(last == cur && rowEmpty[cur] == true)
        {
            cur ++;
        }
        else if(rowEmpty[cur] == false)
        {
            MoveRowTo(cur, last);
            rowEmpty[last] = false;
            rowEmpty[cur] = true;
            last ++;
            cur ++;
        }
        else cur++;
    }
    for(int i = 0; i < POOL_HEIGHT; i ++) rowEmpty[i] = false;
}

void GameLogicBasic::MoveRowTo(int from, int to)
{
    for(int i = 0; i < POOL_WIDTH; i ++) pool[i][to] = pool[i][from];
}

vector<int> GameLogicBasic::getEliminatedRow()
{
    vector<int> ret;
    for(int i = 0; i < POOL_HEIGHT; i ++)
    {
        if(rowEmpty[i]) ret.push_back(i);
    }
    
    return ret;
}