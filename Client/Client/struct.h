#pragma once

struct Vec2
{
	float x;
	float y;

public:
	float Length()
	{
		return sqrt(x * x + y * y);
	}

	// 해당 벡터의 각도 단위를 1로 해주기 위해
	Vec2& Normalize()
	{
		float fLen = Length();
		if (fLen == 0.f)
			return *this;
		//assert(fLen != 0.f);
		x /= fLen;
		y /= fLen;
		return *this;
	}


public:
	Vec2& operator = (POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}
	Vec2 operator +(Vec2 _vOther)
	{
		return Vec2(x + _vOther.x, y + _vOther.y);
	}
	Vec2 operator -(Vec2 _vOther)
	{
		return Vec2(x - _vOther.x, y - _vOther.y);
	}
	Vec2 operator *(Vec2 _vOther)
	{
		return Vec2(x * _vOther.x, y * _vOther.y);
	}
	Vec2 operator /(Vec2 _vOther)
	{
		assert(!(0.f == _vOther.x || 0.f == _vOther.y));
		return Vec2(x / _vOther.x, y / _vOther.y);
	}
	Vec2 operator *(float _fOther)
	{
		return Vec2(x * _fOther, y * _fOther);
	}
	Vec2 operator /(float _fOther)
	{
		assert(0 != _fOther);
		return Vec2(x / _fOther, y / _fOther);
	}

public:
	Vec2()
		: x(0.f)
		, y(0.f)
	{}
	Vec2(float _x, float _y)
		: x(_x)
		, y(_y)
	{}
	Vec2(int _x, int _y)
		: x((float)_x)
		, y((float)_y)
	{}

	Vec2(const POINT _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{}


	~Vec2()
	{}


};