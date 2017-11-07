#ifndef NAV_H
#define NAV_H


#include "util.h"


namespace namespace_MDP
{


	succ_states getSuccessors(int s, int a, int w, int h);

	GRAPH generateRandomNavigation(int w, int h, vector<int> &dead_ends)
	{

		GRAPH G;
		int num_states = h*w;

		for(int s=0; s<num_states; s++)
		{

			action_edge actions;
			for(int a=0; a<4; a++)
			{
				succ_states succs = getSuccessors(s,a,w,h);

				action_ut_states act_ut_st = make_tuple(to_string(a),0,succs);

				if(num_states-1-w==s && a == 1)
				{
					//cout<<s<<" "<<a<<endl;
					act_ut_st = make_tuple(to_string(a),1,succs);
				}
				if(num_states-1-1==s && a == 2)
				{
					//cout<<s<<" "<<a<<endl;
					act_ut_st = make_tuple(to_string(a),1,succs);
				}


				

				actions.push_back(act_ut_st);
			}

			if(find(dead_ends.begin(),dead_ends.end(),s)!=dead_ends.end())
			{
				G[to_string(s)] = action_edge();
			}else{
				G[to_string(s)] =actions;
			}

			
		}


		return G;


	}

	succ_states getSuccessors(int s, int a, int w, int h)
	{

		probability P0 = 0.8;
		probability P1 = 0.1;
		probability P2 = 0.1;

		succ_states succs;
		int s1;


		switch(a)
		{
			//UP
			case 0: 

				s1 = s-w;
				if(s1>0)
				{
					succs.push_back(make_tuple(P0,to_string(s1)));
					s1 = s+1;
					if(s1%w!=0)
						succs.push_back(make_tuple(P1,to_string(s1)));
					s1 = s-1;
					if(s%w!=0)
						succs.push_back(make_tuple(P2,to_string(s1)));
				}
				break;
			//DOWN
			case 1:

				s1 = s+w;
				if(s1<w*h)
				{
					succs.push_back(make_tuple(P0,to_string(s1)));
					s1 = s+1;
					if(s1%w!=0)
						succs.push_back(make_tuple(P1,to_string(s1)));
					s1 = s-1;	
					if(s%w!=0)
						succs.push_back(make_tuple(P2,to_string(s1)));
				}
				
				break;
			//RIGHT
			case 2:
				s1 = s+1;
				if(s1%w!=0)
				{
					succs.push_back(make_tuple(P0,to_string(s1)));
					s1 = s+w;
					if(s1<w*h)
						succs.push_back(make_tuple(P1,to_string(s1)));
					s1 = s-w;
					if(s1>0)
						succs.push_back(make_tuple(P2,to_string(s1)));
				}
				
				break;
			//LEFT
			case 3:
				s1 = s-1;
				if(s%w!=0)
				{
					succs.push_back(make_tuple(P0,to_string(s1)));
					s1 = s+w;
					if(s1<w*h)
						succs.push_back(make_tuple(P1,to_string(s1)));
					s1 = s-w;
					if(s1>0)
						succs.push_back(make_tuple(P2,to_string(s1)));
				}
				
				break;




			default:
				break;
		}

		return succs;

	}

	void graphNavigation(int w,int h, valueFunctionPr &V, Policy &P, vector<int> &dead_ends, string file_name)
	{
		ofstream file;

        file.open(file_name+"_Problem.dot");

        file<<"digraph G"<<endl;
        file<<"{"<<endl;
        file<<"node [shape=plaintext]"<<endl;
        file<<"a[label=<<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\">"<<endl;
        
        for(int i=0; i<h; i++)
        {
        	file<<"<TR>"<<endl;
        	for(int j=0; j<w; j++)
        	{

        		int id_state = i*w+j;



        		if(find(dead_ends.begin(),dead_ends.end(),id_state)!=dead_ends.end())
					file<<"<TD width=\"35\" height=\"35\" fixedsize=\"true\" BGCOLOR=\"gray\">";        			
				else
					if(id_state==0)
        				file<<"<TD width=\"35\" height=\"35\" fixedsize=\"true\" BGCOLOR=\"cyan\">";
        			else
        				if(id_state==(h*w)-1)
        					file<<"<TD width=\"35\" height=\"35\" fixedsize=\"true\" BGCOLOR=\"palegreen\">";
        				else
        					file<<"<TD width=\"35\" height=\"35\" fixedsize=\"true\">";

        		file<<id_state;
        		file<<"</TD>"<<endl;

        	}
        	file<<"</TR>"<<endl;
        }


        file<<" </TABLE>>];"<<endl;
        file<<"}"<<endl;
//-----------------------------------------------------------------------
        file.close();

        file.open(file_name+"_ValuePr.dot");

        file<<"digraph G"<<endl;
        file<<"{"<<endl;
        file<<"node [shape=plaintext]"<<endl;
        file<<"a[label=<<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\">"<<endl;
        
        for(int i=0; i<h; i++)
        {
        	file<<"<TR>"<<endl;
        	for(int j=0; j<w; j++)
        	{
        		int id_state = i*w+j;




        		if(find(dead_ends.begin(),dead_ends.end(),id_state)!=dead_ends.end())
					file<<"<TD width=\"35\" height=\"35\" fixedsize=\"true\" BGCOLOR=\"gray\">";        			
				else
					if(id_state==0)
        				file<<"<TD width=\"35\" height=\"35\" fixedsize=\"true\" BGCOLOR=\"cyan\">";
        			else
        				if(id_state==(h*w)-1)
        					file<<"<TD width=\"35\" height=\"35\" fixedsize=\"true\" BGCOLOR=\"palegreen\">";
        				else
        					file<<"<TD width=\"35\" height=\"35\" fixedsize=\"true\">";

        		file<<setprecision(2)<<V[to_string(id_state)];
        		file<<"</TD>"<<endl;

        	}
        	file<<"</TR>"<<endl;
        }


        file<<" </TABLE>>];"<<endl;
        file<<"}"<<endl;
//-----------------------------------------------------------------------
       	file.close();

       	map<id_action,string> symbol;
       	symbol["0"] = "&#x2191;";
       	symbol["1"] = "&#x2193;";
       	symbol["2"] = "&#x2192;";
       	symbol["3"] = "&#x2190;";
       	symbol["None"] = "&#x27F2;";

        file.open(file_name+"_Policy.dot");

        file<<"digraph G"<<endl;
        file<<"{"<<endl;
        file<<"node [shape=plaintext]"<<endl;
        file<<"a[label=<<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\">"<<endl;
        
        for(int i=0; i<h; i++)
        {
        	file<<"<TR>"<<endl;
        	for(int j=0; j<w; j++)
        	{
        		int id_state = i*w+j;
        		//cout<<"id_state "<<id_state<<endl;
        		//cout<<(h-1)*(w-1)-1<<endl;


        		if(find(dead_ends.begin(),dead_ends.end(),id_state)!=dead_ends.end())
					file<<"<TD width=\"35\" height=\"35\" fixedsize=\"true\" BGCOLOR=\"gray\">";        			
				else
					if(id_state==0)
        				file<<"<TD width=\"35\" height=\"35\" fixedsize=\"true\" BGCOLOR=\"cyan\">";
        			else
        				if(id_state==(h*w)-1)
        					file<<"<TD width=\"35\" height=\"35\" fixedsize=\"true\" BGCOLOR=\"palegreen\">";
        				else
        					file<<"<TD width=\"35\" height=\"35\" fixedsize=\"true\">";

        		file<<symbol[P[to_string(id_state)]];
        		file<<"</TD>"<<endl;

        	}
        	file<<"</TR>"<<endl;
        }


        file<<" </TABLE>>];"<<endl;
        file<<"}"<<endl;




	}

	vector<int> randomDeadEnds(int w, int h, int n)
	{

		vector<int> dead_ends;
		int max = w*h-1;
        int min = 1;

        for(int i=0; i<n; i++)
        {
        	uniform_int_distribution<int> uid(min,max);	
			dead_ends.push_back(uid(rng));        	
        }

        
        

        return dead_ends;
	}

}



#endif