#ifndef _VECTOR3_H
#define _VECTOR3_H

#include <string>

// EngineObject(Vector3)
class Vector3 {
public:
    // EngineField(float, x)
    float x;
    // EngineField(float, y)
    float y;
    // EngineField(float, z)
    float z;

    Vector3() : x(0), y(0), z(0) {};
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {};

    float Magnitude() const;
    float SqrMagnitude() const;
    void operator=(Vector3& v1);
    void operator=(Vector3* v1);
    std::string toString();

    static float Dot(const Vector3& v1, const Vector3& v2);
};

#endif
