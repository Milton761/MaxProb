#ifndef UTIL_H
#define UTIL_H


#include "types.h"


using namespace std;

namespace namespace_MDP
{


//FUNCTION DECLARATION HEADERS


    int random_succesor(int id);
    int random_num_actions();
    int random_utility_value();
    int random_num_succesors();
    vector<double> random_pr_distribution(int n);


    GRAPH build_random_graph(){


        GRAPH G;

        //this for is for each state
        for(int i=0; i<N_STATES; i++)
        {

            cout<<"------BUILDIG STATE "<<i<<" -------"<<endl;
           

            int num_actions_per_state = random_num_actions();
            cout<<"number of actions: "<<num_actions_per_state<<endl;

            action_edge vector_action_edge;
            //this for is for each action of a state
            for(int j=0; j<num_actions_per_state; j++){
                cout<<"current action: "<<j<<"/"<<num_actions_per_state<<endl;

                int num_succ_per_action = random_num_succesors();
                cout<<"number of succesors: "<<num_succ_per_action<<endl;

                

                succ_states vector_succesors;
                vector<id_state> states_visited;


                //this for is for succesor states of a action
                vector<id_state> v;
                vector<double> pr_dist = random_pr_distribution(num_succ_per_action);
                for(int k=0; k<num_succ_per_action; k++)
                {
                
                    cout<<"current succesor: "<<k<<"/"<<num_succ_per_action<<endl;    
                    id_state label = to_string(random_succesor(i));
                    
                    

                    if (find(v.begin(), v.end(),label)==v.end())
                    {
                        v.push_back(label);

                        vector_succesors.push_back(make_tuple(pr_dist[k],label));

                        cout<<i<<" --"<<j<<"->"<<label<<endl;
                    }else{
                        cout<<"Generate 1 more time"<<endl;
                        k--;
                    }

                }

                id_action label_action = to_string(j);


                vector_action_edge.push_back(make_tuple(label_action,random_utility_value(),vector_succesors));

            }

            id_state label_current_state = to_string(i);

            G[label_current_state] = vector_action_edge;   

            
            //action_ut_states tuple_action_ut_states = make_tuple(random_utility_value());




            cout<<"++++++++++++++++++++++++++++++++++++"<<endl;

        }

        return G;

    }

    //check this function 
    int  random_succesor(int id)
    {

        

        int max = id + RANGE_SUCC_STATE_MAX;
        int min = id - RANGE_SUCC_STATE_MIN;

        if(max >= N_STATES)
            max = N_STATES-1;
        if(min < 0)
            min = 0;

        uniform_int_distribution<int> uid(min,max);
        

        return uid(rng);

    }

    

    vector<double> probability_distribution(int n_states){

        vector<double> pd;
        return pd;
    }

    int random_num_succesors(){
        uniform_int_distribution<int> uid(1, MAX_SUCC_STATE_PER_ACTION);
        return uid(rng);
    }

    int random_num_actions(){

        uniform_int_distribution<int> uid(1, MAX_ACTION_PER_STATE);
        return uid(rng);
    }

    int random_utility_value(){

        uniform_int_distribution<int> uid(MIN_UTILITY, MAX_UTILITY);
        return uid(rng);

    }

    vector<double> random_pr_distribution(int n)
    {
        vector<double> result;
        int max=100;
        int sum_pr=0;


        for(int i=0; i<n-1 ;i++)
        {
            

            max = 100 - sum_pr - (n - (i+1));
            uniform_int_distribution<int> rand_pr(1,max);
            double randomN = rand_pr(rng);

            //cout<<"(0,"<<max<<") -> "<<randomN<<endl;

            double pr = randomN/100;
            result.push_back(pr);
            sum_pr = sum_pr + randomN;
            //cout<<"SUM: "<<sum_pr<<endl;
          
            
        }

        result.push_back(1.0-(sum_pr*1.0/100));

        return result;

    }

    void graph_to_dot(GRAPH &G, string file_name)
    {
        ofstream file;

        file.open(file_name);

        file<<"digraph G"<<endl;
        file<<"{"<<endl;
        //here the graph


        

        
       

        for(auto &var: G)
        {

              

            id_state current_state_label = var.first;
            action_edge vector_action_edge = var.second;
            file<<current_state_label<<" [shape=circle]"<<endl;

            for(int j=0; j<vector_action_edge.size(); j++)
            {
                action_ut_states tuple_action_ut_states = vector_action_edge[j];



                id_action id_action_label = get<0>(tuple_action_ut_states);
                ut_value utility = get<1>(tuple_action_ut_states);
                succ_states vector_succesors = get<2>(tuple_action_ut_states);

                string action_name = "state_"+current_state_label+"_action_"+id_action_label;


                file<<current_state_label<<" -> "<<action_name<<" [label=\""<<id_action_label<<"\",shape=\"box\", color=\"blue\"]"<<endl;
                file<<action_name<<" [shape=point, label=\"\"]"<<endl;

                for(int k=0; k<vector_succesors.size(); k++)
                {

                    tuple<probability, id_state> tuple_pr_state = vector_succesors[k];
                    probability pr = get<0>(tuple_pr_state);
                    id_state succ_state_label = get<1>(tuple_pr_state);

                    file<<action_name<<" -> "<<succ_state_label<<" [label=\""<<pr<<"\",color=\"green\"]"<<endl;


                }

            }

        }

        



        file<<"}"<<endl;


    }

    tuple<GRAPH_D, brother_states > determinism_mdp(GRAPH G)
    {

        GRAPH_D G_D;

        brother_states map_brother_states;
        for(auto &var: G)
        {

              

            id_state current_state_label = var.first;
            action_edge vector_action_edge = var.second;

            succ_states vector_succesors;

            
            succ_states  vector_succesors_D;

            for(int j=0; j<vector_action_edge.size(); j++)
            {
                action_ut_states tuple_action_ut_states = vector_action_edge[j];



                id_action id_action_label = get<0>(tuple_action_ut_states);
                ut_value utility = get<1>(tuple_action_ut_states);
                succ_states vector_succesors = get<2>(tuple_action_ut_states);

                
               

                vector<id_state> vector_brothers;
                for(int k=0; k<vector_succesors.size(); k++)
                {
                    vector_brothers.push_back(get<1>(vector_succesors[k]));
                }

                for(int k=0; k<vector_succesors.size(); k++)
                {

                    tuple<probability, id_state> tuple_pr_state = vector_succesors[k];
                    probability pr = get<0>(tuple_pr_state);
                    id_state succ_state_label = get<1>(tuple_pr_state);

                    
                    vector_succesors_D.push_back(make_tuple(pr, succ_state_label));

                    map_brother_states[succ_state_label] = vector_brothers;

                }


               
            }

           
            //sort states by probabilities
            sort(begin(vector_succesors_D), end(vector_succesors_D), [](auto const &t1, auto const &t2){
                return get<0>(t1) > get<0>(t2); // or use a custom compare function
            });
            G_D[current_state_label] = vector_succesors_D;
           

        }

        return make_tuple(G_D, map_brother_states);
    }

    void graph_D_to_file(tuple<GRAPH_D, brother_states> tuple_G_D, string file_name)    
    {

        GRAPH_D G_D = get<0>(tuple_G_D);
        brother_states map_vector_brothers = get<1>(tuple_G_D);

        ofstream file;

        file.open(file_name);


        file<<"digraph G"<<endl;
        file<<"{"<<endl;

        for(auto& kv : G_D)
        {
            file<<kv.first<<" [shape=\"circle\"]"<<endl;

            cout<<kv.first<<" -> { ";
            for(int i=0; i<kv.second.size(); i++)
            {
                cout<<get<1>(kv.second[i])<<" ";

                file<<kv.first<<" -> "<<get<1>(kv.second[i])<<" [label=\""<<get<0>(kv.second[i])<<"\"]"<<endl;

            }            
            cout<<"}"<<endl;
        }

        file<<"}"<<endl;

    }


//NOT SOLVED WITH DETERMINIZARION
    void solve_max_prob(tuple<GRAPH_D, brother_states> tuple_G_D)
    {

        GRAPH_D G_D = get<0>(tuple_G_D);
        brother_states map_brother_states = get<1>(tuple_G_D);

        deque<id_state> frontier;

        id_state initial_state = "0";
        frontier.push_front(initial_state);

        while(!frontier.empty())
        {
            id_state current_state = frontier.front();
            frontier.pop_front();

            if(G_D[current_state].empty())
            {
                cout<<"DEAD END : "<<current_state<<endl;
            }else{


                //id_state state_max_prob = G_D[current_state][0]                
            }




        }



    }


}

#endif