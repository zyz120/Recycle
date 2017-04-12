#ifndef _GAME_LAYER1_H_
#define _GAME_LAYER1_H_
#include "cocos2d.h"
#include "BlockContainer.h"
#include "HowtoLayer.h"
#include "GameOverLayer.h"

class GameLayer1 : public cocos2d::Layer
{
public: // functions
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameLayer1);
	void showSpeedUp();
	void nextLevel();
	void addScore(int n);
	void testGameOver();
	void pauseGame();
	void changePauseState();
	void initNumber(cocos2d::LabelTTF*, int flag);	
	void initLevel();
	bool judgeItem(int x, int y);
	void addItem(int);

	int getPara(int);
	void setPara(int &, int);

	void update(float dt);

public: // Nodes*
	BlockContainer* container;
	cocos2d::Sprite* recycle;
	cocos2d::Sprite* kitchen;
	cocos2d::Sprite* harmful;
	cocos2d::Sprite* other;
	cocos2d::Sprite* recycle2;
	cocos2d::Sprite* kitchen2;
	cocos2d::Sprite* harmful2;
	cocos2d::Sprite* other2;
	cocos2d::LabelTTF* scoreLabel;
	cocos2d::LabelTTF* topScore;
	cocos2d::LabelTTF* removable;
	cocos2d::LabelTTF* accuracy;
	HowtoLayer* layer;
	cocos2d::Menu* menu;
	GameOverLayer* gameOverLayer;

public: // about touch events
	cocos2d::EventDispatcher* dispatcher;
	cocos2d::EventListenerTouchOneByOne* listener;
	bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);

public: // params
	int refreshTime;
	int m_count1;
	int m_count2;
	int speedCount;
	int currentSpeed;
	int currentLevel;
	int* levelKind;
	cocos2d::Vec2* checkPositions[4];
	int currentScore;
	int totalClickCount;
	int rightClickCount;
	int lastFrameTotal;
	int pauseFlag;

	int random;
};

#endif // _GAME_LAYER1_H_