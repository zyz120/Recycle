#ifndef _BLOCK_H_
#define _BLOCK_H_
#include "cocos2d.h"

class Block : public cocos2d::Node
{
public: // functions
	virtual bool init();
	CREATE_FUNC(Block);
	void born(std::string);
	void dead();
	void deadItem();
	void setAllInit();
	void showPath(std::string from, std::string to);
	void showStar();

public: // Nodes*
	cocos2d::Sprite* picture;

public: // params
	std::string picName;
	std::string kind;
	bool isAlive;
	bool isFlying;
};

#endif // _BLOCK_H_