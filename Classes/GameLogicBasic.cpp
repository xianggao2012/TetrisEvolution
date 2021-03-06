//
//  GameLogicBasic.cpp
//  TetrisEvolution
//
//  Created by Xiang Gao on 3/10/16.
//
//

#include "GameLogicBasic.hpp"
#include<iostream>
using namespace std;

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
    int _random = rand() % BLOCK_TYPES;
    _random = rand() % BLOCK_TYPES;
    
    // 1. empty pool
    pool.depth = 0;
    pool.width = POOL_WIDTH;
    pool.height = POOL_HEIGHT;
    for(int i = 0; i < POOL_WIDTH; i ++)
    {
        for(int j = 0; j < POOL_HEIGHT; j ++) pool.status[i][j] = POOL_BLOCK_EMPTY;
    }
    // 2. mover
    mover.len = BLOCK_COMP;
    mover.status = MOVER_STATUS_NORMAL;
    mover.isActive = true;

    int x = POOL_WIDTH / 2 - 1;
    int y = POOL_HEIGHT - 1;
    
    //test
    _random = 2;
    
    for(int i = 0; i < BLOCK_COMP; i ++)
    {
        mover.shapes[i][0] = blockSet[_random][i][0];
        mover.shapes[i][1] = blockSet[_random][i][1];
        mover.block_status[i] = rand() % 2 == 0 ? MOVER_BLOCK_BLACK : MOVER_BLOCK_WHITE;
        // add mover to the pool; real position int the pool, not shape
        mover.positions[i] = pair<int, int>(x + mover.shapes[i][0], y - mover.shapes[i][1]);
    }
    
    // 3. candidates
    for(int i = 0; i < CANDIDATES; i ++)
    {
        _random = rand() % BLOCK_TYPES;

        for(int j = 0; j < BLOCK_COMP; j ++)
        {
            candidates[i].shapes[j][0] = blockSet[_random][j][0];
            candidates[i].shapes[j][1] = blockSet[_random][j][1];
            candidates[i].block_status[j] = rand() % 2 == 0 ? MOVER_BLOCK_BLACK : MOVER_BLOCK_WHITE;
        }
        candidates[i].len = BLOCK_COMP;
        candidates[i].status = MOVER_STATUS_NORMAL;
        candidates[i].isActive = false;
    } 
    

    // 5. row set to not full
    for(int i = 0; i < POOL_HEIGHT; i ++) rowEmpty[i] = false;
    
    // test:
    for(int i = 0; i < POOL_WIDTH; i ++) pool.status[i][0] = POOL_BLOCK_WHITE;
    for(int i = 0; i < POOL_WIDTH; i ++) pool.status[i][1] = POOL_BLOCK_BLACK;
    for(int i = 0; i < POOL_WIDTH; i ++) pool.status[i][2] = POOL_BLOCK_WHITE;
    pool.status[4][0] = POOL_BLOCK_EMPTY;
    pool.status[4][1] = POOL_BLOCK_EMPTY;
    pool.status[4][2] = POOL_BLOCK_EMPTY;
    pool.status[1][1] = POOL_BLOCK_EMPTY;
    
    
    return true;
}

bool GameLogicBasic::DropDown()
{
    bool touched = false;
    if(!isMoverActive()) return touched;
    
    for(auto &block : mover.positions){
        
        if(block.second == 0
           || (pool.status[block.first][block.second - 1] != POOL_BLOCK_EMPTY)) touched = true;
    }
    
    if(touched) return touched;
    else for(auto &block : mover.positions) block.second -= 1;
    
    return touched;
}

void GameLogicBasic::MergeMover()
{
    for(int i = 0; i < BLOCK_COMP; i ++)
    {
        if(mover.block_status[i] == MOVER_BLOCK_WHITE)
            pool.status[mover.positions[i].first][mover.positions[i].second] =  POOL_BLOCK_WHITE;
        else if(mover.block_status[i] == MOVER_BLOCK_BLACK)
            pool.status[mover.positions[i].first][mover.positions[i].second] =  POOL_BLOCK_BLACK;
    }
    mover.isActive = false;
}

void GameLogicBasic::Generate()
{
    // 1. copy mover shape from first candidate
    for(int i = 0; i < BLOCK_COMP; i++)
    {
        mover.shapes[i][0] = candidates[0].shapes[i][0];
        mover.shapes[i][1] = candidates[0].shapes[i][1];
        mover.block_status[i] = candidates[0].block_status[i];
    }
    mover.len = candidates[0].len;
    mover.status = candidates[0].status;
    mover.isActive = true;
    
    
    // 2. adjust remained candidates
    for(int i = 0; i < CANDIDATES - 1; i ++)
    {
        for(int j = 0; j < BLOCK_COMP; j++)
        {
            candidates[i].shapes[j][0] = candidates[i + 1].shapes[j][0];
            candidates[i].shapes[j][1] = candidates[i + 1].shapes[j][1];
            candidates[i].block_status[j] = candidates[i + 1].block_status[j];
        }
        candidates[i].len = candidates[i + 1].len;
        candidates[i].status = candidates[i + 1].status;
    }
    
    // 3. randomize a new candidate
    int _random = rand() % BLOCK_TYPES;
    for(int i = 0; i < BLOCK_COMP; i ++)
    {
        candidates[CANDIDATES - 1].shapes[i][0] = blockSet[_random][i][0];
        candidates[CANDIDATES - 1].shapes[i][1] = blockSet[_random][i][1];
        candidates[CANDIDATES - 1].block_status[i] = rand() % 2 == 0 ? MOVER_BLOCK_BLACK : MOVER_BLOCK_WHITE;
    }
    candidates[CANDIDATES - 1].len = BLOCK_COMP;
    candidates[CANDIDATES - 1].status = MOVER_STATUS_NORMAL;
    candidates[CANDIDATES - 1].isActive = false;
    
    // 4. add mover to the pool; real position, not shape
    int x = POOL_WIDTH / 2 - 1;
    int y = POOL_HEIGHT - 1;

    for(int i = 0; i < BLOCK_COMP; i ++)
    {
        mover.positions[i] = pair<int, int>(x + mover.shapes[i][0], y - mover.shapes[i][1]);
    }
    
}

bool GameLogicBasic::MoveLeft()
{
    for(auto &block : mover.positions) if(block.first == 0
                                             || (pool.status[block.first - 1][block.second] != POOL_BLOCK_EMPTY)) return false;

    for(auto &block : mover.positions) block.first -= 1;
    
    return true;
}

bool GameLogicBasic::MoveRight()
{
    for(auto &block : mover.positions) if(block.first == (POOL_WIDTH - 1)
                                         || (pool.status[block.first + 1][block.second]) != POOL_BLOCK_EMPTY) return false;

    for(auto &block : mover.positions) block.first += 1;
    
    return true;
}

bool GameLogicBasic::Rotate()
{
    int hmax = 0, h = POOL_HEIGHT, w = POOL_WIDTH;
    int tx, ty, ax, ay; //temp, availability

    for(auto &block : mover.positions)
    {
        hmax = (hmax >= block.second ? hmax : block.second);
        h = (h <= block.second ? h : block.second);
        w = (w <= block.first ? w : block.first);
    }
    hmax = hmax - h;

    // check rotate availability
    for(auto &block : mover.positions)
    {
        tx = block.first;
        ty = block.second;
        ax = hmax - (ty - h) + w;
        ay = (tx - w) + h;
        if(ax <=0
           || ax >= (POOL_WIDTH - 1)
           || ay <= 0
           || ay >= (POOL_HEIGHT - 1)
           || pool.status[ax][ay] != POOL_BLOCK_EMPTY)
            return false;
    }
    
    // newx=hmax - y,newy=x
    for(auto &block : mover.positions)
    {
        tx = block.first;
        ty = block.second;
        block.first = hmax - (ty - h) + w;
        block.second = (tx - w) + h;
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
            if(!pool.status[i][j]) rowFull = false;
        }
        if(rowFull)
        {
            foundRowFull = true;
            for(int i = 0; i < POOL_WIDTH; i ++) pool.status[i][j] = POOL_BLOCK_EMPTY;
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
    for(int i = 0; i < POOL_WIDTH; i ++) pool.status[i][to] = pool.status[i][from];
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

int GameLogicBasic::DigDown(int rows)
{
    if(pool.depth == 0) return -1;
    
    int delta = pool.depth >= rows ? rows : pool.depth;
    pool.depth = pool.depth == delta ? 0 : (pool.depth - delta);
    
    for(int i = POOL_HEIGHT - delta - 1; i >= 0; i--)
    {
        MoveRowTo(i, i + delta);
    }
    
    GenerateRow(delta);
    
    return delta;
}

bool GameLogicBasic::GenerateRow(int rows)
{
    int _random;
    for(int i = 0; i < rows; i ++)
    {
        for(int j = 0; j < POOL_WIDTH; j ++)
        {
            _random = rand() % 2;
            if(_random) pool.status[j][i] = rand() % 2 == 0 ? POOL_BLOCK_BLACK : POOL_BLOCK_WHITE;
            else pool.status[j][i] = POOL_BLOCK_EMPTY;
        }
    }
    
    return true;
}

bool GameLogicBasic::isPoolBlockEmpty(int x, int y)
{
    return pool.status[x][y] == POOL_BLOCK_EMPTY;
}
pair<int, int> GameLogicBasic::getMoverPosition(int n)
{
    pair<int, int> ret;
    ret.first = mover.positions[n].first;
    ret.second = mover.positions[n].second;
    
    return ret;
}

int GameLogicBasic::getMoverLength()
{
    return mover.len;
}
void GameLogicBasic::setPoolDepth(int n)
{
    pool.depth = n;
}
bool GameLogicBasic::isRowCleared(int r)
{
    return rowEmpty[r];
}
bool GameLogicBasic::isMoverActive()
{
    return mover.isActive;
}
void GameLogicBasic::RemoveBlock(pair<int, int> pos)
{
    int x = pos.first;
    int y = pos.second;
    pool.status[x][y] = POOL_BLOCK_EMPTY;
    for(int i = y; i < POOL_HEIGHT - 1; i ++)
    {
        pool.status[x][i] = pool.status[x][i + 1];
    }
    pool.status[x][POOL_HEIGHT - 1] = POOL_BLOCK_EMPTY;
}

bool GameLogicBasic::isMoverBlack(int i)
{
    return mover.block_status[i] == MOVER_BLOCK_BLACK;
}


bool GameLogicBasic::isMoverWhite(int i)
{
    return mover.block_status[i] == MOVER_BLOCK_WHITE;
}

bool GameLogicBasic::isPoolBlockWhite(int i, int j)
{
    return pool.status[i][j] == POOL_BLOCK_WHITE;
}
bool GameLogicBasic::isPoolBlockBlack(int i, int j)
{
    return pool.status[i][j] == POOL_BLOCK_BLACK;
}
