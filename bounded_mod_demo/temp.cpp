#include <iostream>

using namespace std;

inline int bounded_mod_negative(int value, int max){
    value = value % max;
    if(value < 0){
        value += max;
    }
    return value;
}

main(){
    for (int i = -10; i < 10; i++)
    {
        // cout << "i is at " << i << " and i % 5 is: " << (i % 5) << endl;
        cout << "Function value is : " << bounded_mod_negative(i, 5) << endl;
    }
    return 0;
}