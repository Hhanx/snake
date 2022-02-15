#define _CRT_SECURE_NO_WARNINGS
#include "Csnake.h"

//蛇的速度随时间变化而变化 时间越长 速度越快
//整体函数
void Csnake::gameInit(){

	initgraph(1000,600);
	
	this->size = 2;//长度 
	this->direction = STOP;
	this->sleep = 100;

	for (int i = 0; i < 1; i++) {

		this->coordinates[i].x = 20 * i + 50;
		this->coordinates[i].y = 100;

	}
	this->ok = false;
}

void Csnake::gameDraw(){

	BeginBatchDraw();
	
	setbkcolor(RGB(124,135,205));
	cleardevice();
	
	//初始化蛇的身体
	this->snakeTongue();
	this->snakeBody();
	this->snakeEye();
	//食物初始化
	this->snakeFood();
	//初始化墙
	this->snakeWall();
	this->gameRule();
	if (this->ok && this->coordinates[0].x >= this->x - this->r && this->coordinates[0].x <= this->x + this->r
		&& this->coordinates[0].y >= this->y - this->r && this->coordinates[0].y <= this->y + this->r)
	{
		this->ok = false;
		this->size++;
	}

	if (!this->ok){

		this->gameSrand();
	}

	if (this->color == RGB(124, 135, 205))
	{
		this->gameSrand();
	}
	

	EndBatchDraw();
}

void Csnake::gameMove(){

	for (int i = this->size - 1; i > 0; i--){

		this->coordinates[i] = this->coordinates[i - 1];
	}

	switch (direction){

		case UP:
			this->coordinates[0].y -= this->speed;
			break;
		case DOWN:
			this->coordinates[0].y += this->speed;
			break;
		case LEFT:		
			this->coordinates[0].x -= this->speed;
			break;
		case RIGHT:		
			this->coordinates[0].x += this->speed;
			break;

	}
		
}

void Csnake::gameKey(){

	if(_kbhit())
		switch (_getch())//上72     下80    左75    右77
		{
		case 72:
		case 'w':case 'W':
			if (this->direction != DOWN)
				this->direction = UP;
			break;
		case 's':case 'S':
		case 80:
			if (this->direction != UP)
				this->direction = DOWN;
			break;
		case 'a':case 'A':
		case 75:
			if (this->direction != RIGHT)
				this->direction = LEFT;
			break;
		case 'd':case 'D':
		case 77:
			if (this->direction != LEFT)
				this->direction = RIGHT;
			break;
		case ' ':
				this->direction = STOP;
			break;
		case 27:
				this->Esc_initSrart();		
			break;
		}

}

void Csnake::gameSrand(){

	srand((unsigned)time(NULL));
	this->x = rand() % 700 + 50;
	this->y = rand() % 500 + 50;
	this->r = rand() % 5 + 10;
	this->color = RGB(rand() % 255, rand() % 255, rand() % 255);
	this->ok = true;

}

void Csnake::gameRule()
{
	
	setfillcolor(RGB(206,201,201));
	fillrectangle(800,0,1000,600);
	setbkmode(TRANSPARENT);
	settextcolor(RED);
	settextstyle(40, 0, _T("微软雅黑"));
	RECT r1 = { 800, 10, 1000, 600 };
	drawtext(_T("游戏规则"), &r1, DT_CENTER);
	settextstyle(30, 0, _T("幼圆"));
	settextcolor(BLUE);
	RECT r2 = { 800, 60, 1000, 600 };
	drawtext(_T("前 ：W ↑"), &r2, DT_CENTER);

	RECT r3 = { 800, 110, 1000, 600 };
	drawtext(_T("后 ：S ↓"), &r3, DT_CENTER);

	RECT r4 = { 800, 160, 1000, 600 };
	drawtext(_T("左 ：A ←"), &r4, DT_CENTER);

	RECT r5 = { 800,210, 1000, 600 };
	drawtext(_T("右 ：D →"), &r5, DT_CENTER);


	settextstyle(25, 0, _T("幼圆"));
	RECT r6 = { 800,300, 1000, 600 };
	drawtext(_T("暂停 : 空格"), &r6, DT_CENTER);

	RECT r7 = { 800,350, 1000, 600 };
	drawtext(_T("返回菜单 : ESC"), &r7, DT_CENTER);
//
	int fensu_int = this->size - 2;
	TCHAR fensu_char[5];
	_itow(fensu_int,fensu_char,5);
	settextstyle(20, 0, _T("黑体"));
	RECT r8 = { 800,410, 1000, 600 };
	drawtext(_T("分数："), &r8, DT_LEFT);

	setfillcolor(RGB(255, 210, 73));
	fillrectangle(800, 430, 1000, 500);

	settextstyle(70, 0, _T("幼圆"));
	RECT r9 = { 800,430, 1000, 500 };
	drawtext(fensu_char, &r9, DT_CENTER);

	settextstyle(20, 0, _T("黑体"));
	RECT r10 = { 800,510, 1000, 600 };
	drawtext(_T("当前速度：(级)"), &r10, DT_LEFT);
	fillrectangle(800, 530, 1000, 600);


	TCHAR speed_char[5];
	_itow(sleep,speed_char,5);
	settextstyle(70, 0, _T("幼圆"));
	RECT r11 = { 800,530, 1000, 600 };
	drawtext(speed_char, &r11, DT_CENTER);

	settextstyle(15, 0, _T("幼圆"));
	RECT r55 = { 800,250, 1000, 600 };
	drawtext(_T("最快速度：10"), &r55, DT_CENTER);

	RECT r51 = { 800,270, 1000, 600 };
	drawtext(_T("最大长度：100"), &r51, DT_CENTER);

}

void Csnake::gameVictory()
{
	closegraph();
	initgraph(600, 300);
	setbkcolor(RGB(128, 128, 128));
	cleardevice();
	//
	settextcolor(RED);
	settextstyle(60, 0, _T("黑体"));
	RECT r = { -10, 50, 590, 300 };
	drawtext(_T("    恭喜你赢了   "), &r, DT_CENTER);
	//
	settextcolor(WHITE);
	settextstyle(30, 0, _T("微软雅黑"));
	RECT r2 = { 0, 150, 600, 300 };
	drawtext(_T("按回车返回菜单"), &r2, DT_CENTER);
	//
	settextstyle(0, 0, _T("微软雅黑"));
	TCHAR size_char[5];
	_itow(size, size_char, 5);
	RECT r3 = { 0, 200, 600, 300 };
	drawtext(_T("您得分:"), &r3, DT_CENTER);

	//分数
	settextcolor(YELLOW);
	RECT r33 = { 0, 220, 600, 300 };
	drawtext(size_char, &r33, DT_CENTER);
	//


	switch (_getch())
	{
		case 13:this->initmain(); break;
	}
}

//撞墙
void Csnake::gameWall_Over(Key key){
	
	int i = 0;
	int a = 1;
	initgraph(600,300);

	setbkcolor(RGB(128,128,128));
	cleardevice();

	drawText_Over();

	while (a == 1) {
		switch (_getch()){
		case 13:
			if (i == 1){
				if (key == simple) {
					this->simpleMode();
				}
				if (key == endless) {
					this->endlessMode();
				}
				if (key == difficult) {
					this->difficultMode();
				}
			}
			if (i == 2){
				this->initmain();
			}
			break;
		case 224:
			switch (_getch()){
			case 75:
				i--;
				switchSelection_Over(i);
				break;
			case 77:
				i++;
				switchSelection_Over(i);
				break;
			}
		}
		if (i == 0) {
			i = 2;
		}
		if (i == 3){
			i = 1;
		}
	}
}

void Csnake::drawText_Over(){
	
	settextcolor(WHITE);
	settextstyle(60, 0, _T("微软雅黑"));
	RECT r1 = { 0, 150, 300, 300 };
	drawtext(_T("重玩"), &r1, DT_CENTER);
	RECT r2 = { 0, 150, 900, 300 };
	drawtext(_T("菜单"), &r2, DT_CENTER);
	settextstyle(0, 0, _T("微软雅黑"));
	RECT r3 = { 0, 250, 590, 300 };
	drawtext(_T("使用← →进行选择"), &r3, DT_CENTER);

	settextcolor(RED);
	settextstyle(60, 0, _T("黑体"));
	RECT r = { -10, 50, 590, 300 };
	drawtext(_T("    恭喜你死亡了   "), &r, DT_CENTER);
}

void Csnake::switchSelection_Over(int i){
	drawText_Over();
	settextcolor(BLUE);
	settextstyle(60, 0, _T("微软雅黑"));
	if(i == 1){
		RECT r1 = { 0, 150, 300, 300 };
		drawtext(_T("重玩"), &r1, DT_CENTER);
	}
	if(i == 2){
		RECT r2 = { 0, 150, 900, 300 };
		drawtext(_T("菜单"), &r2, DT_CENTER);
	}
}

//主菜单子函数
void Csnake::initStart() {

	initgraph(300, 300);
	setbkcolor(WHITE);
	cleardevice();
}

void Csnake::Drawtext() {

	RECT r1 = { 0, 50, 300, 300 };
	RECT r2 = { 0, 100, 300, 300 };
	RECT r3 = { 0, 150, 300, 300 };
	RECT r4 = { 0, 200, 300, 300 };
	RECT r5 = { 0, 250, 300, 300 };
	settextcolor(RED);
	drawtext(_T("欢迎进入贪吃蛇游戏"), &r1, DT_CENTER);
	settextcolor(BLUE);

	drawtext(_T("《   简单模式   》"), &r2, DT_CENTER);

	drawtext(_T("《   无尽模式   》"), &r3, DT_CENTER);

	drawtext(_T("《   困难模式   》"), &r4, DT_CENTER);

	drawtext(_T("使用“↑↓”选择"), &r5, DT_CENTER);
}

void Csnake::switchSelection(int ii) {

	Drawtext();

	settextcolor(RGB(255, 128, 0));
	if (ii == 1) {
		RECT r = { 0, 100, 300, 300 };
		drawtext(_T("《   简单模式   》"), &r, DT_CENTER);
	}
	if (ii == 2) {
		RECT r = { 0, 150, 300, 300 };
		drawtext(_T("《   无尽模式   》"), &r, DT_CENTER);
	}
	if (ii == 3) {
		RECT r = { 0, 200, 300, 300 };
		drawtext(_T("《   困难模式   》"), &r, DT_CENTER);
	}

}
//主菜单
void Csnake::initmain() {
	this->initStart();
	this->Drawtext();

	int i = 1;
	while (TRUE) {
		switch (_getch()) {
		case 13:
			closegraph();
			if (i == 1) {
				this->simpleMode();
			}
			if (i == 2) {
				this->endlessMode();
			}
			if (i == 3) {
				this->difficultMode();
			}
			break;
		case 224:
			switch (_getch()) {
			case 72:
				i--;
				this->switchSelection(i);
				break;
			case 80:
				i++;
				this->switchSelection(i);
				break;
			}
		}
		if (i == 4) {
			i = 1;
		}
		if (i == 0) {
			i = 3;
		}
	}

}
//按钮事件
void Csnake::Esc_initSrart(){

	this->initmain();

}
//画图函数
void Csnake::snakeBody(){
	for (int i = 0; i < this->size; i++) {
		//头颜色
		setfillcolor(GREEN);
		solidcircle(this->coordinates[0].x, this->coordinates[0].y, 10);
		//身
		setfillcolor(YELLOW);
		solidcircle(this->coordinates[i].x, this->coordinates[i].y, 10);
	}

}

void Csnake::snakeEye(){
	
	if (this->direction == LEFT || this->direction == RIGHT) {

		this->eye[0].x = this->coordinates[0].x;
		this->eye[0].y = this->coordinates[0].y - 7;
		this->eye[1].x = this->coordinates[0].x;
		this->eye[1].y = this->coordinates[0].y + 7;

	}
	else {

		this->eye[0].x = this->coordinates[0].x - 7;
		this->eye[0].y = this->coordinates[0].y;
		this->eye[1].x = this->coordinates[0].x + 7;
		this->eye[1].y = this->coordinates[0].y;

	}

	setfillcolor(BLACK);
	fillcircle(this->eye[0].x, this->eye[0].y, 5);
	fillcircle(this->eye[1].x, this->eye[1].y, 5);
}

void Csnake::snakeTongue(){

	int x = this->coordinates[0].x;
	int y = this->coordinates[0].y;
	int* ppts = NULL;
	
	if (this->direction == RIGHT) {

		int pts[] = {  
			    
					x + 5 ,  y - 2 ,
					x + 5 + 15 ,  y - 2,//长
					x + 5 + 8 ,  y,    //中
					x + 5 + 15 ,  y + 2,//长
					x + 5 ,  y + 2,
					x + 5,  y - 2
			
		};
		ppts = pts;
	}
	else if (this->direction == LEFT) {

		int pts[] = {

					x - 5 ,  y - 2 ,
					x - 5 - 15 ,  y - 2,//长
					x - 5 - 8 ,  y,    //中
					x - 5 - 15 ,  y + 2,//长
					x - 5 ,  y + 2,
					x - 5,  y - 2
		};
		ppts = pts;
	}
	else if (this->direction == DOWN)
	{
		int pts[] = {

					x - 2 ,  y + 5,
					x - 2 ,  y + 5 + 15,//长
					x     ,  y + 5 + 8,    //中
					x + 2 ,  y + 5 + 15,//长
					x + 2 ,  y + 5,
					x - 2 ,  y + 5
		};
		ppts = pts;
	}
	else if (this->direction == UP)
	{
		int pts[] = {

					x - 2 ,  y - 5,
					x - 2 ,  y - 5 - 15,//长
					x     ,  y - 5 - 8,    //中
					x + 2 ,  y - 5 - 15,//长
					x + 2 ,  y - 5,
					x - 2 ,  y - 5

		};
		ppts = pts;
	}

	this->tongue = (POINT*)ppts;

	setfillcolor(RGB(255,174,201));
	solidpolygon(tongue, 6);

	polyline(tongue, 6);
}

void Csnake::snakeFood(){
	//cout << this->color << this->x << this->y << this->r << endl;
	setfillcolor(this->color);
	solidcircle(this->x,this->y,this->r);
}

void Csnake::snakeWall(){
	 //              x  y   x   y
	//solidrectangle(0, 0, 20, 20);
	int x;
	int xx;

	int y;
	int yy;
	int x_max = 800;
	int y_max = 600;
	setfillcolor(RGB(254,82,63));
//左
	for (x = 0,xx = 20,y = 0,yy = 20;/*y <= y_max,*/ yy <= y_max; y += 20,yy += 20){

		fillrectangle(x, y, xx, yy);

	}
//上
	for (y = 0, yy = 20,x = 0, xx = 20; /*x <= x_max,*/ xx <= x_max; x += 20, xx += 20) {

		fillrectangle(x, y, xx, yy);

	}
//右
	for (x = 800-20, xx = 800, y = 0, yy = 20; /*y <= y_max,*/ yy <= y_max; y += 20, yy += 20) {

		fillrectangle(x, y, xx, yy);

	}
//下
	for (y = 600-20, yy = 600, x = 0, xx = 20;/* x <= x_max,*/ xx <= x_max; x += 20, xx += 20) {

		fillrectangle(x, y, xx, yy);
	}

}

void Csnake::simpleMode() {
	//snake.gameWall_Over();//
	this->gameInit();
	int snakeSize = size;
	bool loop = TRUE;
	while (loop) {
		Key key = simple;
		this->gameDraw();
		this->gameMove();
		this->gameKey();
		this->simpleModeHeiWall(key);
		if (snakeSize < size && !(minSleep > sleep))
		{
			snakeSize = size;
			sleep -= 5;
		}
		if (size >= 25)
		{
			loop = FALSE;
			break;
		}
		Sleep(sleep);
	}
	gameVictory();
}
//模式
void Csnake::simpleModeHeiWall(Key key) {

	if (this->coordinates[0].x <= 20 || this->coordinates[0].x >= 800-20 ||
		this->coordinates[0].y <= 20 || this->coordinates[0].y >= 600-20) {
		gameWall_Over(key);
	}

}

void Csnake::endlessMode() {

	this->gameInit();
	int snakeSize = size;
	bool loop = TRUE;
	while (loop) {
		
		this->gameDraw();
		this->gameMove();
		this->gameKey();
		this->endlessModeHeiWall();
		if (snakeSize < size && !(minSleep > sleep))
		{
			snakeSize = size;
			sleep -= 5;
		}
		if (size >= 25)
		{
			loop = FALSE;
			break;
		}
		Sleep(sleep);
	}
	gameVictory();
}

void Csnake::endlessModeHeiWall(){

	if (this->coordinates[0].x <= 20) {
		this->coordinates[0].x = 800-20;
	}
	else if (this->coordinates[0].x >= 800-20) {
		this->coordinates[0].x = 20;
	}
	else if (this->coordinates[0].y <= 20) {
		this->coordinates[0].y = 600 - 20;
	}
	else if (this->coordinates[0].y >= 600 - 20) {
		this->coordinates[0].y = 20;
	}
}

void Csnake::difficultMode() {

	this->gameInit();
	Key key = difficult;
	int snakeSize = size;
	bool loop = TRUE;
	while (loop) {

		this->gameDraw();//初始化界面
		this->gameMove();//移动函数
		this->gameKey();//按键反应
		this->simpleModeHeiWall(key);//判断是否撞墙
		if (snakeSize < size && !(minSleep > sleep))
		{
			snakeSize = size;

			sleep -= 5;
		}
		if (size >= 25)
		{
			loop = FALSE;
			break;
		}
		Sleep(sleep);
	}
	gameVictory();
}