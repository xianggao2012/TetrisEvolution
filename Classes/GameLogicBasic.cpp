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
    int _random = rand() % BLOCK_TYPES;
    _random = rand() % BLOCK_TYPES;
    
    // 1. empty pool
    pool.depth = 0;
    pool.width = POOL_WIDTH;
    pool.height = POOL_HEIGHT;
    for(int i = 0; i < POOL_WIDTH; i ++)
    {
        for(int j = 0; j < POOL_HEIGHT; j ++) pool.status[i][j] = POOL_BLO_EMPTY;
    }
    // 2. mover
    mover.len = BLOCK_COMP;
    mover.type = MOV_STA_NORMAL;

    for(int i = 0; i < BLOCK_COMP; i ++)
    {
        mover.shapes[i][0] = blockSet[_random][i][0];
        mover.shapes[i][1] = blockSet[_random][i][1];
        mover.status[i] = MOV_BLO_NORMAL;
    }

    // 3. candidates
    for(int i = 0; i < CANDIDATES; i ++)
    {
        _random = rand() % BLOCK_TYPES;

        for(int j = 0; j < BLOCK_COMP; j ++)
        {
            candidates[i].shapes[j][0] = blockSet[_random][j][0];
            candidates[i].shapes[j][1] = blockSet[_random][j][1];
            candidates[i].status[j] = MOV_BLO_NORMAL;
        }
        candidates[i].len = BLOCK_COMP;
        candidates[i].type = MOV_STA_NORMAL;
    } 
    
    // 4. add mover to the pool; real position int the pool, not shape
    int x = POOL_WIDTH / 2 - 1;
    int y = POOL_HEIGHT - 1;
    for(int i = 0; i < BLOCK_COMP; i ++)
    {
        mover.positions[i] = pair<int, int>(x + mover.shapes[i][0], y - mover.shapes[i][1]);
    }

    // 5. row set to not full
    for(int i = 0; i < POOL_HEIGHT; i ++) rowEmpty[i] = false;
    
    // test:
    for(int i = 0; i < POOL_WIDTH; i ++) pool.status[i][0] = POOL_BLO_SETTLED;
    pool.status[4][0] = POOL_BLO_EMPTY;
    pool.status[1][1] = POOL_BLO_SETTLED;
    
    return true;
}

bool GameLogicBasic::DropDown()
{
    bool touched = false;
    
    for(auto &block : mover.positions){
        
        if(block.second == 0
           || (pool.status[block.first][block.second - 1] != POOL_BLO_EMPTY)) touched = true;
    }
    
    if(touched) return touched;
    else for(auto &block : mover.positions) block.second -= 1;
    
    return touched;
}

void GameLogicBasic::MergeMover()
{
    for(auto &block : mover.positions) pool.status[block.first][block.second] = POOL_BLO_SETTLED;
}

void GameLogicBasic::Generate()
{
    // 1. copy mover shape from first candidate
    for(int i = 0; i < BLOCK_COMP; i++)
    {
        mover.shapes[i][0] = candidates[0].shapes[i][0];
        mover.shapes[i][1] = candidates[0].shapes[i][1];
        mover.status[i] = candidates[0].status[i];
    }
    mover.len = candidates[0].len;
    mover.type = candidates[0].type;
    
    
    // 2. adjust remained candidates
    for(int i = 0; i < CANDIDATES - 1; i ++)
    {
        for(int j = 0; j < BLOCK_COMP; j++)
        {
            candidates[i].shapes[j][0] = candidates[i + 1].shapes[j][0];
            candidates[i].shapes[j][1] = candidates[i + 1].shapes[j][1];
            candidates[i].status[j] = candidates[i + 1].status[j];
        }
        candidates[i].len = candidates[i + 1].len;
        candidates[i].type = candidates[i + 1].type;
    }
    
    // 3. randomize a new candidate
    int _random = rand() % BLOCK_TYPES;
    for(int i = 0; i < BLOCK_COMP; i ++)
    {
        candidates[CANDIDATES - 1].shapes[i][0] = blockSet[_random][i][0];
        candidates[CANDIDATES - 1].shapes[i][1] = blockSet[_random][i][1];
    }
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
                                             || (pool.status[block.first - 1][block.second] != POOL_BLO_EMPTY)) return false;

    for(auto &block : mover.positions) block.first -= 1;
    
    return true;
}

bool GameLogicBasic::MoveRight()
{
    for(auto &block : mover.positions) if(block.first == (POOL_WIDTH - 1)
                                         || (pool.status[block.first + 1][block.second]) != POOL_BLO_EMPTY) return false;

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
           || pool.status[ax][ay] == POOL_BLO_SETTLED)
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
            for(int i = 0; i < POOL_WIDTH; i ++) pool.status[i][j] = POOL_BLO_EMPTY;
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

bool GameLogicBasic::DigDown(int n)
{
    if(pool.depth == 0) return false;
    
    int delta = pool.depth >= n ? n : pool.depth;
    pool.depth = pool.depth == delta ? 0 : (pool.depth - delta);
    
    for(int i = POOL_HEIGHT - delta - 1; i >= 0; i--)
    {
        MoveRowTo(i, delta);
    }
    
    GenerateRow(delta);
    
    return true;
}

bool GameLogicBasic::GenerateRow(int n)
{
    int _random;
    for(int i = 0; i < n; i ++)
    {
        for(int j = 0; j < POOL_WIDTH; j ++)
        {
            _random = rand() % 2;
            if(_random) pool.status[j][i] = POOL_BLO_SETTLED;
            else pool.status[j][i] = POOL_BLO_EMPTY;
        }
    }
    
    return true;
}