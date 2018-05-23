//Drive.py- serial interface giving drive control to pi
#include "simpletools.h"				// Include simple tools
#include "fdserial.h"
#include "string.h"
#include "abdrive.h"
#include <stdlib.h>
fdserial *pi;
char type[8];							//Command type (GO or MOVE)
char leftString[5];				 		//Left wheel parameter	(string)
char rightString[5];					//Right Wheel parameter (string)
void parseCommand(char* cmd);

int main() {							// Main function
	pi = fdserial_open(1, 0, 0, 19200);	//Open a serial connection
	char cmd[15];						//Stores the raw command string
	char c;								//stores characters from serial
	int i=0;							//counter
	while(true){
		c = fdserial_rxChar(pi);		//Get a character from serial
		cmd[i] = c;						//Put it into cmd
		i++;
		if(c == '\r'){  				//End the string with a '\r' character
			cmd[i] = '\0';				//Terminate the string
			if(i>=6){
				//print(cmd);
				parseCommand(cmd);		//Parse the command
			}		 
			i = 0;
			//fdserial_rxFlush(pi);
		}	
	}			
}
	
void parseCommand(char* cmd){
	bool err = false;
	int i=0, j=0, left, right;
	while(cmd[i] != ':'){				//Get the command type
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
	
	while(cmd[i] != ':'){				//Get the left parameter
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
	
	while(cmd[i] != '\r'){				//Get the right parameter
		rightString[j] = cmd[i];
		j++;i++;
		if(j>6){
			err = true;
			break;
		}			
	}
	rightString[j] = '\0';
	
	if(!err){
		left = atoi(leftString);		//Convert the wheel parameters to ints
		right = atoi(rightString);
		printf("%d, %d\n", left, right);//Print the command to the terminal
		if(strcmp(type, "GO") == 0)		//Execute the command	
			drive_speed(left, right);	
		else if(strcmp(type, "MOVE") == 0)
			drive_goto(left, right);
	}		
}	