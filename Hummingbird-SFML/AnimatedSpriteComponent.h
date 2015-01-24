#ifndef HB_ANIMATED_SPRITE_COMPONENT_H
#define HB_ANIMATED_SPRITE_COMPONENT_H
#include "SpriteComponent.h"
#include "../Hummingbird-Base/Time.h"
#include "../Hummingbird-Base/Vector2d.h"

// TODO: Hacer que SpriteComponent y AnimatedSpriteComponent sean la misma clase
namespace hb
{
	class AnimatedSpriteComponent : public SpriteComponent
	{
	public:
		AnimatedSpriteComponent(RenderWindowManager* render_manager);
		virtual ~AnimatedSpriteComponent() override;
		virtual void setTexture(const std::string& path, const sf::IntRect& area = sf::IntRect()) override;
		virtual void update() override;
		void setFrameTime(const Time& frame_time);
		void setFrameInterval(int begin_frame, int end_frame);
		void setFrameSize(const Vector2d& frame_size);
		void setFrameMargin(const Vector2d& frame_margin);
		bool isLooping() const;
		void loop(bool loop);
		bool isPlaying() const;
		void play();
		void stop();

	private:
		Vector2d getCoords();

		Time m_time_left;
		Time m_frame_time;
		Vector2d m_frame_size;
		Vector2d m_frame_margin;
		int m_begin_frame, m_current_frame, m_end_frame;
		bool m_playing, m_looping;
	};
}
#endif