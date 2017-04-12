#ifndef __RANK_LAYER_H__
#define __RANK_LAYER_H__
#include "cocos2d.h"
#include "ODSocket\ODSocket.h"

class RankLayer : public cocos2d::Layer
{
public: // functions
	virtual bool init();
	CREATE_FUNC(RankLayer);
	void backToWelcome();
	bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	void receiveData();
	void connect();

public: // Nodes*
	cocos2d::Sprite* background;
	cocos2d::Sprite* star;
	cocos2d::EventListenerTouchOneByOne* listener;
	cocos2d::LabelTTF* names[3];
	cocos2d::LabelTTF* scores[3];
	cocos2d::LabelTTF* myScore;
	cocos2d::LabelTTF* failLabel;

public: // params
	ODSocket socket;
};

#endif // __RANK_LAYER_H__

