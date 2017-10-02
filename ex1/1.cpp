#include <iostream>
#include <climits>
#include <float.h>

using std::cout;
using std::endl;


int recurFact(int n){
    if(n>0){
        return n * recurFact(n-1);
    }
    else{
        return 1;
    }
}

int iterFact(int n){
    int result = 1;
    for(int x = n; x >= 1; x--){
        result = result * x;

    }
    return result;
}

template<class T>
T inverseFact(T max){
    T count= 1;
    while(max>1){
        max = max /count;
        count++;
    }
    return count;
}

int main(int argc, char* argv[]){
    cout << recurFact(10) << endl;
    cout << iterFact(10)  << endl;

    cout << endl;
    cout << "Int max: "     << INT_MAX  << endl;
    cout << "inverse Fac: " << inverseFact(INT_MAX)  << endl;

    cout << endl;
    cout << "Double max: "  << DBL_MAX  << endl;
    cout << "inverse Fac: " << inverseFact(DBL_MAX)  << endl;

    cout << endl;
    cout << "Long max: "    << LONG_MAX << endl;
    cout << "inverse Fac: " << inverseFact(LONG_MAX)  << endl;

    return 0;
}
