#include "Util.h"
USING_NS_CC;

Util::Util()
{
}


Util::~Util()
{
}

Vec2 Util::getPos(Node* node, int x, int y)
{
	Size size = node->getContentSize();
	int tempX = x + size.width / 2;
	int tempY = 968 - y - size.height / 2;
	log(size.width / 2);
	Vec2 vec = Vec2(tempX, tempY);
	return vec;
}