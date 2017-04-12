#include "HowtoLayer.h"
#include "Util.h"
#include "StageScene.h"
#include "WelcomeScene.h"
#include "GameLayer1.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

bool HowtoLayer::init()
{
	if (!Layer::init()){
		return false;
	}

	background = Sprite::create("howtoLayer/howto_bg.png");
	background->setAnchorPoint(Vec2::ZERO);
	background->setPosition(Vec2::ZERO);
	this->addChild(background, 0);

	setScale(0.95f);
	ActionInterval* big = ScaleTo::create(0.14f, 1.06f);
	ActionInterval* sma = ScaleTo::create(0.14f, 1.0f);
	this->runAction(Sequence::create(big, sma, NULL));

	// set swallow touches
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HowtoLayer::onTouchBegan, this);
	listener->setSwallowTouches(true);

	EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void HowtoLayer::addMenu1() // for welcome layer
{
	MenuItemImage* close = MenuItemImage::create("howtoLayer/howto_start_weixuanzhong.png",
		"howtoLayer/howto_start_xuanzhong.png", CC_CALLBACK_0(HowtoLayer::closeThisLayer1, this));
	close->setPosition(Vec2(684, 290));
	Menu* menu = Menu::create(close, NULL);
	menu->setAnchorPoint(Vec2(0, 0));
	menu->setPosition(Vec2(0, 0));
	this->addChild(menu);
}

void HowtoLayer::addMenu2() // for pause layer
{
	MenuItemImage* returnToWelcome = MenuItemImage::create("howtoLayer/howto_menu_weixuanzhong.png",
		"howtoLayer/howto_menu_xuanzhong.png", CC_CALLBACK_0(HowtoLayer::returnToWelcomeLayer, this));
	returnToWelcome->setPosition(Vec2(500, 290));
	MenuItemImage* close = MenuItemImage::create("howtoLayer/howto_start_weixuanzhong.png",
		"howtoLayer/howto_start_xuanzhong.png", CC_CALLBACK_0(HowtoLayer::closeThisLayer2, this));
	close->setPosition(Vec2(684, 290));
	MenuItemImage* volumn = MenuItemImage::create("howtoLayer/howto_yinliang_weixuanzhong.png",
		"howtoLayer/howto_yinliang_xuanzhong.png", CC_CALLBACK_0(HowtoLayer::changeVolume, this));
	volumn->setPosition(Vec2(868, 290));

	Menu* menu = Menu::create(returnToWelcome, close, volumn, NULL);
	menu->setAnchorPoint(Vec2(0, 0));
	menu->setPosition(Vec2(0, 0));
	this->addChild(menu);
}

void HowtoLayer::returnToWelcomeLayer()
{
	StageScene* stage = ((StageScene*)((GameLayer1*)this->getParent())->getParent());
	WelcomeScene* welcome = (WelcomeScene*)stage->welcomeLayer;
	welcome->setVisible(true);
	welcome->listener->setEnabled(true);
	ActionInterval* moveLeft = MoveTo::create(1.0f, Vec2(0, 0));
	welcome->runAction(moveLeft);
	GameLayer1* parent = (GameLayer1*)this->getParent();
	parent->changePauseState();
}

void HowtoLayer::closeThisLayer1()
{
	WelcomeScene* parent = (WelcomeScene*)this->getParent();

	ActionInterval* big = ScaleTo::create(0.15f, 1.06f);
	ActionInterval* sma = ScaleTo::create(0.15f, 0.3f);
	this->runAction(Sequence::create(big, sma, CallFunc::create([&](){ listener->setEnabled(false);  this->setVisible(false); }), NULL));

}
void HowtoLayer::closeThisLayer2()
{
	GameLayer1* parent = (GameLayer1*)this->getParent();
	parent->changePauseState();

	ActionInterval* big = ScaleTo::create(0.15f, 1.06f);
	ActionInterval* sma = ScaleTo::create(0.15f, 0.3f);
	this->runAction(Sequence::create(big, sma, CallFunc::create([&](){ listener->setEnabled(false);  this->setVisible(false); }), NULL));

}

void HowtoLayer::changeVolume()
{
	StageScene* stage = ((StageScene*)((GameLayer1*)this->getParent())->getParent());
	if (stage->bgmOn){
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		stage->bgmOn = false;
	}
	else{
		playBGM();
		stage->bgmOn = true;
	}

}


bool HowtoLayer::onTouchBegan(cocos2d::Touch* t, cocos2d::Event* e)
{
	return true;
}

void HowtoLayer::playBGM()
{
	// background music player
	int temp = 0;
	if (CCRANDOM_0_1() * 100 > 50)
		temp = 1;
	else
		temp = 2;

	char num[3];
	itoa(temp, num, 10);
	char s1[30] = "music/background";
	char s2[5] = ".mp3";
	strcat(s1, num);
	strcat(s1, s2);

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(s1, true);
}

void HowtoLayer::setbackground()
{
	background->setTexture("howtoLayer/about.png");
}