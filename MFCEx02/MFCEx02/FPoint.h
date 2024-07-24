#pragma once

#define CENTER 321
#define HALFLENGTH 309
class CFPoint {
public:
	float x;
	float y;

	// �⺻ ������
	CFPoint();
	// �Ű������� �ִ� ������
	CFPoint(float x, float y);
	CFPoint(const CPoint& point);

	// ������ �����ε�
	CFPoint operator+(const CFPoint& other) const;
	CFPoint operator-(const CFPoint& other) const;
	CFPoint& operator+=(const CFPoint& other);
	CFPoint& operator-=(const CFPoint& other);

	bool operator==(const CFPoint& other) const;
	bool operator!=(const CFPoint& other) const;

	// ��ƿ��Ƽ �Լ�
	float DistanceTo(const CFPoint& other) const;
	CFPoint DistancePairTo(const CFPoint& other) const;
	CFPoint Offset(float dx, float dy) const;;
	CFPoint CalculateCenter(const CFPoint& start, const CFPoint& end);
	// �Ҽ��� �� �ڸ��� �ݿø��ϴ� �Լ�
	CFPoint RoundToThreeDecimalPlaces(CFPoint point) const;
private:
	
};
