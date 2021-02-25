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

		bool isMoveAnimation = bossPattern == BossPattern::Move1 || bossPattern == BossPattern::Move2;
		if (isMoveAnimation) {
			actionAnimSprite.draw(screen, transform.scale, transform.angle, true, isFlip);
		}
		else {
			waitAnimSprite.draw(screen, transform.scale, transform.angle, true, isFlip);
		}

		static Font font{ 24, "MS 明朝" };

		font.drawText(0, 250, Color::Black, "bossPattern = %d", bossPattern);
		font.drawText(0, 274, Color::Black, "prevBossPattern = %d", prevBossPattern);
	}

	void Boss::changeState(BossPattern _pattern, float time)
	{
		if (component) {
			delete component;
			component = nullptr;
		}

		// Waitを外す
		if (bossPattern != BossPattern::Wait) {
			prevBossPattern = bossPattern;
		}
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
		this->direction = _dir;
	}
}