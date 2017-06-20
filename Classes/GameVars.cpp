#include "GameVars.h"

float GameVars::PTM_Ratio = 0;
float GameVars::gravityX = 0.0;
float GameVars::gravityY = -9.8;
float GameVars::metersHeight = 10;

b2BodyType GameVars::defaultBody = b2BodyType::b2_staticBody;
float GameVars::defaultFriction = 1.0;
float GameVars::defaultRestitution = 0.0;

void GameVars::initVars()
{
	PTM_Ratio = cocos2d::Director::getInstance()->getVisibleSize().height / metersHeight;


}
