#ifndef __CHOOSE_LAYER_H__
#define __CHOOSE_LAYER_H__
#include "cocos2d.h"

class ChooseLayer : public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(ChooseLayer);
	void backToWelcome();
	void toCardLayer1();
	void toCardLayer2();
	void toCardLayer3();
	void toCardLayer4();

	bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);

public: // Nodes*
	cocos2d::EventListenerTouchOneByOne* listener;

};

#endif // __CHOOSE_LAYER_H__
