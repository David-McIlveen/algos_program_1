#include <iostream>
#include <fstream>

using namespace std;

const string DEFAULT_FILE_NAME = "temp_polygon";

main(){
    cout << "Enter Count: ";
    int count;
    if(!(cin >> count)){
        return -1;
    }
    cout << endl;

    string file_name;
    cout << "Enter file Name: ";
    if(!(cin >> file_name) || file_name == ""){
        cout << endl << "Using defualt file name: " << DEFAULT_FILE_NAME << endl;
        file_name = DEFAULT_FILE_NAME;
    }

    cout << "Convex? [y/n]:";
    string yes_or_no;
    bool is_convex = true;
    if(!(cin >> yes_or_no)){
        cout << "Could not interpret, using default of Yes" << endl;
    } else {
        if(yes_or_no == "n" || yes_or_no == "N") is_convex = false;
    }
    int midpoint = count / 2;
    std::ofstream print_out;
    print_out.open(file_name + ".txt");

    print_out << "0 " << midpoint << endl;
    for (int i = 0; i < count; i++){
        if(i == midpoint && !is_convex){
            print_out << "2 " << i << endl;
        } else {
            print_out << "1 " << i << endl;
        }
    }
    
}