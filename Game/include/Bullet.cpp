#include "Bullet.h"
#include "Camera.h"
#include "Map.h"
#include "Actor.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyManager.h"

namespace gnGame {

	Bullet::Bullet()
		: Bullet(Vector2::Zero, Vector2::Zero, BulletType::Enemy)
	{
	}

	Bullet::Bullet(const Vector2& _pos, const Vector2& _velocity, BulletType _bulletType)
		: velocity(_velocity)
		, bulletType(_bulletType)
		, rect()
		, intersectPoint()
		, bounds()
	{
		this->transform.setPos(_pos);
	}

	void Bullet::onStart()
	{
		rect.setSize(20.f);
		rect.setColor(Color::Blue);

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
		boxCollider.update(this->transform.pos, 20.0f, 20.0f);
		rect.setPos(this->transform.pos);
		rect.draw();
	}

	bool Bullet::onScreen()
	{
		return transform.pos.x >= 0 && transform.pos.x <= WindowInfo::WindowWidth
			&& transform.pos.y >= 0 && transform.pos.y <= WindowInfo::WindowHeight;
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

		if (boxCollider.isHitTest(_actor->getCollider())) {
			return true;
		}

		return false;
	}

	bool Bullet::hit(Player& _actor)
	{
		// �v���C���[�Ƃ��������Ƃ��̏���

		if (boxCollider.isHitTest(_actor.getCollider())) {
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
		return boxCollider;
	}

}
