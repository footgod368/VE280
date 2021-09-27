#include <iostream>
#include <cmath>
using namespace std;
class Mycomplex
{
private:
    double x,y;//x+yi
public:
    Mycomplex(){x=y=0;}
    Mycomplex(double _x,double _y){x=_x;y=_y;}
    void disp() {cout<<x<<"+"<<y<<"i"<<endl;}
    Mycomplex plus(Mycomplex c)
    {
        Mycomplex temp;
        temp.x=x+c.x;
        temp.y=y+c.y;
        return temp;
    }
    Mycomplex minus(Mycomplex c)
    {
        Mycomplex temp;
        temp.x=x-c.x;
        temp.y=y-c.y;
        return temp;
    }
    Mycomplex multiply(Mycomplex c)
    {
        Mycomplex temp;
        temp.x=x*c.x-y*c.y;
        temp.y=x*c.y+y*c.x;
        return  temp;
    }
    double modulus()
    {
        return sqrt(x*x+y*y);
    }

};
int main()
{
    Mycomplex c1(2,3),c2(3,4);
    c1.disp();
    c2.disp();
    Mycomplex c3=c1.plus(c2);
    c3.disp();
    c3=c1.minus(c2);
    c3.disp();
    c3=c1.multiply(c2);
    c3.disp();
    cout<<c1.modulus()<<endl;
    return 0;
}