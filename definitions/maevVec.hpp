#ifndef maevVec_hpp
#define maevVec_hpp
class Vec2f;
class Vec2i {
public:
  Vec2i(int x, int y);
  ~Vec2i();

  Vec2i operator+(const Vec2i &scale) const;
  Vec2i operator-(const Vec2i &scale) const;

  Vec2i operator-() const;

  Vec2f operator+(const Vec2f &scale) const;
  Vec2f operator-(const Vec2f &scale) const;

  Vec2i operator*(int scale) const;
  Vec2f operator*(float scale)const;

  Vec2f operator/(int scale)const ;
  Vec2f operator/(float scale)const ;

  int dot(const Vec2i &other) const;
  float dot(const Vec2f &other) const;

  /*
  Vec2i cross(Vec2i other);
  Vec2f cross(Vec2f other);
  */

  int getX() const;

  int getY() const;
  
private:
  int x;
  int y;
};

class Vec2f {
public:
  Vec2f(float x, float y);
  ~Vec2f();

  Vec2f operator+(const Vec2f &scale) const;
  Vec2f operator-(const Vec2f &scale) const;

  Vec2f operator+(const Vec2i &scale) const;
  Vec2f operator-(const Vec2i &scale) const ;

  Vec2f operator-() const;

  Vec2f operator*(const int scale) const;
  Vec2f operator*(const float scale) const;

  Vec2f operator/(const int scale) const;
  Vec2f operator/(const float scale) const;

  float dot(const Vec2i &other) const;
  float dot(const Vec2f &other) const;

  /*
  Vec2f cross(const Vec2i other) const;
  Vec2f cross(const Vec2f other) const;
  */

  float getX() const;

  float getY() const;
  
private:

  float x;
  float y;

};


/*
template <class T>
class Vec3 {
public:
  Vec3(T x, T y, T z);
  ~Vec3();

  Vec3 operator+(Vec3<T> other);
  Vec3 operator-(Vec3<T> other);
  Vec3 operator*(Vec3<T> other);
  Vec3 operator/(Vec3<T> other);

  Vec3 dot(Vec3<T> other);
  Vec3 cross(Vec2<T> other);

  Vec3 getX();
  Vec3 getY();
  Vec3 getZ();

private:
  T x;
  T y;
  T z;
};
*/
#endif //define maevVec_hpp
