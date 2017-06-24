#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "b2d\b2dRootWorldNode.h"

class HelloWorld : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	
	void update(float dt) override;

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	
	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);

	b2WorldNode* _rootWorld;	

};

#endif // __HELLOWORLD_SCENE_H__
