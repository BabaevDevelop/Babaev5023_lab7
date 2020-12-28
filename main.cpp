#include <iostream>
#include "longStr.h"
using namespace std;

int main() {
    long num;
    char * s[255];

    cout << "Enter number to convert" << endl;
    cin >> num;
    cout << ltoab(num, *s);

    return 0;
}
