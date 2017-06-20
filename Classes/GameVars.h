#ifndef __GAME_VARS_H__
#define __GAME_VARS_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"

/** Debug draw Box2d objects and log stats of bodies if debug is true. */
#if (COCOS2D_DEBUG==1)
	#ifndef  CC_BOX2D_DEBUG
	#define CC_BOX2D_DEBUG 1
	#endif
#else
	#ifndef  CC_BOX2D_DEBUG
	#define CC_BOX2D_DEBUG 0
	#endif
#endif

class GameVars
{
public:

	//b2d world defaults
	static float PTM_Ratio;
	static float gravityX;
	static float gravityY;
	static float metersHeight;

	//b2d body defaults
	static b2BodyType defaultBody;
	static float defaultFriction;
	static float defaultRestitution;


	static void initVars();

};

#endif //  __GAME_VARS_H__
