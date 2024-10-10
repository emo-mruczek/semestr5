#include <float.h>
#include <stdio.h>

int main() {
    printf("Macheps:\n");
    printf("Float: %.9g\n", FLT_EPSILON);
    printf("Double: %.17g\n", DBL_EPSILON);
    printf("Long double: %.21Lg\n", LDBL_EPSILON);

    printf("Max:\n");
    printf("Float: %.9g\n", FLT_MAX);
    printf("Double: %.17g\n", DBL_MAX);
    printf("Long double: %.21Lg\n", LDBL_MAX);

    return 0;
}
