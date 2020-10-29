#include "Player.h"
#include "WindowInfo.h"
#include <cmath>

namespace gnGame {

	namespace PlayerInfo {
		// プレイヤーにかかる重力
		constexpr float Gravity = 0.98f;

		// プレイヤーが進む速さ
		constexpr float Speed = 5.0f;

		// プレイヤーのジャンプ力
		constexpr float JumpPower = 7.0f;


		// プレイヤーの進む距離
		float getAxis() {
			float result = 0;
			if (Input::getKey(Key::A)) {
				result -= 1.0f;
			}

			if (Input::getKey(Key::D)) {
				result += 1.0f;
			}

			return result;
		}
	};

	PlayerImage::PlayerImage()
		: texture("Image/char.png")
		, sprite(texture)
	{
	}

	Player::Player()
		: pImage()
		, pos(100, 100)
		, velocity()
		, isJump(false)
		, isGround(false)
	{
	}

	void Player::onStart()
	{
		bounds.minPos.setPos(0, 0);
		bounds.maxPos.setPos(32, 64);
		bounds.size.setPos(bounds.maxPos - bounds.minPos);
		bounds.center.setPos(bounds.size.half());
	}

	void Player::onUpdate()
	{
		// 移動変数部
		float gy = PlayerInfo::Gravity;

		// 移動部
		pos.x += PlayerInfo::getAxis() * PlayerInfo::Speed;

		if (Input::getKeyDown(Key::SPACE)) {
			//isJump = 1;
			pos.x = 300.f;

			if (isGround) {
				isGround = false;
				isJump = 1;
				pos.y -= PlayerInfo::JumpPower;
				isJump = 0;
			}
		}


		// 判定ボックス更新部
		bounds.minPos.setPos(pos.x - bounds.center.x, pos.y - bounds.center.y);
		bounds.maxPos.setPos(32 + pos.x - bounds.center.x, 64 + pos.y - bounds.center.y);
		bounds.size.setPos(bounds.maxPos - bounds.minPos);
		bounds.center.setPos(bounds.size.half());

		// 移動判定部
		if (pos.y + bounds.center.y >= 416) {
			gy = 0;
			isGround = true;
		}


		if (pos.x + bounds.center.x >= WindowInfo::WindowWidth) {
			pos.x = WindowInfo::WindowWidth - bounds.center.x;
		}

		if (pos.x - bounds.center.x <= 0) {
			pos.x = 0 + bounds.center.x;
		}

		pos.y += gy;

		// 座標更新部
		pImage.sprite.setPos(pos);


		// 描画部
		pImage.sprite.draw();

		debug();
	}

	void Player::debug()
	{
		Debug::drawFormatText(0, 0, Color::Black, "Pos = %s", pos.toString().c_str());
		Debug::drawFormatText(0, 20, Color::Black, "isGround = %d", isGround);
		Debug::drawFormatText(0, 40, Color::Black, "isJump   = %d", isJump);

		Debug::drawLine(bounds.minPos, Vector2{ bounds.minPos.x, bounds.maxPos.y }, 3.f, Color::Red);
		Debug::drawLine(bounds.minPos, Vector2{ bounds.maxPos.x, bounds.minPos.y }, 3.f, Color::Red);
		Debug::drawLine(Vector2{ bounds.maxPos.x, bounds.minPos.y }, bounds.maxPos, 3.f, Color::Red);
		Debug::drawLine(Vector2{ bounds.minPos.x, bounds.maxPos.y }, bounds.maxPos, 3.f, Color::Red);
	}
}