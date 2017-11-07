#include <iostream>
#include <algorithm>
#include <tuple>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <random>

#include "types.h"
#include "lrtdp.h"

using namespace std;
using namespace namespace_MDP;

void foo_p(vector<int> &V);

id_action random_action(vector<id_action> &actions, vector<probability> &pr_distribution);

int main()
{

	cout<<"Hello World"<<endl;


	vector<tuple<int,string> > states;

	states.push_back(make_tuple(3,"hola"));
	states.push_back(make_tuple(2,"como"));
	states.push_back(make_tuple(5,"hoear"));
	states.push_back(make_tuple(1,"asdad"));



	std::sort(begin(states), end(states), [](auto const &t1, auto const &t2) {
        return get<0>(t1) > get<0>(t2); // or use a custom compare function
	});

	for(int i=0; i<states.size(); i++)
	{
		cout<<get<0>(states[i])<<endl;
	}


	cout<<"TEST QUEUE"<<endl;
	queue<int> Q;

	Q.push(1);
	Q.push(2);
	Q.push(3);
	Q.push(4);
	Q.push(5);


	cout<<Q.front()<<endl;
	Q.pop();
	cout<<Q.front()<<endl;
	Q.pop();
	cout<<Q.front()<<endl;
	cout<<"+++++++++++++++++++++++++"<<endl;


	vector<int> V;
	V.push_back(0);
	V.push_back(1);
	V.push_back(2);
	V.push_back(3);
	V.push_back(4);

	foo_p(V);

	for (auto v: V)
	{
		cout<<v<<" ";
	}
	cout<<endl;


    vector<id_action> A = {"A","B","C"};
    vector<probability> PD = {0.5,0.3,0.2};

    cout<<random_action(A, PD)<<endl;


	return 0;
}

id_action random_action(vector<id_action> &actions, vector<probability> &pr_distribution)
{

	discrete_distribution<> d(pr_distribution.begin(),pr_distribution.end());
	int index_action = d(namespace_MDP::rng);
	return actions[index_action];
}

void foo_p(vector<int> &V)
{
	V[0] = 9;		
}

