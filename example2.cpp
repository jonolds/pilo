#include <iostream>
#include <wiringPi.h>
#include <wiringSerial.h>
#include "PiLo.h"
#include "Path.h"

using namespace std;

int main(){
	PiLo pilo;  //Start by creating a PiLo object (serial is started in the constructor)

	if(!pilo.ok()){
		return 1;
	}
	string command = "";
	while(command != "ex") {
		cin >> command;
		if(command != "ex")
			pilo.sendLine(command);
	}

	//pilo.sendCommand(pilo.TICKS, 100, 100); //Drive the robot forward 100 ticks


	//Create a path
	//  Path myPath;
	//  myPath.push_back(100, 100);
	//  myPath.push_back(-85, 85);
	//  myPath.push_back(85, 0);
	//  myPath.push_back(-100, -100);

	//pilo.sendPath(myPath);   //Send the path to the robot
	//  pilo.sendCommand(1, 100, 100);
	return 0;
}
