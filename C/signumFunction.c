#include <stdio.h>

int main() {
    printf("enter a number: ");
    float x;
    scanf("%f",&x);
    if (x>0) printf("positive");
    else if (x == 0) printf("zero");
    else printf ("negative");
    printf("\n");
    return 0;
}