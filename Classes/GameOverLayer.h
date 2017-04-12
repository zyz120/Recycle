#ifndef __GAME_OVER_LAYER_H__
#define __GAME_OVER_LAYER_H__
#include "cocos2d.h"
class GameOverLayer : public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(GameOverLayer);

	void closeThisLayer();
	void initScores();
	void closeAnim();

	bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);

public:
	cocos2d::LabelTTF* myScore;
	cocos2d::LabelTTF* topScore;
	cocos2d::EventListenerTouchOneByOne* listener;
};

#endif // __GAME_OVER_LAYER_H__
