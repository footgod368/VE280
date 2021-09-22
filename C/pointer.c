#include <stdio.h>
void increment(int *px); //函数原型，后面加分号
 int main()
{
 int x=1;
 printf("%d\n",x);//会是1
 increment(&x); //把x的地址传给函数
 printf("%d\n",x);//会是2
 return 0;
}
 void increment(int *px)//自变量是一个指针，copy了&x
{
  (*px)++;//注意不能是 *px++ , 它会增加px而不是它所指的量
}
