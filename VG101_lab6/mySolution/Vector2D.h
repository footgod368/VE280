#include <iostream>
#include <cmath>

#ifndef VECTOR2D_H
#define VECTOR2D_H

using namespace std;

template <class T>
class Vector2D
{
private:
    T x, y;
    void copyFrom(const Vector2D &source);

public:
    Vector2D(T x_ = 0, T y_ = 0);
    Vector2D(const Vector2D &source);
    Vector2D &operator=(const Vector2D &source);

    Vector2D operator+(const Vector2D &v);
    Vector2D operator-(const Vector2D &v);
    Vector2D operator*(T lambda);
    Vector2D operator/(T lambda);
    Vector2D &operator+=(const Vector2D &v);
    Vector2D &operator-=(const Vector2D &v);
    Vector2D &operator*=(const T lambda);
    Vector2D &operator/=(const T lambda);

    bool operator==(const Vector2D &v);

    T getLength();

    void print();

    ~Vector2D() {}
};

typedef Vector2D<int> Point;

template <class T>
void Vector2D<T>::copyFrom(const Vector2D<T> &source)
{
    if (x != source.x || y != source.y)
    {
        x = source.x;
        y = source.y;
    }
}

template <class T>
Vector2D<T>::Vector2D(T x_, T y_)
    : x(x_), y(y_) {}

template <class T>
Vector2D<T>::Vector2D(const Vector2D<T> &source)
{
    x = 0;
    y = 0;
    copyFrom(source);
}

template <class T>
Vector2D<T> &Vector2D<T>::operator=(const Vector2D<T> &source)
{
    copyFrom(source);
    return *this;
}

template <class T>
Vector2D<T> Vector2D<T>::operator+(const Vector2D<T> &v)
{
    Vector2D<T> result(x + v.x, y + v.y);
    return result;
}

template <class T>
Vector2D<T> Vector2D<T>::operator-(const Vector2D<T> &v)
{
    Vector2D<T> result(x - v.x, y - v.y);
    return result;
}

template <class T>
Vector2D<T> Vector2D<T>::operator*(const T lambda)
{
    Vector2D<T> result(x * lambda, y * lambda);
    return result;
}

template <class T>
Vector2D<T> Vector2D<T>::operator/(const T lambda)
{
    Vector2D<T> result(x / lambda, y / lambda);
    return result;
}

template <class T>
Vector2D<T> &Vector2D<T>::operator+=(const Vector2D<T> &v)
{
    *this = *this + v;
    return *this;
}

template <class T>
Vector2D<T> &Vector2D<T>::operator-=(const Vector2D<T> &v)
{
    *this = *this - v;
    return *this;
}

template <class T>
Vector2D<T> &Vector2D<T>::operator*=(const T lambda)
{
    *this = *this * lambda;
    return *this;
}

template <class T>
Vector2D<T> &Vector2D<T>::operator/=(const T lambda)
{
    *this = *this / lambda;
    return *this;
}

template <class T>
bool Vector2D<T>::operator==(const Vector2D &v)
{
    return x == v.x && y == v.y;
}

template <class T>
T Vector2D<T>::getLength()
{
    return sqrt(x * x + y * y);
}

template <class T>
void Vector2D<T>::print()
{
    cout << x << " " << y << endl;
}

#endif
