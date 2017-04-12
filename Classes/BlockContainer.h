#ifndef _BLOCK_CONTAINER_H_
#define _BLOCK_CONTAINER_H_

#define _ROW 7
#define _COL 12

#include "cocos2d.h"
#include "Block.h"

class BlockContainer : public cocos2d::Node
{
public: // functions
	virtual bool init();
	CREATE_FUNC(BlockContainer);

	void initBlankBlocks();
	void initLevelBlocks(int level);
	bool addFourBlocks(int level, int num);
	int judgeDestroyBlocks(int x, int y, bool flag);
	bool ifHasLeft();
	void showPath(int flag, int b, int f, int t, std::string from, std::string to);
	void showStar(int x, int y);
	void addItem(std::string);
	int getTotal();

public: // params
	std::string blockPath[11][8];
	int total;

public: // Nodes*
	Block* blockMatrix[_ROW+1][_COL+1];

};

#endif // _BLOCK_CONTAINER_H_