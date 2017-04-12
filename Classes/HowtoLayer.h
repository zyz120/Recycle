#ifndef __HOW_TO_LAYER_H__
#define __HOW_TO_LAYER_H__
#include "cocos2d.h"

class HowtoLayer : public cocos2d::Layer
{
public: // functions
	virtual bool init();
	CREATE_FUNC(HowtoLayer);

	void addMenu1();
	void addMenu2();
	void setbackground();

	void returnToWelcomeLayer();
	void closeThisLayer1();
	void closeThisLayer2();
	void changeVolume();
	void playBGM();


	bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);

public: // params

public: // Nodes*
	cocos2d::Sprite* background;
	cocos2d::EventListenerTouchOneByOne* listener;
};

#endif // __HOW_TO_LAYER_H__