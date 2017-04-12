#include "Card.h"
USING_NS_CC;

bool Card::init()
{
	if (!Node::init()){
		return false;
	}

	blankCard = Sprite::create("collectionLayer/kapai_blank.png");
	blankCard->setAnchorPoint(Vec2(0.5, 0.5));
	blankCard->setPosition(Vec2(80, 106));
	this->addChild(blankCard, 0);
	this->setContentSize(blankCard->getContentSize());

	icon = Sprite::create("block/wenhao.png");
	icon->setPosition(Vec2(80, 106));
	this->addChild(icon, 1);

	name = "no";
	id = 40;

	return true;
}

void Card::setIcon(std::string fileName)
{
	icon->setTexture("block/" + fileName);
	name = fileName;
}

void Card::touchBeganAnim()
{
	ActionInterval* sma = ScaleTo::create(0.04f, 0.96f);
	blankCard->runAction(sma);
	icon->runAction(sma->clone());
}

void Card::touchEndedAnim()
{
	ActionInterval* big = ScaleTo::create(0.08f, 1.1f);
	ActionInterval* sma = ScaleTo::create(0.04f, 1.0f);
	blankCard->runAction(Sequence::create(big, sma, NULL));
	icon->runAction(Sequence::create(big->clone(), sma->clone(), NULL));
}