/*
 * MinimaxPlayer.cpp
 *
 *  Created on: Apr 17, 2015
 *      Author: wong
 */
#include <iostream>
#include <assert.h>
#include "MinimaxPlayer.h"

using std::vector;

MinimaxPlayer::MinimaxPlayer(char symb) :
		Player(symb) {

}

MinimaxPlayer::~MinimaxPlayer() {

}

void MinimaxPlayer::get_move(OthelloBoard* b, int& col, int& row) {
    vector <OthelloBoard*> succBoards;
    OthelloBoard *nextMove;
    nextMove = maxUtil(b);
    succ(b, &succBoards);
    exit(0);
}

OthelloBoard *MinimaxPlayer::maxUtil(OthelloBoard* b) {
    vector <OthelloBoard*> succBoards;
    OthelloBoard *currentHighest;

    if(succ(b, &succBoards) == 0) {
        b->set_utility_value(utility(b));
        return b;
    }
    else {
        /* This is my MAX function for loop */
        for(int s = 0; s < succBoards.size(); s++) {
            OthelloBoard *temp = minUtil(succBoards[s]);
            if(s == 0) {
                currentHighest = temp;
            }
            else if(temp->get_utility_value() >=
                currentHighest->get_utility_value()) {
                currentHighest = temp;
                delete temp;
            }
            else {
                delete temp;
            }
        }
    }
}

OthelloBoard *MinimaxPlayer::minUtil(OthelloBoard* b) {
    vector <OthelloBoard*> succBoards;
    OthelloBoard *currentLowest;

    if(succ(b, &succBoards) == 0) {
        b->set_utility_value(utility(b));
        return b;
    }
    else {
        /* This is my MAX function for loop */
        for(int s = 0; s < succBoards.size(); s++) {
            OthelloBoard *temp = maxUtil(succBoards[s]);
            if(s == 0) {
                currentLowest = temp;
            }
            else if(temp->get_utility_value() >=
                currentLowest->get_utility_value()) {
                currentLowest = temp;
                delete temp;
            }
            else {
                delete temp;
            }
        }
    }
}

int MinimaxPlayer::succ(OthelloBoard* b, vector <OthelloBoard*> *sb) {

    for (int c = 0; c < b->get_num_cols(); c++) {
        for (int r = 0; r < b->get_num_rows(); r++) {
            if(b->is_legal_move(c, r, get_symbol())) {
                OthelloBoard *nb = new OthelloBoard(*(b));
                nb->play_move(c, r, get_symbol());
                nb->set_last_move(c, r);
                sb->push_back(nb);
            }
        }
    }
    std::cout << sb->size() << std::endl;
    for(int i = 0; i < sb->size(); i++) {
        (*sb)[i]->display();
    }
/*
	OthelloBoard *nb = new OthelloBoard(*(b));
    std::cout << nb->count_score('O') << std::endl;
    std::cout << b->count_score('O') << std::endl;
    //nb->play_move
    if(b->is_legal_move(1, 0, 'O')) {
    	b->play_move(1, 0, 'O');
    	b->display();
    	nb->display();
    }
    std::cout << "We got this message at least" << std::endl;
*/
    return sb->size();
}

int MinimaxPlayer::utility(OthelloBoard *ts) {
    return ts->count_score(get_symbol());
}


MinimaxPlayer* MinimaxPlayer::clone() {
	MinimaxPlayer* result = new MinimaxPlayer(symbol);
	return result;
}
