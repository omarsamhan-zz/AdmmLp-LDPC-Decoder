#pragma once

#include <vector>

struct code_struct {
    int n; // Code length
    int k; // Code dimention
    int m; // # of rows in parity check matrix
    int d_c; // check degree (regular only)
    int d_v; // variable degree (regular only)
    vector<int> row_density;
    vector<int> col_density;
    vector< vector<int> > chk2var_conn;
    vector< vector<int> > var2chk_conn;
};

#include <string>
#include <sstream>
#include <fstream>
using namespace std;

code_struct read_alist(string filename) {
    ifstream alist_file;
    alist_file.open(filename.cstr());

    code_struct cr; // code read from file
    
    if (!alist_file) {
        cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }

    // Read code length and dimension
    std::string line;
    if(std::getline(infile, line))
        iss >> cr.n >> cr.m;
        cr.k = cr.n - cr.m;
    else {
        cerr << "Cannot read line: code length and dimension\n";
        exit(1);
    }

    // Read check and variable degrees
    if(std::getline(infile, line))
        iss >> cr.d_c >> cr.d_v;
    else {
        cerr << "Cannot read: code degrees!\n";
        exit(1);
    }
    
    // Read check degree vector
    if(std::getline(infile, line)) {
        cr.row_density.resize(cout.code)
        for(int i = 0; i < cr.m; i++) { // read row degrees
            if(!iss >> cr.row_density[i]) {
                cerr << "Error reading row density vector!\n";
                exit(1);
            }
        } 
    } else {
        cerr << "Cannot read: code degrees!\n";
        exit(1);
    }

    // Read check degree vector
    if(std::getline(infile, line)) {
        cr.row_density.resize(cout.code)
        for(int i = 0; i < cr.n; i++) { // read row degrees
            if(!iss >> cr.row_density[i]) {
                cerr << "Error reading column density vector!\n";
                exit(1);
            }
        } 
    } else {
        cerr << "Cannot read: code degrees!\n";
        exit(1);
    }

    infile.close();
    return cr;

}
