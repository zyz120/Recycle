#ifndef __COLLECTION_LAYER_H__
#define __COLLECTION_LAYER_H__
#include "cocos2d.h"
#include "Card.h"

#define _TOTAL_CARD 10

class CollectionLayer : public cocos2d::Layer
{
public: // functions
	virtual bool init();
	CREATE_FUNC(CollectionLayer);

	void update(float dt);
	void moveBackground();
	bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);

	// used for 4 kinds of trash (it's easy to code)
	void initNodes1();
	void initNodes2();
	void initNodes3();
	void initNodes4();

	void closeThisLayer();
	void changeIntro(int index);

public: // Nodes*
	cocos2d::Sprite* background1;
	cocos2d::Sprite* background2;
	cocos2d::EventListenerTouchOneByOne* listener;
	Card* cards[_TOTAL_CARD];
	Card* chosenCard;
	cocos2d::LabelTTF* lb_intro;

	

public: // params
	float speed;
};

#endif // __COLLECTION_LAYER_H__
