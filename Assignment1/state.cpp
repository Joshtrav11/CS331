#include <iostream>
#include "state.h"

state::state() {
	s[0][0] = 0;
	s[0][1] = 0;
	s[0][2] = 0;
	s[1][0] = 3;
	s[1][1] = 3;
	s[1][2] = 1;
}

void state::printState() {
	std::cout << s[0][0] << "," << s[0][1] << "," << s[0][2] << std::endl;
	std::cout << s[1][0]  << "," << s[1][1] << "," << s[1][2] << std::endl;
}