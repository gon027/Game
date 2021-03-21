#include "../include/Player.h"
#include "../include/WindowInfo.h"
#include "../include/Camera.h"
#include "../include/Bullet.h"
#include "../include/TextureManager.h"
#include "../EffectManager.h"
#include "../include/BulletManager.h"
#include "../include/Global.h"
#include <cmath>

namespace gnGame {

	// �v���C���[�̏d�͂⑬���Ȃǂ̃p�����[�^
	namespace PlayerParameters {
		// �v���C���[�ɂ�����d��
		constexpr float Gravity = 0.980f;

		// �ő�̏d��
		constexpr float MaxGravity = Gravity * 10.0f;

		// �v���C���[���i�ޑ���
		//constexpr float Speed = 5.0f;

		// �v���C���[�̃W�����v��
		constexpr float JumpPower = -7.0f;
	};

	// �v���C���[���ړ�����Ƃ��ɓ��͂����l
	namespace PlayerInput {

		static float xspeedtime = 0;

		float getinertia() {
			if (Input::getKey(Key::LEFT)) {
				xspeedtime = max(xspeedtime - 0.2f, -1.0f);
			}
			else if (Input::getKey(Key::RIGHT)) {
				xspeedtime = min(xspeedtime + 0.2f, 1.0f);
			}
			else {
				xspeedtime *= 0.9f;
			}

			return xspeedtime;
		}

	}

	namespace {
		// �v���C���[�̍ő�̃p�����[�^
		// �̗́A�e�̐��A�U���́A����́A�X�s�[�h
		static const ActorParameter MaxParameter{ 30.0f, 20.0f, 2.0f, 3.0f, 5.0f };
	}

	// ---------- �v���C���[�T�E���h�N���X ----------

	PlayerAudio::PlayerAudio()
		: _audioList(2)
	{
		_audioList[0].load(global::AudioAsset("se_jump.wav"));
		_audioList[0].setVolume(-3000);
		_audioList[1].load(global::AudioAsset("se_shot.wav"));
		_audioList[1].setVolume(-3000);

	}

	PlayerAudio::~PlayerAudio()
	{
	}

	void PlayerAudio::playAudio(int _index)
	{
		_audioList[_index].setPosition(0);
		_audioList[_index].play();
	}

	void PlayerAudio::stopAudio(int _index)
	{
		_audioList[_index].stop();
	}

	// ---------- �v���C���[�N���X ----------

	Player::Player()
		: Actor()
		, map()
		, collider()
		, playerState(PlayerState::Wait)
		, playerBody(MaxParameter)
		, playerAudio()
		, moveTime()
		, jumpTime()
		, isJump(false)
		, isGround(false)
		, isFall(false)
		, jumpInput(false)
		, isMove(true)
		, waitImage(2, 1, 3.0f)
		, walkImage(10, 1, 24.0f)
	{
		walkImage.setTexture(TextureManager::getTexture("Main_Walk"));
		waitImage.setTexture(TextureManager::getTexture("Main_Wait"));

		// ���g�̃I�u�W�F�N�g�̖��O�����߂�
		this->name = "Player";

		// jumpTime�̉��Z���Ԃ�0.16�ɂ������̂�scale��10�{�ɂ���
		jumpTime.setTimeScale(10.0f);
	}

	void Player::onStart()
	{
		this->setActive(true);

		// �v���C���[�̃p�����[�^���Z�b�g(���Z�b�g)����
		playerBody.setParamater(MaxParameter);

		velocity = Vector2::Zero;

		bounds.minPos.setPos(0, 0);
		bounds.maxPos.setPos(32, 32);
		bounds.size.setPos(bounds.maxPos - bounds.minPos);
		bounds.center.setPos(bounds.size.half());
	}

	void Player::onUpdate()
	{
		if (!this->isActive)
		{
			return;
		}

		if (this->fallScreen(map->getMapSize().y)) {
			death();
		}

		movePlayer();

		jumpPlayer();

		shotPlayer();

		playerBody.onUpdate();

		if (!isMove) {
			moveTime.update();
			if (moveTime.isTimeUp(0.25)) {
				isMove = true;
				moveTime.reset();
			}
		}

		{
			float healMp = playerBody.getParameter().mp + Time::deltaTime();
			healMp = clamp(healMp, 0.0f, MaxParameter.mp);
			playerBody.setMP(healMp);
		}

		// ----- ���W�X�V -----
		if(isMove)
			this->transform.pos = intersectTileMap();			 // ���W���X�V

		// ��ʊO�Ƀv���C���[���o�Ȃ��悤�ɂ���
		this->transform.pos = vecClamp(
			this->transform.pos,
			{
				Camera::minScreenPos().x + 16.0f, Camera::minScreenPos().y + 16.0f
			},
			{
				Camera::maxScreenPos().x - 16.0f, 10000.0f
			}
		);

		Camera::setTarget(this->transform.pos);                  // �v���C���[��ǐՂ���悤�ɃJ�����ɍ��W��n��
		auto screen = Camera::toScreenPos(this->transform.pos);  // ���W���X�N���[�����W�ւƕϊ�

		// ----- �R���C�_�[�X�V -----
		collider.update(screen, 32.0f, 32.0f);

		// ----- �`�� -----
		const float scaleXY = 32.0f / 24.0f;
		isFlip = velocity.x < 0.0f;
		if (std::abs(velocity.x) <= 0.005f) {
			velocity.x = 0.0f;
			waitImage.draw(screen, { scaleXY, scaleXY }, transform.angle, true, isFlip);
		}
		else {
			walkImage.draw(screen, { scaleXY, scaleXY }, transform.angle, true, isFlip);
		}

		// ----- �f�o�b�O -----
		debug();
	}

	void Player::setMap(Map* _map)
	{
		map = _map;
	}

	Vector2 Player::intersectTileMap()
	{
		auto nextPos = this->transform.pos + velocity;

		// ������s�����W�����߂�
		float offX{ bounds.center.x / 4.0f - 1.0f };
		float offY{ bounds.center.y / 4.0f - 1.0f };

		// �㉺����p�ɔ���{�b�N�X�X�V
		bounds.minPos.setPos(this->transform.pos.x - bounds.center.x, nextPos.y - bounds.center.y);
		bounds.maxPos.setPos(this->transform.pos.x + bounds.center.x, nextPos.y + bounds.center.y);

		// -- �� --
		intersectPoint.bottom[0] = Vector2{ bounds.minPos.x + offX, bounds.maxPos.y + 1.0f };
		intersectPoint.bottom[1] = Vector2{ bounds.maxPos.x - offX, bounds.maxPos.y + 1.0f };

		// -- �� --
		intersectPoint.top[0]    = Vector2{ bounds.minPos.x + offX, bounds.minPos.y };
		intersectPoint.top[1]    = Vector2{ bounds.maxPos.x - offX, bounds.minPos.y };

		nextPos = verticalIntersect(nextPos);

		// ���E����p�ɔ���{�b�N�X�X�V
		bounds.minPos.setPos(nextPos.x - bounds.center.x, this->transform.pos.y - bounds.center.y);
		bounds.maxPos.setPos(nextPos.x + bounds.center.x, this->transform.pos.y + bounds.center.y);

		// -- �E --
		intersectPoint.right[0] = Vector2{ bounds.maxPos.x , bounds.minPos.y + offY };
		intersectPoint.right[1] = Vector2{ bounds.maxPos.x , bounds.maxPos.y - offY };

		// -- �� --
		intersectPoint.left[0]  = Vector2{ bounds.minPos.x - 1.0f, bounds.minPos.y + offY };
		intersectPoint.left[1]  = Vector2{ bounds.minPos.x - 1.0f, bounds.maxPos.y - offY };
		
		nextPos = holizontalIntersect(nextPos);

		return nextPos;
	}

	Vector2 Player::verticalIntersect(const Vector2& _nextPos)
	{
		auto nextPos = _nextPos;

		// -- ��Ƃ̓����蔻�� --
		for (int i{ 0 }; i < IntersectPoint::Size; ++i) {
			auto mapID = map->getTile((int)intersectPoint.top[i].x / 32, (int)intersectPoint.top[i].y / 32);

			if (mapID == MapTile::BLOCK) {
				auto hitPos = ((int)intersectPoint.top[i].y / MapInfo::MapSize + 1) * (float)MapInfo::MapSize;

				if (intersectPoint.top[i].y <= hitPos) {
					nextPos.y = nextPos.y + fabsf(intersectPoint.top[i].y - hitPos);

					break;
				}
			}
		}

		// -- ���Ƃ̓����蔻�� --
		for (int i{ 0 }; i < IntersectPoint::Size; ++i) {
			auto mapID = map->getTile((int)intersectPoint.bottom[i].x / 32, (int)intersectPoint.bottom[i].y / 32);

			if (mapID == MapTile::BLOCK) {
				auto hitPos = (int)(intersectPoint.bottom[i].y / MapInfo::MapSize) * (float)MapInfo::MapSize;

				if (intersectPoint.bottom[i].y >= hitPos) {
					nextPos.y = nextPos.y - fabsf(intersectPoint.bottom[i].y - hitPos) + 1.0f;

					// �n�ʂɂ��Ă���Ƃ�
					isGround = true;

					break;
				}
			}
			else if(mapID == MapTile::OBJECT){
				auto sub = this->transform.pos.y - nextPos.y;
				if (sub <= 0) {
					auto hitPos = (int)(intersectPoint.bottom[i].y / MapInfo::MapSize) * (float)MapInfo::MapSize;

					if (intersectPoint.bottom[i].y >= hitPos) {
						nextPos.y = nextPos.y - fabsf(intersectPoint.bottom[i].y - hitPos) + 1.0f;

						// �n�ʂɂ��Ă���Ƃ�
						isGround = true;

						break;
					}
				}

			}
			else {
				// ���Ƀ}�b�v�`�b�v���Ȃ��Ƃ�
				isGround = false;
			}
		}

		return nextPos;
	}

	Vector2 Player::holizontalIntersect(const Vector2& _nextPos)
	{
		auto nextPos = _nextPos;

		// -- �E�Ƃ̓����蔻�� --
		for (int i{ 0 }; i < IntersectPoint::Size; ++i) {
			auto mapID = map->getTile((int)intersectPoint.right[i].x / 32, (int)intersectPoint.right[i].y / 32);

			if (mapID == MapTile::BLOCK) {
				float hitPos = (int)(intersectPoint.right[i].x / MapInfo::MapSize) * (float)MapInfo::MapSize;

				if (intersectPoint.right[i].x >= hitPos) {
					nextPos.x = nextPos.x - fabsf(intersectPoint.right[i].x - hitPos);
					break;
				}
			}
		}

		// -- ���Ƃ̓����蔻�� --		
		for (int i{ 0 }; i < IntersectPoint::Size; ++i) {
			auto mapID = map->getTile((int)intersectPoint.left[i].x / 32, (int)intersectPoint.left[i].y / 32);

			if (mapID == MapTile::BLOCK) {
				float hitPos = ((int)intersectPoint.left[i].x / MapInfo::MapSize + 1) * (float)MapInfo::MapSize;

				if (intersectPoint.left[i].x <= hitPos) {
					nextPos.x = nextPos.x + fabsf(intersectPoint.left[i].x - hitPos) - 1.0f;
					break;
				}
			}
		}

		return nextPos;
	}

	void Player::resetPosition(const Vector2& _pos)
	{
		this->setActive(true);
		this->transform.setPos(_pos);
	}

	BoxCollider& Player::getCollider()
	{
		return collider;
	}

	PlayerBody& Player::getPlayerBody()
	{
		return playerBody;
	}

	void Player::death()
	{
		isActive = false;
	}

	void Player::respawn(const Vector2& _pos)
	{
		// velocity��0�ɂ���
		this->velocity = Vector2::Zero;

		PlayerInput::xspeedtime = 0.0f;

		isGround = true;

		// �p�����[�^�����Ƃɖ߂�
		playerBody.setParamater(MaxParameter);

		this->transform.setPos(_pos);
		Camera::setTarget(this->transform.pos);

		isActive = true;
	}

	void Player::reset()
	{
		velocity = Vector2::Zero;
		isMove = true;
	}

	void Player::setIsMove(bool _isMove)
	{
		isMove = _isMove;
	}

	void Player::movePlayer()
	{
		// ----- �ړ� -----
		velocity.x = PlayerInput::getinertia() * playerBody.getParameter().speed;
	}

	void Player::jumpPlayer()
	{
		// ----- �W�����v -----

		jumpInput = Input::getKeyDown(Key::Z);

		// �W�����v�L�[�������ꂽ��
		if (jumpInput) {
			// �n�ʂɑ������Ă���Ƃ�
			if (isGround) {
				playerAudio.playAudio(0);
				isGround = false;
				isJump = true;
				isFall = true;
				jumpTime.reset();
			}
		}

		// �󒆂ɂ���Ƃ�
		if (isJump) {

			// 1.0�b�𒴂�����jump�t���O��false�ɂ���
			if(jumpTime.isTimeUp(1.0f)){
				jumpTime.setTime(1.0f);
				isJump = false;
				jumpInput = false;
			}

			jumpTime.update();
			velocity.y = PlayerParameters::JumpPower * jumpTime.getFrameTime();
		}
		else {
			isFall = true;
			velocity.y += PlayerParameters::Gravity;
			velocity.y = min(velocity.y, PlayerParameters::MaxGravity);
		}

		// �n�ʂɑ������Ă���Ƃ��A�n�ʂɂ߂荞�܂Ȃ��悤�ɂ���
		if (isGround) {
			isFall = false;
			velocity.y = 0.0f;
		}
	}

	void Player::shotPlayer()
	{
		if (Input::getKeyDown(Key::X)) {

			if (playerBody.getParameter().mp < 2) {
				return;
			}

			playerAudio.playAudio(1);

			float vx = (velocity.x >= 0) ? 10.0f : -10.0f;
			BulletPtr bulletPtr(new Bullet(this->transform.pos, Vector2{ vx, 0.0f }, BulletType::Player));
			bulletPtr->onStart();
			bulletPtr->setAttack(playerBody.getParameter().attack);
			BulletManager::getIns()->addBullet(bulletPtr);
			playerBody.subMp(2.0f);
		}
	}

	void Player::debug()
	{	
#if _DEBUG
		static Font font{ 24, "MS ����" };
		
		font.drawText(0, 60,   Color::Black, "Position = %s", this->transform.pos.toString().c_str());
		font.drawText(0, 80,   Color::Black, "Velocity = %s", velocity.toString().c_str());
		//Debug::drawFormatText(0, 80,   Color::Black, "isGround = %d", isGround);
		//Debug::drawFormatText(0, 100, Color::Black, "isJump   = %d", isJump);
		//Debug::drawFormatText(0, 120,  Color::Black, "isFall   = %d", isFall);
#endif // _DEBUG
	}
}