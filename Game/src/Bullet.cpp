#include "../include/Bullet.h"
#include "../include/Camera.h"
#include "../include/EnemyManager.h"
#include "../include/TextureManager.h"
#include "../include/Map.h"
#include "../include/Player.h"
#include "../include/Enemy.h"

namespace gnGame {

	Bullet::Bullet()
		: Bullet(Vector2::Zero, Vector2::Zero, BulletType::Enemy)
	{
	}

	Bullet::Bullet(const Vector2& _pos, const Vector2& _velocity, BulletType _bulletType)
		: velocity(_velocity)
		, bulletType(_bulletType)
		, bulletImage()
		, intersectPoint()
		, bounds()
		, attack(1.0f)
	{
		this->transform.setPos(_pos);
		bulletImage.setTexture(TextureManager::getTexture("Test_Bullet"));
	}

	void Bullet::onStart()
	{
		bounds.minPos.setPos(0, 0);
		bounds.maxPos.setPos(20, 20);
		bounds.size.setPos(bounds.maxPos - bounds.minPos);
		bounds.center.setPos(bounds.size.half());
	}

	void Bullet::onUpdate()
	{
		if (!this->getActive()) {
			return;
		}
		
		this->transform.pos += velocity;
		auto screen = Camera::toScreenPos(this->transform.pos);
		collider.update(screen, 20.0f, 20.0f);
		bulletImage.draw(screen, Vector2::One, 0.0f);
	}

	bool Bullet::isOnScreen()
	{
		return Camera::isOnScreen(transform.pos);
	}

	void Bullet::setAttack(float _attack)
	{
		attack = _attack;
	}

	float Bullet::getAttack()
	{
		return attack;
	}

	bool Bullet::intersectMap(Map& _map)
	{
		auto nextPos = this->transform.pos;

		// ������s�����W�����߂�
		float offX{ bounds.center.x / 4.0f - 1.0f };
		float offY{ bounds.center.y / 4.0f - 1.0f };

		// �㉺����p�̂ɔ���{�b�N�X�X�V
		bounds.minPos.setPos(this->transform.pos.x - bounds.center.x, nextPos.y - bounds.center.y);
		bounds.maxPos.setPos(this->transform.pos.x + bounds.center.x, nextPos.y + bounds.center.y);

		// -- �� --
		intersectPoint.bottom[0] = Vector2{ bounds.minPos.x + offX, bounds.maxPos.y + 1.0f };
		intersectPoint.bottom[1] = Vector2{ bounds.maxPos.x - offX, bounds.maxPos.y + 1.0f };

		// -- �� --
		intersectPoint.top[0] = Vector2{ bounds.minPos.x + offX, bounds.minPos.y - 1.0f };
		intersectPoint.top[1] = Vector2{ bounds.maxPos.x - offX, bounds.minPos.y - 1.0f };

		// -- ��Ƃ̓����蔻�� --
		for (int i{}; i < IntersectPoint::Size; ++i) {
			if (_map.checkTile((int)intersectPoint.top[i].x, (int)intersectPoint.top[i].y)) {
				return true;
			}
		}

		// -- ���Ƃ̓����蔻�� --
		for (int i{}; i < IntersectPoint::Size; ++i) {
			if (_map.checkTile((int)intersectPoint.bottom[i].x, (int)intersectPoint.bottom[i].y)) {
				return true;
			}
		}

		// ���E����p�ɔ���{�b�N�X�X�V
		bounds.minPos.setPos(nextPos.x - bounds.center.x, this->transform.pos.y - bounds.center.y);
		bounds.maxPos.setPos(nextPos.x + bounds.center.x, this->transform.pos.y + bounds.center.y);

		// -- �E --
		intersectPoint.right[0] = Vector2{ bounds.maxPos.x , bounds.minPos.y + offY };
		intersectPoint.right[1] = Vector2{ bounds.maxPos.x , bounds.maxPos.y - offY };

		// -- �� --
		intersectPoint.left[0] = Vector2{ bounds.minPos.x - 1.0f, bounds.minPos.y + offY };
		intersectPoint.left[1] = Vector2{ bounds.minPos.x - 1.0f, bounds.maxPos.y - offY };


		// -- �E�Ƃ̓����蔻�� --
		for (int i{}; i < IntersectPoint::Size; ++i) {
			if (_map.checkTile((int)intersectPoint.right[i].x, (int)intersectPoint.right[i].y)) {
				return true;
			}
		}

		// -- ���Ƃ̓����蔻�� --		
		for (int i{}; i < IntersectPoint::Size; ++i) {
			if (_map.checkTile((int)intersectPoint.left[i].x, (int)intersectPoint.left[i].y)) {
				return true;
			}
		}

		return false;
	}

	bool Bullet::hit(EnemyPtr& _actor)
	{
		// Actor�Ƃ��������Ƃ��̏���

		if (collider.isHitTest(_actor->getCollider())) {
			return true;
		}

		return false;
	}

	bool Bullet::hit(Player& _actor)
	{
		// �v���C���[�Ƃ��������Ƃ��̏���

		if (collider.isHitTest(_actor.getCollider())) {
			return true;
		}

		return false;
	}

	BulletType Bullet::getBulletType()
	{
		return bulletType;
	}

	BoxCollider& Bullet::getCollider()
	{
		return collider;
	}

}
