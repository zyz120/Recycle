#include "StageScene.h"
#include "WelcomeScene.h"
#include "Util.h"

USING_NS_CC;

Scene* StageScene::createScene()
{
	auto scene = Scene::create();

	auto layer = StageScene::create();

	scene->addChild(layer, 20);

	return scene;
}


bool StageScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	// add welcome layer ！！！！！！ ZOrder = 30
	welcomeLayer = WelcomeScene::create();
	this->addChild(welcomeLayer, 30);

	// add level layer ！！！！！！ ZOrder = 20
	gameLayer1 = GameLayer1::create();
	this->addChild(gameLayer1, 20);


	bgmOn = true;
	gameOn = false;

	return true;
}