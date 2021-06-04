#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "../include/Lib.h"
#include "../include/Singleton.h"
#include <vector>
#include <memory>

namespace gnGame {

	namespace gnLib {
		class GameObject;
	}
	
	class Actor;
	class Player;
	class Bullet;
	
	using PlayerPtr = std::shared_ptr<Player>;

	using BulletPtr = std::shared_ptr<Bullet>;
	using BulletColliderList = std::vector<BulletPtr>;

	using ActorPtr = std::shared_ptr<Actor>;
	using ActorColliderList = std::vector<ActorPtr>;

	using GameObjectPtr = std::shared_ptr<gnLib::GameObject>;
	using GameObjectColliderList = std::vector<GameObjectPtr>;
	
	/// <summary>
	/// コライダー（衝突判定）を管理するマネージャクラス
	/// </summary>
	class CollisionManager : public Singleton<CollisionManager> {
		friend Singleton<CollisionManager>;

	public:
		void setPlayer(PlayerPtr& _player);

		void addBullet(const BulletPtr& _bullet);

		void addActor(const ActorPtr& _actor);

		void addObject(const GameObjectPtr& _object);

		void onUpdate();

		void clearList();

	private:
		CollisionManager()
			: player(nullptr)
			, bulletColliderList()
			, actorColliderList()
			, objectColliderList()
		{}
		
	private:
		PlayerPtr              player;              // プレイヤー
		BulletColliderList     bulletColliderList;  // 弾
		ActorColliderList      actorColliderList;   // 敵
		GameObjectColliderList objectColliderList;  // オブジェクト
	};

}

#endif // !COLLISIONMANAGER_H