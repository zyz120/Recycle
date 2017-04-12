#include "CollectionLayer.h"
#include "Util.h"
USING_NS_CC;

std::string tempString[40] = {
"1_R_bolilei.png", "1_R_feizhilei.png", "1_R_jinshulei.png", "1_R_niunaihe.png",
"1_R_suliaolei.png", "1_R_yilaguan.png", "1_R_zhiwu.png", "1_R_luomao.png",
"2_K_caigengcaiye.png", "2_K_canzhibaiye.png", "2_K_gugeneizang.png", "2_K_guopi.png",
"2_K_shengcaishengfan.png", "2_K_beike.png", "2_K_danke.png", "2_K_xiguapi.png",
"3_H_feidengpao.png", "3_H_feidianchi.png", "3_H_feishouji.png", "3_H_guoqiyaopin.png",
"3_H_shachongji.png", "3_H_youqitong.png", "3_H_youqishua.png", "3_H_xiangshui.png",
"4_O_huitu.png", "4_O_huitusaozhou.png", "4_O_juanzhi.png", "4_O_pocipan.png",
"4_O_poguanzi.png", "4_O_wushui.png", "4_O_yandi.png", "4_O_yicixingcanju.png",
"1_R_shubao.png", "1_R_jingzi.png", "2_K_gutou.png", "2_K_xiangjiaopi.png",
"3_H_kouhong.png", "3_H_piaobaiji.png", "4_O_dongwufenbian.png", "4_O_yanhe.png"
};

std::string introString[41] = {
	"回收一个玻璃瓶所节省的能量，大约可以让一个一百瓦的灯泡点亮四个小时　", // 0
	"用可再生纸制作的纸制品，不仅有一种独特的麻质感，更能有效减少树木的砍伐　 ",
	"金属类，填埋和焚烧会污染土壤和水源，请合理回收利用　",
	"牛奶盒竟然也是可回收垃圾，这点要好好记住啊　",
	"塑料瓶可以抽丝成纱线，变身为服装面料，也可以制作垃圾袋　",
	"金属类，多为铝制品，回收后可以制作自行车　",
	"回收的不止是花费大量资源加工的织物，更是一份给需要帮助的人简单又暖心的爱　",
	"金属类，填埋和焚烧会污染土壤和水源，请合理回收利用　",
	"剩菜叶　", // 8
	"残枝败叶　",
	"鱼骨头　",
	"果皮　",
	"剩饭　",
	"贝壳　",
	"鸡蛋壳　",
	"西瓜皮　",
	"废灯泡　", // 16
	"废电池　",
	"旧手机　",
	"药品　",
	"杀虫剂　",
	"油漆桶　",
	"油漆刷　",
	"香水瓶　",
	"灰土　", // 24
	"旧扫把　",
	"纸巾　",
	"碎盘子　",
	"破瓷罐　",
	"污水　",
	"烟蒂　",
	"一次性餐具　",
	"书包　", // 32
	"镜子　",
	"骨头　",
	"香蕉皮　",
	"口红　",
	"洗衣液　",
	"宠物粪便　",
	"香烟盒　",
	"尚未回收此类垃圾　" // 40
};


bool CollectionLayer::init()
{
	if (!Layer::init()){
		return false;
	}

	// init params
	speed = 2;
	chosenCard = NULL;

	// set two background pictures
	background1 = Sprite::create("collectionLayer/kapai_bg_kehuishou.png");
	background2 = Sprite::create("collectionLayer/kapai_bg_kehuishou.png");
	background1->setAnchorPoint(Vec2::ZERO);
	background1->setPosition(Vec2::ZERO);
	background2->setAnchorPoint(Vec2::ZERO);
	background2->setPosition(Vec2(0, 960));
	this->addChild(background1, 10);
	this->addChild(background2, 10);



	// set swallow touches
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(CollectionLayer::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(CollectionLayer::onTouchEnded, this);
	listener->setSwallowTouches(true);

	EventDispatcher* dispathcer = Director::getInstance()->getEventDispatcher();
	dispathcer->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();
	
	// set blank card
	for (int i = 0; i < _TOTAL_CARD; i++)
	{
		int tempI = i % 5;
		cards[i] = Card::create();
		cards[i]->setAnchorPoint(Vec2::ZERO);
		cards[i]->setPosition(Vec2(94.6f*(tempI + 1) + tempI * 160, 600 / (i / 5 + 1)));
		this->addChild(cards[i], 12);
	}

	Sprite* intro = Sprite::create("collectionLayer/kapai_introduction.png");
	intro->setAnchorPoint(Vec2::ZERO);
	intro->setPosition(Vec2(259, 80));
	this->addChild(intro, 12);

	// set menu item
	MenuItemImage* back = MenuItemImage::create("collectionLayer/back_weixuanzhong.png",
		"collectionLayer/back_xuanzhong.png", CC_CALLBACK_0(CollectionLayer::closeThisLayer, this));
	back->setPosition(Util::getPos(back, 88, 50));
	Menu* menu = Menu::create(back, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 12);

	// set introdution sprite and label
	lb_intro = LabelTTF::create("", "YouYuan", 28);
	lb_intro->setDimensions(Size(600, 200));
	lb_intro->setColor(Color3B(0, 0, 0));
	lb_intro->setHorizontalAlignment(kCCTextAlignmentLeft);
	lb_intro->setPosition(Vec2(684, 85));
	this->addChild(lb_intro, 13);


	return true;
}

void CollectionLayer::update(float dt)
{
	moveBackground();
}

void CollectionLayer::moveBackground()
{
	ActionInterval* move1 = MoveBy::create(1.0f, Vec2(-speed / 3, -speed));
	ActionInterval* move2 = MoveBy::create(1.0f, Vec2(-speed / 3, -speed));

	background1->runAction(move1);
	background2->runAction(move2);

	if (background1->getPositionY() <= -960)
		background1->setPosition(Vec2(0, 960));
	if (background2->getPositionY() <= -960)
		background2->setPosition(Vec2(0, 960));

}

bool CollectionLayer::onTouchBegan(Touch* touch, Event* event)
{
	chosenCard = NULL;
	for (int i = 0; i < 10; i++){
		if (cards[i]->getBoundingBox().containsPoint(touch->getLocation())){
			chosenCard = cards[i];
			chosenCard->touchBeganAnim();
		}
	}
	return true;
}

void CollectionLayer::onTouchEnded(Touch* touch, Event* event)
{
	if (chosenCard != NULL){
		chosenCard->touchEndedAnim();
		changeIntro(chosenCard->id);
	}
}
void CollectionLayer::initNodes1()
{
	for (int i = 0; i < 8; i++)
	{
		if ((UserDefault::getInstance()->getIntegerForKey("maxLevel", -1) > -1)){
				cards[i]->setIcon(tempString[i]);
				cards[i]->id = i;
		}
	}
	if ((UserDefault::getInstance()->getIntegerForKey("maxLevel", -1) > 6)){
		cards[8]->setIcon(tempString[32]);
		cards[9]->setIcon(tempString[33]);
		cards[8]->id = 32;
		cards[9]->id = 33;
	}
}
void CollectionLayer::initNodes2()
{
	background1->setTexture("collectionLayer/kapai_bg_chuyu.png");
	background2->setTexture("collectionLayer/kapai_bg_chuyu.png");

	for (int i = 0; i < 8; i++)
	{
		if ((UserDefault::getInstance()->getIntegerForKey("maxLevel", -1) > 0)){
			cards[i]->setIcon(tempString[i+8]);
			cards[i]->id = i + 8;
		}
	}
	if ((UserDefault::getInstance()->getIntegerForKey("maxLevel", -1) > 7)){
		cards[8]->setIcon(tempString[34]);
		cards[9]->setIcon(tempString[35]);
		cards[8]->id = 34;
		cards[9]->id = 35;
	}
}
void CollectionLayer::initNodes3()
{
	background1->setTexture("collectionLayer/kapai_bg_youhai.png");
	background2->setTexture("collectionLayer/kapai_bg_youhai.png");

	for (int i = 0; i < 8; i++)
	{
		if ((UserDefault::getInstance()->getIntegerForKey("maxLevel", -1) > 1)){
			cards[i]->setIcon(tempString[i+16]);
			cards[i]->id = i + 16;
		}
	}
	if ((UserDefault::getInstance()->getIntegerForKey("maxLevel", -1) > 8)){
		cards[8]->setIcon(tempString[36]);
		cards[9]->setIcon(tempString[37]);
		cards[8]->id = 36;
		cards[9]->id = 37;
	}
}
void CollectionLayer::initNodes4()
{
	background1->setTexture("collectionLayer/kapai_bg_qita.png");
	background2->setTexture("collectionLayer/kapai_bg_qita.png");

	for (int i = 0; i < 8; i++)
	{
		if ((UserDefault::getInstance()->getIntegerForKey("maxLevel", -1) > 2)){
			cards[i]->setIcon(tempString[i+24]);
			cards[i]->id = i + 24;
		}
	}
	if ((UserDefault::getInstance()->getIntegerForKey("maxLevel", -1) > 9)){
		cards[8]->setIcon(tempString[38]);
		cards[9]->setIcon(tempString[39]);
		cards[8]->id = 38;
		cards[9]->id = 39;
	}
}

void CollectionLayer::closeThisLayer()
{
	ActionInterval* moveOut = MoveBy::create(1.0f, Vec2(1368, 0));
	this->runAction(Sequence::create(CallFunc::create([&]()
	{
		this->unscheduleUpdate();
		background1->setAnchorPoint(Vec2::ZERO);
		background1->setPosition(Vec2::ZERO);
		background2->setAnchorPoint(Vec2::ZERO);
		background2->setPosition(Vec2(0, 960));
	}), moveOut, CallFunc::create([&]()
	{
		this->setVisible(false);
		listener->setEnabled(false);
	}), NULL));
}

void CollectionLayer::changeIntro(int index)
{
	lb_intro->runAction(Sequence::create(FadeOut::create(0.1f), CallFunc::create([=]()
	{
		lb_intro->setString(introString[index]);
	}), FadeIn::create(0.1f), NULL));
}
