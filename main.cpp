#include <iostream>
#include <cstdlib>
#include "longStr.h"

using namespace std;

int main() {
    long num;
    char *s[255];
    char start[80], *end;

    cout << "Enter number to convert" << endl;

    cin >> start;
    cout << strtolMine(start, &end, 16) << endl;
    cout << strtol(start, &end, 16);
    return 0;
}
