//
//  TEHeader.h
//  TetrisEvolution
//
//  Created by Xiang Gao on 1/8/16.
//
//

#ifndef TEHEADER_H
#define TEHEADER_H

//#include "ConfigFactory.h"      // singleton object managing all xml configs
//#include "LayerMenu.h"
//#include "LayerGameClassic.h"
//#include "GameLogicBasic.hpp"

// Description
// File
#define CONF_DEFAULT_XML "default_scene.xml"

// Scene

//
#define POOL_WIDTH 10
#define POOL_HEIGHT 20
#define POOL_LEFT_BORDER 400
#define POOL_BOTTOM_BORDER 100

#define BLOCK_SIZE 80
#define BLOCK_SIZE_F 80.0f
#define BLOCK_TYPES 7
#define BLOCK_COMP 4
#define CANDIDATES 3
#define DROP_INTERVAL 2
//#define GEN_INTERVAL 1

// Layer elements
// LayerGameBasic
#define LGB_BG "Background"
#define LGB_BG_IMG "image"
#define LGB_BG_X "px"
#define LGB_BG_Y "py"

#endif /* TEHeader_h */


// z axis
#define Z_ITEM_EFFECT 5
