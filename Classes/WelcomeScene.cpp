#include "WelcomeScene.h"
#include "SimpleAudioEngine.h"
#include "StageScene.h"
#include "CollectionLayer.h"
#include "Util.h"
#include "ChooseLayer.h"
#include "RankLayer.h"
#include "RankScene.h"

USING_NS_CC;

Scene* WelcomeScene::createScene()
{
	auto scene = Scene::create();

	auto layer = WelcomeScene::create();

	scene->addChild(layer, 20);

	return scene;
}


bool WelcomeScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	/*
	background and buttons are set bellow
	*/
	// background and title
	Sprite* background = Sprite::create("welcomeScene/shouye_beijing.png");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(background, 20);

	Sprite* logo = Sprite::create("welcomeScene/shouye_logo_kexunhuan.png");
	logo->setPosition(Util::getPos(logo, 628, 290));
	ActionInterval* rotate = RotateBy::create(4.0f, 359);
	ActionInterval* fadeIn2 = FadeIn::create(1.8f);
	RepeatForever* repeatRotate = RepeatForever::create(rotate);
	logo->setOpacity(0);
	logo->runAction(fadeIn2);
	logo->runAction(repeatRotate);
	this->addChild(logo, 21);

	// seven buttons totally
	MenuItemImage* btn_start = MenuItemImage::create("welcomeScene/shouye_kaishi_weixuanzhong.png",
		"welcomeScene/shouye_kaishi_xuanzhong.png", CC_CALLBACK_1(WelcomeScene::startCallback, this));
	btn_start->setPosition(Util::getPos(btn_start, 420, 440));
	MenuItemImage* btn_collection = MenuItemImage::create("welcomeScene/shouye_lajishouji_weixuanzhong.png",
		"welcomeScene/shouye_lajishouji_xuanzhong.png", CC_CALLBACK_1(WelcomeScene::collectionCallback, this));
	btn_collection->setPosition(Util::getPos(btn_collection, 420, 578));
	MenuItemImage* btn_forest = MenuItemImage::create("welcomeScene/shouye_senlin_weixuanzhong.png",
		"welcomeScene/shouye_senlin_xuanzhong.png", CC_CALLBACK_1(WelcomeScene::forestCallback, this));
	btn_forest->setPosition(Util::getPos(btn_forest, 550, 578));
	MenuItemImage* btn_help = MenuItemImage::create("welcomeScene/shouye_bangzhu_weixuanzhong.png",
		"welcomeScene/shouye_bangzhu_xuanzhong.png", CC_CALLBACK_1(WelcomeScene::helpCallback, this));
	btn_help->setPosition(Util::getPos(btn_help, 680, 578));
	MenuItemImage* btn_volumn = MenuItemImage::create("welcomeScene/shouye_yinliang_weixuanzhong.png",
		"welcomeScene/shouye_yinliang_xuanzhong.png", CC_CALLBACK_1(WelcomeScene::volumnCallback, this));
	btn_volumn->setPosition(Util::getPos(btn_volumn, 810, 578));
	MenuItemImage* btn_about = MenuItemImage::create("welcomeScene/shouye_about_weixuanzhong.png",
		"welcomeScene/shouye_about_xuanzhong.png", CC_CALLBACK_1(WelcomeScene::aboutCallback, this));
	btn_about->setPosition(Util::getPos(btn_about, -120, 745));
	ActionInterval* rotate1 = RotateBy::create(1.2f, 359);
	ActionInterval* moveBy1 = MoveBy::create(1.2f, Vec3(200, 0, 0));
	btn_about->runAction(rotate1);
	btn_about->runAction(moveBy1);
	MenuItemImage* btn_rank = MenuItemImage::create("welcomeScene/shouye_rank_weixuanzhong.png",
		"welcomeScene/shouye_rank_xuanzhong.png", CC_CALLBACK_1(WelcomeScene::rankCallback, this));
	btn_rank->setPosition(Util::getPos(btn_rank, 1352, 745));
	ActionInterval* rotate2 = RotateBy::create(1.2f, -359);
	ActionInterval* moveBy2 = MoveBy::create(1.2f, Vec3(-200, 0, 0));
	btn_rank->runAction(rotate2);
	btn_rank->runAction(moveBy2);

	// menu
	menu = Menu::create(btn_start, btn_collection, btn_forest, btn_help, btn_volumn, NULL);
	menu->setAnchorPoint(Vec2::ZERO);
	menu->setPosition(Vec2::ZERO);	
	ActionInterval* fadeIn3 = FadeIn::create(1.8f);
	menu->setOpacity(0);
	menu->runAction(fadeIn3);
	this->addChild(menu, 21);
	Menu* menu2 = Menu::create(btn_about, btn_rank, NULL);
	menu2->setAnchorPoint(Vec2::ZERO);
	menu2->setPosition(Vec2::ZERO);
	this->addChild(menu2, 21);
	

	// settings about touch event
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(WelcomeScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(WelcomeScene::onTouchEnded, this);
	listener->setSwallowTouches(true);

	dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	// partical system
	ParticleSnow* ps = ParticleSnow::createWithTotalParticles(8000);
	ps->setSpeed(50);
	ps->setGravity(Vec2(0, -50));
	ps->setTexture(Director::getInstance()->getTextureCache()->addImage("welcomeScene/light.png"));
	ps->setPosition(Vec2(visibleSize.width/2, visibleSize.height));
	this->addChild(ps, 31);

	srand(time(0));
	playBGM();

	return true;
}

void WelcomeScene::startCallback(cocos2d::Ref* pSender)
{
	Action* slide = MoveBy::create(1.5f, Vec3(1400, 0, 0));
	this->runAction(Sequence::create(CallFunc::create([&]()
	{
		menu->setEnabled(false);
	}), slide, 
		CallFunc::create([&]()
	{
		menu->setEnabled(true);
	}), NULL));
	((StageScene*)this->getParent())->gameOn = true;
	//---
	((StageScene*)this->getParent())->gameLayer1->initLevel();
	//---
	listener->setEnabled(false);
}
void WelcomeScene::collectionCallback(cocos2d::Ref* pSender)
{
	ChooseLayer* layer = ChooseLayer::create();
	layer->setPosition(Vec2(0, 968));
	layer->setAnchorPoint(Vec2::ZERO);

	menu->setEnabled(false);

	ActionInterval* jump1 = JumpTo::create(0.5f, Vec2::ZERO, 0, 1);
	ActionInterval* jump2 = JumpTo::create(0.4f, Vec2::ZERO, 150, 1);
	ActionInterval* jump3 = JumpTo::create(0.2f, Vec2::ZERO, 60, 1);
	layer->runAction(Sequence::create(jump1, jump2, jump3, CallFunc::create([&](){menu->setEnabled(true); }), NULL));

	this->addChild(layer, 40);
}

void WelcomeScene::forestCallback(cocos2d::Ref* pSender)
{
	TreeLayer* layer = TreeLayer::create();
	layer->setPosition(Vec2(0, 968));
	layer->setAnchorPoint(Vec2::ZERO);

	menu->setEnabled(false);

	ActionInterval* jump1 = JumpTo::create(0.5f, Vec2::ZERO, 0, 1);
	ActionInterval* jump2 = JumpTo::create(0.4f, Vec2::ZERO, 150, 1);
	ActionInterval* jump3 = JumpTo::create(0.2f, Vec2::ZERO, 60, 1);
	layer->runAction(Sequence::create(jump1, jump2, jump3, CallFunc::create([&](){menu->setEnabled(true); }), NULL));

	this->addChild(layer, 40);
}

void WelcomeScene::helpCallback(cocos2d::Ref* pSender)
{
	HowtoLayer* layer = HowtoLayer::create();
	layer->addMenu1();
	layer->setVisible(true);
	layer->listener->setEnabled(true);
	layer->setScale(0.95f);
	ActionInterval* big = ScaleTo::create(0.14f, 1.06f);
	ActionInterval* sma = ScaleTo::create(0.14f, 1.0f);
	layer->runAction(Sequence::create(big, sma, NULL));
	this->addChild(layer, 100);
}

void WelcomeScene::volumnCallback(cocos2d::Ref* pSender)
{
	if (((StageScene*)this->getParent())->bgmOn){
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		((StageScene*)this->getParent())->bgmOn = false;
	}
	else{
		playBGM();
		((StageScene*)this->getParent())->bgmOn = true;
	}
}

void WelcomeScene::aboutCallback(cocos2d::Ref* pSender)
{
	HowtoLayer* layer = HowtoLayer::create();
	layer->setbackground();
	layer->addMenu1();
	layer->setVisible(true);
	layer->listener->setEnabled(true);
	layer->setScale(0.95f);
	ActionInterval* big = ScaleTo::create(0.14f, 1.06f);
	ActionInterval* sma = ScaleTo::create(0.14f, 1.0f);
	layer->runAction(Sequence::create(big, sma, NULL));
	this->addChild(layer, 100);
}

void WelcomeScene::rankCallback(cocos2d::Ref* pSender)
{
	/*
	RankLayer* layer = RankLayer::create();
	layer->setPosition(Vec2(0, 968));
	layer->setAnchorPoint(Vec2::ZERO);

	menu->setEnabled(false);

	ActionInterval* jump1 = JumpTo::create(0.5f, Vec2::ZERO, 0, 1);
	ActionInterval* jump2 = JumpTo::create(0.4f, Vec2::ZERO, 150, 1);
	ActionInterval* jump3 = JumpTo::create(0.2f, Vec2::ZERO, 60, 1);
	layer->runAction(Sequence::create(jump1, jump2, jump3, CallFunc::create([&](){menu->setEnabled(true); }), NULL));

	this->addChild(layer, 40);
	*/
	Scene* scene = RankScene::createScene();
	Director::getInstance()->setDepthTest(true);
	TransitionScene* tran = TransitionPageTurn::create(1.5f, scene, false);
	Director::getInstance()->replaceScene(tran);
}


bool WelcomeScene::onTouchBegan(Touch* touch, Event* event)
{
	log("%s", FileUtils::getInstance()->getWritablePath().c_str());
	return true;
}

void WelcomeScene::onTouchEnded(Touch* touch, Event* event)
{
	log("ended1");
}

void WelcomeScene::playBGM()
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
