// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <cmath>
#include <ostream>
#include "../utils/checkML.h"
#include <iostream>
/*
 * A class implementing a 2-dimensional vector and corresponding
 * operations. All operations generate new Vector2D, they do not
 * modify the vectors on which they operate. The only methods that
 * modify the state are the different setters (and operator=).
 *
 */
class Vector2D {
public:

	// various constructors
	Vector2D() noexcept :
		x_(), y_() {
	}

	Vector2D(const Vector2D& v) :
		x_(v.getX()), y_(v.getY()) {
	}

	Vector2D(Vector2D&& v) :
		x_(v.getX()), y_(v.getY()) {
	}

	Vector2D(const Vector2D* v) :
		x_(v->getX()), y_(v->getY()) {
	}

	Vector2D(float x, float y) :
		x_(x), y_(y) {
	}

	~Vector2D() {
	}

	// various getters
	inline float getX() const {
		return x_;
	}

	inline float getY() const {
		return y_;
	}

	// various setters
	inline void setX(float x) {
		x_ = x;
	}

	inline void setY(float y) {
		y_ = y;
	}

	inline void set(float x, float y) {
		x_ = x;
		y_ = y;
	}

	inline void set(const Vector2D& v) {
		x_ = v.x_;
		y_ = v.y_;
	}

	inline void set(const Vector2D&& v) {
		x_ = v.x_;
		y_ = v.y_;
	}

	inline void set(const Vector2D* v) {
		x_ = v->x_;
		y_ = v->y_;
	}

	// copy assignment
	inline Vector2D& operator=(const Vector2D& v) {
		x_ = v.x_;
		y_ = v.y_;
		return *this;
	}

	// move assignment - not really needed
	inline Vector2D& operator=(const Vector2D&& v) {
		x_ = v.x_;
		y_ = v.y_;
		return *this;
	}

	// ** various operations

	// length of the vector
	inline float magnitude() const {
		return sqrtf(powf(x_, 2) + powf(y_, 2));
	}

	// vector in the same direction of length 1
	inline Vector2D normalize() const {
		return *this / magnitude();
	}

	// counter clockwise rotation in a normal coordinate system, and
	// it is clockwise rotation if we work with a coordinate system
	// in which the vertical axe is flipped (it is like a mirror over
	// the horizontal axe)-- which the case when working with the SDL.
	//
	Vector2D rotate(float degrees) const;

	// Computes the angle between 'this' and 'v'. The result is
	// between -180 and 180, and is such that the following holds:
	//
	//   this->rotate(angle) == v
	//
	float angle(const Vector2D& v) const;

	// vector subtraction
	inline Vector2D operator-(const Vector2D& v) const {
		return Vector2D(x_ - v.x_, y_ - v.y_);
	}

	// vector addition
	inline Vector2D operator+(const Vector2D& v) const {
		return Vector2D(x_ + v.x_, y_ + v.y_);
	}

	// multiplication by constant (scaling)
	inline Vector2D operator*(float d) const {
		return Vector2D(x_ * d, y_ * d);
	}

	// division by constant (scaling)
	inline Vector2D operator/(float d) const {
		return Vector2D(x_ / d, y_ / d);
	}

	// scalar multiplication
	inline float operator *(const Vector2D& d) const {
		return d.x_ * x_ + d.y_ * y_;
	}

	// equality
	inline bool operator ==(const Vector2D& d) const {
		return d.x_ == x_ && d.y_ == y_;
	}

	// inequality
	inline bool operator !=(const Vector2D& d) const {
		return d.x_ != x_ || d.y_ != y_;
	}

	static bool verticalCollision(const Vector2D& pVert, const Vector2D& p2, const Vector2D& v2, Vector2D& intersect) {
		//Both vectors are vertical and the same
		if (v2.getX() == 0.0 && p2.getX() == pVert.getX())
		{
			intersect = Vector2D(p2.getX(), 0.0);
			return true;
		}
		//Both vectors are vertical and parallel
		if (v2.getX() == 0.0)
			return false;

		float m2 = v2.getY() / v2.getX();
		float n2 = p2.getY() - m2 * p2.getX();
		float y = pVert.getX() * m2 + n2;
		intersect = Vector2D(pVert.getX(), y);
		return true;
	}

	static bool intersection(const Vector2D& p1, const Vector2D& v1, const Vector2D& p2, const Vector2D& v2, Vector2D& intersect) {
		if (v1.getX() == 0.0)
			return verticalCollision(p1, p2, v2, intersect);
		if (v2.getX() == 0.0)
			return verticalCollision(p2, p1, v1, intersect);
		float m1 = v1.getY() / v1.getX();
		float m2 = v2.getY() / v2.getX();
		float n1 = p1.getY() - m1 * p1.getX();
		float n2 = p2.getY() - m2 * p2.getX();
		//Lines are the same
		if (m1 == m2 && n1 == n2)
		{
			intersect = p1;
			return true;
		}
		//Vectors have the same incline
		if (m1 == m2)
			return false;
		float x = (n2 - n1) / (m1 - m2);
		intersect = Vector2D(x, m1 * x + n1);
		return true;
	}

	inline static Vector2D Lerp(Vector2D const& a, Vector2D const& b, float i) {
		if (i < 0) return a;
		if (i > 1) return b;
		float x = Lerp(a.getX(), b.getX(), i);
		float y = Lerp(a.getY(), b.getY(), i);

		return Vector2D(x, y);
	}
	inline static float Lerp(float a, float b, float i) {
		if (i < 0) return a;
		if (i > 1) return b;
		if (b < a) return Lerp(b, a, 1 - i);
		return a + (b - a) * i;
	}

private:
	float x_;  // first coordinate
	float y_;  // second coordinate
};

// needed for printing a value of tyep Vector2D with std::cout.
// The definition is in .cpp
std::ostream& operator<<(std::ostream& os, const Vector2D& v);

using Point2D = Vector2D;
