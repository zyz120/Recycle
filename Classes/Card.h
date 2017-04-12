#ifndef __CARD_H__
#define __CARD_H__
#include "cocos2d.h"

class Card : public cocos2d::Node
{
public: // functions
	virtual bool init();
	CREATE_FUNC(Card);

	void setIcon(std::string fileName);
	void touchBeganAnim();
	void touchEndedAnim();

public: // Nodes*
	cocos2d::Sprite* icon;
	cocos2d::Sprite* blankCard;

public: // params
	std::string name;
	int id;

};

#endif // __CARD_H__
