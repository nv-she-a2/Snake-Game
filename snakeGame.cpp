//
//  SnakeGame
//
//  Created by Anvesha Barnwal on 21/06/20.
//  Copyright © 2020 Anvesha Barnwal. All rights reserved.
//

#include<iostream>
#include<cstdlib>
#include<vector>
#include"conio.h"
using namespace std;

bool gameOver;
const int width=40;
const int height=20;
int fruitx, fruity, score,nTail,speed=500000;
vector<int> tailX,tailY;
enum eDirection { STOP=0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

int get_direction();

void Setup()
{
	gameOver = false;
	dir = RIGHT;
	tailX.push_back(width/2);
	tailY.push_back(height/2);
    nTail++;
	fruitx=rand()%(width-1)+1;
    fruity=rand()%(height-1)+1;
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
		for(int j=0;j<=width;j++)
		{
			if(j==0 || j==width)
				cout<<"#";
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
	int prevX=tailX[0],prevY=tailY[0];
	switch(dir)
	{
		case LEFT:
			tailX[0]--;
			break;
		case RIGHT:
			tailX[0]++;
			break;
		case UP:
			tailY[0]--;
			break;
		case DOWN:
			tailY[0]++;
			break;
		default:
			break;
	}
	if(tailX[0]==0 || tailX[0]==width || tailY[0]==0 || tailY[0]==height)
		gameOver=true;
	if(tailX[0]==fruitx && tailY[0]==fruity)
	{
		score+=10;
		tailX.push_back(tailX[nTail-1]);
		tailY.push_back(tailY[nTail-1]);
		nTail++;
        speed-=100;
		fruitx=rand()%(width-1)+1;
		fruity=rand()%(height-1)+1;
	}
	for(int i=1;i<nTail;i++)
	{
		int tempX=tailX[i],tempY=tailY[i];
		tailX[i]=prevX;
		tailY[i]=prevY;
		if(tailX[0]==tailX[i] && tailY[0]==tailY[i])
			gameOver=true;
		if(fruitx==tailX[i] && fruity==tailY[i])
		{
			fruitx=rand()%(width-1)+1;
            fruity=rand()%(height-1)+1;
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
    initTermios();
	Setup();
	while(!gameOver)
	{
		Draw();
		if(kbhit())
		{
			Input();
		}
		Logic();
        usleep(speed);
	}
    resetTermios();
	return 0;
}
