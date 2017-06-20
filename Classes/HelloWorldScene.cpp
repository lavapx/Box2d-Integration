#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...
	//Director::getInstance()->

	Director::getInstance()->setDisplayStats(false);

	GameVars::initVars();

	world = b2WorldNode::create(0,-9.8,20);
	this->addChild(world);

	auto box = b2Sprite::create("TestCube.png", b2BodyType::b2_dynamicBody, 1.0, .5);
	auto box2 = b2Sprite::create("TestCube.png", b2BodyType::b2_dynamicBody, 1.0, .5);
	auto box3 = b2Sprite::create("TestCube.png", b2BodyType::b2_dynamicBody, 1.0, .5);
	auto box4 = b2Sprite::create("TestCube.png", b2BodyType::b2_dynamicBody, 1.0, .5);

	auto floor = b2Sprite::create("clear.png", Rect(0, 0, visibleSize.width, 20), b2BodyType::b2_staticBody, 1.0,0.0);
	auto wallL = b2Sprite::create("clear.png", Rect(0, 0, 4, visibleSize.height), b2BodyType::b2_staticBody, 1.0, 0.0);
	auto wallR = b2Sprite::create("clear.png", Rect(0, 0, 4, visibleSize.height), b2BodyType::b2_staticBody, 1.0, 0.0);
	auto ceil = b2Sprite::create("clear.png", Rect(0, 0, visibleSize.width, 4), b2BodyType::b2_staticBody, 1.0, 0.0);
	
	world->addChild(box);
	world->addChild(box2);
	world->addChild(box3);
	world->addChild(box4);

	world->addChild(floor);
	world->addChild(wallL);
	world->addChild(wallR);
	world->addChild(ceil);

	box->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	box2->setPosition(visibleSize.width / 2, visibleSize.height / 2+20);
	box3->setPosition(visibleSize.width / 2+40, visibleSize.height / 2 + 60);
	box4->setPosition(visibleSize.width / 2-40, visibleSize.height / 2 + 40);

	floor->setPosition(visibleSize.width / 2, 10);
	wallL->setPosition(2, visibleSize.height / 2);
	wallR->setPosition(visibleSize.width - 2, visibleSize.height / 2);
	ceil->setPosition(visibleSize.width / 2, visibleSize.height -2);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = [](Touch* touch, Event* event)->bool
	{
		auto bounds = event->getCurrentTarget()->getBoundingBox();
		auto sprite = static_cast<b2Sprite*>(event->getCurrentTarget());
		if (bounds.containsPoint(touch->getLocation()))
		{

			sprite->setPosition(touch->getLocation());
			sprite->getBody()->SetGravityScale(0);
			sprite->getBody()->SetLinearVelocity(b2Vec2(0, 0));
			sprite->getBody()->SetAngularVelocity(0);
			sprite->getBody()->SetSleepingAllowed(false);
			sprite->getBody()->SetAwake(true);
			return true;
		}
		else
			return false;
	};
	touchListener->onTouchMoved = [](Touch* touch, Event* event)->bool
	{
		auto bounds = event->getCurrentTarget()->getBoundingBox();
		auto sprite = static_cast<b2Sprite*>(event->getCurrentTarget());
		
		sprite->setPosition(touch->getLocation());
		sprite->getBody()->SetLinearVelocity(b2Vec2(0, 0));
		sprite->getBody()->SetAngularVelocity(0);
		sprite->getBody()->SetAwake(true);
		
		return true;
	};
	touchListener->onTouchEnded = [](Touch* touch, Event* event) -> bool
	{
		auto bounds = event->getCurrentTarget()->getBoundingBox();
		auto sprite = static_cast<b2Sprite*>(event->getCurrentTarget());
		
		sprite->setPosition(touch->getLocation());
		sprite->getBody()->SetGravityScale(1);
		sprite->getBody()->SetSleepingAllowed(true);
		sprite->getBody()->SetAwake(true);
		
		return true;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, box);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener->clone(), box2);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener->clone(), box3);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener->clone(), box4);

	scheduleUpdate();
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}

void HelloWorld::update(float dt)
{
	world->update(dt);

}