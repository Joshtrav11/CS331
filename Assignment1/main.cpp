#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <vector>
#include <queue>
#include <list>
#include <algorithm>
#include <stack>

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

int containsS(vector <state*> *visitedStates, state *ss) {

	int cont = -1;

	for(int i = 0; i < visitedStates->size(); i++) {
		if((*visitedStates)[i]->getID() == ss->getID()) {
			cont = i;
			break;
		}
	}

	return cont;
}

void showPath(state *s, state *gs, int nodesExpanded, char *outputFile) {

	ofstream outF;
	outF.open(outputFile);

	vector <state*> q;

	q.push_back(s);

	while((s = s->getParent()) != NULL) {
		q.push_back(s);
	}

	cout << "Number of States: " << q.size() << endl;
	cout << endl;

	while(!q.empty()) {
		s = q.back();
		q.pop_back();
		s->printState();
		cout << endl;
		s->printStateToFile(outF);
		delete s;
	}

	outF << "Nodes Expanded: " << nodesExpanded << endl;

	outF.close();
}

void uninformedBFS(state *startState, state *goalState, char *outputFile) {
	
	queue <state*> q;
	list <int> visitedStates;
	vector <state*> succStates;
	state *temp;
	state *tempS;
	int nodesExpanded = 0;
	bool goalFound = false;

	q.push(startState);

	while(!q.empty()) {

		temp = q.front();
		q.pop();

		if(temp->getID() == goalState->getID()) {

			showPath(temp, goalState, nodesExpanded, outputFile);
			cout << "Nodes expanded: " << nodesExpanded << endl;
			cout << endl;
			goalFound = true;

			while(!q.empty()) {
				temp = q.front();
				q.pop();
				delete temp;
			}

		}
		else {
			nodesExpanded++;
			succ(temp, &succStates);
			while(!succStates.empty()){
				tempS = succStates.back();
				succStates.pop_back();
				if(!contains(&visitedStates, tempS->getID())) {
					visitedStates.push_back(tempS->getID());
					tempS->setParent(temp);
					q.push(tempS);
				}
				else
					delete tempS;
			}
		}
	}
	if(!goalFound) {
		cout << "No solution found" << endl;
	}
}

void uninformedDFS(state *startState, state *goalState, char *outputFile) {
	
	stack <state*> st;
	list <int> visitedStates;
	vector <state*> succStates;
	state *temp;
	state *tempS;
	int nodesExpanded = 0;
	bool goalFound = false;

	st.push(startState);

	while(!st.empty()) {

		temp = st.top();
		st.pop();

		if(temp->getID() == goalState->getID()) {

			showPath(temp, goalState, nodesExpanded, outputFile);
			cout << "Nodes expanded: " << nodesExpanded << endl;
			cout << endl;
			goalFound = true;

			while(!st.empty()) {
				temp = st.top();
				st.pop();
				delete temp;
			}

		}
		else {
			nodesExpanded++;
			succ(temp, &succStates);
			while(!succStates.empty()){
				tempS = succStates.back();
				succStates.pop_back();
				if(!contains(&visitedStates, tempS->getID())) {
					visitedStates.push_back(tempS->getID());
					tempS->setParent(temp);
					st.push(tempS);
				}
				else
					delete tempS;
			}
		}
	}
	if(!goalFound) {
		cout << "No solution found" << endl;
	}
}

void uninformedIDDFS(state *startState, state *goalState, char *outputFile) {

	stack <state*> st;
	list <int> visitedStates;
	vector <state*> succStates;
	state *temp;
	state *tempS;
	bool goalFound = false;

	for(int MAXIT = 0; MAXIT < 100; MAXIT++) {

		st.push(startState);
		int nodesExpanded = 0;
		while(!st.empty()) {

			temp = st.top();
			st.pop();

			if(temp->getID() == goalState->getID()) {

				showPath(temp, goalState, nodesExpanded, outputFile);
				cout << "Nodes expanded: " << nodesExpanded << endl;
				cout << endl;
				goalFound = true;

				while(!st.empty()) {
					temp = st.top();
					st.pop();
					delete temp;
				}

			}
			else if(temp->getDepth() <= MAXIT) {
				
				nodesExpanded++;
				succ(temp, &succStates);
				while(!succStates.empty()){
					tempS = succStates.back();
					succStates.pop_back();
					if(!contains(&visitedStates, tempS->getID())) {
						visitedStates.push_back(tempS->getID());
						tempS->setParent(temp);
						st.push(tempS);
					}
					else
						delete tempS;
				}

			}
		}
		while(!visitedStates.empty())
			visitedStates.pop_back();
		if(goalFound)
			break;
	}
	if(!goalFound) {
		cout << "No solution found" << endl;
	}
}

void informedAStar(state *startState, state *goalState, char *outputFile) {

	vector <state*> open;
	vector <state*> closed;
	vector <state*> succStates;
	state *temp;
	state *tempS;
	int nodesExpanded = 0;
	bool goalFound = false;

	open.push_back(startState);

	while(!open.empty()) {

		temp = open[0];
		int location = 0;

		for(int i = 0; i < open.size(); i++) {
			if (open[i]->getFValue(goalState) > temp->getFValue(goalState))
			{
				temp = open[i];
				location = i;
			}
		}
		
		open.erase(open.begin() + location);
		closed.push_back(temp);

		if(temp->getID() == goalState->getID()) {

			showPath(temp, goalState, nodesExpanded, outputFile);
			cout << "Nodes expanded: " << nodesExpanded << endl;
			cout << endl;
			goalFound = true;

			while(!open.empty()) {
				temp = open.back();
				open.pop_back();
				delete temp;
			}

		}
		else {

			nodesExpanded++;
			succ(temp, &succStates);
			while(!succStates.empty()){

				tempS = succStates.back();
				succStates.pop_back();
				if(containsS(&closed, tempS) == -1) {
					if(containsS(&open, tempS) == -1) {
						tempS->setParent(temp);
						open.push_back(tempS);
					}
					else {
						state *o = open[containsS(&open, tempS)];
						if(tempS->getDepth() < o->getDepth()) {
							o->setDepth(tempS->getDepth());
							o->setParent(tempS->getParent());
						}
					}
				}
				else
					delete tempS;
			}
		}

	}
	
	if(!goalFound) {
		cout << "No solution found" << endl;
	}
}

int main(int argc, char **argv) {

	if(argc != 5) {
		cout << "Usage: ./sheep <init_file> <goal_file> <mode> <output_file>" << endl;
		exit(1);
	}

	int** startStateArray = new int*[2];
	for(int i = 0; i < 2; ++i)
	    startStateArray[i] = new int[3];
	int** goalStateArray = new int*[2];
	for(int i = 0; i < 2; ++i)
	    goalStateArray[i] = new int[3];

	getFile(startStateArray, argv[1]);
	getFile(goalStateArray, argv[2]);

	//state ss(startStateArray), gs(goalStateArray);
	state *ss = new state(startStateArray);
	state *gs = new state(goalStateArray);

	if(strncmp(argv[3],"bfs",3) == 0)
		uninformedBFS(ss, gs, argv[4]);
	else if(strncmp(argv[3],"dfs",3) == 0)
		uninformedDFS(ss, gs, argv[4]);
	else if(strncmp(argv[3],"iddfs",5) == 0)
		uninformedIDDFS(ss, gs, argv[4]);
	else if(strncmp(argv[3],"astar",5) == 0)
		informedAStar(ss, gs, argv[4]);
	else {
		cout << "unrecognized command" << endl;
	}

	delete gs;

	for(int i = 0; i < 2; ++i)
   		delete [] startStateArray[i];
   	for(int i = 0; i < 2; ++i)
   		delete [] goalStateArray[i];

	return 0;
}