#include "../include/TutorialObject.h"
#include "../include/Camera.h"
#include "../include/TextureManager.h"

namespace gnGame {

	// ----- MoveIntro -----
	MoveIntro::MoveIntro(const Vector2& _pos)
		: sprite()
	{
		this->transform.setPos(_pos);
		sprite.setTexture(TextureManager::getTexture("Move"));
	}

	void MoveIntro::onUpdate()
	{
		auto screen = Camera::toScreenPos(this->transform.pos);
		sprite.draw(screen, Vector2::One, 0.0f, false);
	}

	// ----- JumpIntro -----
	JumpIntro::JumpIntro(const Vector2& _pos)
		: sprite()
	{
		this->transform.setPos(_pos);
		sprite.setTexture(TextureManager::getTexture("Jump"));
	}

	void JumpIntro::onUpdate()
	{
		auto screen = Camera::toScreenPos(this->transform.pos);
		sprite.draw(screen, Vector2::One, 0.0f, false);
	}

	// ----- ShotIntro -----
	ShotIntro::ShotIntro(const Vector2& _pos)
		: sprite()
	{
		this->transform.setPos(_pos);
		sprite.setTexture(TextureManager::getTexture("Shot"));
	}

	void ShotIntro::onUpdate()
	{
		auto screen = Camera::toScreenPos(this->transform.pos);
		sprite.draw(screen, Vector2::One, 0.0f, false);
	}

	// ----- TutorialObjectList -----
	TutorialObjectList* TutorialObjectList::getIns()
	{
		static TutorialObjectList Instance;
		return &Instance;
	}

	void TutorialObjectList::addObject(TutorialObjectPtr _object)
	{
		tutorialObjectList.emplace_back(_object);
	}

	void TutorialObjectList::update()
	{
		for (auto& object : tutorialObjectList) {
			object->onUpdate();
		}
	}

	void TutorialObjectList::clear()
	{
		tutorialObjectList.clear();
	}
}