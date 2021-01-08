// Project Identifier: 1761414855B69983BD8035097EFBD312EB0527F0
//  MST.cpp
//  project4
//
//  Created by Michael Gertler on 4/6/20.
//  Copyright © 2020 Michael Gertler. All rights reserved.
//

#include "MST.hpp"
#include <math.h>
#include <iostream>

void MST::initialize_starting_vertex(unsigned int &num_locations, size_t &permLength){
    distance_matrix.clear();
    distance_matrix.resize(num_locations - permLength);
    sum = 0;
    for(unsigned int i = 0; i < num_locations - permLength; ++i){
        if(permLength == 0){
            distance_matrix[i].v = i;
        }
        else{
            distance_matrix[i].v = path[i + permLength];
        }
        distance_matrix[i].d = numeric_limits<double>::infinity();
    }

    distance_matrix[0].d = 0;
}

double MST::euclidean_distance(Vertex &v1, Vertex &v2){
    double distance = 0;
    if((v1.location == 'M' && v2.location == 'N') || (v1.location == 'N' && v2.location == 'M')){
        distance = numeric_limits<double>::infinity();
        return distance;
    }
    double x = v1.x - v2.x;
    double y = v1.y - v2.y;
    
    distance = (x * x) + (y * y);
    distance = sqrt(distance);
    
    return distance;
}

void MST::prims_algorithm(vector<Vertex> &locations){
//    unsigned int counter = 0;
    unsigned int num_times = static_cast<unsigned int>(distance_matrix.size());
    unsigned int size = static_cast<unsigned int>(distance_matrix.size());
    for(unsigned int i = 0; i < num_times; ++i){
        //STEP 1
        unsigned int min_index = 0;
        for(unsigned int j = 1; j < size; ++j){
            if(distance_matrix[j].d < distance_matrix[min_index].d && distance_matrix[j].k == false){
                min_index = j;
            }
        }
        //STEP 2
        distance_matrix[min_index].k = true;
        sum += distance_matrix[min_index].d;
        //Add to sum
        
        //STEP 3
        for(unsigned int k = 0; k < size; ++k){
            if(distance_matrix[k].k == false){
                double dist = euclidean_distance(locations[distance_matrix[min_index].v], locations[distance_matrix[k].v]);
                if(dist < distance_matrix[k].d){
                    distance_matrix[k].d = dist;
                    distance_matrix[k].p = distance_matrix[min_index].v;
                }
            }
        }
        swap(distance_matrix[min_index], distance_matrix[size - 1]);
        --size;
    }
}

void MST::print_results(){
//    for(unsigned int i = 0; i < distance_matrix.size(); ++i){
//        sum += distance_matrix[i].d;
//    }
    if(sum == numeric_limits<double>::infinity()){
        cerr << "Cannot construct MST\n";
        exit(1);
    }
    cout << sum << endl;
    
    for(unsigned int i = 0; i < distance_matrix.size() - 1; ++i){
        if(distance_matrix[i].v < distance_matrix[i].p){
            cout << distance_matrix[i].v << " " << distance_matrix[i].p << endl;
        }
        else{
            cout << distance_matrix[i].p << " " << distance_matrix[i].v << endl;
        }
    }
}

void MST::part_A_algorithm(vector<Vertex> &locations, unsigned int &num_locations, size_t permLength){
//    set_location(locations);
    initialize_starting_vertex(num_locations, permLength);
    prims_algorithm(locations);
    if(permLength == 0){
        print_results();
    }
}


//void MST::path_length_calculator(){
//    for(unsigned int i = 0; i < distance_matrix.size(); ++i){
//        sum += distance_matrix[i].d;
//    }
//}
