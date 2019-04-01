#include <iostream>
#include <map>
#include <list>
#include <stack>
#include "state.h"
#include "main.h"
#include <ctime>

using namespace std;
void solveN_Queens(int n);


int main() {
	srand((unsigned)(time(0)));

	solveN_Queens(100);
}

void solveN_Queens(int n) {
	clock_t begin = clock();
	stack<state> solution;
	map<int, vector<int>> visitedMap;
	for (int i = 0; i <= n; i++)
	{
		vector<int> positions;
		for (int j = 0; j <= n; j++)
			positions.push_back(0);
		visitedMap.insert(pair<int, vector<int>>(i, positions));
	}
	int newPosition;
	state x(n);
	int count = 0;
	while (solution.size() != n)
	{
		newPosition = x.possibleMoves(visitedMap);
		if (newPosition != -1) {
			count++;
			state new_state(newPosition, x);
			visitedMap.at(x.getQueenPositions().size() + 1).at(newPosition) = 1;
			solution.push(new_state);
			x = new_state;
		}
		else {
			int size = x.getQueenPositions().size() + 1;
			for (int i = 1; i <= n; i++)
			{
				visitedMap.at(size)[i] = 0;
			}
			solution.pop();
			if (solution.empty()) {
				for (int i = 1; i <= n; i++)
				{
					if (visitedMap.at(1)[i] != 1)
					{
						newPosition = i;
						break;
					}
				}
				state new_state(n);
				x = new_state;
			} else {
				x = solution.top();
			}
		}
	}

	x.printSolution();

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "for n=" << n << " it takes: " << elapsed_secs << " seconds, count:" << count << "\n\n";
}