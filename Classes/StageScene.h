#ifndef _STAGE_SCENE_H_
#define _STAGE_SCENE_H_
#include "cocos2d.h"
#include "GameLayer1.h"
#include "WelcomeScene.h"
#include "TreeLayer.h"

class StageScene : public cocos2d::Layer
{
public: // functions
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(StageScene);

public: // Nodes*
	GameLayer1* gameLayer1;
	TreeLayer* treeLayer;
	WelcomeScene* welcomeLayer;

public: // params
	bool gameOn;
	bool bgmOn;

};

#endif // _STAGE_SCENE_H_