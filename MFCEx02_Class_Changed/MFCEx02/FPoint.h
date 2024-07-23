#pragma once

class CFPoint {
public:
	float x;
	float y;

	// 기본 생성자
	CFPoint();
	// 매개변수가 있는 생성자
	CFPoint(float x, float y);

	// 연산자 오버로딩
	CFPoint operator+(const CFPoint& other) const;
	CFPoint operator-(const CFPoint& other) const;
	CFPoint& operator+=(const CFPoint& other);
	CFPoint& operator-=(const CFPoint& other);

	// 비교 연산자 오버로딩
	bool operator==(const CFPoint& other) const;
	bool operator!=(const CFPoint& other) const;

	// 유틸리티 함수
	float DistanceTo(const CFPoint& other) const;
	void Offset(float dx, float dy);

private:
	// 소수점 두 자리로 반올림하는 함수
	float RoundToTwoDecimalPlaces(float value) const;
};
