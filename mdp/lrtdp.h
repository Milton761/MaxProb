#ifndef LRTDP_H
#define LRTDP_H

#include "types.h"



namespace namespace_MDP
{

	probability initializeV(id_state s)
	{
		return 0.1;
	}

	id_action greedy_action(id_state s, GRAPH &G, valueFunctionPr &V)
	{
		tuple<probability, id_action> Pr_Act;
		auto edge = G[s];


		vector<probability> vectorPr;
		vector<id_action> vectorAc;
		probability tmpPr;

		for(auto action: edge)
		{
			auto id_action = get<0>(action);
			auto ut = get<1>(action);
			auto succs = get<2>(action);

			tmpPr = 0;

			for(auto succ: succs)
			{
				auto pr = get<0>(succ);
				auto s1 = get<1>(succ);

				if(V.count(s1)==0)
				{
					V[s1] = 0;
				}

				tmpPr = tmpPr + pr*V[s1];
			}

			vectorPr.push_back(tmpPr);
			vectorAc.push_back(id_action);

		}


		int index_max = 0;
		probability maxPrV = vectorPr[0];

		for(int i=0; i<vectorPr	.size(); i++)
		{
			if(vectorPr[i]>maxPrV)
			{
				index_max=i;
				maxPrV=vectorPr[i];
			}
		}

		return vectorAc[index_max];

	}


	id_state next_state(id_state s, id_action a, GRAPH &G)
	{
		
		vector<id_state> succsV;
		vector<probability> pr_distribution;

		auto edge = G[s];

		for(auto action: edge)
		{
			auto id_action = get<0>(action);
			auto ut = get<1>(action);
			auto succs = get<2>(action);

			for (auto succ: succs)
			{
				pr_distribution.push_back(get<0>(succ));
				succsV.push_back(get<1>(succ));
			} 
		}

		discrete_distribution<> d(pr_distribution.begin(), pr_distribution.end());
		int index_state = d(rng);

		return succsV[index_state];
	}

	probability QValue(id_state s, id_action a, GRAPH &G, valueFunctionPr &V)
	{


		tuple<probability, id_action> Pr_Act;
		auto edge = G[s];

		probability tmpPr;

		for(auto action: edge)
		{
			auto id_action = get<0>(action);
			auto ut = get<1>(action);
			auto succs = get<2>(action);


			tmpPr = 0;

			if (a == id_action)
			{

				for(auto succ: succs)
				{
					auto pr = get<0>(succ);
					auto s1 = get<1>(succ);

					if(V.count(s1)==0)
					{
						V[s1] = 0;
					}

					tmpPr = tmpPr + pr*V[s1];
				}

		
				break;
			}

		}

		

		return tmpPr;
		
	}

	void updateV(id_state s, valueFunctionPr &V, GRAPH &G, Policy &P)
	{
		id_action a = greedy_action(s,G, V);
		V[s] = QValue(s,a,G,V);
		P[s] = a;
	}


    //add void* as parameter to add Heuristic Function

	tuple<valueFunctionPr, Policy> rtdp(GRAPH &G, id_state s, id_state goal)
	{
		valueFunctionPr V;
		Policy P;
		V[goal] = 1;


		while(s!=goal)
		{

			if(G[s].size()!=0)
			{

				id_action a = greedy_action(s, G, V);
				updateV(s,V,G,P);
				s = next_state(s,a,G);	
			}else{
				break;
			}

		}

		return forward_as_tuple(V,P);
	}

/*
	valueFunctionPr lrtdp(GRAPH &G, id_state s0, id_state goal, error threshold)
	{

		valueFunctionPr V;

		while(!solved(s0))
		{
			lrtdp_trial(s0, V, G);
		}

		return V;

	}

	bool check_solved(id_state s)
	{
		return false;
	}


	void lrtdp_trial(id_state s, valueFunctionPr &V, GRAPH &G)
	{
		stack<id_state> visited;


		while(s!=goal && !solved(s))
		{
			visited.push(s);

			if(!V.count(s))
			{
				//initialize V[s]
				V[s] = initializeV(s);
			}

			id_action a = greedy_action(s,G);
			updateV(s, V, G);
			s = next_state(s,a, G);

		}

		while(!visited.empty())
		{
			s = visited.top();
			visited.pop();

			if(!check_solved(s))
			{
				break;
			}
		}
	}
*/



}


#endif