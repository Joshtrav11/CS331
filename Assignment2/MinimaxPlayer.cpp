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

    if(get_symbol() == 'X')
        nextMove = maxUtil(b, get_symbol());
    else if (get_symbol() == 'O')
        nextMove = minUtil(b, get_symbol());

    std::cout << "Should move to: " << nextMove->get_last_move_col() <<
        nextMove->get_last_move_row() << std::endl;
    exit(0);
}

OthelloBoard *MinimaxPlayer::maxUtil(OthelloBoard* b, char t) {
    vector <OthelloBoard*> succBoards;
    OthelloBoard *currentHighest;
    char otherPlayer;

    if(t == 'X')
        otherPlayer = 'O';
    else if(t == 'O')
        otherPlayer = 'X';
    else
        assert("Failure");

    if(succ(b, &succBoards, t) == 0) {
        b->set_utility_value(utility(b));
        return b;
    }
    
    else {
        /*
        for(int i = 0; i < succBoards.size(); i++) {
            succBoards[i]->display();
        }
        exit(0);
        */
        /* This is my MAX function for loop */
        for(int s = 0; s < succBoards.size(); s++) {
            //succBoards[s]->display();
            OthelloBoard *temp = minUtil(succBoards[s], otherPlayer);
            std::cout << temp->get_utility_value() << std::endl;
            //exit(0);
            //temp->display();
            if(s == 0) {
                currentHighest = temp;
                //continue;
            }
            else if(temp->get_utility_value() >
                currentHighest->get_utility_value()) {
                currentHighest = temp;
                std::cout << "max else if before delete" << std::endl;
                delete temp;
                std::cout << "max else if after delete" << std::endl;
            }
            else {
                std::cout << "max else before delete" << std::endl;
                delete temp;
                std::cout << "max else after delete" << std::endl;
            }
        }
        b->set_utility_value(currentHighest->get_utility_value());
        return currentHighest;
    }
}

OthelloBoard *MinimaxPlayer::minUtil(OthelloBoard* b, char t) {
    vector <OthelloBoard*> succBoards;
    OthelloBoard *currentLowest;
    char otherPlayer;

    if(t == 'X')
        otherPlayer = 'O';
    else if(t == 'O')
        otherPlayer = 'X';
    else 
        assert("Failure");

    if(succ(b, &succBoards, t) == 0) {
        b->set_utility_value(utility(b));
        return b;
    }
    else {
        /*
        for(int i = 0; i < succBoards.size(); i++) {
            succBoards[i]->display();
        }
        exit(0);
        */
        /* This is my MIN function for loop */
        for(int s = 0; s < succBoards.size(); s++) {
            succBoards[s]->display();
            OthelloBoard *temp = maxUtil(succBoards[s], otherPlayer);
            //std::cout << temp->get_utility_value() << std::endl;
            //exit(0);
            temp->display();
            if(s == 0) {
                currentLowest = temp;
                //continue;
            }
            else if(temp->get_utility_value() <
                currentLowest->get_utility_value()) {
                currentLowest = temp;
                std::cout << "min else if before delete" << std::endl;
                delete temp;
                std::cout << "min else if after delete" << std::endl;
            }
            else {
                std::cout << "min else before delete" << std::endl;
                delete temp;
                std::cout << "min else after delete" << std::endl;
            }
        }
        b->set_utility_value(currentLowest->get_utility_value());
        return currentLowest;
    }
}

int MinimaxPlayer::succ(OthelloBoard* b, vector <OthelloBoard*> *sb, char t) {

    for (int c = 0; c < b->get_num_cols(); c++) {
        for (int r = 0; r < b->get_num_rows(); r++) {
            if(b->is_legal_move(c, r, t)) {
                OthelloBoard *nb = new OthelloBoard(*(b));
                nb->play_move(c, r, t);
                nb->set_last_move(c, r);
                sb->push_back(nb);
            }
        }
    }
    /*
    std::cout << sb->size() << std::endl;
    for(int i = 0; i < sb->size(); i++) {
        (*sb)[i]->display();
    }
    */
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
// This might be problem, should use whatever character is being succ?
int MinimaxPlayer::utility(OthelloBoard *ts) {
    return ts->count_score(get_symbol());
}


MinimaxPlayer* MinimaxPlayer::clone() {
	MinimaxPlayer* result = new MinimaxPlayer(symbol);
	return result;
}
