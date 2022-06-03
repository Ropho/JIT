#include "func.hpp"

int r_sqrt (int input) {
    
    int output = round (sqrt (input));
    
    return output;
}


int in (void) {

    int rax = 0;
    scanf ("%d", &rax);

    return rax;
}


void out (long long input) {

    printf ("%lld\n", input);
    return;
}
