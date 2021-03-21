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

		const bool isPlayerDirection() {
			return true;
		}
	}

	Boss::Boss(GameScene* _gameScene, const Vector2& _pos, const ActorParameter _parameter)
		: Enemy(_pos, _parameter, EnemyType::Boss)
		, gameScene(_gameScene)
		, component(new BossAction::BossWait{})
		, bossPattern(BossPattern::Wait)
		, prevBossPattern(BossPattern::Wait)
		, waitAnimSprite  (8, 1, 6.0f)
		, actionAnimSprite(7, 1, 12.0f)
	{	 
		waitAnimSprite.setTexture(TextureManager::getTexture("Boss_Wait"));
		actionAnimSprite.setTexture(TextureManager::getTexture("Boss_Action"));
		this->direction = Direction::Left;
		this->isFlip = isDirection(direction);
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
		bounds.minPos.setPos(0, 0);
		bounds.maxPos.setPos(96.0f, 96.0f);
		bounds.size.setPos(bounds.maxPos - bounds.minPos);
		bounds.center.setPos(bounds.size.half());
	}

	void Boss::onUpdate()
	{
		// 重力処理
		this->physics();
		this->transform.pos = intersectTileMap();

		component->update(this);

		this->isFlip = isDirection(direction);
		auto screen(Camera::toScreenPos(this->transform.pos));
		collider.update(screen, 80.0f, 80.0f);

		bool isMoveAnimation = 
			bossPattern == BossPattern::MoveRight 
			|| bossPattern == BossPattern::MoveLeft
			|| bossPattern == BossPattern::MoveAttackRight
			|| bossPattern == BossPattern::MoveAttackLeft;
		if (isMoveAnimation) {
			actionAnimSprite.draw(screen, transform.scale, transform.angle, true, isFlip);
		}
		else {
			waitAnimSprite.draw(screen, transform.scale, transform.angle, true, isFlip);
		}
	}

	void Boss::changeState(BossPattern _pattern, float time)
	{
		if (component) {
			delete component;
			component = nullptr;
		}

		prevBossPattern = bossPattern;
		bossPattern = _pattern;

		// 右(左)へ行く動作を複数回行おうとしたとき
		// 左向いていて、左行こうとしたとき
		bool isLeft = getDir() == Direction::Left && bossPattern == BossPattern::MoveLeft;
		bool isAttackLeft = getDir() == Direction::Left && bossPattern == BossPattern::MoveAttackLeft;

		// 右向いていて、右行こうとしたとき
		bool isRight = getDir() == Direction::Right && bossPattern == BossPattern::MoveRight;
		bool isAttackRight = getDir() == Direction::Right && bossPattern == BossPattern::MoveAttackRight;
		if (isLeft || isAttackLeft || isRight || isAttackRight) {
			bossPattern = BossPattern::Wait;
		}
		
		switch (bossPattern)
		{
		case gnGame::BossPattern::Wait:
			component = new BossAction::BossWait{ time };
			break;
		case gnGame::BossPattern::MoveRight:
			component = new BossAction::BossMoveRight{ this };
			break;
		case gnGame::BossPattern::MoveLeft:
			component = new BossAction::BossMoveLeft{ this };
			break;
		case gnGame::BossPattern::MoveAttackRight:
			component = new BossAction::BossMoveShotRight{ this };
			break;
		case gnGame::BossPattern::MoveAttackLeft:
			component = new BossAction::BossMoveShotLeft{ this };
			break;
		case gnGame::BossPattern::TargetPlayerShot:
			component = new BossAction::TargetPlayerShot{ gameScene };
			break;
		case gnGame::BossPattern::ScatterShot:
			component = new BossAction::ScatterShot{ gameScene };
			break;
		case gnGame::BossPattern::LinearShot:
			component = new BossAction::LinearShot{ };
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
		this->direction = _dir;
	}

}