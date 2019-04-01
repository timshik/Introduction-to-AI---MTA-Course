#include "state.h"
using namespace std;

state::state(int *arr,int g, list<int> fatherMovments, int action)
{
	this->movements = fatherMovments;
	if(action != -1)
		movements.push_back(action);
	this->h = getHeuristics(arr);
	this->f = h + g;
	this->g = g;
	for (int i = 0; i < 9; i++)
	{
		this->placeOfNumbers[i] = arr[i];
	}
}

state::~state()
{
}

bool checkIfAlreadySeen(state for_check, map<int, list<state>> &map) {
	int x = for_check.FirstOneInPlace();

	auto itr = map.at(x).begin();
	auto itrEnd = map.at(x).end();
	while (itr != itrEnd) {
		if (*itr == for_check) {
			return true;
		}
		itr++;
	}

	map.at(x).push_front(for_check);
	return false;
}

void state::createNewNode(state x, queue<state>&my_queue, map<int, list<state>> &map)
{
	int *arr = new int[4];
	int *newArr = new int[9];
	int empty = findEmptySlot();
	int heurisit = 0;
	int action;

	canMoveToEmpty(empty,arr);

	for (int i = 0; i < 4; i++) {
		if (arr[i] != -1) {
			newArr = makeNewArr(empty, arr[i], x.return_arr(),action);
			state y(newArr, g + 1,x.getMovements(),action);
			if(!checkIfAlreadySeen(y,map))
				my_queue.push(y);
		}
	}
}

int state::findEmptySlot()
{
	for (int i = 0; i < 9; i++)
		if (placeOfNumbers[i] == 0)
			return i;

	return 0;
}

bool state::operator!=(state & state)
{
	for (int i = 0; i < 9; i++)
	{
		if (this->placeOfNumbers[i] != state.placeOfNumbers[i])
			return true;
	}
	return false;
}

int state::FirstOneInPlace()
{
	for (int i = 1; i < 9; i++)
	{
		if (i == getDest(this->placeOfNumbers[i])) {
			return i;
		}
	}
	return 9;
}

void state::printAllMovements()
{
	auto itr = this->movements.begin();
	auto itrEnd = this->movements.end();

	while (itr != itrEnd) {
		switch (*itr)
		{
		case 0:
			cout << "UP";
			break;
		case 1:
			cout << "DOWN";
			break;
		case 2:
			cout << "LEFT";
			break;
		case 3:
			cout << "RIGHT";
			break;
		default:
			break;
		}
		cout << ", ";
		itr++;
	}
}

int moveToCurrectPlace(int place, int dest) {
	int mod_sol, div_sol;

	mod_sol = abs(place % 3 - dest % 3);
	div_sol = abs(place / 3 - dest / 3);

	return mod_sol + div_sol;
}

void canMoveToEmpty(int num, int * &arr) {
	switch (num)
	{
	case 0:
		arr[0] = 1;
		arr[1] = 3;
		arr[2] = -1;
		arr[3] = -1;
		break;
	case 1:
		arr[0] = 0;
		arr[1] = 2;
		arr[2] = 4;
		arr[3] = -1;
		break;
	case 2:
		arr[0] = 1;
		arr[1] = 5;
		arr[2] = -1;
		arr[3] = -1;
		break;
	case 3:
		arr[0] = 0;
		arr[1] = 4;
		arr[2] = 6;
		arr[3] = -1;
		break;
	case 4:
		arr[0] = 1;
		arr[1] = 3;
		arr[2] = 5;
		arr[3] = 7;
		break;
	case 5:
		arr[0] = 2;
		arr[1] = 4;
		arr[2] = 8;
		arr[3] = -1;
		break;
	case 6:
		arr[0] = 3;
		arr[1] = 7;
		arr[2] = -1;
		arr[3] = -1;
		break;
	case 7:
		arr[0] = 4;
		arr[1] = 6;
		arr[2] = 8;
		arr[3] = -1;
		break;
	case 8:
		arr[0] = 5;
		arr[1] = 7;
		arr[2] = -1;
		arr[3] = -1;
		break;
	default:
		break;
	}
}

int getAction(int empty, int i) {
	switch ((i % 3 - empty % 3))
	{
	case 1:
		return 2;
	case -1:
		return 3;
	default:
		break;
	}

	switch ((i / 3 - empty / 3))
	{
	case 1:
		return 0;
	case -1:
		return 1;
	default:
		break;
	}

	return -1;
}

int *makeNewArr(int empty, int i, int *arr, int &action) {
	int *new_arr = new int[9];

	for (int i = 0; i < 9; i++) {
		new_arr[i] = arr[i];
	}

	action = getAction(empty, i);

	int temp = new_arr[i];
	new_arr[i] = new_arr[empty];
	new_arr[empty] = temp;

	return new_arr;
}

int getHeuristics(int * arr)
{
	int sum = 0;

	for (int i = 0; i < 9; i++)
	{
		if (arr[i] != 0)
			sum += moveToCurrectPlace(i, getDest(arr[i]));
	}

	return sum;
}

int getDest(int i) {
	switch (i)
	{
	case 1:
		return 0;
	case 2:
		return 1;
	case 3:
		return 2;
	case 4:
		return 5;
	case 5:
		return 8;
	case 6:
		return 7;
	case 7:
		return 6;
	case 8:
		return 3;
	default:
		break;
	}

	return -1;
}

void sortQueue(queue<state>&my_queue) {
	list<state> list;

	while (!my_queue.empty()) {
		list.push_front(my_queue.front());
		my_queue.pop();
	}

	list.sort(compare_states);
	while (!list.empty()) {
		my_queue.push(list.front());
		list.pop_front();
	}
}

void print(state x) {
	for (int i = 0; i < 9; i++)
	{
		cout << x.getNum(i) << " | ";
		if (i % 3 == 2) {
			cout << endl;
		}
	}
}

bool compare_states(state &one, state &two) {
	return (one.returnf() < two.returnf());
}
