#ifndef HB_VECTOR_2D_H
#define HB_VECTOR_2D_H

namespace hb
{
	class Vector2d
	{
	public:
		double x, y;
		Vector2d(): x(0), y(0){};
		Vector2d(double x, double y): x(x), y(y){};
		Vector2d(const Vector2d& v): x(v.x), y(v.y){};
	};
	
}

hb::Vector2d operator -(const hb::Vector2d& right);
hb::Vector2d& operator +=(hb::Vector2d& left, const hb::Vector2d& right);
hb::Vector2d& operator -=(hb::Vector2d& left, const hb::Vector2d& right);
hb::Vector2d operator +(const hb::Vector2d& left, const hb::Vector2d& right);
hb::Vector2d operator -(const hb::Vector2d& left, const hb::Vector2d& right);
hb::Vector2d operator *(const hb::Vector2d& left, double right);
hb::Vector2d operator *(double left, const hb::Vector2d& right);
hb::Vector2d& operator *=(hb::Vector2d& left, double right);
hb::Vector2d operator /(const hb::Vector2d& left, double right);
hb::Vector2d& operator /=(hb::Vector2d& left, double right);
bool operator ==(const hb::Vector2d& left, const hb::Vector2d& right);
#endif
