#ifndef NUM_H
#define NUM_H

#include <fstream>
#include <iostream>

class state {

private:

	int **s;
	int id;
	state *parent;
	int depth;

public:

	state();
	state(int **sa);
	~state();
	void hash();
	void copy(state *stc);
	int **getStateArray();
	void printState();
	void printStateToFile(std::ofstream &outputFile);
	bool boatLocation();
	int getVal(int i, int j);
	void moveChicken(bool side);
	void moveBoat(bool side);
	bool isLosingState();
	void moveWolf(bool side);
	int getID();
	void setParent(state *p);
	state *getParent();
	int getDepth();
	int setDepth(int d);
	int heuristic(state *gs);
	int getFValue(state *gs);

};

#endif