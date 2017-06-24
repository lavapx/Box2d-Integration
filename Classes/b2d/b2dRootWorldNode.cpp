#include "b2dRootWorldNode.h"

USING_NS_CC;

//		***	INSTANTIATION	***

b2WorldNode::b2WorldNode()
	:Node()
{
	_world = nullptr;
#if (CC_BOX2D_DEBUG)
	_customCommand = nullptr;
	_debugDrawInst = nullptr;
#endif

	_PTM_Ratio = 0;

	_velocityIterations = 3;
	_positionIterations = 3;

}

b2WorldNode::~b2WorldNode()
{
	delete _world;
	_world = nullptr;
#if (CC_BOX2D_DEBUG)
	delete _customCommand;
	_customCommand = nullptr;

	delete _debugDrawInst;
	_debugDrawInst = nullptr;
#endif

}

bool b2WorldNode::init()
{
#if (CC_BOX2D_DEBUG)
	_debugDrawInst = new GLESDebugDraw(_PTM_Ratio);

	uint32 flags = 0;
		flags += b2Draw::e_shapeBit;
	//  flags += b2Draw::e_jointBit;
	//	flags += b2Draw::e_aabbBit;
	//	flags += b2Draw::e_pairBit;
		flags += b2Draw::e_centerOfMassBit;
	_debugDrawInst->SetFlags(flags);

	_world->SetDebugDraw(_debugDrawInst);
#endif

	return true;

}

bool b2WorldNode::init(float gravityX, float gravityY, float metersHeight)
{
	_PTM_Ratio = Director::getInstance()->getVisibleSize().height / metersHeight;
	_world = new b2World(b2Vec2(gravityX, gravityY));

	return init();

}

b2WorldNode* b2WorldNode::create()
{
	b2WorldNode* b2dWorldNode = new (std::nothrow) b2WorldNode();
	if (b2dWorldNode && b2dWorldNode->init(GameVars::gravityX,GameVars::gravityY,GameVars::PTM_Ratio))
	{
		b2dWorldNode->autorelease();
		return b2dWorldNode;
	}
	CC_SAFE_DELETE(b2dWorldNode);
	return nullptr;

}

b2WorldNode* b2WorldNode::create(float metersHeight)
{
	b2WorldNode* b2dWorldNode = new (std::nothrow) b2WorldNode();
	if (b2dWorldNode && b2dWorldNode->init(GameVars::gravityX, GameVars::gravityY, metersHeight))
	{
		b2dWorldNode->autorelease();
		return b2dWorldNode;
	}
	CC_SAFE_DELETE(b2dWorldNode);
	return nullptr;


}

b2WorldNode* b2WorldNode::create(float gravityX, float gravityY)
{
	b2WorldNode* b2dWorldNode = new (std::nothrow) b2WorldNode();
	if (b2dWorldNode && b2dWorldNode->init(gravityX, gravityY, GameVars::metersHeight))
	{
		b2dWorldNode->autorelease();
		return b2dWorldNode;
	}
	CC_SAFE_DELETE(b2dWorldNode);
	return nullptr;


}

b2WorldNode* b2WorldNode::create(float gravityX, float gravityY, float metersHeight)
{
	b2WorldNode* b2dWorldNode = new (std::nothrow) b2WorldNode();
	if (b2dWorldNode && b2dWorldNode->init(gravityX, gravityY, metersHeight))
	{
		b2dWorldNode->autorelease();
		return b2dWorldNode;
	}
	CC_SAFE_DELETE(b2dWorldNode);
	return nullptr;


}

//		***	GET/SET	***

b2World* b2WorldNode::getb2World()
{
	return _world;

}

float& b2WorldNode::getPTM()
{
	return _PTM_Ratio;

}


//		***	CHILDREN	***

void b2WorldNode::addChild(Node* child, int localZOrder, const std::string &name)
{
	if (addChildBody(child)) {
		this->Node::addChild(child, localZOrder, name);
	}
	else {
		CCLOG("unable to add child physics body, cancelling node addChild");
	}

}

bool b2WorldNode::addChildBody(Node* child)
{
	
	if (b2Sprite* newB2Dchild = dynamic_cast<b2Sprite*>(child))
	{
		newB2Dchild->setBody(_world->CreateBody(newB2Dchild->getBodyDef()), this);

		if (newB2Dchild->getBody()->GetType() == b2_dynamicBody || newB2Dchild->getBody()->GetType() == b2_kinematicBody)
		{
			addDynamicChild(newB2Dchild->getBody());
		}
		return true;
	}
	else
	{
		return false;
	}
	
}

void b2WorldNode::addDynamicChild(b2Body* child)
{
	_dynamicChild.push_back(child);
}

void b2WorldNode::removeDynamicChild(b2Body* child)
{
	//find child in vector and remove
	_dynamicChild.erase(std::find(_dynamicChild.begin(), _dynamicChild.end(), child));
}


//		***	DELTA FUNCTIONS	***

void b2WorldNode::update(float dt)
{
	//stepping b2d world based on incoming delta
	_world->Step(dt, _velocityIterations, _positionIterations);

	//traverse dynamic child vector of pointers, if dynamic child is awake it's transform is likely changing and the sprites transform is called to update it.
	for (int i = 0;i < _dynamicChild.size();i++)
	{
		if (_dynamicChild[i]->IsAwake())
		{
			float deg = CC_RADIANS_TO_DEGREES(-_dynamicChild[i]->GetAngle());
			b2Vec2 pos = _dynamicChild[i]->GetPosition();
			Vec2 pos2 = Vec2(pos.x*_PTM_Ratio, pos.y*_PTM_Ratio);

			b2Sprite* dc = static_cast<b2Sprite*>(_dynamicChild.at(i)->GetUserData());

			if (deg != dc->getRotation())
			{
				dc->setRotation(deg);

			}
			if (pos2 != dc->getPosition())
			{
				dc->setPosition(pos2);
			}
		}
	}


	//b2body logging
#if (CC_BOX2D_DEBUG)
	int bodyCount = 0;
	for (b2Body* b = _world->GetBodyList(); b;b = b->GetNext())
	{
		bodyCount++;
		if (b->IsAwake() && b->GetType() == b2_dynamicBody || b->IsAwake() && b->GetType() == b2_kinematicBody)
		{
			b2Vec2 pos = b->GetPosition();
			float deg = CC_RADIANS_TO_DEGREES(b->GetAngle());

				CCLOG("Body %i \n------\nis at position: %f, %f", bodyCount, pos.x*b2WorldNode::_PTM_Ratio, pos.y*b2WorldNode::_PTM_Ratio);
				CCLOG("has rotation: %f", deg);
				CCLOG("is awake? %s", (b->IsAwake() ? "yes" : "no"));
				CCLOG("has Velocity: %f, %f\n\n", b->GetLinearVelocity().x, b->GetLinearVelocity().y);
		}
	}
#endif
	
}

#if (CC_BOX2D_DEBUG)

void b2WorldNode::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t parentFlags)
{
	Node::draw(renderer, transform, parentFlags);
	_customCommand = new CustomCommand();
	_customCommand->init(10);
	_customCommand->func = CC_CALLBACK_0(b2WorldNode::onDraw, this);
	Director::getInstance()->getRenderer()->addCommand(_customCommand);

}

void b2WorldNode::onDraw()
{
	this->debugDraw();
	delete _customCommand;
	_customCommand = nullptr;

}



void b2WorldNode::debugDraw()
{
	_world->DrawDebugData();

}
#endif
