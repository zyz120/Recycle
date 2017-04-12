#ifndef _UTIL_H_
#define _UTIL_H_
#include "cocos2d.h"

class Util
{
public:
	Util();
	~Util();

public: // tool functions
	static cocos2d::Vec2 getPos(cocos2d::Node*, int, int);

};

#endif // _UTIL_H_