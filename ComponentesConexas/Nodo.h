#pragma once

class Nodo
{
private:
	int x;
	int y;
public:
	Nodo(int x = 0, int y = 0) : x(x), y(y) {}
	~Nodo() {}

	int getX() { return x; }
	int getY() { return y; }
};