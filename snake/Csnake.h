#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
using namespace std;
#define SNAKE_MAX 500
#pragma once
enum Key
{
	//按键
	UP,
	DOWN,
	LEFT,
	RIGHT,
	STOP,
	//模式
	simple,
	endless,
	difficult,
	//
};
class Csnake{
public://菜单
	void initStart();//初始化窗口
	void Drawtext();//初始化字体
	void switchSelection(int ii);
	void initmain();
	void Esc_initSrart();//
public:
	//Mode
	void simpleMode();//简单模式
	void simpleModeHeiWall(Key key);

	void endlessMode();//无尽模式
	void endlessModeHeiWall();
	void difficultMode();//困难模式

public:
	void gameInit();//创建窗口，赋好相应的值，打印大概的蛇的初始化长度
	void gameDraw();//刷新snake
	void gameMove();//移动snake
	void gameKey(); //按键检测
	void gameSrand();//随机生成器
	void gameRule();//游戏玩法
	void gameVictory();//胜利
public://打印
	void snakeBody();//身体
	void snakeEye();//眼睛
	void snakeTongue();//舌头
	void snakeFood();//食物
	void snakeWall();//墙体
public://撞墙参数
	void gameWall_Over(Key key);//撞墙主函数
	void drawText_Over();//初始化字体
	void switchSelection_Over(int i);//左右选择
	//蛇的参数
private:
	int size;//长度
	int speed = 10;//间隔
	DWORD sleep;
	DWORD minSleep = 10;
	Key direction;//方向
	POINT eye[2];//眼睛
	POINT *tongue;//舌头
	POINT coordinates[SNAKE_MAX];//蛇坐标

	//食物的参数
private:
	int x;
	int y;
	int r;//半径
	bool ok;//是否被吃掉
	DWORD color;

};

