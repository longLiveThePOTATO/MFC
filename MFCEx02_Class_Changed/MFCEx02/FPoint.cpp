#include "stdafx.h"
#include "FPoint.h"
#include <cmath>
#include <math.h>

// 기본 생성자: 좌표를 (0, 0)으로 초기화
CFPoint::CFPoint() : x(0.0f), y(0.0f) {}

// 매개변수가 있는 생성자
CFPoint::CFPoint(float x, float y) : x(RoundToTwoDecimalPlaces(x)), y(RoundToTwoDecimalPlaces(y)) {}

// 소수점 두 자리로 반올림하는 함수
float CFPoint::RoundToTwoDecimalPlaces(float value) const {
	return roundf(value * 100) / 100;
}

// 더하기 연산자 오버로딩
CFPoint CFPoint::operator+(const CFPoint& other) const {
	return CFPoint(RoundToTwoDecimalPlaces(x + other.x), RoundToTwoDecimalPlaces(y + other.y));
}

// 빼기 연산자 오버로딩
CFPoint CFPoint::operator-(const CFPoint& other) const {
	return CFPoint(RoundToTwoDecimalPlaces(x - other.x), RoundToTwoDecimalPlaces(y - other.y));
}

// 더하기 대입 연산자 오버로딩
CFPoint& CFPoint::operator+=(const CFPoint& other) {
	x = RoundToTwoDecimalPlaces(x + other.x);
	y = RoundToTwoDecimalPlaces(y + other.y);
	return *this;
}

// 빼기 대입 연산자 오버로딩
CFPoint& CFPoint::operator-=(const CFPoint& other) {
	x = RoundToTwoDecimalPlaces(x - other.x);
	y = RoundToTwoDecimalPlaces(y - other.y);
	return *this;
}

// 비교 연산자 오버로딩
bool CFPoint::operator==(const CFPoint& other) const {
	return RoundToTwoDecimalPlaces(x) == RoundToTwoDecimalPlaces(other.x) && RoundToTwoDecimalPlaces(y) == RoundToTwoDecimalPlaces(other.y);
}

// 비교 연산자 오버로딩
bool CFPoint::operator!=(const CFPoint& other) const {
	return !(*this == other);
}

// 두 점 사이의 거리 계산 함수
float CFPoint::DistanceTo(const CFPoint& other) const {
	float dx = RoundToTwoDecimalPlaces(x - other.x);
	float dy = RoundToTwoDecimalPlaces(y - other.y);
	return RoundToTwoDecimalPlaces(std::sqrt(dx * dx + dy * dy));
}

// 좌표 이동 함수
void CFPoint::Offset(float dx, float dy) {
	x = RoundToTwoDecimalPlaces(x + dx);
	y = RoundToTwoDecimalPlaces(y + dy);
}
