#ifndef VEC3_H
#define VEC3_H

#include <math.h>

//Alternate Vec3 struct without SSE, simpler and may be the same speed, will benchmark once project is complete

struct Vec3 {
	float x, y, z;

	Vec3();
	Vec3(float x0, float y0, float z0);

	Vec3 operator+(const Vec3& rhs) const;
	Vec3 operator-(const Vec3& rhs) const;
	Vec3 operator*(float rhs) const;
	Vec3 operator/(float rhs) const;
	Vec3 operator-() const;

	Vec3& operator+=(const Vec3& rhs);
	Vec3& operator-=(const Vec3& rhs);
	Vec3& operator*=(float rhs);
	Vec3& operator/=(float rhs);

	float mag() const;
	float lengthSquared() const;

	Vec3 normal() const;
	Vec3& normalize();

	static float dot(const Vec3& lhs, const Vec3& rhs);
	static float angle(const Vec3& lhs, const Vec3& rhs);
	static Vec3 cross(const Vec3& lhs, const Vec3& rhs);
};

inline Vec3::Vec3() : x(0.0f), y(0.0f), z(0.0f) {
	//Constructs zero vector
}

inline Vec3::Vec3(float x0, float y0, float z0) : x(x0), y(y0), z(z0) {
	//Creates vector with components <x0, y0, z0>
}

inline Vec3 Vec3::operator+(const Vec3& rhs) const {
	return Vec3(x + rhs.x, y + rhs.y, z + rhs.z);
}

inline Vec3 Vec3::operator-(const Vec3& rhs) const {
	return Vec3(x - rhs.x, y - rhs.y, z - rhs.z);
}

inline Vec3 Vec3::operator*(float rhs) const {
	return Vec3(x * rhs, y * rhs, z * rhs);
}

inline Vec3 Vec3::operator/(float rhs) const {
	return Vec3(x / rhs, y / rhs, z / rhs);
}

inline Vec3 Vec3::operator-() const {
	return Vec3(-x, -y, -z);
}

inline Vec3& Vec3::operator+=(const Vec3& rhs) {
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

inline Vec3& Vec3::operator-=(const Vec3& rhs) {
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

inline Vec3& Vec3::operator*=(float rhs) {
	x *= rhs;
	y *= rhs;
	z *= rhs;
	return *this;
}

inline Vec3& Vec3::operator/=(float rhs) {
	x /= rhs;
	y /= rhs;
	z /= rhs;
	return *this;
}

inline float Vec3::mag() const {
	return sqrtf(lengthSquared());
}

inline float Vec3::lengthSquared() const {
	return x*x + y*y + z*z;
}

inline Vec3 Vec3::normal() const {
	return operator/(mag());
}

inline Vec3& Vec3::normalize() {
	return operator/=(mag());
}

inline float Vec3::dot(const Vec3& lhs, const Vec3& rhs) {
	return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z;
}

inline float Vec3::angle(const Vec3& lhs, const Vec3& rhs) {
	return acosf(dot(lhs, rhs) / lhs.mag() / rhs.mag());
}

inline Vec3 Vec3::cross(const Vec3& lhs, const Vec3& rhs) {
	return Vec3(lhs.y*rhs.z - lhs.z*rhs.y, lhs.x*rhs.z - lhs.z*rhs.x, lhs.x*rhs.y - lhs.y*rhs.x);
}

#endif //VEC3_H