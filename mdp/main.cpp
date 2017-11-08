#include "util.h"
#include "vi.h"
#include "navigation.h"
#include "lrtdp.h"

using namespace namespace_MDP;

int main()
{
    
	/*

  
    GRAPH G = build_random_graph();
    graph_to_dot(G,"G.dot");
	
	tuple<GRAPH_D, brother_states > tuple_G_D = determinism_mdp(G);

	graph_D_to_file(tuple_G_D,"G1_D.dot");

*/
/*
	vector<double> pr = random_pr_distribution(2);

	for(int i=0; i<pr.size() ; i++)
	{
		cout<<pr[i]<<endl;
	}
*/
//	valueIteration(G, "29", 0.01);


	int w = 5;
	int h = 5;


	vector<int> dead_ends;
	dead_ends.push_back(w*h-1-w-1);
	//dead_ends.push_back(2);
	//dead_ends.push_back(10);

	//dead_ends = randomDeadEnds(w,h,20);

	GRAPH N = generateRandomNavigation(w,h,dead_ends);



	graph_to_dot(N,"N.dot");
	

	auto V_P = valueIteration(N, to_string(w*h-1), 0.001);

	valueFunctionPr V = get<0>(V_P);
	Policy P = get<1>(V_P);
	
	cout<<"----------------------------------------------------------------------------"<<endl;
	for(int i=0; i<V.size(); i++)
	{
		
		if (find(dead_ends.begin(),dead_ends.end(),i)!=dead_ends.end())
			cout<<setw(6)<<"X"<<" ";
		else
			cout<<setw(6)<<i<<" ";

		if((i+1)%w==0)
			cout<<endl;
	}

	cout<<"----------------------------------------------------------------------------"<<endl;

	for(int i=0; i<V.size(); i++)
	{
		cout<<setw(6)<<setprecision(2)<<V[to_string(i)]<<" ";
		if((i+1)%w==0)
			cout<<endl;
	}


	map<id_state,string> nav_action;
	nav_action["0"] = "UP";
	nav_action["1"] = "DOWN";
	nav_action["2"] = "RIGHT";
	nav_action["3"] = "LEFT";
	nav_action["None"] = "Stay";

	cout<<"----------------------------------------------------------------------------"<<endl;


	for(int i=0; i<V.size(); i++)
	{
		
		cout<<setw(6)<<nav_action[P[to_string(i)]]<<" ";
		if((i+1)%w==0)
			cout<<endl;
	}

	cout<<"----------------------------------------------------------------------------"<<endl;
	


	string file_name = "Nav_VI_" + to_string(w)+"_"+to_string(h);
	graphNavigation(w, h, V, P, dead_ends, file_name);
//-----------------------
	string folder_name  = "Nav_" + to_string(w)+"_"+to_string(h) +"_folder";
	string problem_name = file_name+"_Problem.dot";
	string value_name   = file_name+"_ValuePr.dot";
	string policy_name  = file_name+"_Policy.dot";

	string cmd0 = "rm -rf "+ file_name +"_folder";
	system(cmd0.c_str());
	string cmd1 = "mkdir "+ file_name +"_folder";
	system(cmd1.c_str());
	string cmd2 = "mv "+problem_name +" "+ folder_name;
	system(cmd2.c_str());
	cmd2 = "mv "+policy_name+" "+ folder_name;
	system(cmd2.c_str());
	cmd2 = "mv "+value_name+" "+ folder_name;
	system(cmd2.c_str());



	string cmd_draw = "dot -Tsvg "+folder_name+"/"+problem_name+" -o "+folder_name+"/A_"+file_name+"_Problem.svg";
	system(cmd_draw.c_str());
	cmd_draw = "dot -Tsvg "+folder_name+"/"+value_name+" -o "+folder_name+"/B_"+file_name+"_ValuePr.svg";
	system(cmd_draw.c_str());
	cmd_draw = "dot -Tsvg "+folder_name+"/"+policy_name+" -o "+folder_name+"/C_"+file_name+"_Policy.svg";
	system(cmd_draw.c_str());
//-------------


	auto v_p = rtdp(N,"0",to_string(w*h-1));

	V = get<0>(v_p);
	P = get<1>(v_p);

	file_name = "Nav_RTDP_" + to_string(w)+"_"+to_string(h);
	graphNavigation(w, h, V, P, dead_ends, file_name);

	problem_name = file_name+"_Problem.dot";
	value_name   = file_name+"_ValuePr.dot";
	policy_name  = file_name+"_Policy.dot";

	
	cmd2 = "mv "+problem_name +" "+ folder_name;
	system(cmd2.c_str());
	cmd2 = "mv "+policy_name+" "+ folder_name;
	system(cmd2.c_str());
	cmd2 = "mv "+value_name+" "+ folder_name;
	system(cmd2.c_str());



	cmd_draw = "dot -Tsvg "+folder_name+"/"+problem_name+" -o "+folder_name+"/A_"+file_name+"_Problem.svg";
	system(cmd_draw.c_str());
	cmd_draw = "dot -Tsvg "+folder_name+"/"+value_name+" -o "+folder_name+"/B_"+file_name+"_ValuePr.svg";
	system(cmd_draw.c_str());
	cmd_draw = "dot -Tsvg "+folder_name+"/"+policy_name+" -o "+folder_name+"/C_"+file_name+"_Policy.svg";
	system(cmd_draw.c_str());


	for(int i=0; i<V.size(); i++)
	{
		cout<<setw(6)<<setprecision(2)<<V[to_string(i)]<<" ";
		if((i+1)%w==0)
			cout<<endl;
	}

	//map<id_state,string> nav_action;
	nav_action["0"] = "UP";
	nav_action["1"] = "DOWN";
	nav_action["2"] = "RIGHT";
	nav_action["3"] = "LEFT";
	nav_action["None"] = "Stay";

	cout<<"----------------------------------------------------------------------------"<<endl;
	

	for(int i=0; i<V.size(); i++)
	{
		
		cout<<setw(6)<<nav_action[P[to_string(i)]]<<" ";
		if((i+1)%w==0)
			cout<<endl;
	}

    return 0;

}
