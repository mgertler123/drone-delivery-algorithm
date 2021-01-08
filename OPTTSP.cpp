// Project Identifier: 1761414855B69983BD8035097EFBD312EB0527F0
//  OPTTSP.cpp
//  project4
//
//  Created by Michael Gertler on 4/9/20.
//  Copyright © 2020 Michael Gertler. All rights reserved.
//

#include "OPTTSP.hpp"
#include <math.h>
#include <iostream>
#include <algorithm>

void OPTTSP::genPerms(size_t permLength){
    //Base case
    if (permLength == path.size()) {
         //Add closing edge from last to first
        currDistance += distance_matrix_OPT[path[path.size() - 1]][path[0]];
        //Check/Update best so far
        update();
        //Subtract closing edge
        currDistance -= distance_matrix_OPT[path[path.size() - 1]][path[0]];
        return;
    } // if
    if (!promising(permLength))
        return;
    for (size_t i = permLength; i < path.size(); ++i) {
        swap(path[permLength], path[i]);
        currDistance += distance_matrix_OPT[path[permLength - 1]][path[permLength]];
        genPerms(permLength + 1);
        currDistance -= distance_matrix_OPT[path[permLength - 1]][path[permLength]];
        swap(path[permLength], path[i]);
    } // for
} // genPerms()


bool OPTTSP::promising(size_t permLength){
//    if((path.size() - permLength) < 5){
//        return true;
//    }
    
    if(currDistance > distance_best_so_far){
        return false;
    }
    
    //Run part A
    unsigned int num_locations = static_cast<unsigned int>(loc.size());
    promising_MST.set_path(path);
    promising_MST.part_A_algorithm(loc, num_locations, permLength);

    //Connect first endpoint to MST
    promising_MST.sum += min_dist(static_cast<unsigned int>(0));
    
    //Connect second endpoint to MST
    promising_MST.sum += min_dist(static_cast<unsigned int>(permLength - 1));
    
    //Add currDistance to sum
    promising_MST.sum += currDistance;
    
    //Check
    if(promising_MST.sum <= distance_best_so_far){
        return true;
    }
    return false;
}


void OPTTSP::update(){
    //Check
    if(currDistance < distance_best_so_far){
        //Update
        distance_best_so_far = currDistance;
        path_best_so_far = path;
    }
}


double OPTTSP::euclidean_distance(Vertex &v1, Vertex &v2){
    double x = v1.x - v2.x;
    double y = v1.y - v2.y;
    
    double distance = (x * x) + (y * y);
    distance = sqrt(distance);
    
    return distance;
}


void OPTTSP::part_C_algorithm(vector<Vertex> &locations){
    //Part B for Part C
    FASTTSP temp;
    temp.arbitrary_insertion(locations);
    set_path_distance_best_so_far(temp.get_cycle(), temp.get_distance());
    set_locations(locations);
    create_distance_matrix();
    size_t one = 1;
    //genPerms()
    genPerms(one);
    //Print
    print_function();
}


void OPTTSP::print_function(){
    cout << distance_best_so_far << endl;
    for(unsigned int i = 0; i < path_best_so_far.size(); ++i){
        cout << path_best_so_far[i] << " -> ";
    }
    cout << endl;
}


double OPTTSP::min_dist(unsigned int index){
    double temp_dist = numeric_limits<double>::infinity();
    for(unsigned int j = 0; j < promising_MST.get_distance_matrix().size(); ++j){
        if(distance_matrix_OPT[path[index]][promising_MST.get_distance_matrix()[j].v] < temp_dist){
            temp_dist = distance_matrix_OPT[path[index]][promising_MST.get_distance_matrix()[j].v];
        }
    }
    return temp_dist;
}

void OPTTSP::create_distance_matrix(){
    vector<double> temp;
    temp.resize(loc.size());
    for(unsigned int i = 0; i < loc.size(); ++i){
        for(unsigned int j  = 0; j < loc.size(); ++j){
            double distance = euclidean_distance(loc[i], loc[j]);
            temp[j] = distance;
        }
        distance_matrix_OPT.emplace_back(temp);
    }
}

