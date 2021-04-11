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
	const int COLLISION_LAYERS = 16;

	//PHYSIOGNOMY
	//Hunger y Tiredness
	const int MAX_MULTIPLE_STATES = 6; //Numero de estados de daño que el jugador puede tener
	const float NONEHUNGER_LEVEL = 0.75f; //Por encinma del 75% estará en NONE y por debajo en HUNGER
	const float HUNGER_LEVEL = 0.35f; //Por encima del 35% estará en HUNGER y por debajo en STARVING
	const int MAX_SLEEP_HOURS = 8; //Horas máximas de sueño en una noche
	const float NONETIRED_LEVEL = 0.75f; //Por encinma del 75% estará en NONE y por debajo en TIRED
	const float TIRED_LEVEL = 0.35f; //Por encima del 35% estará en TIRED y por debajo en EXHASUTED

	//Pain, Bleed, Concussion y Intoxication
	const float REDUCE_WEAPON_DAMAGE = 0.2f; //En %
	const int CONTUSION_INCREASE_TIME = 5000; //Cantidad de tiempo que PainComponent añade a ContusionComponent
	const int INTOXICATION_INCREASE_TIME = 5000; //Cantidad de tiempo que PainComponent añade a IntoxicationComponent
	const int CONTUSION_TIME = 10000;	 //Tiempo que dura la contusion
	const int INTOXICATION_TIME = 20000; //Tiempo que dura la intoxicacion
	const int TIME_PER_NEWSUMOFTIME = 8000; //Tiempo que tarda PainComponent en añadir tiempo a Contusion e Intoxication
	const int TIME_TO_DECREASE_HUNGER = 10000;
	const float HUNGER_TO_DECREASE = 0.15f; //En %
	const int MAX_NEWDAMAGE_TIME = 10000; 

	//WEAPONS

	//Basic Weapon
	const int WEAPON_TIER1_DAMAGE = 100;
	const int WEAPON_TIER2_DAMAGE = 100;
	const int WEAPON_TIER3_DAMAGE = 100;

	const int WEAPON_TIER1_FIRERATE = 1.75f;
	const int WEAPON_TIER2_FIRERATE = 1.75f;
	const int WEAPON_TIER3_FIRERATE = 1.75f;

	//Ricochet Weapon
	const int RICOCHET_TIER1_DAMAGE = 100;
	const int RICOCHET_TIER2_DAMAGE = 100;
	const int RICOCHET_TIER3_DAMAGE = 100;

	const int RICOCHET_TIER1_FIRERATE = 1.75f;
	const int RICOCHET_TIER2_FIRERATE = 1.75f;
	const int RICOCHET_TIER3_FIRERATE = 1.75f;

	//Charge Weapon
	const int CHARGE_TIER1_DAMAGE = 100;
	const int CHARGE_TIER2_DAMAGE = 100;
	const int CHARGE_TIER3_DAMAGE = 100;

	const int CHARGE_TIER1_FIRERATE = 1;
	const int CHARGE_TIER2_FIRERATE = 1;
	const int CHARGE_TIER3_FIRERATE = 1;
}