#include <stdio.h>
#include <string.h>
void myStrcpy(char * pDst,const char * pSrc)
{
    int len1=strlen(pDst);
    int len2=strlen(pSrc);
    if(len1<len2){printf("error\n");return;}
    while((*pDst++=*pSrc++)!='\0');//在while的判断语句中使用++，即可实现不需要循环体
}
int main()
{
    char str1[5]="abcd",str2[6]="12345";
    myStrcpy(str2,str1);
    printf("str1=%s\nstr2=%s\n",str1,str2);
    return 0;
}
