//Print out the prime factor decomposition for a positive integer (>1)
#include <stdio.h>
#include <math.h> //note that you need to type in "gcc xxx.c -o xxx -lm" in terminal if you include math.h in linux

int isPrime(int n);
int pfd(int n);

int main(){
    int n;
    printf("enter a positive integer greater than 1 : ");
    scanf("%d",&n);
    if (isPrime(n))
    printf("%d=1x%d\n",n,n);
    else
    {
        printf("%d=",n);
        pfd(n);
    }
}

int isPrime(int n){
    double limit = sqrt(n) + 1;
    if (n==2) return 1;
    else
    {
        for (int i=2;i<limit;i++)
            if (n%i==0) return 0;
        return 1;
    }
}

int pfd(int n) {
    if (isPrime(n))
    {
        printf("%d\n",n);
        return 0;
    }
    else
    {   int factor;
        for (int i=2;i<n;i++)
        {
            if (n%i==0)
            {
                printf("%dx",i);
                factor =i;
                break;
            }
        }
        return (pfd(n/factor));
    }
}