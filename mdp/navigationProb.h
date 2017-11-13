#ifndef NAV_P_H
#define NAV_P_H


#include "util.h"

using namespace namespace_MDP;

namespace _NAVP
{

	succ_states getSuccessors(int s, int a, int w, int h,vector<int>& dead_ends, int s0, int goal);

	GRAPH generateRandomNavigation(int w, int h, int s0, int goal, vector<int>& dead_ends)
	{

		GRAPH G;
		int num_states = h*w;

		for(int s=0; s<num_states; s++)
		{
			action_edge actions;

			for(int a=0; a<4; a++)
			{
				succ_states succs = getSuccessors(s,a,w,h,dead_ends, s0, goal);

				//utility could represent a cost or a reward;
				int ut = 0;

				action_ut_states a_ut_s = make_tuple(to_string(a),0,succs);

				actions.push_back(a_ut_s);
			}

		}

		return G;

	}

	succ_states getSuccessors(int s, int a, int w, int h,vector<int>& dead_ends, int s0, int goal)
	{
		probability Pmax = 0.9;
		probability Pmin = 0.1;

		succ_states succs;
		int s1;	


		probability interval = (Pmax-Pmin)/(w-1);

		


		switch(a)
		{
			//UP
			case 0:
				break;
			//DOWN
			case 1																																																								:
				break;
			//RIGHT
			case 2:
				break;
			//LEFT
			case 3:
				break;
			default:
				break;
		}
	} 


}
 
#endif