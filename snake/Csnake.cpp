#define _CRT_SECURE_NO_WARNINGS
#include "Csnake.h"

//�ߵ��ٶ���ʱ��仯���仯 ʱ��Խ�� �ٶ�Խ��
//���庯��
void Csnake::gameInit(){

	initgraph(1000,600);
	
	this->size = 2;//���� 
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
	
	//��ʼ���ߵ�����
	this->snakeTongue();
	this->snakeBody();
	this->snakeEye();
	//ʳ���ʼ��
	this->snakeFood();
	//��ʼ��ǽ
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
		switch (_getch())//��72     ��80    ��75    ��77
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
	settextstyle(40, 0, _T("΢���ź�"));
	RECT r1 = { 800, 10, 1000, 600 };
	drawtext(_T("��Ϸ����"), &r1, DT_CENTER);
	settextstyle(30, 0, _T("��Բ"));
	settextcolor(BLUE);
	RECT r2 = { 800, 60, 1000, 600 };
	drawtext(_T("ǰ ��W ��"), &r2, DT_CENTER);

	RECT r3 = { 800, 110, 1000, 600 };
	drawtext(_T("�� ��S ��"), &r3, DT_CENTER);

	RECT r4 = { 800, 160, 1000, 600 };
	drawtext(_T("�� ��A ��"), &r4, DT_CENTER);

	RECT r5 = { 800,210, 1000, 600 };
	drawtext(_T("�� ��D ��"), &r5, DT_CENTER);


	settextstyle(25, 0, _T("��Բ"));
	RECT r6 = { 800,300, 1000, 600 };
	drawtext(_T("��ͣ : �ո�"), &r6, DT_CENTER);

	RECT r7 = { 800,350, 1000, 600 };
	drawtext(_T("���ز˵� : ESC"), &r7, DT_CENTER);
//
	int fensu_int = this->size - 2;
	TCHAR fensu_char[5];
	_itow(fensu_int,fensu_char,5);
	settextstyle(20, 0, _T("����"));
	RECT r8 = { 800,410, 1000, 600 };
	drawtext(_T("������"), &r8, DT_LEFT);

	setfillcolor(RGB(255, 210, 73));
	fillrectangle(800, 430, 1000, 500);

	settextstyle(70, 0, _T("��Բ"));
	RECT r9 = { 800,430, 1000, 500 };
	drawtext(fensu_char, &r9, DT_CENTER);

	settextstyle(20, 0, _T("����"));
	RECT r10 = { 800,510, 1000, 600 };
	drawtext(_T("��ǰ�ٶȣ�(��)"), &r10, DT_LEFT);
	fillrectangle(800, 530, 1000, 600);


	TCHAR speed_char[5];
	_itow(sleep,speed_char,5);
	settextstyle(70, 0, _T("��Բ"));
	RECT r11 = { 800,530, 1000, 600 };
	drawtext(speed_char, &r11, DT_CENTER);

	settextstyle(15, 0, _T("��Բ"));
	RECT r55 = { 800,250, 1000, 600 };
	drawtext(_T("����ٶȣ�10"), &r55, DT_CENTER);

	RECT r51 = { 800,270, 1000, 600 };
	drawtext(_T("��󳤶ȣ�100"), &r51, DT_CENTER);

}

void Csnake::gameVictory()
{
	closegraph();
	initgraph(600, 300);
	setbkcolor(RGB(128, 128, 128));
	cleardevice();
	//
	settextcolor(RED);
	settextstyle(60, 0, _T("����"));
	RECT r = { -10, 50, 590, 300 };
	drawtext(_T("    ��ϲ��Ӯ��   "), &r, DT_CENTER);
	//
	settextcolor(WHITE);
	settextstyle(30, 0, _T("΢���ź�"));
	RECT r2 = { 0, 150, 600, 300 };
	drawtext(_T("���س����ز˵�"), &r2, DT_CENTER);
	//
	settextstyle(0, 0, _T("΢���ź�"));
	TCHAR size_char[5];
	_itow(size, size_char, 5);
	RECT r3 = { 0, 200, 600, 300 };
	drawtext(_T("���÷�:"), &r3, DT_CENTER);

	//����
	settextcolor(YELLOW);
	RECT r33 = { 0, 220, 600, 300 };
	drawtext(size_char, &r33, DT_CENTER);
	//


	switch (_getch())
	{
		case 13:this->initmain(); break;
	}
}

//ײǽ
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
	settextstyle(60, 0, _T("΢���ź�"));
	RECT r1 = { 0, 150, 300, 300 };
	drawtext(_T("����"), &r1, DT_CENTER);
	RECT r2 = { 0, 150, 900, 300 };
	drawtext(_T("�˵�"), &r2, DT_CENTER);
	settextstyle(0, 0, _T("΢���ź�"));
	RECT r3 = { 0, 250, 590, 300 };
	drawtext(_T("ʹ�á� ������ѡ��"), &r3, DT_CENTER);

	settextcolor(RED);
	settextstyle(60, 0, _T("����"));
	RECT r = { -10, 50, 590, 300 };
	drawtext(_T("    ��ϲ��������   "), &r, DT_CENTER);
}

void Csnake::switchSelection_Over(int i){
	drawText_Over();
	settextcolor(BLUE);
	settextstyle(60, 0, _T("΢���ź�"));
	if(i == 1){
		RECT r1 = { 0, 150, 300, 300 };
		drawtext(_T("����"), &r1, DT_CENTER);
	}
	if(i == 2){
		RECT r2 = { 0, 150, 900, 300 };
		drawtext(_T("�˵�"), &r2, DT_CENTER);
	}
}

//���˵��Ӻ���
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
	drawtext(_T("��ӭ����̰������Ϸ"), &r1, DT_CENTER);
	settextcolor(BLUE);

	drawtext(_T("��   ��ģʽ   ��"), &r2, DT_CENTER);

	drawtext(_T("��   �޾�ģʽ   ��"), &r3, DT_CENTER);

	drawtext(_T("��   ����ģʽ   ��"), &r4, DT_CENTER);

	drawtext(_T("ʹ�á�������ѡ��"), &r5, DT_CENTER);
}

void Csnake::switchSelection(int ii) {

	Drawtext();

	settextcolor(RGB(255, 128, 0));
	if (ii == 1) {
		RECT r = { 0, 100, 300, 300 };
		drawtext(_T("��   ��ģʽ   ��"), &r, DT_CENTER);
	}
	if (ii == 2) {
		RECT r = { 0, 150, 300, 300 };
		drawtext(_T("��   �޾�ģʽ   ��"), &r, DT_CENTER);
	}
	if (ii == 3) {
		RECT r = { 0, 200, 300, 300 };
		drawtext(_T("��   ����ģʽ   ��"), &r, DT_CENTER);
	}

}
//���˵�
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
//��ť�¼�
void Csnake::Esc_initSrart(){

	this->initmain();

}
//��ͼ����
void Csnake::snakeBody(){
	for (int i = 0; i < this->size; i++) {
		//ͷ��ɫ
		setfillcolor(GREEN);
		solidcircle(this->coordinates[0].x, this->coordinates[0].y, 10);
		//��
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
					x + 5 + 15 ,  y - 2,//��
					x + 5 + 8 ,  y,    //��
					x + 5 + 15 ,  y + 2,//��
					x + 5 ,  y + 2,
					x + 5,  y - 2
			
		};
		ppts = pts;
	}
	else if (this->direction == LEFT) {

		int pts[] = {

					x - 5 ,  y - 2 ,
					x - 5 - 15 ,  y - 2,//��
					x - 5 - 8 ,  y,    //��
					x - 5 - 15 ,  y + 2,//��
					x - 5 ,  y + 2,
					x - 5,  y - 2
		};
		ppts = pts;
	}
	else if (this->direction == DOWN)
	{
		int pts[] = {

					x - 2 ,  y + 5,
					x - 2 ,  y + 5 + 15,//��
					x     ,  y + 5 + 8,    //��
					x + 2 ,  y + 5 + 15,//��
					x + 2 ,  y + 5,
					x - 2 ,  y + 5
		};
		ppts = pts;
	}
	else if (this->direction == UP)
	{
		int pts[] = {

					x - 2 ,  y - 5,
					x - 2 ,  y - 5 - 15,//��
					x     ,  y - 5 - 8,    //��
					x + 2 ,  y - 5 - 15,//��
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
//��
	for (x = 0,xx = 20,y = 0,yy = 20;/*y <= y_max,*/ yy <= y_max; y += 20,yy += 20){

		fillrectangle(x, y, xx, yy);

	}
//��
	for (y = 0, yy = 20,x = 0, xx = 20; /*x <= x_max,*/ xx <= x_max; x += 20, xx += 20) {

		fillrectangle(x, y, xx, yy);

	}
//��
	for (x = 800-20, xx = 800, y = 0, yy = 20; /*y <= y_max,*/ yy <= y_max; y += 20, yy += 20) {

		fillrectangle(x, y, xx, yy);

	}
//��
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
//ģʽ
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

		this->gameDraw();//��ʼ������
		this->gameMove();//�ƶ�����
		this->gameKey();//������Ӧ
		this->simpleModeHeiWall(key);//�ж��Ƿ�ײǽ
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