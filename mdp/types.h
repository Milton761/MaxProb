#ifndef TYPES_H
#define TYPES_H

#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <string>
#include <random>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <deque>
#include <cmath>
#include <iomanip>
#include <stack>

using namespace std;


namespace namespace_MDP
{


    #define N_STATES 30
    #define MAX_ACTION_PER_STATE 2
    #define MIN_UTILITY 0
    #define MAX_UTILITY 0
    #define MAX_SUCC_STATE_PER_ACTION 2
    #define RANGE_SUCC_STATE_MIN 5
    #define RANGE_SUCC_STATE_MAX 10


    static mt19937 rng(chrono::system_clock::now().time_since_epoch().count());

    string COLORS[4] = {"blue", "yellow", "green", "red"};

    typedef string id_state;
    typedef string id_action;
    typedef double ut_value;
    typedef double probability;
    typedef double error;

    typedef map<id_state, probability> BellmanResidual;
    typedef map<id_state, probability> valueFunctionPr;

    typedef map<id_state,id_action> Policy;



    typedef vector<tuple<probability, id_state> > succ_states;
    typedef tuple<id_action, ut_value, succ_states> action_ut_states;
    typedef vector<action_ut_states> action_edge;

    typedef map<id_state, action_edge> GRAPH;


    enum _STATE_{_idS_,_edge_};

//types for determinized graph

    
    typedef map<id_state, vector<id_state>  > brother_states;

    // succ_ states = all posibles succesor for all posible actions ordered by probability
    typedef map<id_state, succ_states > GRAPH_D;



}


#endif
