#pragma once

enum EModelID
{
	E_MODEL_ID_UNKNOWN = 0,

	E_MODEL_ID_SKYBOX,
	E_MODEL_ID_SPHERE,
	E_MODEL_ID_SHIP,
};

enum EShaderID
{
	E_SHADER_ID_UNKNOWN = 0,

	E_SHADER_ID_DEFAULT,
	E_SHADER_ID_STANDARD,
	E_SHADER_ID_SKYBOX,

	E_SHADER_ID_MAX,
};

enum EMaterialID
{
	E_MATERIAL_ID_UNKNOWN = 0,

	E_MATERIAL_ID_DEFAULT,
	E_MATERIAL_ID_STANDARD,
};

enum ETextureID
{
	E_TEXTURE_ID_UNKNOWN = 0,
	E_TEXTURE_ID_DIFFUSE,
};

enum EGameStatus
{
	E_GAME_STATUS_INIT = 0,

	E_GAME_STATUS_LOAD_SCENE_START,
	E_GAME_STATUS_LOAD_SCENE_FINISH,
};

#define SERVER_PORT 9988
#define SERVER_ADDRESS "127.0.0.1"
#define RECEIVE_BUFFER_SIZE 1024*1024*5
#define SEND_BUFFER_SIZE 1024*1024*5
#define MAX_SEND_HEAP_LENGTH 1024*1024

#define PLAYER_VELOCITY 50.0f
#define PLAYER_ROTATION_VELOCITY 50.0f
#define ACTION_FRONT 1
#define ACTION_BACK 2
#define ACTION_LEFT 4
#define ACTION_RIGHT 8

