#include "ChooseLayer.h"
#include "Util.h"
#include "CollectionLayer.h"
USING_NS_CC;

bool ChooseLayer::init()
{
	if (!Layer::init()){
		return false;
	}

	// set background
	Sprite* background = Sprite::create("collectionLayer/kapai_background.png");
	background->setAnchorPoint(Vec2::ZERO);
	background->setPosition(Vec2::ZERO);
	this->addChild(background, 0);

	// set menu btn
	MenuItemImage* back = MenuItemImage::create("collectionLayer/back_weixuanzhong.png",
		"collectionLayer/back_xuanzhong.png", CC_CALLBACK_0(ChooseLayer::backToWelcome, this));
	back->setPosition(Util::getPos(back, 88, 88));
	MenuItemImage* recycle = MenuItemImage::create("collectionLayer/kapai_sy_kehuishou.png",
		"collectionLayer/kapai_sy_kehuishou_pressed.png", CC_CALLBACK_0(ChooseLayer::toCardLayer1, this));
	recycle->setPosition(Util::getPos(recycle, 207, 346));
	MenuItemImage* kitchen = MenuItemImage::create("collectionLayer/kapai_sy_chuyu.png",
		"collectionLayer/kapai_sy_chuyu_pressed.png", CC_CALLBACK_0(ChooseLayer::toCardLayer2, this));
	kitchen->setPosition(Util::getPos(kitchen, 454, 346));
	MenuItemImage* harmful = MenuItemImage::create("collectionLayer/kapai_sy_youhai.png",
		"collectionLayer/kapai_sy_youhai_pressed.png", CC_CALLBACK_0(ChooseLayer::toCardLayer3, this));
	harmful->setPosition(Util::getPos(harmful, 702, 346));
	MenuItemImage* other = MenuItemImage::create("collectionLayer/kapai_sy_qita.png",
		"collectionLayer/kapai_sy_qita_pressed.png", CC_CALLBACK_0(ChooseLayer::toCardLayer4, this));
	other->setPosition(Util::getPos(other, 954, 346));

	Menu* menu = Menu::create(back, recycle, kitchen, harmful, other, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	// set swallow touches
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(ChooseLayer::onTouchBegan, this);
	listener->setSwallowTouches(true);

	EventDispatcher* dispathcer = Director::getInstance()->getEventDispatcher();
	dispathcer->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void ChooseLayer::backToWelcome()
{
	ActionInterval* moveOut = MoveBy::create(1.0f, Vec2(1368, 0));
	this->runAction(Sequence::create(moveOut, CallFunc::create([&]()
	{
		this->setVisible(false);
		listener->setEnabled(false);
	}), NULL));
}

void ChooseLayer::toCardLayer1()
{
	CollectionLayer* layer = CollectionLayer::create();
	layer->setPosition(Vec2(1368, 0));
	this->addChild(layer, 2);
	layer->initNodes1();
	ActionInterval* moveOut = MoveBy::create(1.0f, Vec2(-1368, 0));
	layer->runAction(moveOut);
}
void ChooseLayer::toCardLayer2()
{
	CollectionLayer* layer = CollectionLayer::create();
	layer->setPosition(Vec2(1368, 0));
	this->addChild(layer, 2);
	layer->initNodes2();
	ActionInterval* moveOut = MoveBy::create(1.0f, Vec2(-1368, 0));
	layer->runAction(moveOut);
}
void ChooseLayer::toCardLayer3()
{
	CollectionLayer* layer = CollectionLayer::create();
	layer->setPosition(Vec2(1368, 0));
	this->addChild(layer, 2);
	layer->initNodes3();
	ActionInterval* moveOut = MoveBy::create(1.0f, Vec2(-1368, 0));
	layer->runAction(moveOut);
}
void ChooseLayer::toCardLayer4()
{
	CollectionLayer* layer = CollectionLayer::create();
	layer->setPosition(Vec2(1368, 0));
	this->addChild(layer, 2);
	layer->initNodes4();
	ActionInterval* moveOut = MoveBy::create(1.0f, Vec2(-1368, 0));
	layer->runAction(moveOut);
}

bool ChooseLayer::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}