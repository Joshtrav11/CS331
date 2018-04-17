#include <iostream>
#include "state.h"

state::state() {

	s = new int*[2];
	for(int i = 0; i < 2; ++i)
	    s[i] = new int[3];

	s[0][0] = 0;
	s[0][1] = 0;
	s[0][2] = 0;
	s[1][0] = 0;
	s[1][1] = 0;
	s[1][2] = 0;

}

state::state(int **sa) {

	s = new int*[2];
	for(int i = 0; i < 2; ++i)
	    s[i] = new int[3];

	s[0][0] = sa[0][0];
	s[0][1] = sa[0][1];
	s[0][2] = sa[0][2];
	s[1][0] = sa[1][0];
	s[1][1] = sa[1][1];
	s[1][2] = sa[1][2];

}

state::~state() {

	for(int i = 0; i < 2; ++i)
   		delete [] s[i];

}

void state::copy(state *stc) {

	int **sa = stc->getStateArray();

	s[0][0] = sa[0][0];
	s[0][1] = sa[0][1];
	s[0][2] = sa[0][2];
	s[1][0] = sa[1][0];
	s[1][1] = sa[1][1];
	s[1][2] = sa[1][2];

}

int **state::getStateArray() { return s;}

void state::printState() {

	std::cout << s[0][0] << "," << s[0][1] << "," << s[0][2] << std::endl;
	std::cout << s[1][0]  << "," << s[1][1] << "," << s[1][2] << std::endl;

}

bool state::boatLocation() { return (s[0][2] == 0);}

int state::getVal(int i, int j) { return s[i][j];}

void state::moveChicken(bool side) {
	if(s[side][0] != 0) {
		s[side][0]--;
		s[!side][0]++;
	}
	else
		std::cout << "No chickens available to transfer" << std::endl;
}

void state::moveBoat(bool side) {
	s[side][2] = 1;
	s[!side][2] = 0;
}

bool state::isLosingState() {
	if((s[0][0] < s[0][1]) || (s[1][0] < s[1][1]))
		return true;
	else
		return false;
}

void state::moveWolf(bool side) {
	if(s[side][1] != 0) {
		s[side][1]--;
		s[!side][1]++;
	}
	else
		std::cout << "No wolves available to transfer" << std::endl;
}
