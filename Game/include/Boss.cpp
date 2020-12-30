#include "../include/Boss.h"
#include "../include/Camera.h"
#include "../include/TextureManager.h"
#include "../include/BossState.h"
#include "../include/GameScene.h"

namespace gnGame {

	Boss::Boss()
		: Enemy()
		, gameScene(nullptr)
		, component(new BossAction::BossWait{})
		, bossPattern(BossPattern::Wait)
	{
	}

	Boss::Boss(GameScene* _gameScene, const Vector2& _pos, const ActorParameter _parameter)
		: Enemy(_pos, _parameter)
		, gameScene(_gameScene)
		, component(new BossAction::BossWait{})
		, bossPattern(BossPattern::Wait)
	{
	}

	Boss::~Boss()
	{
		if (component) {
			delete component;
			component = nullptr;
		}
	}

	void Boss::onStart()
	{
		this->sprite.setTexture(TextureManager::getTexture("Boss"));

		bounds.minPos.setPos(0, 0);
		bounds.maxPos.setPos(96, 96);
		bounds.size.setPos(bounds.maxPos - bounds.minPos);
		bounds.center.setPos(bounds.size.half());
	}

	void Boss::onUpdate()
	{

		if (!getActive()) {
			// セレクトシーンへ戻る
			gameScene->changeSelectScene();
		}

		// 重力処理
		this->transform.pos = intersectTileMap();

		component->update(this);

		auto screen(Camera::toScreenPos(this->transform.pos));
		collider.update(screen, 96.0f, 96.0f);
		sprite.draw(screen, transform.scale, transform.angle, true, isFlip);
	}

	void Boss::changeState(BossPattern _pattern)
	{
		if (component) {
			delete component;
			component = nullptr;
		}

		switch (_pattern)
		{
		case gnGame::BossPattern::Wait:
			bossPattern = BossPattern::Wait;
			component = new BossAction::BossWait{ };
			break;
		case gnGame::BossPattern::Move1:
			bossPattern = BossPattern::Move1;
			component = new BossAction::BossMove1{ };
			break;
		case gnGame::BossPattern::Move2:
			bossPattern = BossPattern::Move2;
			component = new BossAction::BossMove2{ };
			break;
		case gnGame::BossPattern::Attack1:
			bossPattern = BossPattern::Attack1;
			component = new BossAction::BossAction1{ gameScene };
			break;
		case gnGame::BossPattern::Attack2:
			bossPattern = BossPattern::Attack2;
			component = new BossAction::BossAction2{ gameScene };
			break;
		case gnGame::BossPattern::Attack3:
			bossPattern = BossPattern::Attack3;
			component = new BossAction::BossAction3{ };
			break;
		default:   // 仮にパターンになかった場合、Waitとする
			bossPattern = BossPattern::Wait;
			component = new BossAction::BossWait{ };
			break;
		}
	}

	const BossPattern& Boss::getBossPattern()
	{
		return bossPattern;
	}
}