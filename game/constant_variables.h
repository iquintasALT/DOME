#pragma once

namespace consts {
	const float GRAVITY = 8.0f;
	const float FRAME_RATE = 60.0f;
	const float DELTA_TIME = 1 / FRAME_RATE;
	const float PLAYER_SPEED = 3.0f;
	const float JUMP_SPEED = 3.0f;
	const float MELEE_ENEMY_SPEED = 2.5f;
	const float MELEE_ENEMY_STOPDISTANCE = 50.0f;
	const float RANGED_ENEMY_SPEED = PLAYER_SPEED / 2;
	const float RANGED_ENEMY_MARGINDISTANCE = 250.0f;
	const float RANGED_ENEMY_SHOOTDISTANCE = 350.0f;
	const float ACTIVATE_ENEMY_DISTANCE = 400.0f;
	const int WINDOW_WIDTH = 1088;
	const int WINDOW_HEIGHT = 736;
	const float FALLING_DMG_SPEED = 8;
	const float CHARGEWEAPON_HEIGHT = 15;

	//PHYSIOGNOMY
	const int MAX_MULTIPLE_STATES = 6; //Numero de estados de daño que el jugador puede tener
	const float NONEHUNGER_LEVEL = 0.75f; //Por encinma del 75% estará en NONE y por debajo en HUNGER
	const float HUNGER_LEVEL = 0.35f; //Por encima del 35% estará en HUNGER y por debajo en STARVING
	const int MAX_SLEEP_HOURS = 8; //Horas máximas de sueño en una noche
	const float NONETIRED_LEVEL = 0.75f; //Por encinma del 75% estará en NONE y por debajo en TIRED
	const float TIRED_LEVEL = 0.35f; //Por encima del 35% estará en TIRED y por debajo en EXHASUTED
	const int MAX_NEWDAMAGE_TIME = 10000; 
	const int TIME_PER_NEWSUMOFTIME = 8000; //Tiempo mayor al que añada, si no, los daños temporales nunca terminarian sin la necesidad de ser curados
	const int CONTUSION_TIME_TO_END = 10000; 
	const int INTOXICATION_TIME_TO_END = 20000; 
	const int TIME_TO_INCREASE_CONTUSION = 5000;
	const int TIME_TO_INCREASE_INTOXICATION = 5000;
	const int TIME_TO_DECREASE_HUNGER = 10000;
	const float HUNGER_TO_DECREASE = 0.15f;

	//WEAPONS

	//Basic Weapon
	const int WEAPON_TIER1_DAMAGE = 100;
	const int WEAPON_TIER2_DAMAGE = 100;
	const int WEAPON_TIER3_DAMAGE = 100;

	const int WEAPON_TIER1_FIRERATE = 100;
	const int WEAPON_TIER2_FIRERATE = 100;
	const int WEAPON_TIER3_FIRERATE = 100;

	//Ricochet Weapon
	const int RICOCHET_TIER1_DAMAGE = 100;
	const int RICOCHET_TIER2_DAMAGE = 100;
	const int RICOCHET_TIER3_DAMAGE = 100;

	const int RICOCHET_TIER1_FIRERATE = 100;
	const int RICOCHET_TIER2_FIRERATE = 100;
	const int RICOCHET_TIER3_FIRERATE = 100;

	//Charge Weapon
	const int CHARGE_TIER1_DAMAGE = 100;
	const int CHARGE_TIER2_DAMAGE = 100;
	const int CHARGE_TIER3_DAMAGE = 100;

	const int CHARGE_TIER1_FIRERATE = 100;
	const int CHARGE_TIER2_FIRERATE = 100;
	const int CHARGE_TIER3_FIRERATE = 100;

}