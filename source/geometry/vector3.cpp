#include "geometry/vector3.h"

#include <cmath>
#include <sstream>

float Vector3::Magnitude() const {
    return sqrt(x * x + y * y + z * z);
}

float Vector3::SqrMagnitude() const {
    return x * x + y * y + z * z;
}

float Vector3::Dot(const Vector3& v1, const Vector3& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

std::string Vector3::toString() {
    std::stringstream ss;
    ss << "[" << this->x << " " << this->y << " " << this->z << "]";
    return ss.str();
}

void Vector3::operator=(Vector3& v1) {
    this->x = v1.x;
    this->y = v1.y;
    this->z = v1.z;
}

void Vector3::operator=(Vector3* v1) {
    this->x = v1->x;
    this->y = v1->y;
    this->z = v1->z;
}
