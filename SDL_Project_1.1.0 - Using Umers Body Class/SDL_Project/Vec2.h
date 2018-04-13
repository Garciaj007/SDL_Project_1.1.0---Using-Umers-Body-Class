#pragma once
class Vec2
{
public:
	int x, y;
	inline Vec2() {
		x = 0;
		y = 0;
	};
	inline Vec2(int x, int y) {
		x = x;
		y = y;
	}
	~Vec2();
};

