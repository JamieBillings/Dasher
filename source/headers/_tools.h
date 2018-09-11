#ifndef TOOLS_H_INCLUDED
#define TOOLD_H_INCLUDED

class Vector2D
{
public:
	double x = 0.00;
	double y = 0.00;

	void Create(double _x, double _y);
	void Normalise(double* _x, double* _y);
};

namespace Tools
{
	bool Collision(int _x1, int _y1, int _w1, int _h1, int _x2, int _y2, int _w2, int _h2);

}

#endif