#pragma once

class CFPoint {
public:
	float x;
	float y;

	// �⺻ ������
	CFPoint();
	// �Ű������� �ִ� ������
	CFPoint(float x, float y);

	// ������ �����ε�
	CFPoint operator+(const CFPoint& other) const;
	CFPoint operator-(const CFPoint& other) const;
	CFPoint& operator+=(const CFPoint& other);
	CFPoint& operator-=(const CFPoint& other);

	// �� ������ �����ε�
	bool operator==(const CFPoint& other) const;
	bool operator!=(const CFPoint& other) const;

	// ��ƿ��Ƽ �Լ�
	float DistanceTo(const CFPoint& other) const;
	void Offset(float dx, float dy);

private:
	// �Ҽ��� �� �ڸ��� �ݿø��ϴ� �Լ�
	float RoundToTwoDecimalPlaces(float value) const;
};
