#pragma once

namespace consts {

	const float FRAME_RATE = 60.0f;
	const float DELTA_TIME = 1 / FRAME_RATE;
	const int WINDOW_WIDTH = 1408;
	const int WINDOW_HEIGHT = 792;

	// PLAYER
	const float GRAVITY = 8.0f;
	const float PLAYER_SPEED = 3.0f;
	const float PLAYER_BACKWARDS_SPEED = 1.5f;
	const float CAMERA_MARGIN_FROM_PLAYER = -250;
	const float JUMP_SPEED = 3.0f;
	const float STAIRS_SPEED = 1.5f;
	const float FALLING_DMG_SPEED = 8;
	const float ACCELERATION = 5;
	const float DECELERATION = 7;
	// ENEMIES
	const float MELEE_ENEMY_SPEED = 2.5f;
	const float MELEE_ENEMY_STOPDISTANCE = 80.0f;
	const float RANGED_ENEMY_SPEED = PLAYER_SPEED / 2;
	const float RANGED_ENEMY_MARGINDISTANCE = 250.0f;
	const float RANGED_ENEMY_SHOOTDISTANCE = 350.0f;
	const float FLYING_ENEMY_HOVERHEIGHT = 160.0f;
	const float FLYING_ENEMY_APPROACHDISTANCE = 180.0f;
	const float ACTIVATE_ENEMY_DISTANCE = 40.0f;
	const short int ENEMY_ATTACK_COOLDOWN = 1000;

	// COLLISIONS
	const int COLLISION_LAYERS = 16;

	// PHYSIOGNOMY
	// Hunger y Tiredness
	const int MAX_MULTIPLE_STATES = 6; //Numero de estados de daño que el jugador puede tener
	const float NONEHUNGER_LEVEL = 0.75f; //Por encima del 75% estará en NONE y por debajo en HUNGER
	const float HUNGER_LEVEL = 0.35f; //Por encima del 35% estará en HUNGER y por debajo en STARVING
	const int MAX_SLEEP_HOURS = 8; //Horas máximas de sueño en una noche
	const float NONETIRED_LEVEL = 0.75f; //Por encima del 75% estará en NONE y por debajo en TIRED
	const float TIRED_LEVEL = 0.35f; //Por encima del 35% estará en TIRED y por debajo en EXHASUTED

	// Pain, Bleed, Concussion, Intoxication y Hypothermia
	const float REDUCE_WEAPON_DAMAGE = 0.2f; //En %
	const int CONTUSION_INCREASE_TIME = 5000; //Cantidad de tiempo que PainComponent añade a ContusionComponent
	const int INTOXICATION_INCREASE_TIME = 5000; //Cantidad de tiempo que PainComponent añade a IntoxicationComponent
	const int CONTUSION_TIME = 10000;	 //Tiempo que dura la contusion
	const int INTOXICATION_TIME = 20000; //Tiempo que dura la intoxicacion
	const int TIME_PER_NEWSUMOFTIME = 8000; //Tiempo que tarda PainComponent en añadir tiempo a Contusion e Intoxication
	const int TIME_TO_DECREASE_HUNGER = 10000;
	const float HUNGER_TO_DECREASE = 0.15f; //En %
	const int MAX_NEWDAMAGE_TIME = 5000;
	const int HYPOTHERMIA_TIME = 30000;

	//UI
	const int STATUS_EFFECTS_SIZEX = 48;
	const int STATUS_EFFECTS_SIZEY = 48;

	// WEAPONS

	// Basic Weapon
	const int WEAPON_TIER1_DAMAGE = 100;
	const int WEAPON_TIER2_DAMAGE = 100;
	const int WEAPON_TIER3_DAMAGE = 100;

	const int WEAPON_TIER1_FIRERATE = 1.75f;
	const int WEAPON_TIER2_FIRERATE = 1.75f;
	const int WEAPON_TIER3_FIRERATE = 1.75f;

	// Ricochet Weapon
	const int RICOCHET_TIER1_DAMAGE = 100;
	const int RICOCHET_TIER2_DAMAGE = 100;
	const int RICOCHET_TIER3_DAMAGE = 100;

	const int RICOCHET_TIER1_FIRERATE = 1.75f;
	const int RICOCHET_TIER2_FIRERATE = 1.75f;
	const int RICOCHET_TIER3_FIRERATE = 1.75f;

	// Charge Weapon
	const int CHARGE_TIER1_DAMAGE = 100;
	const int CHARGE_TIER2_DAMAGE = 100;
	const int CHARGE_TIER3_DAMAGE = 100;

	const int CHARGE_TIER1_FIRERATE = 1;
	const int CHARGE_TIER2_FIRERATE = 1;
	const int CHARGE_TIER3_FIRERATE = 1;

	const float CHARGEWEAPON_HEIGHT = 15;

	// Enemy Lives
	const int ENEMY_HP_DEFAULT = 100;
	const int ENEMY_HP_FLYING = 100;
	const int ENEMY_HP_RANGED = 100;

	// LOCALIZACIONES
	const int NUM_LOCATIONS = 5;

	// ESCENA DE AJUSTES Y SETTINGS
	const int VOLUME_LEVELS = 6;

	const int BACK_BUTTON_POSITION_X = WINDOW_WIDTH / 8 - 120;
	const int BACK_BUTTON_POSITION_Y = WINDOW_HEIGHT - WINDOW_HEIGHT / 8;

	const int VOLUME_BAR_POSITION_X = 600;
	const int VOLUME_BAR_POSITION_Y = 100;

	const int VOLUME_BARS_SIZE_X = 300;
	const int VOLUME_BARS_SIZE_Y = 40;

	const int SFX_VOLUME_BAR_POSITION_X = 600;
	const int SFX_VOLUME_BAR_POSITION_Y = 200;

	const int CHANGE_VOLUME_BUTTON_SIZE_X = 32;

	const int ADJUSTER_SIZE_X = 16;
	const int ADJUSTER_SIZE_Y = 64;

	const int BAR_TEXT_POSITION_X = 100;
	const int BAR_TEXT_SIZE_X = 400;
	const int BAR_TEXT_SIZE_Y = 50;

	const int SHOW_FPS_BAR_POS_X = 100;
	const int SHOW_FPS_BAR_POS_Y = 300;
	const int SHOW_FPS_BAR_SIZE_X = 400;
	const int SHOW_FPS_BAR_SIZE_Y = 40;

	const int SHOW_FPS_BUTTON_POS_X = 600;
	const int SHOW_FPS_BUTTON_POS_Y = 300;
	const int SHOW_FPS_BUTTON_SIZE_X = 32;
	const int SHOW_FPS_BUTTON_SIZE_Y = 32;

	// GAMECYCLE
	const int MAX_DAYS = 10;
	const int RAID_TIME = 8 * 60;
}