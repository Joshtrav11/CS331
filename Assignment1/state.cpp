#include <iostream>
#include <functional>
#include <math.h>
#include <fstream>
#include <cmath>

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

	parent = NULL;

	depth = 0;

	hash();

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

	parent = NULL;

	depth = 0;

	hash();

}

state::~state() {

	for(int i = 0; i < 2; ++i)
   		delete [] s[i];

}

void state::hash() {

	id = 0;

	int total = 0;
	int k = 0;
	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < 3; j++) {
			total += ((s[i][j] + 1) * pow(10,k));
			k++;
		}
	}
	id = total;

}

void state::copy(state *stc) {

	int **sa = stc->getStateArray();

	s[0][0] = sa[0][0];
	s[0][1] = sa[0][1];
	s[0][2] = sa[0][2];
	s[1][0] = sa[1][0];
	s[1][1] = sa[1][1];
	s[1][2] = sa[1][2];

	parent = stc->getParent();
	depth = stc->getDepth();

	hash();

}

int **state::getStateArray() { return s;}

void state::printState() {

	std::cout << s[0][0] << "," << s[0][1] << "," << s[0][2] << std::endl;
	std::cout << s[1][0]  << "," << s[1][1] << "," << s[1][2] << std::endl;

}

void state::printStateToFile(std::ofstream &outputFile) {

	outputFile << s[0][0] << "," << s[0][1] << "," << s[0][2] << std::endl;
	outputFile << s[1][0]  << "," << s[1][1] << "," << s[1][2] << std::endl;
	outputFile << std::endl;

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

	hash();

}

void state::moveBoat(bool side) {

	s[side][2] = 1;
	s[!side][2] = 0;

	hash();

}

bool state::isLosingState() {

	if(((s[0][0] < s[0][1]) && s[0][0] != 0) || ((s[1][0] < s[1][1]) && s[1][0] != 0))
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

	hash();

}

int state::getID() {
	return id;
}

void state::setParent(state *p) {
	
	parent = p;
	depth = parent->getDepth() + 1;

}

state *state::getParent() {
	return parent;
}

int state::getDepth() {
	return depth;
}

int state::setDepth(int d) {
	depth = d;
}

int state::heuristic(state *gs) {

	int x = 0, y = 0, z = 0, a = 0, b = 0, h = 0;

	x = std::abs(getVal(0,0) - gs->getVal(0,0));
	y = std::abs(getVal(0,1) - gs->getVal(0,1));
	a = std::abs(getVal(1,0) - gs->getVal(1,0));
	b = std::abs(getVal(1,1) - gs->getVal(1,1));
	z = (std::abs(getVal(0,2) - gs->getVal(0,2))) ? -2 : 1;

	h = (x * 2) + (y * 2) + z;

	return h;
}

int state::getFValue(state *gs) {
	return heuristic(gs) + depth;
}
