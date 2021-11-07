#include <iostream>

using namespace std;

// 基类
struct Shape
{
    void setWidth(int w)
    {
        width = w;
    }
    void setHeight(int h)
    {
        height = h;
    }
    int width;
    int height;
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
    int getArea()
    {
        return (width * height);
    }
};

int main(void)
{
    Rectangle Rect;

    Rect.setWidth(5);
    Rect.setHeight(7);
    Rect.setName("poly-inheritance");
    Rect.sayName();
    // 输出对象的面积
    cout << "Total area: " << Rect.getArea() << endl;

    return 0;
}