// Project Identifier: 1761414855B69983BD8035097EFBD312EB0527F0
//  FASTTSP.hpp
//  project4
//
//  Created by Michael Gertler on 4/8/20.
//  Copyright © 2020 Michael Gertler. All rights reserved.
//

#ifndef FASTTSP_hpp
#define FASTTSP_hpp

#include <stdio.h>
#include <vector>
#include "Vertex.hpp"
#include <limits>

using namespace std;

class FASTTSP{
public:
    
    vector<unsigned int> &get_cycle(){
        return cycle;
    }
    
    double &get_distance(){
        return total_distance;
    }
    
    void arbitrary_insertion(vector<Vertex> &locations);
    
    double euclidean_distance(Vertex &v1, Vertex &v2);
    
    void print_function();
    
    void part_B_algorithm(vector<Vertex> &locations);
    
private:
    vector<unsigned int> cycle;
    double total_distance = 0;
    
};

#endif /* FASTTSP_hpp */
