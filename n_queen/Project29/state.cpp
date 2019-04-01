#include "state.h"

state::state(int new_position, state & father)
{
	queenPositions = father.getQueenPositions();
	queenPositions.push_back(new_position);
	this->n = father.getN();
}

state::state(int n) 
{
	this->n = n;
}

state::state(int n, int new_position)
{
	this->n = n;
	queenPositions.push_back(new_position);
}

int state::possibleMoves(map<int, vector<int>>& visitedMap)
{
	int tempPosition, calc_one, calc_two;
	vector<int> possiblePositions;
	vector<int> closed = visitedMap.at(queenPositions.size() + 1);
	for (int i = 1; i <= queenPositions.size(); i++)
	{
		tempPosition = queenPositions[i-1];
		closed[tempPosition] = 1;
		calc_one = queenPositions.size() + 1 - i;
		calc_two = queenPositions[i-1] + calc_one;
		if (calc_two <= n)
			closed[calc_two] = 1;
		calc_two = queenPositions[i-1] - calc_one;
		if (calc_two > 0)
			closed[calc_two] = 1;
	}

	for (int i = 1; i <= n; i++)
	{
		if (closed[i] == 0)
			possiblePositions.push_back(i);
	}

	if(possiblePositions.size() != 0)
		return possiblePositions[rand() % possiblePositions.size()];
	else
		return -1;
}

void state::printSolution()
{
	for (int i = 0; i < n; i++)
	{
		cout << queenPositions[i] << " ";
	}
	cout << endl;
}
