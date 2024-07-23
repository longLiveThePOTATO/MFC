#include "stdafx.h"
#include "FPoint.h"
#include <cmath>
#include <math.h>

// �⺻ ������: ��ǥ�� (0, 0)���� �ʱ�ȭ
CFPoint::CFPoint() : x(0.0f), y(0.0f) {}

// �Ű������� �ִ� ������
CFPoint::CFPoint(float x, float y) : x(RoundToTwoDecimalPlaces(x)), y(RoundToTwoDecimalPlaces(y)) {}

// �Ҽ��� �� �ڸ��� �ݿø��ϴ� �Լ�
float CFPoint::RoundToTwoDecimalPlaces(float value) const {
	return roundf(value * 100) / 100;
}

// ���ϱ� ������ �����ε�
CFPoint CFPoint::operator+(const CFPoint& other) const {
	return CFPoint(RoundToTwoDecimalPlaces(x + other.x), RoundToTwoDecimalPlaces(y + other.y));
}

// ���� ������ �����ε�
CFPoint CFPoint::operator-(const CFPoint& other) const {
	return CFPoint(RoundToTwoDecimalPlaces(x - other.x), RoundToTwoDecimalPlaces(y - other.y));
}

// ���ϱ� ���� ������ �����ε�
CFPoint& CFPoint::operator+=(const CFPoint& other) {
	x = RoundToTwoDecimalPlaces(x + other.x);
	y = RoundToTwoDecimalPlaces(y + other.y);
	return *this;
}

// ���� ���� ������ �����ε�
CFPoint& CFPoint::operator-=(const CFPoint& other) {
	x = RoundToTwoDecimalPlaces(x - other.x);
	y = RoundToTwoDecimalPlaces(y - other.y);
	return *this;
}

// �� ������ �����ε�
bool CFPoint::operator==(const CFPoint& other) const {
	return RoundToTwoDecimalPlaces(x) == RoundToTwoDecimalPlaces(other.x) && RoundToTwoDecimalPlaces(y) == RoundToTwoDecimalPlaces(other.y);
}

// �� ������ �����ε�
bool CFPoint::operator!=(const CFPoint& other) const {
	return !(*this == other);
}

// �� �� ������ �Ÿ� ��� �Լ�
float CFPoint::DistanceTo(const CFPoint& other) const {
	float dx = RoundToTwoDecimalPlaces(x - other.x);
	float dy = RoundToTwoDecimalPlaces(y - other.y);
	return RoundToTwoDecimalPlaces(std::sqrt(dx * dx + dy * dy));
}

// ��ǥ �̵� �Լ�
void CFPoint::Offset(float dx, float dy) {
	x = RoundToTwoDecimalPlaces(x + dx);
	y = RoundToTwoDecimalPlaces(y + dy);
}
