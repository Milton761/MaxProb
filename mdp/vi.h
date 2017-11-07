#ifndef VI_H
#define VI_H

#include "util.h"


namespace namespace_MDP{



	tuple<probability,id_action> maxPr(id_state s, GRAPH &G, valueFunctionPr &V, id_state goal);

	tuple<valueFunctionPr,Policy> valueIteration(GRAPH &G, id_state goal, error threshold)
	{

		//cout<<"valueIteration"<<goal<<endl;

		valueFunctionPr V;
		BellmanResidual BR;
		Policy P;
		//init probability value function



		for (auto &state : G)
		{
			id_state s = state.first;

			if(s == goal)
				V[s] = 1;
			else
				V[s]= 0;
		}

		int it=0;
		while(true)
		{
			auto Vt = V;
			error errorBelman = 0.0;


			//print value Funtion
			

			for (auto &state: G)
			{
				id_state s = state.first;				
				probability oldV = V[s];

				auto pr_ac = maxPr(s, G, Vt, goal);

				V[s] = get<0>(pr_ac);
				P[s] = get<1>(pr_ac);

				BR[s] = abs(V[s]-oldV);

				errorBelman = max(errorBelman, BR[s]);

			}
/*
			for (auto state: G)
			{
				id_state s = get<_idS_>(state);
				cout<<setprecision(2)<<V[s]<<" ";
			}
			cout<<endl;
*/
			if(errorBelman <= threshold)
			{
				cout<<"num it "<<it<<" "<<endl;
				return forward_as_tuple(V,P);
			}
			it++;	
		}


	}

	tuple<probability,id_action> maxPr(id_state s, GRAPH &G, valueFunctionPr &V, id_state goal)
	{


		vector<probability> vectorPr;
		vector<id_action> vectorAc;

		
		auto edge = G[s];

		if (s==goal)
		{
			vectorPr.push_back(1);
			vectorAc.push_back("None");
		}else{

			if (edge.size()==0)
				return forward_as_tuple(0.0, "None");

			for(auto action: edge)
			{
				auto id_action = get<0>(action);
				auto ut = get<1>(action);
				auto succs = get<2>(action);

				probability tmpPr = 0;

				for(auto succ: succs)
				{
					auto pr = get<0>(succ);
					auto s1 = get<1>(succ);


					tmpPr = tmpPr  +pr * V[s1];
				}

				//tmpPr += ut;

				vectorPr.push_back(tmpPr);
				vectorAc.push_back(id_action);
			}	
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

		return forward_as_tuple(maxPrV, vectorAc[index_max]);

	}

}



#endif