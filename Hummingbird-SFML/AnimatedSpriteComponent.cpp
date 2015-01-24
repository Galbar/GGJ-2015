#include <iostream>
#include "AnimatedSpriteComponent.h"
using namespace hb;


AnimatedSpriteComponent::AnimatedSpriteComponent(RenderWindowManager* render_manager):
SpriteComponent(render_manager),
m_time_left(Time::microseconds(0)),
m_frame_time(Time::microseconds(0)),
m_frame_size(Vector2d(1, 1)),
m_frame_margin(Vector2d(0, 0)),
m_begin_frame(0),
m_current_frame(0),
m_end_frame(0),
m_playing(true),
m_looping(true)
{}


AnimatedSpriteComponent::~AnimatedSpriteComponent()
{}


void AnimatedSpriteComponent::setTexture(const std::string& path, const sf::IntRect& area)
{
	m_texture_id = TextureManager::instance()->loadFromFile(path, area);
	m_sprite.setTexture(TextureManager::instance()->get(m_texture_id));
}


void AnimatedSpriteComponent::update()
{
	if (m_playing)
	{
		m_time_left -= Time::deltaTime;

		if (m_time_left <= Time())
		{
			m_time_left = m_frame_time + m_time_left;
			m_current_frame++;
			if (m_current_frame > m_end_frame)
			{
				if (m_looping)
					m_current_frame = m_begin_frame;
				else
				{
					stop();
					m_current_frame--;
				}
			}

			Vector2d pos = getCoords();
			m_sprite.setTextureRect(sf::IntRect(pos.x, pos.y, m_frame_size.x, m_frame_size.y));
		}
	}
}


void AnimatedSpriteComponent::setFrameTime(const Time& frame_time)
{
	m_frame_time = frame_time;
}


void AnimatedSpriteComponent::setFrameInterval(int begin_frame, int end_frame)
{
	m_begin_frame = begin_frame;
	m_current_frame = begin_frame;
	m_end_frame = end_frame;
}


void AnimatedSpriteComponent::setFrameSize(const Vector2d& frame_size)
{
	m_frame_size = frame_size;
	m_sprite.setOrigin(frame_size.x / 2, frame_size.y / 2);
}


void AnimatedSpriteComponent::setFrameMargin(const Vector2d& frame_margin)
{
	m_frame_margin = frame_margin;
}



bool AnimatedSpriteComponent::isLooping() const
{
	return m_looping;
}


void AnimatedSpriteComponent::loop(bool loop)
{
	m_looping = loop;
}


bool AnimatedSpriteComponent::isPlaying() const
{
	return m_playing;
}


void AnimatedSpriteComponent::play()
{
	m_playing = true;
}


void AnimatedSpriteComponent::stop()
{
	m_playing = false;
}


Vector2d AnimatedSpriteComponent::getCoords()
{
	int nx = m_sprite.getTexture()->getSize().x / (m_frame_size.x + m_frame_margin.x);
	int x_coord = (m_current_frame % nx) * (m_frame_size.x + m_frame_margin.x) + m_frame_margin.x;
	int y_coord = (m_current_frame / nx) * (m_frame_size.y + m_frame_margin.y) + m_frame_margin.y;
	return Vector2d(x_coord, y_coord);
}
