#include "stdafx.h"
#include "FPoint.h"
#include <cmath>
#include <iostream>  // std::cout을 사용하기 위해 필요

// 기본 생성자: 좌표를 (0, 0)으로 초기화
CFPoint::CFPoint() : x(0.0f), y(0.0f) {}

// 매개변수가 있는 생성자
CFPoint::CFPoint(float x, float y) : x(x), y(y) {}

// CPoint를 CFPoint로 변환하는 생성자
CFPoint::CFPoint(const CPoint& point) : x(static_cast<float>(point.x)), y(static_cast<float>(point.y)) {}

// 소수점 세 자리로 반올림하는 함수
CFPoint CFPoint::RoundToThreeDecimalPlaces(CFPoint point) const {
	point.x = std::round(point.x * 1000.0f) / 1000.0f;
	point.y = std::round(point.y * 1000.0f) / 1000.0f;
	return point;
}

// 더하기 연산자 오버로딩
CFPoint CFPoint::operator+(const CFPoint& other) const {
	return CFPoint(x + other.x, y + other.y);
}

// 빼기 연산자 오버로딩
CFPoint CFPoint::operator-(const CFPoint& other) const {
	return CFPoint(x - other.x, y - other.y);
}

// 더하기 대입 연산자 오버로딩
CFPoint& CFPoint::operator+=(const CFPoint& other) {
	x += other.x;
	y += other.y;
	return *this;
}

// 빼기 대입 연산자 오버로딩
CFPoint& CFPoint::operator-=(const CFPoint& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

// 비교 연산자 오버로딩
bool CFPoint::operator==(const CFPoint& other) const {
	return x == other.x && y == other.y;
}

// 비교 연산자 오버로딩
bool CFPoint::operator!=(const CFPoint& other) const {
	return !(*this == other);
}

// 두 점 간의 거리 쌍을 반환하는 함수
CFPoint CFPoint::DistancePairTo(const CFPoint& other) const {
	float dx = x - other.x;
	float dy = y - other.y;
	return CFPoint(dx, dy);
}

// 좌표 이동 함수
CFPoint CFPoint::Offset(float dx, float dy) const {
	return CFPoint(x + dx, y + dy);
}

// 두 점의 중심 좌표 계산 함수
CFPoint CFPoint::CalculateCenter(const CFPoint& start, const CFPoint& end) {
	float centerX = (start.x + end.x) / 2.0f;
	float centerY = (start.y + end.y) / 2.0f;
	std::cout << "CalculateCenter - startX: " << start.x << ", startY: " << start.y
		<< ", endX: " << end.x << ", endY: " << end.y
		<< ", centerX: " << centerX << ", centerY: " << centerY << std::endl;
	return CFPoint(centerX, centerY);
}
