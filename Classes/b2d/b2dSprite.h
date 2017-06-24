#ifndef __B2D_SPRITE_H__
#define __B2D_SPRITE_H__

#include "cocos2d.h"

#include <Box2D\Box2D.h>
#include "b2dRootWorldNode.h"
#include "GameVars.h"


USING_NS_CC;

class b2WorldNode;

class b2Sprite : public cocos2d::Sprite
{

public:
	// INSTANTIATION
	b2Sprite();
	~b2Sprite();

	bool init() override;
	bool initBody();
	bool initBody(b2BodyType type);
	bool initBody(float32 friction, float32 restitution);
	bool initBody(b2BodyType type, float32 friction, float32 restitution);

	static b2Sprite* create();
	/**
	* Creates a b2Sprite with sane defaults.
	*
	* @return  An autoreleased b2Sprite object.
	*/
	static b2Sprite* create(const std::string& filename);
	/**
	* Creates a b2Sprite with specified filename.
	*
	* @param   filename Name of image file to use for sprite.
	* @return  An autoreleased b2Sprite object.
	*/
	static b2Sprite* create(const std::string& filename, b2BodyType type);
	/**
	* Creates a b2Sprite with specified filename and body type.
	*
	* @param   filename Name of image file to use for sprite.
	* @param   type Enum of bodytype - static, dynamic, or kinematic.
	* @return  An autoreleased b2Sprite object.
	*/
	static b2Sprite* create(const std::string& filename, b2BodyType type, float32 friction, float32 restitution);
	/**
	* Creates a b2Sprite with specified filename, body type, friction and restiution.
	*
	* @param   filename Name of image file to use for sprite.
	* @param   type Enum of bodytype - static, dynamic, or kinematic.
	* @param   friction Sets the friction of the body.
	* @param   restitution Sets the restiution/bounciness of the body.
	* @return  An autoreleased b2Sprite object.
	*/
	static b2Sprite* create(const std::string& filename, const Rect& rect);
	/**
	* Creates a b2Sprite with specified filename and rectangle size.
	*
	* @param   filename Name of image file to use for sprite.
	* @param   rect Sets the rectangle.
	* @return  An autoreleased b2Sprite object.
	*/
	static b2Sprite* create(const std::string& filename, const Rect& rect, b2BodyType type);
	/**
	* Creates a b2Sprite with specified filename, rectangle size and body type.
	*
	* @param   filename Name of image file to use for sprite.
	* @param   rect Sets the rectangle.
	* @param   type Enum of bodytype - static, dynamic, or kinematic.
	* @return  An autoreleased b2Sprite object.
	*/
	static b2Sprite* create(const std::string& filename, const Rect& rect, b2BodyType type, float32 friction, float32 restitution);
	/**
	* Creates a b2Sprite with specified filename, rectangle size, body type, friction and restiution.
	*
	* @param   filename Name of image file to use for sprite.
	* @param   rect Sets the texture rectangle.
	* @param   type Enum of bodytype - static, dynamic, or kinematic.
	* @param   friction Sets the friction of the body.
	* @param   restitution Sets the restiution/bounciness of the body.
	* @return  An autoreleased b2Sprite object.
	*/

	// SET/GET

	virtual void setPosition(const Vec2& pos) override;
	virtual void setPosition(float x, float y) override;
	void setB2BodyPosition(float x, float y);

	virtual void setRotation(float rotation) override;
	void setB2BodyRotation(float rotation);

	void setWorldNode(b2WorldNode* world);
	b2WorldNode* getWorldNode();
	
	virtual void setBody(b2Body* body, b2WorldNode* world);
	/**
	* Sets this b2Sprites body.
	*
	* @param   body This should be a body created by a b2World.
	* @param   world The parent/world.
	*/
	b2Body* getBody();

	b2BodyDef* getBodyDef();

protected:

	b2Body * _B2Body;
	b2BodyDef _B2BodyDef;
	b2Fixture * _B2Fixture;
	b2FixtureDef _B2FixtureDef;
	b2PolygonShape _B2Shape;

private:

	b2WorldNode* _parentWorldNode;

};






#endif //  __B2D_SPRITE_H__