#pragma once

namespace consts {

	const float FRAME_RATE = 60.0f;
	const float DELTA_TIME = 1 / FRAME_RATE;
	const int WINDOW_WIDTH = 1280;
	const int WINDOW_HEIGHT = 720;

	// PLAYER
	const float GRAVITY = 8.0f;
	const float PLAYER_SPEED = 3.0f;
	const float PLAYER_BACKWARDS_SPEED = 1.5f;
	const float CAMERA_MARGIN_FROM_PLAYER = -150;
	const float JUMP_SPEED = 3.0f;
	const float STAIRS_SPEED = 1.4f;
	const float FALLING_DMG_SPEED = 5;
	const float ACCELERATION = 5;
	const float DECELERATION = 14;

	// ENEMIES
	const float MELEE_ENEMY_SPEED = 2.0f;
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
	const int MAX_MULTIPLE_STATES = 8;		 //Numero de estados de da�o que el jugador puede tener
	const float HUNGER_THRESHOLD = 0.75f;	 //Por encima del 75% estar� en NONE y por debajo en HUNGER
	const float STARVATION_THRESHOLD = 0.35f;	//Por encima del 35% estar� en HUNGER y por debajo en STARVING
	const int MAX_SLEEP_HOURS = 8;			 //Horas m�ximas de sue�o en una noche
	const float NONETIRED_LEVEL = 0.75f;	 //Por encima del 75% estar� en NONE y por debajo en TIRED
	const float TIRED_LEVEL = 0.35f;		 //Por encima del 35% estar� en TIRED y por debajo en EXHASUTED

	// Pain, Bleed, Concussion, Intoxication y Hypothermia
	const float BLOODLOSS_PER_SECOND_BASE = 15.0f;	//En %. Valor base, el tiempo se reduce con valores altos de hambre
	const float REDUCE_WEAPON_DAMAGE = 0.2f;		//En %
	const int CONCUSSION_INCREASE_TIME = 5000;		//Cantidad de tiempo que PainComponent a�ade a ConcussionComponent
	const int INTOXICATION_INCREASE_TIME = 5000;	//Cantidad de tiempo que PainComponent a�ade a IntoxicationComponent
	const int CONCUSSION_TIME = 5000;				//Tiempo que dura la contusion
	const int INTOXICATION_TIME = 10000;			//Tiempo que dura la intoxicacion
	const int TIME_PER_NEWSUMOFTIME = 8000;			//Tiempo que tarda PainComponent en a�adir tiempo a Concussion e Intoxication
	const int TIME_TO_DECREASE_HUNGER = 10000;
	const float HUNGER_TO_DECREASE = 0.15f;			//En %
	const int HYPOTHERMIA_TIME = 30000;

	//UI
	const int STATUS_EFFECTS_SIZEX = 48;
	const int STATUS_EFFECTS_SIZEY = 48;

	// WEAPONS
	const int WEAPON_FIRERATES[] = { 1.5f, 1.0f, 0.75f, 1.75f, 1.65f, 1.55f, 1.25f, 1.25f, 1.25f };
	const int WEAPON_DAMAGE_VALUES[] = { 30, 30, 30, 70, 90, 110, 90, 130, 170 };
	const int WEAPON_MAGAZINE_SIZES[] = { 12, 21, 35, 6, 7, 8, 5, 5, 5 };

	const float CHARGEWEAPON_HEIGHT = 15;

	// Enemy Lives
	const int ENEMY_HP_DEFAULT = 100;
	const int ENEMY_HP_FLYING = 100;
	const int ENEMY_HP_RANGED = 100;

	// LOCALIZACIONES
	const int NUM_LOCATIONS = 5;

	const float TIREDNESS_FROM_TRAVELING[] = { 0.25f, 0.2f, 0.3f, 0.1f, 0.15f };

	// ESCENA DE AJUSTES Y SETTINGS
	const int VOLUME_LEVELS = 6;

	const int VOLUME_BARS_SIZE_X = 300;
	const int VOLUME_BARS_SIZE_Y = 40;

	const int CHANGE_VOLUME_BUTTON_SIZE_X = 32;

	const int ADJUSTER_SIZE_X = 16;
	const int ADJUSTER_SIZE_Y = 64;

	const int BAR_TEXT_SIZE_X = 400;
	const int BAR_TEXT_SIZE_Y = 50;

	const int SHOW_FPS_BAR_SIZE_X = 400;
	const int SHOW_FPS_BAR_SIZE_Y = 40;

	// GAME CYCLE
	const int MAX_DAYS = 10;
	const int RAID_TIME = 8 * 60;
	const int MAX_ACTIONS = 5;
}