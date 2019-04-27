#include<graphics.h>
#include <stdio.h>
#include <conio.h>//接收键盘输入
#include <time.h>

#define snakeL 100 //蛇的最大长度
#define snakeS 10//蛇的默认移动距离

//定义坐标结构体
typedef enum Ch
{
	up = 72,
	down = 80,
	left = 75,
	right = 77
}CH;

struct Coor
{
	int x;
	int y;
}COOR;
struct Food
{
	Coor fzb;//食物坐标
	int flag;//flag = 0,食物没被吃 flag = 1，食物被吃
}FOOD;
//定义蛇的结构体
struct Snake
{
	Coor szb[snakeL];//蛇每一节坐标
	int n;//蛇的长度
	CH ch;//蛇的方向
}SNAKE;

void Draw();
void Init();
void Move();
void ChangeFX();
void DrawFood();
void FoodZB();
int Eat();
void PZJC();
void Over();


int main(){
	Init();
	int flag = 0;
	while(1)
	{
		while(!_kbhit()){
			if (flag == 0)
			{
				FoodZB();
				}
			DrawFood();
			PZJC();
			Move();
			flag = Eat();
			Sleep(100);
		}
		ChangeFX();
	}
	getchar();
	return 0;
}

void Init(){
	initgraph(800,600);
	cleardevice();//清除屏幕
	rectangle(0,0,10,10);
	SNAKE.szb[0].x = 0;
	SNAKE.szb[0].y = 0;
	SNAKE.n = 1;
	SNAKE.ch = right;
	FOOD.flag = 0;

}

void Move(){
	for (int i = SNAKE.n;i > 0;i--)
	{
		SNAKE.szb[i].x = SNAKE.szb[i - 1].x;
		SNAKE.szb[i].y = SNAKE.szb[i - 1].y;
	}
	switch (SNAKE.ch)
	{
	case up:
		SNAKE.szb[0].y -= snakeS;
		break;
	case down:
		SNAKE.szb[0].y += snakeS;
		break;
	case right:
		SNAKE.szb[0].x += snakeS;
		break;
	case left:
		SNAKE.szb[0].x -= snakeS;
		break;	
	}
	Draw();
}
void Draw(){
	for(int i = SNAKE.n-1;i >= 0;i--){
		rectangle(SNAKE.szb[i].x,SNAKE.szb[i].y,
		SNAKE.szb[i].x+snakeS,SNAKE.szb[i].y+snakeS);
	}
	setcolor(RGB(0,0,0));
	rectangle(SNAKE.szb[SNAKE.n].x,SNAKE.szb[SNAKE.n].y,
			SNAKE.szb[SNAKE.n].x+snakeS,
			SNAKE.szb[SNAKE.n].y+snakeS);
	setcolor(RGB(255,255,255));
	rectangle(SNAKE.szb[SNAKE.n-1].x,SNAKE.szb[SNAKE.n-1].y,
		SNAKE.szb[SNAKE.n-1].x+snakeS,
		SNAKE.szb[SNAKE.n-1].y+snakeS);

}
//改变方向
void ChangeFX(){
	int move;
	move = _getch();
	switch (move)
	{
	case up:
		if (SNAKE.ch != down)
		{
			SNAKE.ch = up;
		}
		break;
	case down:
		if (SNAKE.ch != up)
		{
			SNAKE.ch = down;
		}
		break;
	case right:
		if (SNAKE.ch != left)
		{
			SNAKE.ch = right;
		}
		break;
	case left:
		if (SNAKE.ch != right)
		{
			SNAKE.ch = left;
		}
		break;
	}
}

void DrawFood(){
	setcolor(WHITE);
	roundrect(FOOD.fzb.x,FOOD.fzb.y,
		FOOD.fzb.x+snakeS,
		FOOD.fzb.y+snakeS,10,10);
}

void FoodZB(){
	srand(unsigned (time(NULL)));
	FOOD.fzb.x =rand()%(800/snakeS)*snakeS;
	FOOD.fzb.y =rand()%(600/snakeS)*snakeS;
	FOOD.flag = 1;
}
int Eat(){
	if (SNAKE.szb[0].x == FOOD.fzb.x && SNAKE.szb[0].y == FOOD.fzb.y)
	{
		SNAKE.n+=3;
		setcolor(RGB(0,0,0));
		roundrect(FOOD.fzb.x,FOOD.fzb.y,
			FOOD.fzb.x+snakeS,
			FOOD.fzb.y+snakeS,10,10);
		setcolor(WHITE);
		FOOD.flag = 0;
		return FOOD.flag;
	}
	return 1;
}


//碰撞检查
void PZJC(){
	if (SNAKE.szb[0].x<0||SNAKE.szb[0].x>800
		|| SNAKE.szb[0].y<0||SNAKE.szb[0].y>600)
	{
		Over();
	}
	for (int i = SNAKE.n-2;i > 0;i--)
	{
		if (SNAKE.szb[0].x == SNAKE.szb[i].x
			&& SNAKE.szb[0].y == SNAKE.szb[i].y)
		{
			Over();
		}
	}
}

void Over(){
	cleardevice();
	setcolor(RED);
	settextstyle(50,0,L"华文彩云");
	outtextxy(100,50,L"Game Over");
	getch();
	closegraph();
}