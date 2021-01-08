// Project Identifier: 1761414855B69983BD8035097EFBD312EB0527F0//  MST.hpp
//  project4
//
//  Created by Michael Gertler on 4/6/20.
//  Copyright © 2020 Michael Gertler. All rights reserved.
//

#ifndef MST_hpp
#define MST_hpp

#include <stdio.h>
#include <vector>
#include "Vertex.hpp"
#include <limits>

using namespace std;

struct PrimVertex {
    unsigned int v;
    bool k = false;
    double d;
    unsigned int p;
};

class MST {
    
public:
    
    void set_path(vector<unsigned int> &temp){
        path = temp;
    }
    
    vector<PrimVertex> get_distance_matrix(){
        return distance_matrix;
    }
    
    void initialize_starting_vertex(unsigned int &num_locations, size_t &permLength);
    
    void prims_algorithm(vector<Vertex> &locations);
    
    double euclidean_distance(Vertex &v1, Vertex &v2);
    
    void print_results();
    
    void part_A_algorithm(vector<Vertex> &locations, unsigned int &num_locations, size_t permLength);
    
    void path_length_calculator();

    double sum = 0;
    
private:
    vector<PrimVertex> distance_matrix;
    vector<unsigned int> path;
    
};

#endif /* MST_hpp */
