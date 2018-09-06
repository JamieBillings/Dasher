void Vector2D::Create(double _x, double _y)
{
	x = _x;
	y = _y;
}

void Vector2D::Normalise(double* _x, double* _y)
{	
	double temp_x = *_x;
	double temp_y = *_y;

	//pie-fags therom
	double hypotenuse_sq = (temp_x*temp_x) + (temp_y*temp_y);
	double hypotenuse = sqrt(hypotenuse_sq);

	//Normalising
	if(temp_x != 0){temp_x = temp_x/hypotenuse;}
	if(temp_y != 0){temp_y = temp_y/hypotenuse;}

	*_x = temp_x;
	*_y = temp_y;
}


namespace Tools
{

bool BoxCollision(int _x1, int _y1, int _w1, int _h1, int _x2, int _y2, int _w2, int _h2)
{
	if((_x1 < _x2 && _x1 + _w1 > _x2) || (_x1 < _x2 + _w2 && _x1 + _w1 > _x2 + _w2) || (_x1 == _x2)){
		if((_y1 < _y2 && _y1 + _h1 > _y2) || (_y1 < _y2 + _w2 && _y1 + _h1 > _y2 + _h2) || (_y1 == _y2)){
			return true;
		}
	}
	return false;
}

bool LineCollision(int _x1, int _y1, int _w1, int _h1, int line_x_1, int line_y_1, int line_x_2, line_y_2)
{
	
}

}