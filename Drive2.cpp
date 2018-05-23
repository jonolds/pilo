#include "simpletools.h"	// Include simple tools
#include "abdrive.h"
using namespace std;
fdserial *pi;
int speed = 26;
void parseCommand(char* cmd), parseCommand2(char* cmd);
void inch(int distance), turnL(), turnR(), turnL2(), turnR2(), for1(), veerR();

int main() {				//Main function
	inch(65);
}

void veerR() {
}		

void parseCommand2(char* cmd) {
	if(cmd == "l2")
		turnL2();
}

void for1() { inch(12); }		
void inch(int distance) {
	int rounds = distance/10, remainder = distance % 10;
	for(int i = 0; i < rounds; i++) {
		drive_speed(speed, speed+1);
		pause(5*320);
		drive_speed(speed, speed);
		pause(5*320);
	}
	drive_speed(speed, speed);
	pause(remainder*320);
	drive_speed(0,0);
	//drive_goto(.97*(25.4*left/3.25), 25.4*right/3.25);	 
}
void turnR() { drive_goto(28,-29); }
void turnL() { drive_goto(-28,28); }
void turnR2() { drive_goto(16,-17); }
void turnL2() { drive_goto(-16,16); }

char type[8], leftString[5], rightString[5];//Com type(GO/MOVE)
void parseCommand(char* cmd){
	bool err = false;
	int left, right, i=0, j=0;
	while(cmd[i] != ':'){		//Get the command type
		type[j] = cmd[i];
		j++;i++;
		if(j>4){
			err = true;
			break;
		}			
	}
	i++;
	type[j] = '\0';
	j=0;
	while(cmd[i] != ':'){		//Get the left parameter
		leftString[j] = cmd[i];
		j++;i++;
		if(j>6){
			err = true;
			break;
		}			
	}		
	i++;
	leftString[j] = '\0';
	j=0;
	while(cmd[i] != '\r'){		//Get right parameter
		rightString[j] = cmd[i];
		j++;i++;
		if(j>6){
			err = true;
			break;
		}			
	}
	rightString[j] = '\0';
	if(!err){
		left = atoi(leftString); //Convert wheel params to ints
		right = atoi(rightString);
		printf("%d, %d\n", left, right); //Print command to terminal
		if(strcmp(type, "GO") == 0) //Execute command
			drive_speed(left, right);	
		else if(strcmp(type, "MOVE") == 0)
			drive_goto(left, right);
	}		
}