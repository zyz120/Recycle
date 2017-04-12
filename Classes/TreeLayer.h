#ifndef __TREE_LAYER_H__
#define __TREE_LAYER_H__
#include "cocos2d.h"

class TreeLayer : public cocos2d::Layer
{
public: // functions
	virtual bool init();
	CREATE_FUNC(TreeLayer);
	void backClick();
	void trueTreeClick();
	void higherClick();
	void lowerClick();
	void forestClick();

	bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	void update(float dt);

public: // Nodes*
	cocos2d::LabelTTF* treeHeight;
	cocos2d::Sprite* tree;
	cocos2d::EventListenerTouchOneByOne* listener;
	cocos2d::Sprite* background;
	cocos2d::Sprite* background2;
	cocos2d::Sprite* space;
	cocos2d::Sprite* highTree;
	cocos2d::Menu* menu;
	cocos2d::Menu* menu2;
	cocos2d::Menu* menu3;
	cocos2d::Sprite* land1;
	cocos2d::Sprite* land2;

public: // params
	int landSpeed;
};

#endif // __TREE_LAYER_H__