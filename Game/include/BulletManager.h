#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include <memory>
#include "gnLib.h"
#include "Singleton.h"

namespace gnGame {

	class Bullet;
	using BulletPtr = std::shared_ptr<Bullet>;  // �e�̃|�C���^
	using BulletList = std::vector<BulletPtr>;  // �e�̃|�C���^�̃��X�g

	class BulletManager : public Singleton<BulletManager>
	{
		friend  Singleton<BulletManager>;

	public:
		/// <summary>
		/// �e�𐶐�����
		/// </summary>
		void createBullet(const Vector2& _position, const Vector2& _velocity, float _attack);

		//void removeBullet();

		void onUpdate();

		void onDraw();

		void clearList();

		inline size_t getListSize() {
			return bulletList.size();
		}

	private:
		BulletManager()
			: bulletList()
		{ }

	private:
		BulletList bulletList;
	};

}

#endif // !BULLETMANAGER_H
