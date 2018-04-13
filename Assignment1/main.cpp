#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>

#include "state.h"

using namespace std;

void getFile(int sa[][3], char *startStateFile) {

	string line;
	ifstream ssf(startStateFile);

	int i = 0, j = 0;

	if(ssf.is_open()) {
		while(getline(ssf, line)) {

			stringstream linestream(line);
			string value;

			while(getline(linestream, value, ',')) {
				sa[i][j] = atoi(value.c_str());
				j++;
			}
			i++;
			j = 0;
		}
		ssf.close();
	}
	else
		cout << "Can't find file" << endl;

}

int main(int argc, char **argv) {

	state s;
	int startStateArray[2][3];
	int goalStateArray[2][3];

	getFile(startStateArray, argv[1]);
	getFile(goalStateArray, argv[2]);

	std::cout << startStateArray[0][0] << "," << startStateArray[0][1] << "," << startStateArray[0][2] << std::endl;
	std::cout << startStateArray[1][0]  << "," << startStateArray[1][1] << "," << startStateArray[1][2] << std::endl;

	std::cout << goalStateArray[0][0] << "," << goalStateArray[0][1] << "," << goalStateArray[0][2] << std::endl;
	std::cout << goalStateArray[1][0]  << "," << goalStateArray[1][1] << "," << goalStateArray[1][2] << std::endl;

	//s.printState();

	return 0;
}