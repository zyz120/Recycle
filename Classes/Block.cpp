#include "Block.h"
USING_NS_CC;

bool Block::init()
{
	if (!Node::init()){
		return false;
	}

	picture = Sprite::create("block/blank.png");
	this->addChild(picture, 1);

	setContentSize(Size(114, 114));

	isAlive = false;
	isFlying = false;
	picName = "no";
	kind = "no";

	return true;
}

void Block::born(std::string fileName)
{
	if (isFlying)
		return;
	isAlive = true;
	picName = fileName;
	kind = fileName.substr(2, 2);
	picture->setTexture("block/" + fileName);
	picture->setOpacity(0);
	ActionInterval* fadeIn = FadeIn::create(0.2f);
	ActionInterval* scale = ScaleTo::create(0.2f, 1.4f);
	ActionInterval* scale2 = ScaleTo::create(0.1f, 1.0f);
	Sequence* seq = Sequence::create(fadeIn, scale, scale2, NULL);
	picture->runAction(seq);


	
}

void Block::dead()
{
	// jump down Animation
	isFlying = true;
	isAlive = false;
	picName = "no";
	kind = "no";
	ActionInterval* jumpDown = JumpBy::create(0.8f, Vec2(CCRANDOM_0_1()*300 - 150, -this->getPositionY() - 200), CCRANDOM_0_1() * 200 + 150, 1);
	this->picture->runAction(Sequence::create(jumpDown, 
		CallFunc::create([&]()
		{
			picture->setTexture("block/blank.png");
		}),
		MoveTo::create(0.01f, Vec2(0, 0)), 
		CallFunc::create([&]()
		{
			isFlying = false;
		}),
		NULL));


}

void Block::setAllInit()
{
	isFlying = false;
	this->picture->setTexture("block/blank.png");
	picName = "no";
	isAlive = false;
}

void Block::showPath(std::string from, std::string to)
{
	Sprite* pic = Sprite::create("block/connect_" + from + "_" + to + ".png");
	this->addChild(pic);

	ActionInterval* fadeOut = FadeOut::create(0.5f);
	pic->runAction(fadeOut);

}

void Block::showStar()
{
	Sprite* star1 = Sprite::create("block/star1.png");
	Sprite* star2 = Sprite::create("block/star2.png");
	this->addChild(star1);
	this->addChild(star2);

	star1->runAction(Sequence::create(CCDelayTime::create(0.2f), FadeOut::create(0.1f), NULL));
	star2->runAction(Sequence::create(CCDelayTime::create(0.1f), FadeOut::create(0.1f), NULL));

}

void Block::deadItem()
{
	// jump down Animation
	isFlying = true;
	picName = "no";
	kind = "no";
	isAlive = false;
	ActionInterval* rotate = RotateBy::create(0.8f, 719);
	ActionInterval* fadeOut = FadeOut::create(0.8f);
	ActionInterval* sma = ScaleTo::create(0.8f, 0);

	this->picture->runAction(fadeOut);
	this->picture->runAction(sma);
	this->picture->runAction(Sequence::create(rotate,
		CallFunc::create([&]()
	{		
		picture->setTexture("block/blank.png");
	}),
		MoveTo::create(0.01f, Vec2(0, 0)),
		CallFunc::create([&]()
	{
		isFlying = false;
	}),
		NULL));


}
