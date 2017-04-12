#ifndef __RANK_SCENE_H__
#define __RANK_SCENE_H__
#include "cocos2d.h"
#include "ODSocket\ODSocket.h"

class RankScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(RankScene);

	void receiveData();
	void connect();

	void addPops();
	void addAPop(int type);
	void update(float dt);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void backToWelcome();

	int firstCome = 0;

public: // params
	ODSocket socket;
	int addPopPara;
	cocos2d::Size visibleSize;
	cocos2d::LabelTTF* labels[12];
	cocos2d::LabelTTF* myScore;
	cocos2d::Sprite* pops[6];
	cocos2d::Sprite* star;
	cocos2d::EventListenerTouchOneByOne* listener;
};

#endif // __RANK_SCENE_H__