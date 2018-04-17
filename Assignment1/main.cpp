#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include <queue>
#include <list>
#include <algorithm>

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

bool contains(list <int> *visitedStates, int f) {
	return (std::find(visitedStates->begin(), visitedStates->end(), f) != visitedStates->end());
}

void uniformedBFS(state *startState, state *goalState) {
	
	queue <state*> q;
	list <int> visitedStates;
	vector <state*> succStates;
	state *temp;
	state *tempS;

	q.push(startState);

	while(!q.empty()) {

		cout << q.size() << endl;
		temp = q.front();
		temp->printState();
		q.pop();

		visitedStates.push_back(temp->getID());

		if(temp->getID() == goalState->getID()) {
			cout << "Found the goal state" << endl;
		}
		else {
			succ(temp, &succStates);
			while(!succStates.empty()){
				tempS = succStates.front();
				succStates.pop_back();
				if(!contains(&visitedStates, tempS->getID())) {
					q.push(tempS);
				}
			}
		}
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
	uniformedBFS(&ss, &gs);
	vector <state*> succStates;

	succ(&ss, &succStates);
	//cout << succStates.size() << endl;
	//succStates[0]->hash();

	for(int i = 0; i< succStates.size(); ++i)
		delete succStates[i];

	for(int i = 0; i < 2; ++i)
   		delete [] startStateArray[i];
   	for(int i = 0; i < 2; ++i)
   		delete [] goalStateArray[i];

	return 0;
}