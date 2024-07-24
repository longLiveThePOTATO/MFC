#pragma once

#define CENTER 321
#define HALFLENGTH 309
class CFPoint {
public:
	float x;
	float y;

	// 기본 생성자
	CFPoint();
	// 매개변수가 있는 생성자
	CFPoint(float x, float y);
	CFPoint(const CPoint& point);

	// 연산자 오버로딩
	CFPoint operator+(const CFPoint& other) const;
	CFPoint operator-(const CFPoint& other) const;
	CFPoint& operator+=(const CFPoint& other);
	CFPoint& operator-=(const CFPoint& other);

	bool operator==(const CFPoint& other) const;
	bool operator!=(const CFPoint& other) const;

	// 유틸리티 함수
	float DistanceTo(const CFPoint& other) const;
	CFPoint DistancePairTo(const CFPoint& other) const;
	CFPoint Offset(float dx, float dy) const;;
	CFPoint CalculateCenter(const CFPoint& start, const CFPoint& end);
	// 소수점 세 자리로 반올림하는 함수
	CFPoint RoundToThreeDecimalPlaces(CFPoint point) const;
private:
	
};
