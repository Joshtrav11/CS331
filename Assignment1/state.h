#ifndef NUM_H
#define NUM_H

class state {

private:

	int **s;
	int id;

public:

	state();
	state(int **sa);
	~state();
	void hash();
	void copy(state *stc);
	int **getStateArray();
	void printState();
	bool boatLocation();
	int getVal(int i, int j);
	void moveChicken(bool side);
	void moveBoat(bool side);
	bool isLosingState();
	void moveWolf(bool side);
	int getID();

};

#endif