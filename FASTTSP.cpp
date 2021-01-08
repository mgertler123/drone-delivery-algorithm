// Project Identifier: 1761414855B69983BD8035097EFBD312EB0527F0
//  FASTTSP.cpp
//  project4
//
//  Created by Michael Gertler on 4/8/20.
//  Copyright © 2020 Michael Gertler. All rights reserved.
//

#include "FASTTSP.hpp"
#include <math.h>
#include <iostream>


void FASTTSP::arbitrary_insertion(vector<Vertex> &locations){
    //Insert first vertex into cycle
    cycle.emplace_back(0);
    cycle.emplace_back(0);
    
    for(unsigned int k = 1; k < locations.size(); ++k){
        double cost_diff = numeric_limits<double>::infinity();
        unsigned int index_i = 0;
        unsigned int index_j = index_i + 1;
        for(unsigned int i = 0; i < cycle.size(); ++i){
            double dist = 0;
            if((i+1) == cycle.size()){
                dist = euclidean_distance(locations[cycle[i]], locations[k]) + euclidean_distance(locations[k], locations[cycle[0]]) - euclidean_distance(locations[cycle[i]], locations[cycle[0]]);
            }
            else{
                dist = euclidean_distance(locations[cycle[i]], locations[k]) + euclidean_distance(locations[k], locations[cycle[i+1]]) - euclidean_distance(locations[cycle[i]], locations[cycle[i+1]]);
            }
            
            if(dist < cost_diff){
                cost_diff = dist;
                index_i = i;
                index_j = i + 1;
            }
        }
        if(index_j == cycle.size()){
            cycle.emplace_back(k);
        }
        else{
            cycle.insert(cycle.begin() + index_j, k);
        }
        
        total_distance += cost_diff;
    }
    
}

double FASTTSP::euclidean_distance(Vertex &v1, Vertex &v2){
    double x = v1.x - v2.x;
    double y = v1.y - v2.y;
    
    double distance = (x * x) + (y * y);
    distance = sqrt(distance);
    
    return distance;
}

void FASTTSP::print_function(){
    cout << total_distance << endl;
    for(unsigned int i = 0; i < cycle.size() - 1; ++i){
        cout << cycle[i] << " -> ";
    }
    cout << endl;
}

void FASTTSP::part_B_algorithm(vector<Vertex> &locations){
    arbitrary_insertion(locations);
    print_function();
}
