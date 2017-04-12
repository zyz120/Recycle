#include "GameLayer1.h"
#include "StageScene.h"
#include "Util.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

bool GameLayer1::init()
{
	if (!Layer::init()){
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	// init params
	random = (int)(CCRANDOM_0_1() * 10000) + 1;
	setPara(refreshTime, 300);
	m_count1 = 0;
	m_count2 = 0;
	speedCount = 0; // used for speed up function
	currentSpeed = 0;
	currentLevel = 0;
	pauseFlag = 0; 
	totalClickCount = 0;
	rightClickCount = 0;
	lastFrameTotal = 0;
	levelKind = new int[12]{1000, 100, 10, 1, 1000, 100, 10, 1000, 100, 10, 1};
	if (!UserDefault::getInstance()->getIntegerForKey("maxLevel", 0) > currentLevel)
		UserDefault::getInstance()->setIntegerForKey("maxLevel", 0);

	// background and label are set bellow
	Sprite* background = Sprite::create("gameScene/game_beijing.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(background, 0);

	recycle = Sprite::create("gameScene/game_zhuangtai_kehuishou_feidangqian.png");
	kitchen = Sprite::create("gameScene/game_zhuangtai_chuyu_feidangqian.png");
	harmful = Sprite::create("gameScene/game_zhuangtai_youhai_feidangqian.png");
	other = Sprite::create("gameScene/game_zhuangtai_qita_feidangqian.png");
	recycle->setPosition(Util::getPos(recycle, 36, 892));
	kitchen->setPosition(Util::getPos(kitchen, 130, 892));
	harmful->setPosition(Util::getPos(harmful, 224, 892));
	other->setPosition(Util::getPos(other, 318, 892));
	this->addChild(recycle, 1);
	this->addChild(kitchen, 1);
	this->addChild(harmful, 1);
	this->addChild(other, 1);
	recycle2 = Sprite::create("gameScene/game_zhuangtai_kehuishou_dangqian.png");
	kitchen2 = Sprite::create("gameScene/game_zhuangtai_chuyu_dangqian.png");
	harmful2 = Sprite::create("gameScene/game_zhuangtai_youhai_dangqian.png");
	other2 = Sprite::create("gameScene/game_zhuangtai_qita_dangqian.png");
	recycle2->setPosition(Util::getPos(recycle, 36, 892));
	kitchen2->setPosition(Util::getPos(kitchen, 130, 892));
	harmful2->setPosition(Util::getPos(harmful, 224, 892));
	other2->setPosition(Util::getPos(other, 318, 892));
	this->addChild(recycle2, 2);
	this->addChild(kitchen2, 2);
	this->addChild(harmful2, 2);
	this->addChild(other2, 2);

	// menu is set bellow
	MenuItemImage* btn_pause = MenuItemImage::create("gameScene/game_caidan_zanting_weixuanzhong.png",
		"gameScene/game_caidan_zanting_xuanzhong.png", CC_CALLBACK_0(GameLayer1::pauseGame, this));
	btn_pause->setPosition(Util::getPos(btn_pause, 26, 18));
	menu = Menu::create(btn_pause, NULL);
	menu->setPosition(Vec2::ZERO);
	menu->setAnchorPoint(Vec2::ZERO);
	this->addChild(menu, 2);


	// add touch event lisntener
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameLayer1::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameLayer1::onTouchEnded, this);

	dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// init the container and level
	container = BlockContainer::create();
	container->initBlankBlocks();
	container->setPosition(Vec2::ZERO);
	this->addChild(container, 2);
	container->initLevelBlocks(currentLevel);
	this->scheduleUpdate();
	kitchen2->setVisible(false);
	harmful2->setVisible(false);
	other2->setVisible(false);

	// add the label to show score
	currentScore = 0;
	scoreLabel = LabelTTF::create("0", "Futura Condensed.ttf", 80);
	scoreLabel->setColor(Color3B(0, 0, 0));
	scoreLabel->setPosition(Util::getPos(scoreLabel, 682, 0));
	this->addChild(scoreLabel, 2);
	char tempChar[10];
	itoa(UserDefault::getInstance()->getIntegerForKey("top", 0), tempChar, 10);
	topScore = LabelTTF::create(tempChar, "Futura Condensed.ttf", 60);
	topScore->setColor(Color3B(0, 0, 0));
	topScore->setPosition(Util::getPos(topScore, 1222, 4));
	this->addChild(topScore, 2);
	removable = LabelTTF::create("", "Futura Condensed.ttf", 60);
	itoa(container->total, tempChar, 10);
	removable->setString(tempChar);
	removable->setColor(Color3B(0, 0, 0));
	removable->setPosition(Util::getPos(topScore, 820, 882));
	this->addChild(removable, 2);
	accuracy = LabelTTF::create("0", "Futura Condensed.ttf", 50);
	accuracy->setColor(Color3B(0, 0, 0));
	accuracy->setPosition(Util::getPos(accuracy, 1250, 886));
	this->addChild(accuracy, 2);

	// howto layer init
	layer = HowtoLayer::create();
	layer->setAnchorPoint(Vec2(0.5, 0.5));
	layer->setPosition(Vec2(0, 0));
	layer->addMenu2();
	layer->setVisible(false);
	layer->listener->setEnabled(false);
	this->addChild(layer, 200);

	// gameOver layer init
	gameOverLayer = GameOverLayer::create();
	gameOverLayer->setVisible(false);
	gameOverLayer->listener->setEnabled(false);
	this->addChild(gameOverLayer, 200);
	gameOverLayer->initScores();

	return true;
}

bool GameLayer1::onTouchBegan(Touch* touch, Event* event)
{
	// get the coordinate of the touch point
	int tempX = ((int)touch->getLocation().y - 85) / 114;
	int tempY = ((int)touch->getLocation().x) / 114;
	bool flag = false;

	if (tempX >= 0 && tempX <= 6){

		bool ifContinue = judgeItem(6 - tempX, tempY);

		// judge
		if (ifContinue){
			flag = !container->blockMatrix[6 - tempX][tempY]->isAlive;
			if (flag)
				totalClickCount++;
			if (!container->blockMatrix[6 - tempX][tempY]->isAlive){
				container->blockMatrix[6 - tempX][tempY]->showStar();
			}
			int storeTotal = container->total;
			if (!container->judgeDestroyBlocks(6 - tempX, tempY, true)){ // fail to destroy blocks
				if (container->addFourBlocks(currentLevel, 4)){
					initNumber(removable, 1);
					testGameOver();
				}
				if (getPara(refreshTime) > 6){
					speedCount = 1 - speedCount;
					if (getPara(refreshTime) > 120){
						setPara(refreshTime, getPara(refreshTime) - 6);
					}
					else{
						setPara(refreshTime, getPara(refreshTime) - 3);
					}
					if (!speedCount)
						showSpeedUp();
				}
			}
			else{ // success to destroy blocks
				if (flag)
					rightClickCount++;
				UserDefault::getInstance()->setIntegerForKey("treeheight", UserDefault::getInstance()->getIntegerForKey("treeheight", 0) + (int)((currentLevel + 2) * (CCRANDOM_0_1())));
				addScore(storeTotal - container->total);
				addItem(storeTotal - container->total);
				if (!container->ifHasLeft()){
					nextLevel();
				}
			}
		}
		if (flag){
			initNumber(accuracy, 2);
			initNumber(removable, 1);
		}
	}
	return true;
}

void GameLayer1::onTouchEnded(Touch* touch, Event* event)
{
}


void GameLayer1::update(float dt)
{
	m_count1 = (m_count1 + 1) % getPara(refreshTime);
	m_count2 = (m_count2 + 1) % (600 + getPara(refreshTime) * 3);

	if (m_count1 == getPara(refreshTime) - 1){
		if (((StageScene*)this->getParent())->gameOn){
			container->addFourBlocks(currentLevel, 1);
			initNumber(removable, 1);
			testGameOver();
		}
	}
	if (m_count2 == 599 + getPara(refreshTime) * 3){
		if (getPara(refreshTime) > 12){
			if (getPara(refreshTime) < 120){
				setPara(refreshTime, getPara(refreshTime) - 6);
			}
			else {
				setPara(refreshTime, getPara(refreshTime) - 12);
			}
			showSpeedUp();
		}
	}
}

void GameLayer1::showSpeedUp()
{
	Sprite* speedUp = Sprite::create("gameScene/game_speedup.png");
	char score[10] = "";
	currentSpeed++;
	itoa(currentSpeed, score, 10);
	LabelTTF* scoreLabel = LabelTTF::create(score, "Futura Condensed.ttf", 59);
	scoreLabel->setColor(Color3B(0, 0, 0));
	scoreLabel->setAnchorPoint(Vec2::ZERO);
	scoreLabel->setPosition(240, 16);
	speedUp->addChild(scoreLabel);
	speedUp->setAnchorPoint(Vec2::ZERO);
	speedUp->setPosition(Vec2(1370, 800));
	this->addChild(speedUp, 3);

	ActionInterval* moveby1 = MoveBy::create(0.3f, Vec2(-346, 0));
	ActionInterval* breakTime = MoveBy::create(1.2f, Vec2(0, 0));
	ActionInterval* moveby2 = MoveBy::create(0.3f, Vec2(346, 0));

	speedUp->runAction(Sequence::create(moveby1, breakTime, moveby2, NULL));

}

void GameLayer1::nextLevel()
{
	float deltaTime = 0.45f;
	currentLevel++;

	if (currentLevel == 10)
		setPara(refreshTime, 36);

	if (!(UserDefault::getInstance()->getIntegerForKey("maxLevel", 0) > currentLevel))
		UserDefault::getInstance()->setIntegerForKey("maxLevel", currentLevel);

	MoveBy* move = MoveBy::create(deltaTime*7, Vec2(0, 0));
	this->runAction(Sequence::create(CallFunc::create([&](){ 
		menu->setEnabled(false);
		listener->setEnabled(false); 
		this->unscheduleUpdate();
		for (int i = 0; i < _ROW;i++)
		for (int j = 0; j < _COL; j++)
			container->blockMatrix[i][j]->dead();

	}), move, CallFunc::create([&](){
		container->initLevelBlocks(currentLevel);
		listener->setEnabled(true);
		menu->setEnabled(true);
		this->scheduleUpdate();
		initNumber(removable, 1);
	}), NULL));

	ActionInterval* moveIn = MoveBy::create(deltaTime, Vec2(1368, 0));
	ActionInterval* moveOut = MoveBy::create(deltaTime, Vec2(1368, 0));
	ActionInterval* moveDown11 = MoveTo::create(deltaTime, Vec2(0, 316));
	ActionInterval* moveDown12 = MoveTo::create(deltaTime, Vec2(0, 316));
	ActionInterval* moveDown13 = MoveTo::create(deltaTime, Vec2(0, 316));
	ActionInterval* moveDown1 = MoveTo::create(deltaTime, Vec2(0, -400));
	ActionInterval* moveDown2 = MoveTo::create(deltaTime, Vec2(0, -400));
	ActionInterval* moveDown3 = MoveTo::create(deltaTime, Vec2(0, -400));
	ActionInterval** moveDownArray = new ActionInterval*[4]();
	for (int i = 0; i < 4;i++)
		moveDownArray[i] = MoveTo::create(deltaTime, Vec2(0, -400));

	Sprite*	levelUpBg = Sprite::create("gameScene/game_guoguanbeijing.png");
	levelUpBg->setAnchorPoint(Vec2::ZERO);
	levelUpBg->setPosition(Vec2(-1368, 316));
	this->addChild(levelUpBg, 4);
	Sprite*	stage = Sprite::create("gameScene/game_stage.png");
	stage->setAnchorPoint(Vec2::ZERO);
	stage->setPosition(Vec2(0, 950));
	this->addChild(stage, 5);
	Sprite*	clear = Sprite::create("gameScene/game_clear.png");
	clear->setAnchorPoint(Vec2::ZERO);
	clear->setPosition(Vec2(0, 950));
	this->addChild(clear, 5);
	Sprite*	next = Sprite::create("gameScene/game_next.png");
	next->setAnchorPoint(Vec2::ZERO);
	next->setPosition(Vec2(0, 950));
	this->addChild(next, 5);

	levelUpBg->runAction(Sequence::create(moveIn, 
		MoveBy::create(deltaTime*6, Vec3::ZERO),moveOut, NULL));

	stage->runAction(Sequence::create(MoveBy::create(deltaTime, Vec3::ZERO), moveDown11,
		MoveBy::create(deltaTime * 5, Vec3::ZERO), moveDown1, NULL));

	clear->runAction(Sequence::create(MoveBy::create(deltaTime * 2, Vec3::ZERO), moveDown12,
		MoveBy::create(deltaTime * 4, Vec3::ZERO), moveDown2, NULL));

	next->runAction(Sequence::create(MoveBy::create(deltaTime * 3, Vec3::ZERO), moveDown13,
		MoveBy::create(deltaTime * 3, Vec3::ZERO), moveDown3, NULL));

	int r_check = levelKind[currentLevel] / 1000;
	int k_check = levelKind[currentLevel] % 1000 / 100;
	int h_check = levelKind[currentLevel] % 100 / 10;
	int o_check = levelKind[currentLevel] % 10;
	recycle2->setVisible(r_check);
	kitchen2->setVisible(k_check);
	harmful2->setVisible(h_check);
	other2->setVisible(o_check);
	int total_check = r_check + k_check + h_check + o_check;

	Sprite** tempIcons = new Sprite*[total_check];
	int count = 0;
	if (r_check) tempIcons[count++] = Sprite::create("gameScene/game_zhuangtai_kehuishou_white.png");
	if (k_check) tempIcons[count++] = Sprite::create("gameScene/game_zhuangtai_chuyu_white.png");
	if (h_check) tempIcons[count++] = Sprite::create("gameScene/game_zhuangtai_youhai_white.png");
	if (o_check) tempIcons[count++] = Sprite::create("gameScene/game_zhuangtai_qita_white.png");
	for (int i = 0; i < total_check; i++){
		tempIcons[i]->setPosition(Vec2(740 + 80 * i, 1000));
		this->addChild(tempIcons[i], 8);
	}
	for (int i = 0; i < total_check; i++){
		tempIcons[i]->runAction(Sequence::create(MoveBy::create(deltaTime * 3, Vec3::ZERO), MoveTo::create(deltaTime, Vec2(tempIcons[i]->getPositionX(), 386)),
			MoveBy::create(deltaTime * 3, Vec3::ZERO), moveDownArray[i], NULL));
	}
}

void GameLayer1::addScore(int n)
{
	int scoreToAdd = n * (currentLevel+1);
	setPara(currentScore, getPara(currentScore) + scoreToAdd);
	char score[10];
	char curScore[10];
	itoa(scoreToAdd, score, 10);
	itoa(getPara(currentScore), curScore, 10);
	std::string labelTextTemp(score);
	std::string plus = "+";
	std::string labelText = plus + labelTextTemp;


	LabelTTF* scoreAddLabel;
	if (n != 0)
		scoreAddLabel = LabelTTF::create(labelText, "Futura Condensed.ttf", 59);
	else
		scoreAddLabel = LabelTTF::create("", "Futura Condensed.ttf", 59);

	scoreAddLabel->setColor(Color3B(0, 0, 0));
	scoreAddLabel->setPosition(Util::getPos(scoreLabel, 680, 80));
	this->addChild(scoreAddLabel, 2);

	ActionInterval* moveUp = MoveBy::create(0.5f, Vec2(0, 80));
	ActionInterval* fadeOut = FadeOut::create(0.5f);

	scoreAddLabel->runAction(moveUp);
	scoreAddLabel->runAction(fadeOut);

	scoreLabel->setString(curScore);
}

void GameLayer1::testGameOver()
{
	int lastScore = UserDefault::getInstance()->getIntegerForKey("top", 0);
	if (lastScore < getPara(currentScore))
		UserDefault::getInstance()->setIntegerForKey("top", getPara(currentScore));
	if (container->total == _ROW*_COL){
		gameOverLayer->initScores();
		this->unscheduleUpdate();
		gameOverLayer->setVisible(true);
		gameOverLayer->setOpacity(255);
		gameOverLayer->listener->setEnabled(true);
		gameOverLayer->setScale(0.95f);
		ActionInterval* big = ScaleTo::create(0.14f, 1.06f);
		ActionInterval* sma = ScaleTo::create(0.14f, 1.0f);
		gameOverLayer->runAction(Sequence::create(big, sma, NULL));
	}
}

void GameLayer1::pauseGame()
{
	layer->setVisible(true);
	layer->listener->setEnabled(true);
	layer->setScale(0.95f);
	ActionInterval* big = ScaleTo::create(0.14f, 1.06f);
	ActionInterval* sma = ScaleTo::create(0.14f, 1.0f);
	layer ->runAction(Sequence::create(big, sma, NULL));
	changePauseState();

	/*
	// will be replaced !
	*/
}

void GameLayer1::changePauseState()
{
	if (!pauseFlag){
		listener->setEnabled(false);
		this->unscheduleUpdate();
		pauseFlag = 1;
	}
	else{
		pauseFlag = 0;
		listener->setEnabled(true);
		this->scheduleUpdate();
	}
}

void GameLayer1::initNumber(LabelTTF* label, int flag) //flag   1-removable  2-accuracy
{
	if (flag == 1){
			char tempChar[10];
			itoa(container->getTotal(), tempChar, 10);
			label->setString(tempChar);
	}
	else if (flag == 2){
		char tempRight[13];
		itoa(rightClickCount, tempRight, 10);
		char tempTotal[6];
		itoa(totalClickCount, tempTotal, 10);
		strcat(tempRight, "/");
		strcat(tempRight, tempTotal);
		label->setString(tempRight);
	}
	ActionInterval* big = ScaleTo::create(0.14f, 1.2f);
	ActionInterval* sma = ScaleTo::create(0.14f, 1.0f);
	label->runAction(Sequence::create(big, sma, NULL));
}

void GameLayer1::initLevel()
{
	// params init
	random = (int)(CCRANDOM_0_1() * 10000) + 1;
	setPara(refreshTime, 300);
	m_count1 = 0;
	m_count2 = 0;
	speedCount = 0;
	currentSpeed = 0;
	currentLevel = 0;
	totalClickCount = 0;
	rightClickCount = 0;
	lastFrameTotal = 0;
	pauseFlag = 0;
	currentScore = 0;

	// howto layer close
	layer->setVisible(false);
	layer->listener->setEnabled(false);

	// init blocks
	container->initLevelBlocks(0);
	this->scheduleUpdate();

	// init LabelTTFs
	char tempString[15];
	itoa(0, tempString, 10);
	scoreLabel->setString(tempString);
	accuracy->setString(tempString);
	itoa(container->total, tempString, 10);
	removable->setString(tempString);
	itoa(UserDefault::getInstance()->getIntegerForKey("top"), tempString, 10);
	topScore->setString(tempString);

	// init icons
	recycle2->setVisible(1);
	kitchen2->setVisible(0);
	harmful2->setVisible(0);
	other2->setVisible(0);
}

void GameLayer1::setPara(int &res, int val)
{
	res = random*val;
}

int GameLayer1::getPara(int res)
{
	int result = res / random;
	return result;
}

bool GameLayer1::judgeItem(int x, int y)
{
	bool res = true;
	std::string kind = container->blockMatrix[x][y]->kind;
	if (kind == "1.")
	{
		currentSpeed -= 2;
		if (currentSpeed < 1)
			currentSpeed = 0;
		showSpeedUp();
		int refres = getPara(refreshTime);
		setPara(refreshTime, refres + 6);
		if (refres > 288)
			setPara(refreshTime, 300);
		container->blockMatrix[x][y]->deadItem();
		res = false;
	}
	else if (kind == "2.")
	{
		currentSpeed -= 3;
		if (currentSpeed < 1)
			currentSpeed = 0;
		showSpeedUp();
		int refres = getPara(refreshTime);
		setPara(refreshTime, refres + 12);
		if (refres > 276)
			setPara(refreshTime, 300);
		container->blockMatrix[x][y]->deadItem();
		res = false;
	}
	else if (kind == "3.")
	{
		currentSpeed -= 4;
		if (currentSpeed < 1)
			currentSpeed = 0;
		showSpeedUp();
		int refres = getPara(refreshTime);
		setPara(refreshTime, refres + 18);
		if (refres > 264)
			setPara(refreshTime, 300);
		container->blockMatrix[x][y]->deadItem();
		res = false;
	}
	else if (kind == "4.")
	{
		currentSpeed -= 5;
		if (currentSpeed < 1)
			currentSpeed = 0;
		showSpeedUp();
		int refres = getPara(refreshTime);
		setPara(refreshTime, refres + 24);
		if (refres > 252)
			setPara(refreshTime, 300);
		container->blockMatrix[x][y]->deadItem();
		res = false;
	}
	else if (kind == "C.")
	{
		int flag = 2000;
		int count = (int)(container->total*0.25);

		for (int i = 0; i < count && flag > 0;){
			int tempX = (int)(CCRANDOM_0_1()*(_ROW - 1));
			int tempY = (int)(CCRANDOM_0_1()*(_COL - 1));
			if (container->blockMatrix[tempX][tempY]->isAlive){
				container->blockMatrix[tempX][tempY]->dead();				
				i++;
			}
			flag--;
		}
		container->blockMatrix[x][y]->deadItem();
		addScore(count * (currentLevel + 1));
		testGameOver();
		res = false;
	}
	if (!res){
		initNumber(removable, 1);
	}
	return res;
}

void GameLayer1::addItem(int para)
{
	std::string itemName[14] = { "1", "1", "1", "1", "1", "1", "1", "1", "1", "C", "2", "3", "4", "C" };
	
	int flag = (int)(CCRANDOM_0_1() * 100);
	int num = (int)(CCRANDOM_0_1() * 13.99);
	int rate = 0;
	switch (para)
	{		
	case 2:
		rate = 97;
		break;
	case 3:
		rate = 90;
		break;
	case 4:
		rate = 80;
		break;
	default:
		rate = 99;
		break;
	}
	if (flag > rate){
		container->addItem("I_" + itemName[num] + ".png");
	}
}