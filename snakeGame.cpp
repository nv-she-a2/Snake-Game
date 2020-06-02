#include<iostream>
#include <unistd.h>
#include <termios.h>
#include<cstdlib>
using namespace std;

bool gameOver;
const int width=40;
const int height=20;
int x,y,fruitx,fruity,score;
int tailX[100],tailY[100],nTail=0;
enum eDirection { STOP=0, LEFT, RIGHT, UP, DOWN};
eDirection dir,prevDir=RIGHT;

int get_direction();

void Setup()
{
	gameOver=false;
	dir= STOP;
	x=width/2;
	y=height/2;
	fruitx=rand()%width;
	fruity=rand()%height;
	score=0;
}

void Draw()
{
	system("clear");
	cout<<"Score: "<<score<<endl;
	for(int i=0;i<width+1;i++)
		cout<<"#";
	cout<<endl;
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			if(j==0 || j==width-1)
				cout<<"#";
			if(i==y && j==x)
				cout<<"O";
			else if(i==fruity && j==fruitx)
				cout<<"F";
			else
			{
				bool print=false;
				for(int k=0;k<nTail;k++)
				{
					if(i==tailY[k] && j==tailX[k])
					{
						cout<<"O";
						print=true;
					}
				}
				if(!print)
					cout<<" ";
			}
		}
		cout<<endl;
	}
	for(int i=0;i<width+1;i++)
		cout<<"#";
	cout<<endl;
}

void Input()
{
	switch(get_direction())
	{
		case 68:
			dir=LEFT;
			break;
		case 67:
			dir=RIGHT;
			break;
		case 65:
			dir=UP;
			break;
		case 66:
			dir=DOWN;
			break;
		case 'x':
		case 'X':
		case 'q':
		case 'Q':
			gameOver=true;
			break;
	}
}

void Logic()
{
	int prevX=x,prevY=y;
	switch(dir)
	{
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		default:
			break;
	}
	if(x==-1 || x==width-1 || y==-1 || y==height)
		gameOver=true;
	if(x==fruitx && y==fruity)
	{
		score+=10;
		nTail++;
		fruitx=rand()%(width-1);
		fruity=rand()%height;
	}
	for(int i=0;i<nTail;i++)
	{
		int tempX=tailX[i],tempY=tailY[i];
		tailX[i]=prevX;
		tailY[i]=prevY;
		if(x==tailX[i] && y==tailY[i])
			gameOver=true;
		if(fruitx==tailX[i] && fruity==tailY[i])
		{
			fruitx=rand()%(width-1);
			fruity=rand()%height;
		}
		prevX=tempX;
		prevY=tempY;
	}
}

int get_direction() {
	int direction = 0;
	for(int i=0;i<3;i++) {
		direction = getchar();
		if(direction!=27 && direction!=91 && (direction<65 || direction>68))
			return direction;
	}
	return direction;
}

int main()
{
	srand(time(NULL));
	Setup();
	struct termios oldattr, newattr;
    tcgetattr(0, &oldattr); //grab old terminal i/o settings
    newattr = oldattr; //make new settings same as old settings
    newattr.c_lflag &= ~ICANON; //disable buffered i/o
    newattr.c_lflag &= ~ECHO; //disable echo mode
    tcsetattr(0, TCSANOW, &newattr); //apply terminal i/o settings
	while(!gameOver)
	{
		Draw();
		Input();
		Logic();
	}
	tcsetattr(0, TCSANOW, &oldattr);//apply old terminal i/o settings
	return 0;
}