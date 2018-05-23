#include "simpletools.h"
#include "abdrive.h"
using namespace std;
fdserial *pi;
void inch(int dist);
void turnL(), turnR(), turnL2(), turnR2(), for1(), veerR();
void setSpeed(int spd);
void setAll(int spd, int trns, int dur, double plus, double norm);
int getTurns(int speed);

/***12 rndDur*/
//speed: 16		turns: 470		plusMulti: 2.6		normMulti: 9.4
/***6 rndDur*/
//speed: 20		turns: 351		plusMulti: 1.7		normMulti: 4.3
//speed: 24		turns: 285		plusMulti: 1.9		normMulti: 4.1
//speed: 28     turns: 240		plusMulti: 2.1		normMulti: 3.9
//speed: 33     turns: 198		plusMulti: 2.5		normMulti: 3.5
//speed: 40     turns: 158		plusMulti: 2.7		normMulti: 3.3

int speed = 28, turns = 240, rndDur = 6;
double plusMulti = 2.1, normMulti = 3.9;

int dist = 24;

int main() {
	setSpeed(24);
	inch(dist);
	setSpeed(28);
	inch(dist);
	
	
	setSpeed(28);
 } 	

void inch(int dist) {
	int rounds = dist/rndDur, remainder = dist % rndDur;
	for(int i = 0; i < rounds; i++) {
		drive_speed(speed, speed+1);
		pause(plusMulti*turns);
		drive_speed(speed, speed);
		pause(normMulti*turns);
	}
	drive_speed(speed, speed);
	pause(remainder*turns);
	drive_speed(0,0);
}
void setAll(int spd, int trns, int dur, double plus, double norm) {
	speed = spd, turns = trns, rndDur = dur;
	plusMulti = plus, norm = normMulti;
}
void setSpeed(int spd) {
	if(spd == 16) 
		setAll(16, 470, 12, 2.6, 9.4);
	if(spd == 20) 
		setAll(20, 351, 6, 1.7, 4.3);
	if(spd == 24) 
		setAll(24, 285, 6, 1.9, 4.1);
	if(spd == 28)
		setAll(28, 240, 6, 2.1, 3.9);
	if(spd == 33) 
		setAll(33, 198, 6, 2.5, 3.5);
	if(spd == 40) 
		setAll(40, 258, 6, 2.7, 3.3);
}

void veerR() {
}

void for1() { inch(12); }
void turnR() { drive_goto(28,-29); }
void turnL() { drive_goto(-28,28); }
void turnR2() { drive_goto(16,-17); }
void turnL2() { drive_goto(-16,16); }