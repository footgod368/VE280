#include <iostream>
#include <fstream>
using namespace std;

// 基类
struct Shape
{
private:
    int width;
    int height;

public:
    void setWidth(int w)
    {
        width = w;
    }
    void setHeight(int h)
    {
        height = h;
    }
};

struct Entity
{
    string name;
    void setName(string str)
    {
        name = str;
    }
    void sayName()
    {
        cout << name << endl;
    }
};

// 派生类
class Rectangle : public Shape,
                  public Entity
{
public:
    int test;
    int getArea()
    {
        return (width * height);
    }
    Rectangle() { test = 100; };
};

int main(void)
{
    Rectangle Rect;

    Rect.setWidth(5);
    Rect.setHeight(7);
    Rect.setName("poly-inheritance");
    Rect.sayName();
    cout << "Total area: " << Rect.getArea() << endl;

    return 0;
}