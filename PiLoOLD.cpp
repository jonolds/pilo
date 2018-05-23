#include "PiLo.h"
PiLo::PiLo(){
	//Open the serial port to the activity board
	if((serial = serialOpen("/dev/ttyS0", 19200)) < 0) {
		printf("Error: Could not open serial device\n");
		isSerialOpen = false;
	} else {
		isSerialOpen = true;
		printf("serial open\n");
	}
	//Start wiringPi
	if(wiringPiSetup() == -1) {
		printf("Error: Could not start WiringPi\n");
		wiringPiStarted = false;
	} else {
		wiringPiStarted = true;
		printf("wiringPi started\n");
	}
}
PiLo::~PiLo(){}
bool PiLo::ok() {
	if(isSerialOpen && wiringPiStarted) {
		printf("pilo okay\n");
		return true;
	}
	return false;
}

void PiLo::sendLine(string input){ //sends a string over serial to the activity board
	string output = "";

	for(int i=0; i<input.length(); i++){
		output += input[i];
		if(output.length() > 0){             //Sends only 8 characters at a time
			serialPrintf(serial, output.c_str());
			serialFlush(serial);
			output.clear();
			usleep(5000);                      //Pause to allow serial flush
		}
	}
	serialPrintf(serial, output.c_str()); //Send the remaining string
	serialFlush(serial);
}

//Sends a single command to the activity board
string PiLo::sendCommand(int type, int left, int right){
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

bool PiLo::sendPath(Path path){ //Sends a list of path instructions
	for(int i=0; i<path.size(); i++){
		cout << sendCommand(2, path[i].left, path[i].right) << endl;
		while(!commandFinished());
	}
	return false;
}

//Returns true upon receipt of the 'done' signal from the activity board
bool PiLo::commandFinished(){
	string incoming;
	if(serialDataAvail(serial) > 0){
		while(serialDataAvail(serial) > 0){
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