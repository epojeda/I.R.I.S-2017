#include <unistd.h>
#include <sys/time.h>
#include <termios.h>
#include <stdio.h>
struct termios mNewTerm;
struct termios mOrgTerm;
int Lspeed = 0;
int Rspeed = 0;
void initKey()
{
	// Sets the terminal to get real-time keyboard values
	tcgetattr(0, &mOrgTerm);
	mNewTerm=mOrgTerm;
	mNewTerm.c_lflag &= ~ICANON;
	mNewTerm.c_lflag &= ~ECHO;
	mNewTerm.c_cc[VMIN] = 1;
	mNewTerm.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &mNewTerm);
}

void resetKey()
{
	tcsetattr(0, TCSANOW, &mOrgTerm);
}

char getKey()
{
	struct timeval aux_time = {0, 0};
	fd_set rfds;
	char key = 0;
	FD_SET(0, &rfds);
	if(select(1, &rfds, 0, 0, &aux_time))
		read(0, &key, 1);
	return key;
}

int forward()
{
	printf("Moving forward \n");
	Lspeed = Lspeed+ 10;
	Rspeed = Rspeed + 10;
	printf("Left speed =" "%d \n", Lspeed);
	printf("Right speed =" "%d \n", Rspeed);
}

int right()
{
	printf("Turning right \n");
	Lspeed = Lspeed + 10;
	Rspeed = Rspeed - 10;
	printf("Left speed =" "%d \n", Lspeed);
	printf("Right speed =" "%d \n", Rspeed);
}

int left()
{
	printf("Turning left \n");
	Lspeed = Lspeed - 10;
	Rspeed = Rspeed + 10;
	printf("Left speed =" "%d \n", Lspeed);
	printf("Right speed =" "%d \n", Rspeed);
}

int backward()
{
	printf("Moving backwards \n");
	Lspeed = Lspeed - 10;
	Rspeed = Rspeed - 10;
	printf("Left speed =" "%d \n", Lspeed);
	printf("Right speed =" "%d \n", Rspeed);
}

int stop()
{
	printf("STOP!!! \n");
	Lspeed = 0;
	Rspeed = 0;
	printf("Left speed =" "%d \n", Lspeed);
	printf("Right speed =" "%d \n", Rspeed);
}

int main()
{
	initKey();
	char key;
	while (1)
	{		
		key = getKey();
		if (key != 0)
		{	
			printf("%c ",key);
			printf("%d \n",key);
		}
		switch (key)
		{
			case 'A': // forward arrow key
				forward();
				break;
			case 'B':
				backward();
				break; 
			case 'C':
				right();
				break;
			case 'D':
				left();
				break; 
			case 32:
				stop();
				break;
			case 'x': //exit
				resetKey();
				return 0;
		}
	}
}




