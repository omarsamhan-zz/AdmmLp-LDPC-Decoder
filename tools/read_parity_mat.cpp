#include "read_parity_mat.h"

code_struct read_alist(string filename) {
    ifstream alist_file;
    alist_file.open(filename.c_str());

    code_struct cr; // code read from file
    
    if (!alist_file) {
        cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }

    // Read code length and dimension
    string line;
    stringstream iss;
    if(std::getline(alist_file, line)) {
        iss >> cr.n >> cr.m;
        cr.k = cr.n - cr.m;
    } else {
        cerr << "Cannot read line: code length and dimension\n";
        exit(1);
    }

    // Read check and variable degrees
    if(std::getline(alist_file, line))
        iss >> cr.d_c >> cr.d_v;
    else {
        cerr << "Cannot read: code degrees!\n";
        exit(1);
    }
    
    // Read check degree vector
    if(std::getline(alist_file, line)) {
        cr.row_density.resize(cr.m);
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

    // Read variable degree vector
    if(std::getline(alist_file, line)) {
        cr.col_density.resize(cr.n);
        for(int i = 0; i < cr.n; i++) { // read row degrees
            if(!iss >> cr.col_density[i]) {
                cerr << "Error reading column density vector!\n";
                exit(1);
            }
        } 
    } else {
        cerr << "Cannot read: code degrees!\n";
        exit(1);
    }

    // Read variable to check node connections 
    if(std::getline(alist_file, line)) {
        cr.var2chk_conn.resize(cr.n);
        for(int i = 0; i < cr.n; i++) { // read row degrees
            cr.var2chk_conn[i].resize(cr.col_density[i]);
            for(int j = 0;i < cr.col_density[i]; j++) {
                if(!(iss >> cr.var2chk_conn[i][j])) {
                    cerr << "Error reading var to chk matrix!\n";
                    exit(1);
                }
            }
        }
    } else {
        cerr << "Cannot read: code degrees!\n";
        exit(1);
    }

    // Read check to variable node connections 
    if(std::getline(alist_file, line)) {
        cr.chk2var_conn.resize(cr.m);
        for(int i = 0; i < cr.m; i++) { // read row degrees
            cr.chk2var_conn[i].resize(cr.col_density[i]);
            for(int j = 0; i < cr.row_density[i]; j++) {
                if(!(iss >> cr.chk2var_conn[i][j])) {
                    cerr << "Error reading chk to var matrix!\n";
                    exit(1);
                }
            }
        }
    } else {
        cerr << "Cannot read: code degrees!\n";
        exit(1);
    }

    alist_file.close();
    return cr;

}
