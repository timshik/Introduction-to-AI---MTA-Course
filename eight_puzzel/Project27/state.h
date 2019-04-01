#pragma once
#include <queue> 
#include <math.h>
#include <list>
#include <algorithm>
#include "state.h"
#include <iostream>
#include <map>

using namespace std;

class state
{
private:
	int placeOfNumbers[9];
	int g, h, f;
	list<int> movements;
public:
	int getNum(int i) { return placeOfNumbers[i]; }
	state(int *arr, int g, list<int> fatherMovments, int action);
	~state();
	int returnf() { return f; }
	void createNewNode(state x, queue<state>&queue, map<int,list<state>> &map);
	int findEmptySlot();
	bool operator!=(state &state);
	bool operator==(state &state) { return !(*this != state); }
	int FirstOneInPlace();
	int *return_arr() { return placeOfNumbers; }
	list<int> getMovements() { return movements; }
	void printAllMovements();
};

bool checkIfAlreadySeen(state for_check, map<int, list<state>>& map);
int moveToCurrectPlace(int place, int dest);
void canMoveToEmpty(int num, int * &arr);
void sortQueue(queue<state>&my_queue);
int *makeNewArr(int empty, int last_arr, int * arr, int&action);
int getHeuristics(int *arr);
void print(state x);
int getDest(int i);
bool compare_states(state &one, state &two);



