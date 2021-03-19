#pragma once

namespace consts {
	const float GRAVITY = 8.0f;
	const float FRAME_RATE = 60.0f;
	const float DELTA_TIME = 1 / FRAME_RATE;
	const float PLAYER_SPEED = 3.0f;
	const float MELEE_ENEMY_SPEED = 2.5f;
	const float MELEE_ENEMY_STOPDISTANCE = 50.0f;
	const float RANGED_ENEMY_SPEED = PLAYER_SPEED / 2;
	const float RANGED_ENEMY_MARGINDISTANCE = 250.0f;
	const float RANGED_ENEMY_SHOOTDISTANCE = 350.0f;
	const float ACTIVATE_ENEMY_DISTANCE = 400.0f;
	const int WINDOW_WIDTH = 1088;
	const int WINDOW_HEIGHT = 736;
	const float FALLING_DMG_SPEED = 8;
}