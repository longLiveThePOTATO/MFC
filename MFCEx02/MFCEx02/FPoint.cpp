#include "stdafx.h"
#include "FPoint.h"
#include <cmath>
#include <iostream>  // std::cout�� ����ϱ� ���� �ʿ�

// �⺻ ������: ��ǥ�� (0, 0)���� �ʱ�ȭ
CFPoint::CFPoint() : x(0.0f), y(0.0f) {}

// �Ű������� �ִ� ������
CFPoint::CFPoint(float x, float y) : x(x), y(y) {}

// CPoint�� CFPoint�� ��ȯ�ϴ� ������
CFPoint::CFPoint(const CPoint& point) : x(static_cast<float>(point.x)), y(static_cast<float>(point.y)) {}

// �Ҽ��� �� �ڸ��� �ݿø��ϴ� �Լ�
CFPoint CFPoint::RoundToThreeDecimalPlaces(CFPoint point) const {
	point.x = std::round(point.x * 1000.0f) / 1000.0f;
	point.y = std::round(point.y * 1000.0f) / 1000.0f;
	return point;
}

// ���ϱ� ������ �����ε�
CFPoint CFPoint::operator+(const CFPoint& other) const {
	return CFPoint(x + other.x, y + other.y);
}

// ���� ������ �����ε�
CFPoint CFPoint::operator-(const CFPoint& other) const {
	return CFPoint(x - other.x, y - other.y);
}

// ���ϱ� ���� ������ �����ε�
CFPoint& CFPoint::operator+=(const CFPoint& other) {
	x += other.x;
	y += other.y;
	return *this;
}

// ���� ���� ������ �����ε�
CFPoint& CFPoint::operator-=(const CFPoint& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

// �� ������ �����ε�
bool CFPoint::operator==(const CFPoint& other) const {
	return x == other.x && y == other.y;
}

// �� ������ �����ε�
bool CFPoint::operator!=(const CFPoint& other) const {
	return !(*this == other);
}

// �� �� ���� �Ÿ� ���� ��ȯ�ϴ� �Լ�
CFPoint CFPoint::DistancePairTo(const CFPoint& other) const {
	float dx = x - other.x;
	float dy = y - other.y;
	return CFPoint(dx, dy);
}

// ��ǥ �̵� �Լ�
CFPoint CFPoint::Offset(float dx, float dy) const {
	return CFPoint(x + dx, y + dy);
}

// �� ���� �߽� ��ǥ ��� �Լ�
CFPoint CFPoint::CalculateCenter(const CFPoint& start, const CFPoint& end) {
	float centerX = (start.x + end.x) / 2.0f;
	float centerY = (start.y + end.y) / 2.0f;
	std::cout << "CalculateCenter - startX: " << start.x << ", startY: " << start.y
		<< ", endX: " << end.x << ", endY: " << end.y
		<< ", centerX: " << centerX << ", centerY: " << centerY << std::endl;
	return CFPoint(centerX, centerY);
}
