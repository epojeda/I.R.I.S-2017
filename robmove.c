#include <unistd.h>
#include <sys/time.h>
#include <termios.h>
#include <stdio.h>
#include <fstream>
#include <iostream>

char LMOTOR_SPEED_SP[] = "/sys/class/tacho-motor/motor1/speed_sp"; 
char LMOTOR_COMMAND[] = "/sys/class/tacho-motor/motor1/command"; 
char RMOTOR_SPEED_SP[] = "/sys/class/tacho-motor/motor0/speed_sp";
char RMOTOR_COMMAND[] = "/sys/class/tacho-motor/motor0/command";
using namespace std;

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

int Lmotor()
{
	ofstream Lspeed_sp;
	ofstream Lcommand;
	Lspeed_sp.open(LMOTOR_SPEED_SP);
	if(!Lspeed_sp.is_open())
	{
		cout << "failed to open file Lspeed_sp";
		return -1; //failed to open device
	}
	Lcommand.open(LMOTOR_COMMAND);
	if(!Lcommand.is_open())
	{
		cout << "Failed to open file Lspeed_sp";
		return -1; //failed to open device
	}

	cout << "Ready!";
	Lspeed_sp << Lspeed << endl;
	Lcommand << "run-forever" << endl;
	Lcommand.close();
	Lspeed_sp.close();
}

int Rmotor()
{
	ofstream Rspeed_sp;
	ofstream Rcommand;
	Rspeed_sp.open(RMOTOR_SPEED_SP);
	if(!Rspeed_sp.is_open())
	{
		cout << "failed to open file Lspeed_sp";
		return -1; //failed to open device
	}
	Rcommand.open(RMOTOR_COMMAND);
	if(!Rcommand.is_open())
	{
		cout << "Failed to open file Lspeed_sp";
		return -1; //failed to open device
	}

	cout << "Ready!";
	Rspeed_sp << Rspeed << endl;
	Rcommand << "run-forever" << endl; 
	Rcommand.close();
	Rspeed_sp.close();
}
int forward()
{
	printf("Moving forward \n");
	Lspeed = Lspeed+ 10;
	Rspeed = Rspeed + 10;
	printf("Left speed =" "%d \n", Lspeed);
	printf("Right speed =" "%d \n", Rspeed);
	Lmotor(); 
	Rmotor();
}

int right()
{
	printf("Turning right \n");
	Lspeed = Lspeed + 10;
	Rspeed = Rspeed - 10;
	printf("Left speed =" "%d \n", Lspeed);
	printf("Right speed =" "%d \n", Rspeed);
	Lmotor();
	Rmotor();
}

int left()
{
	printf("Turning left \n");
	Lspeed = Lspeed - 10;
	Rspeed = Rspeed + 10;
	printf("Left speed =" "%d \n", Lspeed);
	printf("Right speed =" "%d \n", Rspeed);
	Lmotor();
	Rmotor();
}

int backward()
{
	printf("Moving backwards \n");
	Lspeed = Lspeed - 10;
	Rspeed = Rspeed - 10;
	printf("Left speed =" "%d \n", Lspeed);
	printf("Right speed =" "%d \n", Rspeed);
	Lmotor();
	Rmotor();
}

int stop()
{
	printf("STOP!!! \n");
	Lspeed = 0;
	Rspeed = 0;
	printf("Left speed =" "%d \n", Lspeed);
	printf("Right speed =" "%d \n", Rspeed);
	Lmotor();
	Rmotor();
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
				stop();
				resetKey();
				return 0;
		}
	}
}





