#include "maevVec.hpp"
#include <iostream>

Vec2i::Vec2i(int x, int y) : x(x), y(y) {}

Vec2i::~Vec2i() {};

Vec2i Vec2i::operator+(const Vec2i &scale) const {
  return Vec2i(scale.x + x, scale.y + y);
}

Vec2i Vec2i::operator-(const Vec2i &scale) const { return operator+(-scale); }

Vec2i Vec2i::operator-() const { return Vec2i(-x, -y); }

Vec2f Vec2i::operator+(const Vec2f &scale) const {
  return Vec2f(x + scale.getX(), y + scale.getY());
}

Vec2f Vec2i::operator-(const Vec2f &scale) const { return operator+(-scale); }

Vec2i Vec2i::operator*(const int scale) const {
  return Vec2i(x * scale, y * scale);
}

Vec2f Vec2i::operator*(const float scale) const {
  return Vec2f(x * scale, y * scale);
}

Vec2f Vec2i::operator/(const int scale) const {
  return operator/((float)scale);
}

Vec2f Vec2i::operator/(const float scale) const {
  return operator*((float)(1.0 / scale));
}

int Vec2i::dot(const Vec2i &other) const {
  return (x * other.getX() + y * other.getY());
}

float Vec2i::dot(const Vec2f &other) const {
  return (x * other.getX() + y * other.getY());
}

int Vec2i::getX() const { return x; }

int Vec2i::getY() const { return y; }

Vec2f::Vec2f(float x, float y) : x(x), y(y) {}
Vec2f::~Vec2f() {}

Vec2f Vec2f::operator+(const Vec2f &scale) const {
  return Vec2f(x + scale.x, y + scale.y);
}
Vec2f Vec2f::operator+(const Vec2i &scale) const {
  return Vec2f(x + scale.getX(), y + scale.getY());
}

Vec2f Vec2f::operator-(const Vec2f &scale) const { return operator+(-scale); }

Vec2f Vec2f::operator-() const { return Vec2f(-x, -y); }

Vec2f Vec2f::operator*(const int scale) const {
  return operator*((float)scale);
}

Vec2f Vec2f::operator*(const float scale) const {
  return Vec2f(x * scale, y * scale);
}

Vec2f Vec2f::operator/(const int scale) const {
  return operator/((float)scale);
}
Vec2f Vec2f::operator/(const float scale) const {
  return operator*((float)(1.0 / scale));
}

float Vec2f::dot(const Vec2i &other) const {
  return (x * other.getX() + y * other.getY());
}
float Vec2f::dot(const Vec2f &other) const {
  return (x * other.x + y * other.y);
}

float Vec2f::getX() const { return x; }

float Vec2f::getY() const { return y; }
