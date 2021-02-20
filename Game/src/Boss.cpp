#include "../include/Boss.h"
#include "../include/Camera.h"
#include "../include/TextureManager.h"
#include "../include/BossState.h"
#include "../include/GameScene.h"

namespace gnGame {

	namespace {
		const bool isDirection(const Direction _dir) {
			return _dir == Direction::Right;
		}
	}

	Boss::Boss(GameScene* _gameScene, const Vector2& _pos, const ActorParameter _parameter)
		: Enemy(_pos, _parameter, EnemyType::Boss)
		, gameScene(_gameScene)
		, component(new BossAction::BossWait{})
		, bossPattern(BossPattern::Wait)
		, prevBossPattern(BossPattern::Wait)
	{
		this->dir = Direction::Left;
		this->isFlip = isDirection(dir);
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
		bounds.maxPos.setPos(64, 64);
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
		this->physics();
		this->transform.pos = intersectTileMap();

		component->update(this);

		this->isFlip = isDirection(dir);
		auto screen(Camera::toScreenPos(this->transform.pos));
		collider.update(screen, 96.0f, 96.0f);
		sprite.draw(screen, transform.scale, transform.angle, true, isFlip);
	}

	void Boss::changeState(BossPattern _pattern, float time)
	{
		if (component) {
			delete component;
			component = nullptr;
		}

		prevBossPattern = bossPattern;
		bossPattern = _pattern;
		
		switch (_pattern)
		{
		case gnGame::BossPattern::Wait:
			component = new BossAction::BossWait{ time };
			break;
		case gnGame::BossPattern::Move1:
			component = new BossAction::BossMove1{ };
			break;
		case gnGame::BossPattern::Move2:
			component = new BossAction::BossMove2{ };
			break;
		case gnGame::BossPattern::Attack1:
			component = new BossAction::BossAction1{ gameScene };
			break;
		case gnGame::BossPattern::Attack2:
			component = new BossAction::BossAction2{ gameScene };
			break;
		case gnGame::BossPattern::Attack3:
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

	const BossPattern Boss::getPrevBossPattern()
	{
		return prevBossPattern;
	}

	void Boss::setDirection(Direction _dir)
	{
		this->dir = _dir;
	}
}