#include<bits/stdc++.h>
#include<conio.h>
#include<windows.h>

using namespace std;

bool gameOver = false;	//0 for false and 1 for true
int score = 0, i=-1, j=-1;	//i - tail and j - head
char currTailDir = 'r', currHeadDir = 'r';

struct Position
{
	short x;
	short y;
};

Position head = {4,1};
Position tail = {1,1};
Position prey = {15,99};

struct Turns
{
	//for index position
	short x;
	short y;
	//for direction
	char nxtDir;
};

Turns turn[100];	//Max 100 turns ar a time allowed

void gotoxy(short x, short y)
{
	COORD pos = {x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void createBox()
{
	for(int i=1;i<=45;i++)
	{
		for(int j=1;j<=100;j++)
			if(i==1 || i==45)
				cout<<char(219);
			else
			{
				if(j==1 || j==100)
					cout<<char(219);
				else
					cout<<" ";
			}
		cout<<"\n";
	}
}

bool checkIntersection(Position obj)
{
	int var=i;
	Position temp = tail;
	char tempDir = currTailDir;
	while(temp.x!=head.x || temp.y!=head.y)
	{
		if(temp.x==obj.x && temp.y==obj.y)
			return true;
		switch(tempDir)
		{
			case 'r' : if(temp.x==98)	temp.x=1; else temp.x+=1;	break;
			case 'l' : if(temp.x==1)	temp.x=98; else temp.x-=1;	break;
			case 'u' : if(temp.y==1)	temp.y=43; else temp.y-=1; 	break;
			case 'd' : if(temp.y==43)	temp.y=1; else temp.y+=1;	break;
		}
		if(var>=0)
			if(temp.x==turn[var].x && temp.y==turn[var].y)
			{	
				tempDir=turn[var].nxtDir;
				if(tempDir==currHeadDir)
					var=-1;
				else
					var+=1;
			}	
	}
	return false;
}

void showPrey()
{
	srand(time(0));
	prey.x = 1 + (rand() % 98);
	prey.y = 1 + (rand() % 43);
		/*gotoxy(105,5);
		cout<<"       ";
		gotoxy(105,5);
		cout<<prey.x<<" "<<prey.y;
		*/
	while(checkIntersection(prey))
	{
		prey.x = 1 + (rand() % 98);
		prey.y = 1 + (rand() % 43);
	}
	gotoxy(prey.x,prey.y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
	cout<<(char)219;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
}

void checkInput()
{
	while(_kbhit())
	{
		char key = getch();
		j+=1;
		if(j==0)
			i=0;
		switch(key)
		{
			case 'w' : 
				if(currHeadDir!='d') 
				{
					turn[j].nxtDir = currHeadDir = 'u';
				}
				break;
				
			case 's' : 
				if(currHeadDir!='u')
				{
					turn[j].nxtDir = currHeadDir = 'd';
				}	
				break;
				
			case 'a' : 
				if(currHeadDir!='r') 
				{
					turn[j].nxtDir = currHeadDir = 'l';	
				}
				break;

			case 'd' : 
				if(currHeadDir!='l') 
				{
					turn[j].nxtDir = currHeadDir = 'r';
				}
				break;

			case 27  : gameOver=true;	break; 
		}
		turn[j].x = head.x;
		turn[j].y = head.y;
	}
}

void deleteBody()
{
	gotoxy(tail.x,tail.y);
	cout<<" ";
	switch(currTailDir)
	{
		case 'r' : if(tail.x==98) tail.x=1; else tail.x+=1;	break;
		case 'l' : if(tail.x==1) tail.x=98; else tail.x-=1;	break;
		case 'u' : if(tail.y==1) tail.y=43; else tail.y-=1;	break;
		case 'd' : if(tail.y==43) tail.y=1; else tail.y+=1;	break;
	}
	if(i>=0)
		if(tail.x==turn[i].x && tail.y==turn[i].y)
		{
			currTailDir=turn[i].nxtDir;
			if(currTailDir==currHeadDir)
				i=j=-1;
			else
				i+=1;
		}
}

void moveUp()
{
	if(head.y==1)
		head.y=44;
	/*if(tail.y==0)
		tail.y=43;*/
	/*if(head.y-1==prey.y && head.x==prey.x)
		score++;*/
	gotoxy(head.x,head.y-1);
	cout<<char(233);
	head.y-=1;
}

void moveDown()
{
	if(head.y==43)
		head.y=0;
	/*if(tail.y==44)
		tail.y=1;*/
	/*if(head.y+1==prey.y && head.x==prey.x)	
		score++;*/
	gotoxy(head.x,head.y+1);
	cout<<char(233);
	head.y+=1;
}

void moveLeft()
{
	if(head.x==1)
		head.x=99;
	/*if(tail.x==0)
		tail.x=98;*/
	/*if(head.x-1==prey.x && head.y==prey.y)
		score++;*/
	gotoxy(head.x-1,head.y);
	cout<<char(233);
	head.x-=1;
}

void moveRight()
{		
	if(head.x==98)
		head.x=0;
	/*if(tail.x==99)
		tail.x=1;*/
	/*if(head.x+1==prey.x && head.y==prey.y)
		score++;*/
	//Code for snake head touching snake body is left
	gotoxy(head.x+1,head.y);
	cout<<char(233);		//PRINT
	head.x+=1;
}

void moveSnake()
{
	//Delete '.'
	deleteBody();
	//Shift '.'
	label : gotoxy(head.x,head.y);	//LABEL
	cout<<".";	
	switch(currHeadDir)
	{
		case 'u': moveUp();		break;
		case 'd': moveDown();	break;
		case 'l': moveLeft();	break;
		case 'r': moveRight();	break;
	}
	if(head.x==prey.x && head.y==prey.y)
	{
		score++;
		showPrey();
		goto label;
	}
	Sleep(150);
	gameOver = checkIntersection(head);
}

int main()
{
	system("cls");
	gotoxy(70,30);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
	cout<<"WELCOME to the \"GAME OF SNAKES\"";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
	gotoxy(72,32);
	cout<<"Press any key to continue";
	getch();
	
	system("cls");
	createBox();
	gotoxy(1,1);
	cout<<"...";
	cout<<char(233);
	showPrey();
	while(!gameOver)
	{
		moveSnake();
		checkInput();
		gotoxy(0,46);
		cout<<"SCORE : "<<score;
		//gotoxy(105,5);
		//cout<<"       ";
		//gotoxy(105,5);
		//cout<<tail.x<<" "<<tail.y<<" "<<currTailDir;
		//showPrey();	//To draw prey randomly on the screen except for the positions of snake body if score updates
	}
}
