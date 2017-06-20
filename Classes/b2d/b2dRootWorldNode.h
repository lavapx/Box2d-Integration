#ifndef __B2D_ROOTWORLD_NODE_H__
#define __B2D_ROOTWORLD_NODE_H__

#include "cocos2d.h"

#include <Box2D\Box2D.h>
#include "b2dSprite.h"
#include "GLESDebugDraw.h"
#include "GameVars.h"

USING_NS_CC;



class b2WorldNode : public cocos2d::Node
{
public:
	b2WorldNode();
	~b2WorldNode();
	bool init() override;
	bool init(float gravityX, float gravityY, float metersHeight);

	static b2WorldNode* create();
	/**
	* Creates a b2WorldNode with sane defaults.
	*
	* @return  An autoreleased b2WorldNode object.
	*/
	static b2WorldNode* create(float metersHeight);
	/**
	* Creates a b2WorldNode with specified gravity and PTM ratio of specified height.
	*
	* @param   metersHeight Sets PTM to desired meters in height from screen height.
	* @return  An autoreleased b2WorldNode object.
	*/
	static b2WorldNode* create(float gravityX, float gravityY);
	/**
	* Creates a b2WorldNode with specified gravity and PTM ratio of specified height.
	*
	* @param   gravityX b2World gravity in X.
	* @param   gravityY b2World gravity in Y.
	* @return  An autoreleased b2WorldNode object.
	*/
	static b2WorldNode* create(float gravityX, float gravityY, float metersHeight);
	/**
	* Creates a b2WorldNode with specified gravity and PTM ratio of specified height.
	*
	* @param   gravityX b2World gravity in X.
	* @param   gravityY b2World gravity in Y.
	* @param   metersHeight Sets PTM to desired meters in height from screen height.
	* @return  An autoreleased b2WorldNode object.
	*/
	

	//Get, Set
	b2World* getb2World();
	float& getPTM();


	//Children
	using Node::addChild;
	void addChild(Node* child, int localZOrder, const std::string &name) override;


	//delta functions
	void update(float dt)override;
#if (CC_BOX2D_DEBUG)
	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags) override;

	void onDraw();

	void debugDraw();
#endif	

private:

	bool addChildBody(Node* child);

	void addDynamicChild(b2Body* child);
	void removeDynamicChild(b2Body* child);

	b2World * _world;
#if (CC_BOX2D_DEBUG)
	CustomCommand *_customCommand;
	GLESDebugDraw * _debugDrawInst;
#endif
	std::vector <b2Body*> _dynamicChild;	//stores dynamic and kinematic bodies

	float _PTM_Ratio;	//Pixel to Meter ratio

	int32 _velocityIterations;	//how strongly to correct velocity
	int32 _positionIterations;	//how strongly to correct position


};


#endif // __B2D_ROOTWORLD_NODE_H__