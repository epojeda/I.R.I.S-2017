#include <unistd.h>
#include <sys/time.h>
#include <termios.h>
#include <stdio.h>
//#include <fstream>
//#include <iostream>
struct termios mNewTerm;
struct termios mOrgTerm;
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
}

int backward()
{
	printf("Moving backwards \n");
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
		if (key == 65)
		{
			forward();
		}
		if (key == 66)
		{
			backward();
		}
	}
	resetKey();
	return 0;
}


