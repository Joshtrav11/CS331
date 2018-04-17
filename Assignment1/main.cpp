#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <vector>

#include "state.h"

using namespace std;

void getFile(int **sa, char *startStateFile) {

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

void succ(state *s, vector <state*> *ss) {

	// Check if there is at least one chicken on the side the boat is on
	if(s->getVal(s->boatLocation(), 0) >= 1) {

		state *ns = new state;
		ns->copy(s);
		ns->moveChicken(ns->boatLocation());
		ns->moveBoat(!ns->boatLocation());

		if(!ns->isLosingState()){
			//cout << "went down if" << endl;
			ss->push_back(ns);
		}
		else {
			delete ns;
		}

	}

	if(s->getVal(s->boatLocation(), 0) >= 2) {

		state *ns = new state;
		ns->copy(s);
		ns->moveChicken(ns->boatLocation());
		ns->moveChicken(ns->boatLocation());
		ns->moveBoat(!ns->boatLocation());

		if(!ns->isLosingState()){
			ss->push_back(ns);
		}
		else
			delete ns;

	}

	if(s->getVal(s->boatLocation(), 1) >= 1) {

		state *ns = new state;
		ns->copy(s);
		ns->moveWolf(ns->boatLocation());
		ns->moveBoat(!ns->boatLocation());

		if(!ns->isLosingState()){
			ss->push_back(ns);
		}
		else
			delete ns;
	}

	if(s->getVal(s->boatLocation(), 1) >= 2) {

		state *ns = new state;
		ns->copy(s);
		ns->moveWolf(ns->boatLocation());
		ns->moveWolf(ns->boatLocation());
		ns->moveBoat(!ns->boatLocation());

		if(!ns->isLosingState()){
			ss->push_back(ns);
		}
		else
			delete ns;
	}

	if((s->getVal(s->boatLocation(), 0) >= 1) && (s->getVal(s->boatLocation(), 1) >= 1)) {

		state *ns = new state;
		ns->copy(s);
		ns->moveChicken(ns->boatLocation());
		ns->moveWolf(ns->boatLocation());
		ns->moveBoat(!ns->boatLocation());

		if(!ns->isLosingState()){
			ss->push_back(ns);
		}
		else
			delete ns;

	}

}

int main(int argc, char **argv) {

	int** startStateArray = new int*[2];
	for(int i = 0; i < 2; ++i)
	    startStateArray[i] = new int[3];
	int** goalStateArray = new int*[2];
	for(int i = 0; i < 2; ++i)
	    goalStateArray[i] = new int[3];

	getFile(startStateArray, argv[1]);
	getFile(goalStateArray, argv[2]);

	state ss(startStateArray), gs(goalStateArray);
	vector <state*> succStates;

	succ(&ss, &succStates);

	for(int i = 0; i < 2; ++i)
   		delete [] startStateArray[i];
   	for(int i = 0; i < 2; ++i)
   		delete [] goalStateArray[i];

	return 0;
}