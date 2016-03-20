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
#define DROP_INTERVAL 0.3
//#define GEN_INTERVAL 1

// Layer elements
// LayerGameClassic
#define LGC_BG "Background"
#define LGC_BG_IMG "image"
#define LGC_BG_X "px"
#define LGC_BG_Y "py"
#define LGC_LB "LeftButton"
#define LGC_LB_IMG_DEFAULT "imageDefault"
#define LGC_LB_IMG_CLICKED "imageClicked"
#define LGC_LB_X "px"
#define LGC_LB_Y "py"
#define LGC_RB "RightButton"
#define LGC_RB_IMG_DEFAULT "imageDefault"
#define LGC_RB_IMG_CLICKED "imageClicked"
#define LGC_RB_X "px"
#define LGC_RB_Y "py"
#define LGC_RTB "RotateButton"
#define LGC_RTB_IMG_DEFAULT "imageDefault"
#define LGC_RTB_IMG_CLICKED "imageClicked"
#define LGC_RTB_X "px"
#define LGC_RTB_Y "py"
#define LGC_DB "DownButton"
#define LGC_DB_IMG_DEFAULT "imageDefault"
#define LGC_DB_IMG_CLICKED "imageClicked"
#define LGC_DB_X "px"
#define LGC_DB_Y "py"


#endif /* TEHeader_h */
