#ifndef HB_TRANSFORM_H
#define HB_TRANSFORM_H
#include "Vector3d.h"

namespace hb
{
	class Transform
	{
	public:
		Transform();
		~Transform();
		const Vector3d& getPosition() const;
		void setPosition(const Vector3d& p);
		const Vector3d& getRotation() const;
		void setRotation(const Vector3d& rotation);
		const Vector3d& getScale() const;
		void setScale(const Vector3d& scale);

	private:
		Vector3d m_position;
		Vector3d m_scale;
		Vector3d m_rotation_angle;
	};
}
#endif