#include <cstdlib>
#include <iostream>

using namespace std; // intentional guideline violation: using-directive in global scope

#define MAGIC_VALUE 123 // intentional guideline violation: macro constant
int globalCounter = 0;  // intentional guideline violation: non-const global variable

void doSomethingBad()
{
    // intentional guideline violations:
    // - raw new without corresponding delete (leak)
    // - NULL instead of nullptr
    // - C-style cast
    int* buffer = new int[MAGIC_VALUE];
    if (buffer != NULL) {
        double d = (double)MAGIC_VALUE;
        cout << "Allocated " << MAGIC_VALUE << " ints; d=" << d << ", globalCounter=" << globalCounter << '\n';
    }
    // leak on purpose
}


