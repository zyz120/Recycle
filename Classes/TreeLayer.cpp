#include "TreeLayer.h"
#include "Util.h"
USING_NS_CC;

bool TreeLayer::init()
{
	if (!Layer::init()){
		return false;
	}

	// set the background
	background = Sprite::create("treeLayer/forest_beijing.png");
	background->setPosition(Vec2::ZERO);
	background->setAnchorPoint(Vec2::ZERO);
	this->addChild(background, 1);
	highTree = Sprite::create("treeLayer/forest.png");
	highTree->setPosition(Vec2(0, 968));
	highTree->setAnchorPoint(Vec2::ZERO);
	this->addChild(highTree, 2);
	space = Sprite::create("treeLayer/space.png");
	space->setPosition(Vec2::ZERO);
	space->setOpacity(0);
	space->setAnchorPoint(Vec2::ZERO);
	this->addChild(space, 1);

	land1 = Sprite::create("treeLayer/land.png");
	land1->setAnchorPoint(Vec2::ZERO);
	land1->setPosition(Vec2(200, 105));
	this->addChild(land1, 0);
	land2 = Sprite::create("treeLayer/land.png");
	land2->setAnchorPoint(Vec2::ZERO);
	land2->setPosition(Vec2(200 - 851, 105));
	this->addChild(land2, 0);

	// set the menu
	MenuItemImage* back = MenuItemImage::create("treeLayer/forest_back_weixuanzhong.png", "treeLayer/forest_back_xuanzhong.png",
		CC_CALLBACK_0(TreeLayer::backClick, this));
	back->setPosition(Util::getPos(back, 88, 88));
	MenuItemImage* trueTree = MenuItemImage::create("treeLayer/forest_truetree_weixuanzhong.png", "treeLayer/forest_truetree_xuanzhong.png",
		CC_CALLBACK_0(TreeLayer::trueTreeClick, this));
	trueTree->setPosition(Util::getPos(trueTree, 88, 752));
	MenuItemImage* higher = MenuItemImage::create("treeLayer/forest_higher_weixuanzhong.png", "treeLayer/forest_higher_xuanzhong.png",
		CC_CALLBACK_0(TreeLayer::higherClick, this));
	higher->setPosition(Util::getPos(higher, 1087, 88));

	menu = Menu::create(back, trueTree, higher, NULL);
	menu->setAnchorPoint(Vec2::ZERO);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 2);

	// init params
	landSpeed = 3;
	char height[10];
	itoa(UserDefault::getInstance()->getIntegerForKey("treeheight", 0), height, 10);
	treeHeight = LabelTTF::create(height, "Futura Condensed.ttf", 60);
	treeHeight->setColor(Color3B(80, 80, 80));
	treeHeight->setPosition(Util::getPos(treeHeight, 1135, 810));
	this->addChild(treeHeight, 2);

	// init tree
	int tempHeight = UserDefault::getInstance()->getIntegerForKey("treeheight", 0);
	std::string treeLevel = "1";
	if (tempHeight < 800)
		treeLevel = "1";
	else if (tempHeight < 2000)
		treeLevel = "2";
	else if (tempHeight < 4000)
		treeLevel = "3";
	else if (tempHeight >= 4000)
		treeLevel = "4";

	tree = Sprite::create("treeLayer/forest_tree" + treeLevel + ".png");
	tree->setContentSize(Size(571, 890));
	tree->setPosition(Util::getPos(tree, 386, 0));
	this->addChild(tree, 2);

	// set swallow touch
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(TreeLayer::onTouchBegan, this);
	listener->setSwallowTouches(true);
	EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// init true tree layer
	background2 = Sprite::create("treeLayer/turetree_bg.png");
	background2->setAnchorPoint(Vec2::ZERO);
	background2->setPosition(Vec2::ZERO);
	background2->setOpacity(0);
	this->addChild(background2, 20);
	MenuItemImage* forest = MenuItemImage::create("treeLayer/truetree_forest_weixuanzhong.png", "treeLayer/truetree_forest_xuanzhong.png",
		CC_CALLBACK_0(TreeLayer::forestClick, this));
	forest->setPosition(Util::getPos(forest, 88, 752));
	MenuItemImage* back2 = MenuItemImage::create("treeLayer/forest_back_weixuanzhong.png", "treeLayer/forest_back_xuanzhong.png",
		CC_CALLBACK_0(TreeLayer::backClick, this));
	back2->setPosition(Util::getPos(back2, 88, 88));
	menu2 = Menu::create(forest, back2, NULL);
	menu2->setAnchorPoint(Vec2::ZERO);
	menu2->setPosition(Vec2::ZERO);
	menu2->setEnabled(false);
	menu2->setOpacity(0);
	this->addChild(menu2, 21);

	// init lower menu
	MenuItemImage* lower = MenuItemImage::create("treeLayer/forest_lower_weixuanzhong.png", "treeLayer/forest_lower_xuanzhong.png",
		CC_CALLBACK_0(TreeLayer::lowerClick, this));
	lower->setPosition(Util::getPos(lower, 1087, 88));
	menu3 = Menu::create(lower, NULL);
	menu3->setAnchorPoint(Vec2::ZERO);
	menu3->setPosition(Vec2::ZERO);
	menu3->setEnabled(false);
	menu3->setOpacity(0);
	this->addChild(menu3, 3);

	this->scheduleUpdate();
	return true;
}

void TreeLayer::backClick()
{
	// will be replaced !
	ActionInterval* moveOut = MoveBy::create(1.0f, Vec2(1376, 0));
	land1->setPosition(Vec2(300, 105));
	land2->setPosition(Vec2(300, 105));
	this->runAction(Sequence::create(moveOut, 
		CallFunc::create([&](){ this->setVisible(false); listener->setEnabled(false);  }), NULL));
}

void TreeLayer::trueTreeClick()
{
	ActionInterval* fadeIn = FadeIn::create(0.6f);
	menu2->runAction(fadeIn->clone());
	menu->setEnabled(false);
	background2->runAction(Sequence::create(fadeIn, CallFunc::create([&]()
	{
		menu2->setEnabled(true);
	}), NULL));
}

void TreeLayer::higherClick()
{
	int tempHeight = UserDefault::getInstance()->getIntegerForKey("treeheight", 0);
	if (tempHeight > 3999)
	{
		ActionInterval* fadeIn = FadeIn::create(1.2f);
		ActionInterval* fadeOut = FadeOut::create(1.2f);
		ActionInterval* moveDown = MoveBy::create(1.2f, Vec2(0, -968));
		tree->runAction(moveDown);
		highTree->runAction(moveDown->clone());
		background->runAction(moveDown->clone());
		land1->runAction(moveDown->clone());
		land2->runAction(moveDown->clone());
		treeHeight->runAction(fadeOut);
		space->runAction(fadeIn);
		menu->runAction(fadeOut->clone());
		menu->setEnabled(false);
		menu3->runAction(Sequence::create(fadeIn->clone(), CallFunc::create([&]()
		{
			menu3->setEnabled(true);
		}), NULL));
	}
}

bool TreeLayer::onTouchBegan(Touch* touch, Event* e)
{
	return true;
}

void TreeLayer::forestClick()
{
	ActionInterval* fadeOut = FadeOut::create(0.6f);
	background2->runAction(fadeOut);
	menu2->setEnabled(false);
	menu2->runAction(Sequence::create(fadeOut->clone(), CallFunc::create([&]()
	{
		menu->setEnabled(true);
	}), NULL));
}

void TreeLayer::lowerClick()
{
	ActionInterval* fadeIn = FadeIn::create(1.2f);
	ActionInterval* fadeOut = FadeOut::create(1.2f);
	ActionInterval* moveUp = MoveBy::create(1.2f, Vec2(0, 968));
	tree->runAction(moveUp);
	background->runAction(moveUp->clone());
	highTree->runAction(moveUp->clone());
	land1->runAction(moveUp->clone());
	land2->runAction(moveUp->clone());
	treeHeight->runAction(fadeIn);
	space->runAction(fadeOut);
	menu->runAction(fadeIn->clone());
	menu3->setEnabled(false);
	menu3->runAction(Sequence::create(fadeOut->clone(), CallFunc::create([&]()
	{
		menu->setEnabled(true);
	}), NULL));
}

void TreeLayer::update(float dt)
{
	ActionInterval* moveRight = MoveBy::create(0.1f, Vec2(landSpeed, 0));
	
	land1->runAction(moveRight);
	land2->runAction(moveRight->clone());

	if (land1->getPositionX() > 1000)
		land1->setPositionX(-651);
	if (land2->getPositionX() > 1000)
		land2->setPositionX(-651);
}