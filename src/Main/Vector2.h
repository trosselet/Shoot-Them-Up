#pragma once

#include <cmath>

template <typename T>
class Vector2 {
public:
    T x;
    T y;

    Vector2() : x(0), y(0) {}
    Vector2(T x, T y) : x(x), y(y) {}

    Vector2 operator+(const Vector2& other) const 
    {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator-(const Vector2& other) const 
    {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 operator*(T number) const 
    {
        return Vector2(x * number, y * number);
    }

    Vector2 operator/(T number) const 
    {
        return Vector2(x / number, y / number);
    }

    Vector2& operator+=(const Vector2& other) 
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2& operator-=(const Vector2& other) 
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector2& operator*=(T number) 
    {
        x *= number;
        y *= number;
        return *this;
    }

    Vector2& operator/=(T number) 
    {
        x /= number;
        y /= number;
        return *this;
    }

    bool Normalize()
    {
        float magnitude = std::sqrt(this->x * this->x + this->y * this->y);

        if (magnitude != 0)
        {
            this->x /= magnitude;
            this->y /= magnitude;

            return true;
        }

        return false;
    }
};