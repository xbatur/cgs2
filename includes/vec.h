#ifndef VEC_H
#define VEC_H
#include <cmath>
template<typename T>
class Vec3
{
public:
    //Ctors
    Vec3() : x(T(0)), y(T(0)), z(T(0)) {}
    Vec3(const T& xx) : x(xx), y(xx), z(xx) {}
    Vec3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}
    //Operator overloading
    Vec3<T> operator + (const Vec3<T>& v) const
    {
        return Vec3<T>(x + v.x, y + v.y, z + v.z);
    }
    Vec3<T> operator - (const Vec3<T>& v) const
    {
        return Vec3<T>(x - v.x, y - v.y, z - v.z);
    }
    Vec3<T> operator * (const float& r) const
    {
        return Vec3<T>(x * r, y * r, z * r);
    }
    Vec3<T>& operator=(const Vec3<T>& v) {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }
    Vec3<T>(const Vec3<T>& v) {
        x = v.x;
        y = v.y;
        z = v.z;
    }
    //Functions
    T Length() const;
    Vec3<T>& Normalize();
    T Dot(const Vec3<T>& b) const;
    T Angle(const Vec3<T>& b) const;
    Vec3<T> Cross(const Vec3<T>& v) const;
    //Rotate vector some angle and return new vector.
    Vec3<T> Rotate2D(float Angle) const;
    //Rotate object itself.
    void Rotate2DSelf(float Angle);
    Vec3<T> Project(const Vec3<T>& b) const;
    void Set(int x = 0, int y = 0, int z = 0) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    //Variables
    T x, y, z;
};

typedef Vec3<float> Vec3f;

//Functions

//Get vector length.
template<typename T>
T Vec3<T>::Length() const{
    return sqrt(x * x + y * y + z * z);
}

//For non class object caller.
template<typename T>
T VecLength(const Vec3<T>& v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}
//End vector length.

//Vector normalization, get unit vector.
template<typename T>
Vec3<T>& Vec3<T>::Normalize(){
    T len = Length();
    if (len > 0) {
        T invertLen = 1 / len;
        x *= invertLen, y *= invertLen, z *= invertLen;
    }
    return *this;
}
//For non class object caller.
template<typename T>
Vec3<T>& VecNormalize(const Vec3<T> &v) {
    T len = v.x * v.x + v.y * v.y + v.z * v.z;
    if (len > 0) {
        T invertLen = 1 / sqrt(len);
        v.x *= invertLen, v.y *= invertLen, v.z *= invertLen;
    }
    return *this;
}
// End vector normalization

//Dot Product
template <typename T>
T Vec3<T>::Dot(const Vec3<T>& b) const {
    return (x * b.x + y * b.y + z * b.z);
}

//For non class object caller.
template <typename T>
T VecDot( Vec3<T>& a,  Vec3<T>& b) {
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

//Get cosine angle between them
template <typename T>
T Vec3<T>::Angle(const Vec3<T>& b) const {
    if(abs(Length()) * abs(b.Length()) > 0)
        return cos(Dot(b) / (Length() * b.Length()));
}

//For non class object caller.
template <typename T>
T VecAngle(const Vec3<T>& a, const Vec3<T>& b) {
    if (abs(a.Length()) * abs(b.Length()) > 0)
        return VecDot(a,b) / (VecLength(a) * VecLength(b));
}

//End Dot Product

//Cross Product.
template <typename T>
Vec3<T> Vec3<T>::Cross(const Vec3<T>& v) const {
    return Vec3<T>(
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x
        );
}

//For non class object caller.
template <typename T>
Vec3<T> VecCross( Vec3<T>& a,  Vec3<T>& b) {
    return Vec3<T>(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
        );
}
//End Cross Product

//Rotate
template <typename T>
Vec3<T> Vec3<T>::Rotate2D(float Angle) const {
    return Vec3<T>(x * cos(Angle) - y * sin(Angle),
                   x * sin(Angle) + y * cos(Angle),
                   0
                  );
}

//Rotate object itself.
template <typename T>
void Vec3<T>::Rotate2DSelf(float Angle) {
    int oldX = x;
    int oldY = y;
    x = oldX * cos(Angle) - oldY * sin(Angle);
    y = oldX * sin(Angle) + oldY * cos(Angle);
}

template <typename T>
void VecRotate2DSelf(const Vec3<T> &v,float Angle) {
    int oldX = v.x;
    int oldY = v.y;
    v.x = oldX * cos(Angle) - oldY * sin(Angle);
    v.y = oldX * sin(Angle) + oldY * cos(Angle);
}

//End Rotate

//Project a vector onto b
template <typename T>
Vec3<T> Vec3<T>::Project(const Vec3<T>& b) const {
    float d = b.Length();
    d *= d;
    if(abs(d) > 0)
        return b * (Dot(b) / d);
}

//For non class object caller.
template <typename T>
Vec3<T> vecProject(const Vec3<T>& a, const Vec3<T>& b){
    float d = VecLength(b);
    d *= d;
    if (abs(d) > 0)
    return (b * (VecDot(a,b) / d));
}
//End projection
#endif