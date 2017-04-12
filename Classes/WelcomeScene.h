#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__
#include "cocos2d.h"

class WelcomeScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(WelcomeScene);

	void playBGM();

public:
	cocos2d::EventListenerTouchOneByOne* listener;
	cocos2d::EventDispatcher* dispatcher;
	bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);

private:
	void startCallback(cocos2d::Ref* pSender);
	void collectionCallback(cocos2d::Ref* pSender);
	void forestCallback(cocos2d::Ref* pSender);
	void helpCallback(cocos2d::Ref* pSender);
	void volumnCallback(cocos2d::Ref* pSender);
	void aboutCallback(cocos2d::Ref* pSender);
	void rankCallback(cocos2d::Ref* pSender);

public: // Nodes*
	cocos2d::Menu* menu;
};

#endif // __WELCOME_SCENE_H__