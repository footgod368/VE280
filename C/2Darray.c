#include <stdio.h>
#include <string.h>
int main(){
char arr[3][3];
arr[0][0]='a';
arr[0][1]='b';
arr[0][2]='c';
arr[1][0]='a';
arr[1][1]='b';
arr[1][2]='\0';
arr[2][0]='b';
arr[2][1]='c';
arr[2][2]='\0';
printf("%s\n",arr[0]);
printf("%s\n",arr[1]);
printf("%s\n",arr[2]);
return 0;
}