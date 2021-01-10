#pragma once

#include "SafeDelete.h"
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Sprite.h"
#include "Object3d.h"
#include "DebugText.h"
#include "Audio.h"
#include "CollisionPrimitive.h"

#include<stdio.h>
#include<stdlib.h>
/// <summary>
/// ゲームシーン
/// </summary>
class GameScene
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private: // 静的メンバ変数
	static const int debugTextTexNumber = 0;

public: // メンバ関数

	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	
	void Reset();

private: // メンバ変数
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;
	DebugText debugText;	
	GameScene* Gs=nullptr;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
	Sprite* spriteBG = nullptr;

	Model* modelSkydome = nullptr;
	Model* modelGround = nullptr;
	Model* modelZiki = nullptr;
	Model* modelZiki2 = nullptr;
	Model* modelBlock = nullptr;
	Model* modelBlock2 = nullptr;
	Model* modelBlock3 = nullptr;
	Model* modelStage4 = nullptr;
	Model* modelStage5 = nullptr;
	Model* modelDelta1 = nullptr;
	Model* modelDelta2 = nullptr;
	Model* modelDelta3 = nullptr;
	Model* modelDelta4 = nullptr;
	Model* modelDelta5 = nullptr;
	Model* modelDelta6 = nullptr;

	Object3d* objSkydome = nullptr;
	Object3d* objGround = nullptr;
	Object3d* objZiki = nullptr;
	Object3d* objZiki2 = nullptr;
	Object3d* objBlock = nullptr;
	Object3d* objBlock2 = nullptr;
	Object3d* objBlock3 = nullptr;
	Object3d* objStage4 = nullptr;
	Object3d* objStage5 = nullptr;
	Object3d* objDelta1 = nullptr;
	Object3d* objDelta2 = nullptr;
	Object3d* objDelta3 = nullptr;
	Object3d* objDelta4 = nullptr;
	Object3d* objDelta5 = nullptr;
	Object3d* objDelta6 = nullptr;

	XMFLOAT3 zikipos = { 0.0f,1.0f, -10.0f };
	XMFLOAT3 zikipos2 = { 0.0f,1.0f, -10.0f };
	XMFLOAT3 Blockpos = {};
	XMFLOAT3 Blockpos2 = {};
	XMFLOAT3 Blockpos3 = {};
	XMFLOAT3 Stage4pos = {};
	XMFLOAT3 Stage5pos = {};
	XMFLOAT3 Delta1pos = {};
	XMFLOAT3 Delta2pos = {};
	XMFLOAT3 Delta3pos = {};
	XMFLOAT3 Delta4pos = {};
	XMFLOAT3 Delta5pos = {};
	XMFLOAT3 Delta6pos = {};

	float radius = 3.0f; //半径
	float centerX = 0.0f;//中心座標X（回転の中心）
	float centerY = 0.0f;//中心座標Y（回転の中心）
	float angle = 0.0f;//角度
	float length = radius;//半径の長さ
	float add_X =0;
	float add_Y =0;

	//stageのZ座標は30で自機と当たり判定を行う
	float delta1z = 100.0f;
	float stage1z = 40.0f;
	float stage2z = 60.0f;
	float stage3z = 80.0f;
	float stage4z = 100.0f;
	float stage5z = 30.0f;
	//自機処理
	bool charaChange = false;

	//stage速度
	float stagevel = 0.01f;

	//ゲームオーバー処理
	bool title = false;
	bool tutorial = false;
	bool clear = false;
	bool gameover = false;

	// 当たり判定 球
	Sphere sphere;
	// 当たり判定 平面
	Plane plane;
	//当たり判定　三角形
	//Delta
	Triangle triangle;
	Triangle triangle2;
	Triangle triangle3;
	//MAYAシリーズ
	//stage1
	Triangle triangleM1;
	Triangle triangleM2;
	Triangle triangleM3;
	Triangle triangleM4;
	Triangle triangleM5;
	Triangle triangleM6;
	Triangle triangleM7;
	Triangle triangleM8;
	//stage2
	Triangle triangle2M1;
	Triangle triangle2M2;
	Triangle triangle2M3;
	Triangle triangle2M4;
	Triangle triangle2M5;
	Triangle triangle2M6;
	Triangle triangle2M7;
	Triangle triangle2M8;
	//stage3
	Triangle triangle3M1;
	Triangle triangle3M2;
	Triangle triangle3M3;
	Triangle triangle3M4;
	//stage4
	Triangle triangle4M1;
	Triangle triangle4M2;
	Triangle triangle4M3;
	Triangle triangle4M4;
	Triangle triangle4M5;
	Triangle triangle4M6;
};

