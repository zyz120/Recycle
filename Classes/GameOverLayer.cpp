#include "GameOverLayer.h"
#include "StageScene.h"
#include "WelcomeScene.h"
#include "GameLayer1.h"
USING_NS_CC;

bool GameOverLayer::init()
{
	if (!Layer::init()){
		return false;
	}

	Sprite* background = Sprite::create("gameOverLayer/gameover_bg.png");
	background->setAnchorPoint(Vec2::ZERO);
	background->setPosition(Vec2::ZERO);
	this->addChild(background, 0); 

	MenuItemImage* close = MenuItemImage::create("gameOverLayer/gameover_home_weixuanzhong.png",
		"gameOverLayer/gameover_home_xuanzhong.png", CC_CALLBACK_0(GameOverLayer::closeThisLayer, this));
	close->setPosition(Vec2(684, 290));
	Menu* menu = Menu::create(close, NULL);
	menu->setAnchorPoint(Vec2(0, 0));
	menu->setPosition(Vec2(0, 0));
	this->addChild(menu, 1);

	// set swallow touches
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameOverLayer::onTouchBegan, this);
	listener->setSwallowTouches(true);

	EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	myScore = LabelTTF::create("", "Futura Condensed.ttf", 70);
	myScore->setPosition(Vec2(760, 575));
	this->addChild(myScore, 2);
	topScore = LabelTTF::create("", "Futura Condensed.ttf", 70);
	topScore->setPosition(Vec2(760, 470));
	this->addChild(topScore, 2);

	return true;
}

void GameOverLayer::closeThisLayer()
{
	log("click close!");
	closeAnim();
	StageScene* stage = ((StageScene*)((GameLayer1*)this->getParent())->getParent());
	WelcomeScene* welcome = (WelcomeScene*)stage->welcomeLayer;
	welcome->setVisible(true);
	welcome->listener->setEnabled(true);
	ActionInterval* moveLeft = MoveTo::create(1.0f, Vec2(0, 0));
	welcome->runAction(moveLeft);
}

void GameOverLayer::initScores()
{
	int myS = ((GameLayer1*)(this->getParent()))->getPara(((GameLayer1*)(this->getParent()))->currentScore);
	char temp[20];
	itoa(myS, temp, 10);
	myScore->setString(temp);
	itoa(UserDefault::getInstance()->getIntegerForKey("top", 0), temp, 10);
	topScore->setString(temp);
}

bool GameOverLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	return true;
}

void GameOverLayer::closeAnim()
{
	ActionInterval* big = ScaleBy::create(0.2f, 1.1f);
	ActionInterval* sma = ScaleTo::create(0.3f, 0);
	this->runAction(Sequence::create(big, sma, NULL));
	this->listener->setEnabled(false);
}