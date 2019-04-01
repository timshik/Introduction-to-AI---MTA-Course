#include <iostream> 
#include <queue> 
#include "state.h"
#include <list>

using namespace std;

int main() 
{
	map<int, list<state>> map;
	list<state> list_1, list_2, list_3, list_4, list_5, list_6, list_7, list_8, list_9;
	list<int> movments;
	map.insert(pair<int, list<state>>(1,list_1));
	map.insert(pair<int, list<state>>(2, list_2));
	map.insert(pair<int, list<state>>(3, list_3));
	map.insert(pair<int, list<state>>(4, list_4));
	map.insert(pair<int, list<state>>(5, list_5));
	map.insert(pair<int, list<state>>(6, list_6));
	map.insert(pair<int, list<state>>(7, list_7));
	map.insert(pair<int, list<state>>(8, list_8));
	map.insert(pair<int, list<state>>(9, list_9));
	queue<state> my_queue;
	int * arr_ini = new int[9], *arr = new int[9];
	arr_ini[0] = 4;
	arr_ini[1] = 7;
	arr_ini[2] = 8;
	arr_ini[3] = 6;
	arr_ini[4] = 3;
	arr_ini[5] = 2;
	arr_ini[6] = 0;
	arr_ini[7] = 5;
	arr_ini[8] = 1;
	state x(arr_ini, 0, movments,-1);
	arr[0] = 1;
	arr[1] = 2;
	arr[2] = 3;
	arr[3] = 8;
	arr[4] = 0;
	arr[5] = 4;
	arr[6] = 7;
	arr[7] = 6;
	arr[8] = 5;
	state goal(arr, 0, movments,-1);
	
	while (x != goal)
	{
		x.createNewNode(x,my_queue,map);
		sortQueue(my_queue);
		x = my_queue.front();
		my_queue.pop();
		if (my_queue.empty()) {
			cout << "No solution!\n";
			break;
		}
	}
	int size = 0;
	for (int i = 1; i <= 9; i++)
	{
		size += map.at(i).size();
	}
	
	cout << size << " " << x.returnf() << endl;
	print(x);
	cout << endl;
	x.printAllMovements();

	delete[]arr_ini;
	delete[]arr;
}