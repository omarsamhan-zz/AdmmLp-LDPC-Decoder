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

    code_struct code_r;
    
    if (!alist_file) {
        cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }

    // Read code length and dimension
    std::string line;
    if(std::getline(infile, line))
        iss >> n >> m;
        k = n - m;
    else {
        cerr << "Cannot read line: code length and dimension\n";
        exit(1);
    }

    // Read check and variable degrees
    if(std::getline(infile, line))
        iss >> d_c >> d_v;
    else {
        cerr << "Cannot read: code degrees!\n";
        exit(1);
    }
    
    // Read check degree vector
    if(std::getline(infile, line)) {
        out_code.row_density.resize(cout.code)
        while() 
        //iss >> out_code.d_c >> out_code.d_v;
    } else {
        cerr << "Cannot read: code degrees!\n";
        exit(1);
    }

}
