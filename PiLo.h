#ifndef PILO_H
#define PILO_H
#include <iostream>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <sstream>
#include <unistd.h>
#include "Path.h"
#define MAX_SPEED 127					//Max speed value limit
#define MIN_SPEED 50
using namespace std;
class PiLo {
public:
	PiLo();	
	~PiLo(){};
	bool ok() {if(isSerialOpen && wiringPiStarted) {printf("pilo ok\n"); return true;} return false;}
	void sendLine(string);				//Send string over ser to act board
	string sendCommand(int, int, int);	//Sends a com
	bool sendPath(Path);				//Sends list of path instructs
	const int SPEED = 1, TICKS = 2;
private:
	int serial;
	bool isSerialOpen, wiringPiStarted, commandFinished();
};

PiLo::PiLo() {  //Open ser port to act board/Start wiringPi
	if((serial = serialOpen("/dev/ttyS0", 19200)) < 0) { 
		printf("Err: Can't open ser device\n"); isSerialOpen = false; }
	else { isSerialOpen = true; printf("serial open\n"); }
	if(wiringPiSetup() == -1) { printf("Error: Could not start WiringPi\n"); wiringPiStarted = false; } 
	else { wiringPiStarted = true; printf("wiringPi started\n"); }
}
void PiLo::sendLine(string input) { //send string over ser to act board
	string output = "";
	for(unsigned i =0 ; i < input.length(); i++) {
		output += input[i];
		if(output.length() > 0) {             //Sends only 8 chars at a time
			serialPrintf(serial, output.c_str());
			serialFlush(serial);
			output.clear();
			usleep(5000);                      //Pause to allow serial flush
		}
	}
	serialPrintf(serial, output.c_str()); //Send remaining string
	serialFlush(serial);
}
string PiLo::sendCommand(int type, int left, int right) { //Send single com to act board
	stringstream s;
	string cmd_base;
	cout << "Type = " << type << endl;
	if(type == 1)
		cmd_base = "GO:";
	else
		cmd_base = "MOVE:";
	s << cmd_base << left << ":" << right << "\r";
	sendLine(s.str());
	return s.str();
}
bool PiLo::sendPath(Path path){ //Sends list of path instructs
	for(int i=0; i<path.size(); i++) {
		cout << sendCommand(2, path[i].left, path[i].right) << endl;
		while(!commandFinished());
	}
	return false;
}
bool PiLo::commandFinished() { //true on receipt of 'done' from act board
	string incoming;
	if(serialDataAvail(serial) > 0) {
		while(serialDataAvail(serial) > 0) {
			incoming += (char)serialGetchar(serial);
			//serialFlush(serial);
			usleep(2000);
		}
		cout << incoming << endl;
		if(incoming.compare("done") == 0)
			return true;
	}
	return false;
}
#endif