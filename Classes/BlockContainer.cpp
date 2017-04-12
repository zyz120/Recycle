#include "BlockContainer.h"
#include "Util.h"
USING_NS_CC;

bool BlockContainer::init()
{
	if (!Node::init()){
		return false;
	}

	srand(time(0));

	std::string tempString[88] = { 
		"1_R_bolilei.png", "1_R_feizhilei.png", "1_R_jinshulei.png", "1_R_niunaihe.png",
		"1_R_suliaolei.png", "1_R_yilaguan.png", "1_R_zhiwu.png", "1_R_luomao.png",
		"2_K_caigengcaiye.png", "2_K_canzhibaiye.png", "2_K_gugeneizang.png", "2_K_guopi.png",
		"2_K_shengcaishengfan.png", "2_K_beike.png", "2_K_danke.png", "2_K_xiguapi.png",
		"3_H_feidengpao.png", "3_H_feidianchi.png", "3_H_feishouji.png", "3_H_guoqiyaopin.png",
		"3_H_shachongji.png", "3_H_youqitong.png", "3_H_youqishua.png", "3_H_xiangshui.png", 
		"4_O_huitu.png", "4_O_huitusaozhou.png", "4_O_juanzhi.png", "4_O_pocipan.png",
		"4_O_poguanzi.png", "4_O_wushui.png", "4_O_yandi.png", "4_O_yicixingcanju.png",
		"5_R_bolilei.png", "5_R_feizhilei.png", "5_R_jinshulei.png", "5_R_luomao.png",
		"5_R_niunaihe.png", "5_R_suliaolei.png", "5_R_yilaguan.png", "5_R_zhiwu.png",
		"6_K_beike.png", "6_K_beike_2.png", "6_K_canzhibaiye.png", "6_K_danke.png",
		"6_K_guopi.png", "6_K_guopi_2.png", "6_K_shengcaishengfan.png", "6_K_xiguapi.png",
		"7_H_feidengpao.png", "7_H_feidianchi.png", "7_H_feishouji.png", "7_H_guoqiyaopin.png",
		"7_H_guoqiyaopin_2.png", "7_H_shachongji.png", "7_H_youqitong.png", "7_H_feidianchi_2.png",
		"8_R_bolilei.png", "8_R_jingzi.png", "8_R_jinshulei.png", "8_R_luomao.png",
		"8_R_niunaihe.png", "8_R_shubao.png", "8_R_suliaolei.png", "8_R_yilaguan.png",
		"9_K_gugeneizang.png", "9_K_gugeneizang_2.png", "9_K_gutou.png", "9_K_gutou_2.png",
		"9_K_shengcaishengfan.png", "9_K_shengcaishengfan_2.png", "9_K_xiangjiaopi.png", "9_K_xiangjiaopi_2.png",
		"A_H_feishouji.png", "A_H_feishouji_2.png", "A_H_kouhong.png", "A_H_kouhong_2.png",
		"A_H_piaobaiji.png", "A_H_piaobaiji_2.png", "A_H_xiangshui.png", "A_H_xiangshui_2.png",
		"B_O_dongwufenbian.png", "B_O_dongwufenbian_2.png", "B_O_huitu.png", "B_O_huitu_2.png",
		"B_O_huitusaozhou.png", "B_O_huitusaozhou_2.png", "B_O_yanhe.png", "B_O_yanhe_2.png" };

	for (int k = 0; k < 11;k++)
		for (int i = 0; i < 8; i++)
			blockPath[k][i] = tempString[k*8+i];

	initBlankBlocks();

	return true;
}

void BlockContainer::initBlankBlocks()
{
	total = 0;
	for (int i = 0; i < _ROW+1; i++){
		for (int j = 0; j < _COL+1; j++){
			blockMatrix[i][j] = Block::create();
			blockMatrix[i][j]->setPosition(Util::getPos(blockMatrix[i][j], 114 * j, 85 + 114 * i));
			this->addChild(blockMatrix[i][j], 1);
		}
	}
}

void BlockContainer::initLevelBlocks(int level)
{
	for (int i = 0; i < _ROW;i++)
	for (int j = 0; j < _COL; j++)
		blockMatrix[i][j]->setAllInit();
	total = 0;

	// the blocks init totally
	int count = CCRANDOM_0_1() * 6 + 50 - level / 3;

	for (int i = 0; i < count;){
		int tempX = (CCRANDOM_0_1() - 0.01) * 7;
		int tempY = (CCRANDOM_0_1() - 0.01) * 12;
		if (!blockMatrix[tempX][tempY]->isAlive && !blockMatrix[tempX][tempY]->isFlying){
			i++;
			total++;
			blockMatrix[tempX][tempY]->born(blockPath[level][((int)((CCRANDOM_0_1() - 0.01) * 8))]);
		}
	}

}

int BlockContainer::judgeDestroyBlocks(int x, int y, bool flag)
{
	if (blockMatrix[x][y]->isAlive)
		return 1;

	int tempTotal = total;
	bool f = false;

	Vec2 vec2[4];
	vec2[0] = vec2[1] = vec2[2] = vec2[3] = Vec2(_ROW, _COL);
	for (int i = x;; i--){
		if (blockMatrix[i][y]->isAlive){
			vec2[0] = Vec2(i, y);
			break;
		}
		if (i == 0)
			break;
	}
	for (int i = x;; i++){
		if (blockMatrix[i][y]->isAlive){
			vec2[1] = Vec2(i, y);
			break;
		}
		if (i == _ROW - 1)
			break;
	}
	for (int i = y;; i--){
		if (blockMatrix[x][i]->isAlive){
			vec2[2] = Vec2(x, i);
			break;
		}
		if (i == 0)
			break;
	}
	for (int i = y;; i++){
		if (blockMatrix[x][i]->isAlive){
			vec2[3] = Vec2(x, i);
			break;
		}
		if (i == _COL - 1)
			break;
	}

	if (blockMatrix[(int)vec2[0].x][(int)vec2[0].y]->picName == blockMatrix[(int)vec2[1].x][(int)vec2[1].y]->picName && blockMatrix[(int)vec2[0].x][(int)vec2[0].y]->picName != "no")
	{
		f = true;
		if (blockMatrix[(int)vec2[0].x][(int)vec2[0].y]->picName == blockMatrix[(int)vec2[2].x][(int)vec2[2].y]->picName){
			if (flag){
				total--;
				showPath(0, x, y - 1, (int)vec2[2].y, "R", "L");
				blockMatrix[(int)vec2[2].x][(int)vec2[2].y]->dead();
			}
		}

		if (blockMatrix[(int)vec2[0].x][(int)vec2[0].y]->picName == blockMatrix[(int)vec2[3].x][(int)vec2[3].y]->picName){
			if (flag){
				total--;
				showPath(0, x, y + 1, (int)vec2[3].y, "L", "R");
				blockMatrix[(int)vec2[3].x][(int)vec2[3].y]->dead();
			}
		}
		if (flag){
			total -= 2;
			showPath(1, y, x - 1, (int)vec2[0].x, "B", "T");
			showPath(1, y, x + 1, (int)vec2[1].x, "T", "B");
			blockMatrix[(int)vec2[0].x][(int)vec2[0].y]->dead();
			blockMatrix[(int)vec2[1].x][(int)vec2[1].y]->dead();
		}
	}

	if (blockMatrix[(int)vec2[2].x][(int)vec2[2].y]->picName == blockMatrix[(int)vec2[3].x][(int)vec2[3].y]->picName && blockMatrix[(int)vec2[2].x][(int)vec2[2].y]->picName != "no")
	{
		f = true;
		if (blockMatrix[(int)vec2[2].x][(int)vec2[2].y]->picName == blockMatrix[(int)vec2[1].x][(int)vec2[1].y]->picName){
			if (flag){
				total--;
				showPath(1, y, x + 1, (int)vec2[1].x, "T", "B");
				blockMatrix[(int)vec2[1].x][(int)vec2[1].y]->dead();
			}
		}
		if (blockMatrix[(int)vec2[2].x][(int)vec2[2].y]->picName == blockMatrix[(int)vec2[0].x][(int)vec2[0].y]->picName){
			if (flag){
				total--;
				showPath(1, y, x - 1, (int)vec2[0].x, "B", "T");
				blockMatrix[(int)vec2[0].x][(int)vec2[0].y]->dead();
			}
		}
		if (flag){
			total -= 2;
			showPath(0, x, y - 1, (int)vec2[2].y, "R", "L");
			showPath(0, x, y + 1, (int)vec2[3].y, "L", "R");
			blockMatrix[(int)vec2[2].x][(int)vec2[2].y]->dead();
			blockMatrix[(int)vec2[3].x][(int)vec2[3].y]->dead();
		}
	}


	for (int i = 0; i < 2; i++){
		if (blockMatrix[(int)vec2[i % 4].x][(int)vec2[i % 4].y]->picName == blockMatrix[(int)vec2[(i + 2) % 4].x][(int)vec2[(i + 2) % 4].y]->picName && blockMatrix[(int)vec2[(i + 2) % 4].x][(int)vec2[(i + 2) % 4].y]->picName != "no")
		{
			f = true;
			if (flag){
				total -= 2;
				if (i == 0){ // 0 2
					showPath(0, x, y - 1, (int)vec2[2].y, "R", "L");
					showPath(1, y, x - 1, (int)vec2[0].x, "B", "T");
				}
				else{ // 1 3
					showPath(0, x, y + 1, (int)vec2[3].y, "L", "R");
					showPath(1, y, x + 1, (int)vec2[1].x, "T", "B");
				}
				blockMatrix[(int)vec2[(i + 2) % 4].x][(int)vec2[(i + 2) % 4].y]->dead();
				blockMatrix[(int)vec2[i % 4].x][(int)vec2[i % 4].y]->dead();
			}
		}
	}
	for (int i = 1; i < 4; i += 2){
		if (blockMatrix[(int)vec2[i % 4].x][(int)vec2[i % 4].y]->picName == blockMatrix[(int)vec2[(i + 1) % 4].x][(int)vec2[(i + 1) % 4].y]->picName && blockMatrix[(int)vec2[(i + 1) % 4].x][(int)vec2[(i + 1) % 4].y]->picName != "no")
		{
			f = true;
			if (flag){
				total -= 2;
				if (i == 1){
					showPath(0, x, y - 1, (int)vec2[2].y, "R", "L");
					showPath(1, y, x + 1, (int)vec2[1].x, "T", "B");
				}
				else{
					showPath(1, y, x - 1, (int)vec2[0].x, "B", "T");
					showPath(0, x, y + 1, (int)vec2[3].y, "L", "R");
				}
				blockMatrix[(int)vec2[(i + 1) % 4].x][(int)vec2[(i + 1) % 4].y]->dead();
				blockMatrix[(int)vec2[i % 4].x][(int)vec2[i % 4].y]->dead();
			}
		}
	}
	if (!flag && f)
		return 1;
	return tempTotal - total;
}

bool BlockContainer::addFourBlocks(int level, int num)
{
	int count = 0;
	if (total < _ROW*_COL - num){
		count = num;
	}
	else{
		count = _ROW*_COL - total;
	}

	int temp = 0;


		for (int i = 0; i < count;){
			temp++;
			int tempX = (CCRANDOM_0_1() - 0.01) * _ROW;
			int tempY = (CCRANDOM_0_1() - 0.01) * _COL;
			if (!blockMatrix[tempX][tempY]->isAlive && !blockMatrix[tempX][tempY]->isFlying){
				i++;
				total++;
				blockMatrix[tempX][tempY]->born(blockPath[level][((int)((CCRANDOM_0_1() - 0.01) * 8))]);
			}
			if (temp == 2000)
				break;
		}

		if (total == _ROW*_COL)
			return true;

		return false;
}

bool BlockContainer::ifHasLeft()
{
	if (total > ((int)_ROW*_COL) * 0.3) // x0..3
		return true;
	bool result = false;
	for (int i = 0; i < _ROW; i++){
		for (int j = 0; j < _COL; j++){
			if (!blockMatrix[i][j]->isAlive)
			{
				if (judgeDestroyBlocks(i, j, false))
				{
					result = true;
					break;
				}
			}
		}
		if (result)
			break;
	}
	return result;
}

void BlockContainer::showPath(int flag, int b, int f, int t, std::string from, std::string to) // flag 0-row  1-col
{
	int temp = 0;
	int terminal = f;
	if (t < f){
		temp = t;
		t = f;
		f = temp;
	}

	if (flag)
	for (int i = f; i <= t; i++){
		blockMatrix[i][b]->showPath(from, to);
	}
	else
	for (int i = f; i <= t; i++){
		blockMatrix[b][i]->showPath(from, to);
	}
}

void BlockContainer::showStar(int x, int y)
{
	blockMatrix[x][y]->showStar();
}


void BlockContainer::addItem(std::string fileName)
{
	int temp = 0;
	for (int i = 0; i < 1;){
		temp++;
		int tempX = (CCRANDOM_0_1() - 0.01) * _ROW;
		int tempY = (CCRANDOM_0_1() - 0.01) * _COL;
		if (!blockMatrix[tempX][tempY]->isAlive && !blockMatrix[tempX][tempY]->isFlying){
			i++;
			total++;
			blockMatrix[tempX][tempY]->born(fileName);
		}
		if (temp == 2000)
			break;
	}
}

int BlockContainer::getTotal()
{
	int count = 0;
	for (int i = 0; i < _ROW; i++){
		for (int j = 0; j < _COL; j++){
			if (blockMatrix[i][j]->isAlive)
				count++;
		}
	}
	return count;
}