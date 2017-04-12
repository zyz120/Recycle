#include "RankScene.h"
#include "Util.h"
#include "StageScene.h"
USING_NS_CC;

std::string datas[12];
int count = 0;
float scaleParas[6] = { 0.8f, 0.85f, 0.9f, 0.95f, 1.0f, 1.1f };
float scalePara = 0.8f;

bool RankScene::init()
{
	if (!Layer::init()){
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();

	// init background
	Sprite* background = Sprite::create("rankLayer/bg.png");
	background->setAnchorPoint(Vec2::ZERO);
	background->setPosition(Vec2::ZERO);
	this->addChild(background, 0); 
	auto body = PhysicsBody::createEdgeBox(Size(1232, 720), PHYSICSSHAPE_MATERIAL_DEFAULT, 1);
	body->getShape(0)->setRestitution(0.8f);
	body->getShape(0)->setFriction(0);
	body->getShape(0)->setDensity(1.0f);	
	auto edgeShape = Node::create();
	edgeShape->setPhysicsBody(body);
	edgeShape->setPosition(visibleSize.width / 2,  visibleSize.height / 2 - 20);
	edgeShape->setAnchorPoint(Vec2::ZERO);
	this->addChild(edgeShape);
	star = Sprite::create("rankLayer/star.png");
	star->setPosition(Vec2(600, 55));
	ActionInterval* rotate = RotateBy::create(6.0f, 359);
	RepeatForever* repeat = RepeatForever::create(rotate);
	star->runAction(repeat);
	this->addChild(star, 1);
	char temp[8];
	itoa(UserDefault::getInstance()->getIntegerForKey("top"), temp, 10);
	myScore = LabelTTF::create("", "Futura Condensed.ttf", 80);
	myScore->setColor(Color3B(0, 0, 0));
	myScore->setPosition(Vec2(700, 55));
	myScore->setString(temp);
	this->addChild(myScore, 1);


	for (int i = 0; i < 12; i++){
		labels[i] = LabelTTF::create("", "Futura Condensed.ttf", 50);
		labels[i]->setColor(Color3B(255, 255, 255));		
		this->addChild(labels[i], 10);
	}
	
	// set swallow touches
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(RankScene::onTouchBegan, this);
	EventDispatcher* dispathcer = Director::getInstance()->getEventDispatcher();
	dispathcer->addEventListenerWithSceneGraphPriority(listener, this);
	
	MenuItemImage* back = MenuItemImage::create("rankLayer/rank_back_weixuanzhong.png",
		"rankLayer/rank_back_xuanzhong.png", CC_CALLBACK_0(RankScene::backToWelcome, this));
	back->setPosition(Util::getPos(back, 68, 25));
	Menu* menu = Menu::create(back, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	addPopPara = 0;
	
	connect();
	addPops();

	this->scheduleUpdate();

	return true;
}

Scene* RankScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto layer = RankScene::create();

	scene->addChild(layer, 0);

	return scene;
}


void RankScene::connect()
{
	socket.Init();
	socket.Create(AF_INET, SOCK_STREAM, 0);

	const char* ip = "223.3.30.176";
	int port = 12320;
	bool result = false;
	for (int i = 0; i < 1; i++){
		result = socket.Connect(ip, port);
		if (result)
			break;
	}
	socket.Send("Hello", 1);

	if (result){
		log("success");
		std::thread recvThread = std::thread(&RankScene::receiveData, this);
		recvThread.detach();
	}
	else{
		for (int i = 0; i < 12; i++){
			if (i % 2)
				labels[i]->setString("connect");
			else
				labels[i]->setString("failed");
		}
		return;
	}
}

void RankScene::receiveData()
{
	int flag = 1;
	for (int i = 0; i < flag; i++){
		// 接收数据 Recv
		char data[128] = "";
		int result = socket.Recv(data, 128, 0);

		// 与服务器的连接断开了
		if (result){
			int f = 0;
			const char * split = ",";
			char * p;
			log("%s", data);
			
			p = strtok(data, split);
			while (p != NULL && f < 12) {
				datas[f] = p;	
				labels[f]->setString(p);
				f++;
				p = strtok(NULL, split);				
			}
			// 关闭连接
			if (i == flag - 1)
				socket.Close();
		}
	}
}

void RankScene::addPops()
{
	for (int i = 0; i < 6; i++){
		pops[i] = Sprite::create("rankLayer/whiteBall.png");
		pops[i]->setScale(scaleParas[i]);
		pops[i]->setColor(Color3B(CCRANDOM_0_1() * 255, CCRANDOM_0_1() * 255, CCRANDOM_0_1() * 255));
		// ------------------------------------------------------------------------------------------
		PhysicsBody* body = PhysicsBody::createCircle(126 * scaleParas[i]);
		body->getShape(0)->setRestitution(0.9f);
		body->getShape(0)->setFriction(0);
		body->getShape(0)->setDensity(1.0f);
		body->setGravityEnable(false);

		body->setCategoryBitmask(0x0001);
		body->setCollisionBitmask(0x0001);
		body->setContactTestBitmask(0x0001);

		pops[i]->setPhysicsBody(body);
		if (i % 2){
			body->setVelocity(Vect(600, -400 + 200 * ((i+1)/2)));
			pops[i]->setPosition(Vec2(100 + CCRANDOM_0_1() * 50, -50 + 270 * (i+1)/2));
		}
		else{
			body->setVelocity(Vect(-600, -400 + 200 * ((i + 1) / 2)));
			pops[i]->setPosition(Vec2(visibleSize.width - (100 + CCRANDOM_0_1() * 50), -50 + 270 * (i / 2 + 1)));
		}
		this->addChild(pops[i], 8);
		// ------------------------------------------------------------------------------------------
	}	
}

void RankScene::update(float dt)
{
	for (int i = 0; i < 6; i++){
		labels[2 * i]->setPosition(Vec2(pops[i]->getPositionX(), pops[i]->getPositionY() - 28));
		labels[2 * i + 1]->setPosition(Vec2(pops[i]->getPositionX(), pops[i]->getPositionY() + 28));
	}
	addPopPara++;
	if (addPopPara >= 100 && addPopPara <= 6 * 24 + 100 && addPopPara % 6 == 0)
		addAPop(addPopPara / 6 % 2);

}

bool RankScene::onTouchBegan(Touch* touch, Event* event)
{
	for (int i = 0; i < 6; i++){
		if (pops[i]->getBoundingBox().containsPoint(touch->getLocation())){
			pops[i]->runAction(Sequence::create(ScaleBy::create(0.1f, 1.2f), ScaleTo::create(0.1f, scaleParas[i]), NULL));
		}
	}
	return true;
}

void RankScene::addAPop(int type)
{
	Sprite* pop = Sprite::create("rankLayer/whiteBall.png");
	float scaleRate = scalePara * (CCRANDOM_0_1() * 0.5f) + 0.3f;
	pop->setScale(scaleRate);
	pop->setColor(Color3B(CCRANDOM_0_1() * 255, CCRANDOM_0_1() * 255, CCRANDOM_0_1() * 255));
	// ------------------------------------------------------------------------------------------
	PhysicsBody* body = PhysicsBody::createCircle(126 * scaleRate);
	body->getShape(0)->setRestitution(0.9f);
	body->getShape(0)->setFriction(0);
	body->getShape(0)->setDensity(1.0f);
	body->setGravityEnable(false);

	body->setCategoryBitmask(0x0001);
	body->setCollisionBitmask(0x0001);
	body->setContactTestBitmask(0x0001);

	pop->setPhysicsBody(body);
	if (type % 2){
		body->setVelocity(Vect(600, -400 + CCRANDOM_0_1() * 200 ));
		pop->setPosition(Vec2(100 + CCRANDOM_0_1() * 50, CCRANDOM_0_1() * 500 + 200));
	}
	else{
		body->setVelocity(Vect(-600, -400 + CCRANDOM_0_1() * 200));
		pop->setPosition(Vec2(visibleSize.width - (100 + CCRANDOM_0_1() * 50), CCRANDOM_0_1() * 500 + 200));
	}
	this->addChild(pop, 8);
}

void RankScene::backToWelcome()
{
	Scene* scene = StageScene::createScene();
	Director::getInstance()->setDepthTest(true);
	TransitionScene* tran = TransitionPageTurn::create(1.5f, scene, false);
	Director::getInstance()->replaceScene(tran);
}