#include "read_parity_mat.h"
#include <cassert>
#include <iomanip>

code_struct read_alist(string filename) {
    
    // State to check our position in the alist file
    read_alist_state read_state = MAT_SIZE;

    // Open provided file
    ifstream alist_file;
    alist_file.open(filename.c_str());

    // Check if the file was succefully open
    assert(alist_file.is_open() && "Could not open alist file!\n");

    code_struct cr; // code read from file
    
    stringstream iss;
    string line; 

    int count; // Keep count of the vectors and matrices read 

    cout << "Hi!\n";
    while(getline(alist_file, line)) {
        stringstream iss(line);
        switch(read_state) {
            case MAT_SIZE:
                iss >> cr.n >> cr.m;
                cr.k = cr.n - cr.m;
                read_state = DENSITY;
                cout << "n = " << cr.n << ", m = " << cr.m << ", k = " << cr.k << endl;
                break;
            case DENSITY:
                iss >> cr.d_c >> cr.d_v;
                cout << "d_c = " << cr.d_c << ", d_v = " << cr.d_v << endl;
                read_state = COL_DENSITY_VEC;
                break;
            case COL_DENSITY_VEC:
                cr.col_density.resize(cr.n);
                count = 0;
                while(iss >> cr.col_density[count]) count++;

                cout << "col_density = ";
                for(int i=0; i<cr.n; i++) {
                    cout << cr.col_density[i] << " ";
                }
                assert(count == cr.n);
                cout << endl;
                read_state = ROW_DENSITY_VEC;
                break;
            case ROW_DENSITY_VEC:
                cr.row_density.resize(cr.m);
                //count = 0;
                for(count = 0; iss >> cr.row_density[count]; count++){};

                cout << "row_density = ";
                for(int i=0; i<cr.m; i++) {
                    cout << cr.row_density[i] << " ";
                }
                cout << "count = " << count << endl;
                assert(count == cr.m);
                cout << endl;
                read_state = V2C_MAT;
                break;
            case V2C_MAT:
                count = 0;
                static int row_count = 0;
                cr.var2chk_conn.resize(cr.n);
                for(int i=0; i<cr.n; i++) cr.var2chk_conn[i].resize(cr.col_density[i]);
                while(iss >> cr.var2chk_conn[row_count][count]) count++;
                row_count++;
                if(row_count == cr.n) {

                    cout << "var2chk_conn = " << endl;
                    for(int i=0; i<cr.n; i++) {
                        for(int j=0; j<cr.col_density[i]; j++) {
                            cout << setw(5) << cr.var2chk_conn[i][j];
                        }
                        cout << endl;
                    }
                    read_state = C2V_MAT;
                }
                break;
            case C2V_MAT:
                exit(0);
            default:
                cerr << "case does not exist.\n";
                exit(1);
        }
    }

}

//code_struct read_alist(string fi lename) {
//    ifstream alist_file;
//    alist_file.open(filename.c_str());
//
//    code_struct cr; // code read from file
//    
//    if (!alist_file) {
//        cerr << "Unable to open file datafile.txt";
//        exit(1);   // call system to stop
//    }
//
//    // Read code length and dimension
//    string line;
//    stringstream iss;
//    if(std::getline(alist_file, line)) {
//        iss >> cr.n >> cr.m;
//        cr.k = cr.n - cr.m;
//    } else {
//        cerr << "Cannot read line: code length and dimension\n";
//        exit(1);
//    }
//
//    // Read check and variable degrees
//    if(std::getline(alist_file, line))
//        iss >> cr.d_c >> cr.d_v;
//    else {
//        cerr << "Cannot read: code degrees!\n";
//        exit(1);
//    }
//    
//    // Read check degree vector
//    if(std::getline(alist_file, line)) {
//        cr.row_density.resize(cr.m);
//        for(int i = 0; i < cr.m; i++) { // read row degrees
//            if(!iss >> cr.row_density[i]) {
//                cerr << "Error reading row density vector!\n";
//                exit(1);
//            }
//        } 
//    } else {
//        cerr << "Cannot read: code degrees!\n";
//        exit(1);
//    }
//
//    // Read variable degree vector
//    if(std::getline(alist_file, line)) {
//        cr.col_density.resize(cr.n);
//        for(int i = 0; i < cr.n; i++) { // read row degrees
//            if(!iss >> cr.col_density[i]) {
//                cerr << "Error reading column density vector!\n";
//                exit(1);
//            }
//        } 
//    } else {
//        cerr << "Cannot read: code degrees!\n";
//        exit(1);
//    }
//
//    // Read variable to check node connections 
//    if(std::getline(alist_file, line)) {
//        cr.var2chk_conn.resize(cr.n);
//        for(int i = 0; i < cr.n; i++) { // read row degrees
//            cr.var2chk_conn[i].resize(cr.col_density[i]);
//            for(int j = 0;i < cr.col_density[i]; j++) {
//                if(!(iss >> cr.var2chk_conn[i][j])) {
//                    cerr << "Error reading var to chk matrix!\n";
//                    exit(1);
//                }
//            }
//        }
//    } else {
//        cerr << "Cannot read: code degrees!\n";
//        exit(1);
//    }
//
//    // Read check to variable node connections 
//    if(std::getline(alist_file, line)) {
//        cr.chk2var_conn.resize(cr.m);
//        for(int i = 0; i < cr.m; i++) { // read row degrees
//            cr.chk2var_conn[i].resize(cr.col_density[i]);
//            for(int j = 0; i < cr.row_density[i]; j++) {
//                if(!(iss >> cr.chk2var_conn[i][j])) {
//                    cerr << "Error reading chk to var matrix!\n";
//                    exit(1);
//                }
//            }
//        }
//    } else {
//        cerr << "Cannot read: code degrees!\n";
//        exit(1);
//    }
//
//    alist_file.close();
//    return cr;
//
//}
