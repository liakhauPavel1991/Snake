#include<stdio.h>
#include<conio.h>
#include<locale.h>
#include<windows.h>
#include<stdlib.h>
#include<iso646.h> 
#include<iostream>
#include<time.h>

#define WIDTH 40
using namespace std;

void setcur (int x, int y);
void setBox (int height, int width, char box[][WIDTH]);
void Print (int height, int width, char box[][WIDTH]);
void SpeedSnake (int * speed);

class Snake 
{
	public:
		int y;
		int x;
		Snake (int y, int x)
		{
			this->y = y;
			this->x = x;
		}
		Snake ()
		{
			this->y = 0;
			this->x = 0;
		}
		
};

int main ()
{
	system ("MODE CON: COLS=140 LINES=70");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251); 
	srand(time(0));
		
	int width = WIDTH;  // width ~ x
	int height = width/2; // height ~ y
	int speed = 300; // 1000 = 1 second
	int score = 0;
	
	char box [height][WIDTH]; // main square
	setBox (height, width, box); // set
	char key = ' '; 
	char rememberKey = ' ';
	char checkSlam = ' ';
 	int i, j;
 	
	char body = 'O'; // snake	(head)
	int before_x, before_y;	
	int x, y;
	y = height - height/2;
	x = width / 2;	
	box[y][x] = body;
	
	char point = '*'; // point
	int py, px;
	py = rand()%(height/2)+(height/2-1);
	px = rand()%(width/2)+1;
	
	int countBody = 1; // body of snake
	int sizeArray = (width-2)*(height-2);
	Snake coordBody[sizeArray] = {};	
	coordBody[0].y = y;
	coordBody[0].x = x;
	
	
	while(px == x and py == y)
	{
		px = rand()%(width/2)+1;
		py = rand()%(height/2)+(height/2-1);
	}
	box[py][px] = point;
	
	clock_t startTime, endTime, clockTicksTaken;
	fflush(stdin);
	
	do
	{		
		setcur(0, 0);
		// --------------------------------------------------------------------------------Create snake
		for(i=0; i<countBody; i++)  
		{
			box[coordBody[i].y][coordBody[i].x] = body;
		}
		// --------------------------------------------------------------------------------Drawing area
		Print (height, width, box);
		cout << "Score: " << score << endl;	

		// --------------------------------------------------------------------------------Clear point
		for (i=0; i<countBody; i++) 
		{
			box[coordBody[i].y][coordBody[i].x] = ' ';
		}

				
		//---------------------------------------------------------------------------------Remember coordinates
		before_y = y;
		before_x = x; 
		
	
		
		//SpeedSnake (&speed); //  ----------------------------------------------------------Waiting
		Sleep(speed);
		
		rememberKey = key;	
		{// -------------------------------------------------------------------------------Check keys
		if (GetAsyncKeyState('W') == 1)  // Check pressed
		{
			key = 'w';
		} 
		if (GetAsyncKeyState('S') == 1)
		{
			key = 's';		
		} 
		if (GetAsyncKeyState('A') == 1)
		{
			key = 'a';
		} 
		if (GetAsyncKeyState('D') == 1)
		{
			key = 'd';
		} 
		if (GetAsyncKeyState('W')>>(8*sizeof(short int)-1) == -1) // Check clamped
		{
			key = 'w';
		} 
		if (GetAsyncKeyState('S')>>(8*sizeof(short int)-1) == -1)
		{
			key = 's';		
		} 
		if (GetAsyncKeyState('A')>>(8*sizeof(short int)-1) == -1)
		{
			key = 'a';
		} 
		if (GetAsyncKeyState('D')>>(8*sizeof(short int)-1) == -1)
		{
			key = 'd';
		} 
		
		if (key == 'w') y--;  
		if (key == 's') y++;
		if (key == 'a') x--;
		if (key == 'd') x++;
		
		
		
		if (x==coordBody[1].x and y==coordBody[1].y) //------------------------------------чтобы змейка не шла в обратном направлении
		{
			key = rememberKey;
			y = before_y;
			x = before_x; 
			if (key == 'w') y--;  
			if (key == 's') y++;
			if (key == 'a') x--;
			if (key == 'd') x++;
		}
		if (box[y][x] == '#') //----------------------------------------------------------- Check out
		{
			key = 'q';
		}
	
		}	
					
		
		// -------------------------------------------------------------------------------- Eating point
		if (box[y][x] == '*') 
		{
			score++;
			px = rand()%(width-2)+1;
			py = rand()%(height-2)+1;			
			while(box[py][px] == 'O' or px == x and py == y)
			{
				px = rand()%(width-2)+1;
				py = rand()%(height-2)+1;			
			}	
			box[py][px] = point; 
			
			countBody++;
			speed = speed-speed/10;
		}
		
		
		// ----------------------------------------------------------------------------------New coordinates
		for(i=countBody-1; i>0; i--)
		{
			coordBody[i].y = coordBody[i-1].y;
			coordBody[i].x = coordBody[i-1].x;
		}
		coordBody[0].y = y;
		coordBody[0].x = x;
	
		for (i=1; i<countBody; i++)
		{
			if(coordBody[0].y == coordBody[i].y and coordBody[0].x == coordBody[i].x)	
			{
				key = 'q';
			}
		}	

		
	
	} while (key != 'q' and checkSlam == ' ');
	getch();
	return 0;
}

void SpeedSnake (int *speed)
{
	clock_t startTime, endTime, clockTicksTaken;
	startTime = clock();
		do 
		{			
		endTime = clock();
		clockTicksTaken = endTime - startTime;
		} while (clockTicksTaken < *speed );
}

void setBox (int height, int width, char box[][WIDTH])
{
	int i, j;
	for (i=0; i<height; i++)
		for (j=0; j<width; j++)
		{
			box [i][j] = ' ';
		}
	for (i=0; i<height; i+=(height-1))
		for (j=0; j<width; j++)
		{
			box [i][j] = '#';
		}
	for (i=0; i<height; i++)
		for (j=0; j<width; j+=(width-1))
		{
			box [i][j] = '#';
		}
}

void Print (int height, int width, char box[][WIDTH])
{
	int i, j;
	for (i=0; i<height; i++)
	{
			for (j=0; j<width; j++)
		{
			printf("%c", box[i][j]);
		}
		printf("\n");
	}

}

void setcur (int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


