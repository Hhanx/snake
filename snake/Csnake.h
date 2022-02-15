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
	//����
	UP,
	DOWN,
	LEFT,
	RIGHT,
	STOP,
	//ģʽ
	simple,
	endless,
	difficult,
	//
};
class Csnake{
public://�˵�
	void initStart();//��ʼ������
	void Drawtext();//��ʼ������
	void switchSelection(int ii);
	void initmain();
	void Esc_initSrart();//
public:
	//Mode
	void simpleMode();//��ģʽ
	void simpleModeHeiWall(Key key);

	void endlessMode();//�޾�ģʽ
	void endlessModeHeiWall();
	void difficultMode();//����ģʽ

public:
	void gameInit();//�������ڣ�������Ӧ��ֵ����ӡ��ŵ��ߵĳ�ʼ������
	void gameDraw();//ˢ��snake
	void gameMove();//�ƶ�snake
	void gameKey(); //�������
	void gameSrand();//���������
	void gameRule();//��Ϸ�淨
	void gameVictory();//ʤ��
public://��ӡ
	void snakeBody();//����
	void snakeEye();//�۾�
	void snakeTongue();//��ͷ
	void snakeFood();//ʳ��
	void snakeWall();//ǽ��
public://ײǽ����
	void gameWall_Over(Key key);//ײǽ������
	void drawText_Over();//��ʼ������
	void switchSelection_Over(int i);//����ѡ��
	//�ߵĲ���
private:
	int size;//����
	int speed = 10;//���
	DWORD sleep;
	DWORD minSleep = 10;
	Key direction;//����
	POINT eye[2];//�۾�
	POINT *tongue;//��ͷ
	POINT coordinates[SNAKE_MAX];//������

	//ʳ��Ĳ���
private:
	int x;
	int y;
	int r;//�뾶
	bool ok;//�Ƿ񱻳Ե�
	DWORD color;

};

