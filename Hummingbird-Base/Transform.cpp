#include "Transform.h"
using namespace hb;

Transform::Transform():
m_position(Vector3d()),
m_scale(Vector3d(1, 1, 1)),
m_rotation_angle(Vector3d())
{}


Transform::Transform(const Vector3d& init_pos):
m_position(init_pos),
m_scale(Vector3d(1, 1, 1)),
m_rotation_angle(Vector3d())
{}


Transform::~Transform()
{}


const Vector3d& Transform::getPosition() const
{
	return m_position;
}


void Transform::setPosition(const Vector3d& position)
{
	m_position = position;
}


const Vector3d& Transform::getRotation() const
{
	return m_rotation_angle;
}


void Transform::setRotation(const Vector3d& angle)
{
	m_rotation_angle = angle;
}


const Vector3d& Transform::getScale() const
{
	return m_scale;
}


void Transform::setScale(const Vector3d& scale)
{
	m_scale = scale;
}
