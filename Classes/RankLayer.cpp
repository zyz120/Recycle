#include "RankLayer.h"
#include "Util.h"
#include <thread>
USING_NS_CC;

bool RankLayer::init()
{
	if (!Layer::init()){
		return false;
	}

	// set background and decoration
	background = Sprite::create("rankLayer/rank_bg.png");
	background->setAnchorPoint(Vec2::ZERO);
	background->setPosition(Vec2::ZERO);
	this->addChild(background, 0);

	star = Sprite::create("rankLayer/star.png");
	star->setPosition(Vec2(695, 240));
	ActionInterval* rotate = RotateBy::create(6.0f, 359);
	RepeatForever* repeat = RepeatForever::create(rotate);
	star->runAction(repeat);
	this->addChild(star, 1);

	// set menu
	MenuItemImage* back = MenuItemImage::create("rankLayer/rank_back_weixuanzhong.png",
		"rankLayer/rank_back_xuanzhong.png", CC_CALLBACK_0(RankLayer::backToWelcome, this));
	back->setPosition(Util::getPos(back, 88, 50));
	Menu* menu = Menu::create(back, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	// set swallow touches
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(RankLayer::onTouchBegan, this);
	listener->setSwallowTouches(true);

	EventDispatcher* dispathcer = Director::getInstance()->getEventDispatcher();
	dispathcer->addEventListenerWithSceneGraphPriority(listener, this);

	// init LabelTTFs
	for (int i = 0; i < 3; i++){
		names[i] = LabelTTF::create("", "Futura Condensed.ttf", 80);
		names[i]->setColor(Color3B(0, 0, 0));
		names[i]->setPosition(Vec2(490, 360 + 150 * i));
		this->addChild(names[i], 1);
		scores[i] = LabelTTF::create("", "Futura Condensed.ttf", 80);
		scores[i]->setColor(Color3B(0, 0, 0));
		scores[i]->setPosition(Vec2(890, 360 + 150 * i));
		this->addChild(scores[i], 1);
	}
	char temp[8];
	itoa(UserDefault::getInstance()->getIntegerForKey("top"), temp, 10);
	myScore = LabelTTF::create("", "Futura Condensed.ttf", 80);
	myScore->setColor(Color3B(0, 0, 0));
	myScore->setPosition(Vec2(700, 85));
	myScore->setString(temp);
	this->addChild(myScore, 1);
	failLabel = LabelTTF::create("Fail to connect to the server...", "Futura Condensed.ttf", 100);
	failLabel->setOpacity(0);
	failLabel->setColor(Color3B(0, 0, 0));
	failLabel->setPosition(Vec2(700, 520));
	this->addChild(failLabel, 1);

	connect();

	return true;
}

void RankLayer::backToWelcome()
{
	ActionInterval* moveOut = MoveBy::create(1.0f, Vec2(1368, 0));
	this->runAction(Sequence::create(moveOut, CallFunc::create([&]()
	{
		this->setVisible(false);
		listener->setEnabled(false);
	}), NULL));
}

bool RankLayer::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}

void RankLayer::connect()
{
	socket.Init();
	socket.Create(AF_INET, SOCK_STREAM, 0);

	const char* ip = "223.3.161.93";
	int port = 12320;
	bool result = false;
	for (int i = 0; i < 1; i++){
		result = socket.Connect(ip, port);
		if (result)
			break;
	}
	socket.Send("Hello", 1);

	if (result){
		std::thread recvThread = std::thread(&RankLayer::receiveData, this);
		recvThread.detach();
	}
	else{
		background->setTexture("rankLayer/rank2_bg.png");
		failLabel->setOpacity(255);
		return;
	}
}

void RankLayer::receiveData()
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
			while (p != NULL && f < 6) {
				if (!(f & 1))
					scores[f / 2]->setString(p);
				else
					names[f / 2]->setString(p);
				f++;
				p = strtok(NULL, split);
			}
			// 关闭连接
			if (i == flag - 1)
				socket.Close();
		}
	}
}

