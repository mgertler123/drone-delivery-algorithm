// Project Identifier: 1761414855B69983BD8035097EFBD312EB0527F0
//  OPTTSP.hpp
//  project4
//
//  Created by Michael Gertler on 4/9/20.
//  Copyright © 2020 Michael Gertler. All rights reserved.
//

#ifndef OPTTSP_hpp
#define OPTTSP_hpp

#include <stdio.h>
#include <vector>
#include "Vertex.hpp"
#include "MST.hpp"
#include "FASTTSP.hpp"

using namespace std;

class OPTTSP{
public:
    
    void set_path_distance_best_so_far(vector<unsigned int> &cycle, double &distance){
        path_best_so_far.resize(cycle.size() - 1);
        path.resize(cycle.size() - 1);
        for(unsigned int i = 0; i < cycle.size() - 1; ++i){
            path_best_so_far[i] = cycle[i];
            path[i] = cycle[i];
        }
        distance_best_so_far = distance;
    }
    
    void set_locations(vector<Vertex> &locations){
        loc = locations;
    }
    
    double euclidean_distance(Vertex &v1, Vertex &v2);
    
    bool promising(size_t permLength);
    
    void genPerms(size_t permLength);
    
    void update();
    
    void part_C_algorithm(vector<Vertex> &locations);
    
    void print_function();
    
    double min_dist(unsigned int index);
    
    void create_distance_matrix();
    
private:
    vector<unsigned int> path;
    vector<unsigned int> path_best_so_far;
    double distance_best_so_far;
    double currDistance = 0;
    vector<Vertex> loc;
    MST promising_MST;
    vector<vector<double>> distance_matrix_OPT;
};

#endif /* OPTTSP_hpp */
