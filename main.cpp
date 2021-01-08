// Project Identifier: 1761414855B69983BD8035097EFBD312EB0527F0
//  main.cpp
//  project4
//
//  Created by Michael Gertler on 4/3/20.
//  Copyright © 2020 Michael Gertler. All rights reserved.
//

#include <iostream>
#include "getopt.h"
#include "xcode_redirect.hpp"
#include <iomanip>
#include "MST.hpp"
#include "Vertex.hpp"
#include "FASTTSP.hpp"
#include "OPTTSP.hpp"

using namespace std;

string get_optarg_argument_as_string(){
    string outputMode;
    if (optarg == nullptr) {
        string outputMode = "map";
    }
    else{
        string str(optarg);
        outputMode = str;
    }
    return outputMode;
}

int main(int argc, char * argv[]) {
    
    ios_base::sync_with_stdio(false);
    xcode_redirect(argc, argv);
    cout << setprecision(2);
    cout << fixed;
    
    bool partA = false;
    bool partB = false;
    bool partC = false;
    
    int choice;
    int option_index = 0;
    option long_options[] = {
        { "mode", required_argument,      nullptr, 'm' },
        { "help", no_argument,            nullptr, 'h' },
        { nullptr, 0,                     nullptr, '\0' }
    };

    while ((choice = getopt_long(argc, argv, "m:h", long_options, &option_index)) != -1) {
        switch (choice) {
        case 'm': {
            string mode = get_optarg_argument_as_string();
            if(mode == "MST"){
                partA = true;
            }
            else if(mode == "FASTTSP"){
                partB = true;
            }
            else if(mode == "OPTTSP"){
                partC = true;
            }
            else{
                cerr << "error: invalid command line\n";
                exit(1);
            }
            break;
        }
        case 'h': {
            cout << "Help" << endl;
            exit(0);
        }
        default: {
            cerr << "error: invalid command line\n";
            exit(1);
        }
        } // switch
    } // while
    
    
    //READING INPUT
    unsigned int num_locations = 0;
    cin >> num_locations;
    vector<Vertex> locations;
    locations.resize(num_locations);
    for(unsigned int i = 0; i < num_locations; ++i){
        Vertex temp;
        cin >> temp.x;
        cin >> temp.y;
        if(partA){
            if((temp.x < 0 && temp.y == 0) || (temp.x == 0 && temp.y < 0)){
                temp.location = 'B';
            }
            else if(temp.x < 0 && temp.y < 0){
                temp.location = 'M';
            }
            else{
                temp.location = 'N';
            }
        }
        locations[i] = temp;
    }
    
    
    if(partA){
        size_t zero = 0;
        MST temp;
        temp.part_A_algorithm(locations, num_locations, zero);
    }
    else if(partB){
        FASTTSP temp;
        temp.part_B_algorithm(locations);
    }
    else if(partC){
        OPTTSP temp;
        temp.part_C_algorithm(locations);
    }
    
    
    return 0;
}
