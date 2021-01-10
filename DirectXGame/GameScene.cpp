#include "GameScene.h"
#include "Model.h"
#include "Collision.h"
#include <cassert>
#include <sstream>
#include <iomanip>
using namespace DirectX;
GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	safe_delete(spriteBG);
	safe_delete(objSkydome);
	safe_delete(objGround);
	safe_delete(objZiki);
	safe_delete(objZiki2);
	safe_delete(objBlock);
	safe_delete(objBlock2);
	safe_delete(objBlock3);
	safe_delete(objDelta1);
	safe_delete(objDelta2);
	safe_delete(objDelta3);
	safe_delete(objDelta4);
	safe_delete(objDelta5);
	safe_delete(objDelta6);
	safe_delete(modelSkydome);
	safe_delete(modelGround);
	safe_delete(modelZiki);
	safe_delete(modelZiki2);
	safe_delete(modelBlock);
	safe_delete(modelBlock2);
	safe_delete(modelBlock3);
	safe_delete(modelDelta1);
	safe_delete(modelDelta2);
	safe_delete(modelDelta3);
	safe_delete(modelDelta4);
	safe_delete(modelDelta5);
	safe_delete(modelDelta6);
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio * audio)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;

	// デバッグテキスト用テクスチャ読み込み
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return ;
	}
	// デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);

	// テクスチャ読み込み
	if (!Sprite::LoadTexture(1, L"Resources/background.png")) {
		assert(0);
		return;
	}

	
	// 背景スプライト生成
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });
	// 3Dオブジェクト生成
	objSkydome = Object3d::Create(0.0f,0.0f,0.0f);
	objGround = Object3d::Create(0.0f, -12.0f, 0.0f);
	objZiki = Object3d::Create(0.0f,1.0f, 29.0f);
	objZiki2 = Object3d::Create(0.0f, 1.0f, 29.0f);
	objBlock = Object3d::Create(0.0f, -3.0f, stage1z);
	objBlock2 = Object3d::Create(0.0f, -30.0f, stage2z);
	objBlock3 = Object3d::Create(0.0f, -45.0f, stage3z);
	objStage4 = Object3d::Create(0.0f, -65.0f, stage4z);
	objStage5 = Object3d::Create(0, 0, stage5z);
	objDelta1 = Object3d::Create(-3.0f, 0.0f, delta1z);
	objDelta2 = Object3d::Create(-3.0f, 0.0f, delta1z);
	objDelta3 = Object3d::Create(0.0f, -4.0f, delta1z);
	objDelta4 = Object3d::Create(0.0f, -4.0f, delta1z);
	objDelta5 = Object3d::Create(3.5f, 0.8f, delta1z);
	objDelta6 = Object3d::Create(3.5f, 0.8f, delta1z);

	// テクスチャ2番に読み込み
	Sprite::LoadTexture(2, L"Resources/texture.png");

	modelSkydome = Model::CreateFromOBJ("skydome");
	modelGround = Model::CreateFromOBJ("ground");
	modelZiki = Model::CreateFromOBJ("untitled");
	modelZiki2 = Model::CreateFromOBJ("ziki2");
	modelBlock = Model::CreateFromOBJ("obstacle");
	modelBlock2 = Model::CreateFromOBJ("stage02");
	modelBlock3 = Model::CreateFromOBJ("Stage3");
	modelStage4 = Model::CreateFromOBJ("Stage4");
	modelStage5 = Model::CreateFromOBJ("Stage5");
	modelDelta1 = Model::CreateFromOBJ("triangle");
	modelDelta2 = Model::CreateFromOBJ("triangle2");
	modelDelta3 = Model::CreateFromOBJ("triangle");
	modelDelta4 = Model::CreateFromOBJ("triangle2");
	modelDelta5 = Model::CreateFromOBJ("triangle");
	modelDelta6 = Model::CreateFromOBJ("triangle2");

	objSkydome->SetModel(modelSkydome);
	objGround->SetModel(modelGround);
	objZiki->SetModel(modelZiki);
	objZiki2->SetModel(modelZiki2);
	objBlock->SetModel(modelBlock);
	objBlock2->SetModel(modelBlock2);
	objBlock3->SetModel(modelBlock3);
	objStage4->SetModel(modelStage4);
	objStage5->SetModel(modelStage5);
	objDelta1->SetModel(modelDelta1);
	objDelta2->SetModel(modelDelta2);
	objDelta3->SetModel(modelDelta3);
	objDelta4->SetModel(modelDelta4);
	objDelta5->SetModel(modelDelta5);
	objDelta6->SetModel(modelDelta6);
	// 球の初期値を設定
	sphere.center = XMVectorSet(zikipos.x, zikipos.y, zikipos.z, 1);// 中心点座標
	sphere.radius = 1.0f; // 半径
	
	// 平面の初期値を設定
	//plane.normal = XMVectorSet(0, 1, 0, 0); // 法線ベクトル
	//plane.distance = 0.0f; // 原点(0,0,0)からの距離

	//三角形の初期値を設定
	//stage1
	{
		//左辺
		triangleM1.p0 = XMVectorSet(-7, 3.5f, stage1z, 1);
		triangleM1.p1 = XMVectorSet(-7, -10, stage1z, 1);
		triangleM1.p2 = XMVectorSet(-5.7f, -3.3f, stage1z, 1);
		//右辺
		triangleM2.p0 = XMVectorSet(7, 3.5f, stage1z, 1);
		triangleM2.p1 = XMVectorSet(7, -10, stage1z, 1);
		triangleM2.p2 = XMVectorSet(5.7f, -3.3f, stage1z, 1);
		//上
		triangleM3.p0 = XMVectorSet(-7, 3.5f, stage1z, 1);
		triangleM3.p1 = XMVectorSet(7, 3.5f, stage1z, 1);
		triangleM3.p2 = XMVectorSet(0, 2.1f, stage1z, 1);
		//下
		triangleM4.p0 = XMVectorSet(-7, -10.5, stage1z, 1);
		triangleM4.p1 = XMVectorSet(7, -10.5, stage1z, 1);
		triangleM4.p2 = XMVectorSet(0, -9.1f, stage1z, 1);
		//真ん中縦1
		triangleM7.p0 = XMVectorSet(-1.9f, 1, stage1z, 1);
		triangleM7.p1 = XMVectorSet(2, 1, stage1z, 1);
		triangleM7.p2 = XMVectorSet(-2, -8, stage1z, 1);
		//真ん中縦2
		triangleM8.p0 = XMVectorSet(-2, -8, stage1z, 1);
		triangleM8.p1 = XMVectorSet(2, -8, stage1z, 1);
		triangleM8.p2 = XMVectorSet(2, 1, stage1z, 1);
		//真ん中横1
		triangleM5.p0 = XMVectorSet(-4.6f, -1.6f, stage1z, 1);
		triangleM5.p1 = XMVectorSet(-4.6f, -5.3f, stage1z, 1);
		triangleM5.p2 = XMVectorSet(4.5f, -5.3f, stage1z, 1);
		//真ん中横2
		triangleM6.p0 = XMVectorSet(-4.6f, -1.6f, stage1z, 1);
		triangleM6.p1 = XMVectorSet(4.5f, -5.3f, stage1z, 1);
		triangleM6.p2 = XMVectorSet(4.5f, -1.6f, stage1z, 1);
	}
	//stage2
	{
		//上1
		triangle2M1.p0 = XMVectorSet(-6.9f, 3.5f, stage2z, 1);
		triangle2M1.p1 = XMVectorSet(-6.9f,-0.5f, stage2z, 1);
		triangle2M1.p2 = XMVectorSet(6.9f, 3.5f, stage2z, 1);
		//上2
		triangle2M2.p0 = XMVectorSet(6.9f,3.5f, stage2z, 1);
		triangle2M2.p1 = XMVectorSet(-6.9f,-0.5f, stage2z, 1);
		triangle2M2.p2 = XMVectorSet(6.9f,-0.5f, stage2z, 1);
		//下1
		triangle2M3.p0 = XMVectorSet(-6.9f,-6.6f, stage2z, 1);
		triangle2M3.p1 = XMVectorSet(6.9f,-6.6f, stage2z, 1);
		triangle2M3.p2 = XMVectorSet(6.9f,-10.20f, stage2z, 1);
		//下2
		triangle2M4.p0 = XMVectorSet(6.9f,-10.20f, stage2z, 1);
		triangle2M4.p1 = XMVectorSet(-6.9f,-10.20f, stage2z, 1);
		triangle2M4.p2 = XMVectorSet(-6.9f,-6.6f, stage2z, 1);
		//右1
		triangle2M5.p0 = XMVectorSet(6.9f,-10.20f, stage2z, 1);
		triangle2M5.p1 = XMVectorSet(3,-10.20f, stage2z, 1);
		triangle2M5.p2 = XMVectorSet(3,3.5f, stage2z, 1);
		//右2
		triangle2M6.p0 = XMVectorSet(3,3.5f, stage2z, 1);
		triangle2M6.p1 = XMVectorSet(6.9f,3.5f, stage2z, 1);
		triangle2M6.p2 = XMVectorSet(6.9f,-10.20f, stage2z, 1);
		//左1
		triangle2M7.p0 = XMVectorSet(-6.9f,-10.20f, stage2z, 1);
		triangle2M7.p1 = XMVectorSet(-6.9f,3.5f, stage2z, 1);
		triangle2M7.p2 = XMVectorSet(-3,3.5f, stage2z, 1);
		//左2
		triangle2M8.p0 = XMVectorSet(-3,3.5f, stage2z, 1);
		triangle2M8.p1 = XMVectorSet(-3,-10.20f, stage2z, 1);
		triangle2M8.p2 = XMVectorSet(-6.9f,-10.20f, stage2z, 1);
	}
	//stage3
	{
		//左1
		triangle3M1.p0 = XMVectorSet(-6.9f, 3.5f, stage3z, 1);
		triangle3M1.p1 = XMVectorSet(-6.9f, -10.4f, stage3z, 1);
		triangle3M1.p2 = XMVectorSet(1.9f, -10.4f, stage3z, 1);
		//左2
		triangle3M2.p0 = XMVectorSet(-6.9f, 3.5f, stage3z, 1);
		triangle3M2.p1 = XMVectorSet(1.9f, -10.3f, stage3z, 1);
		triangle3M2.p2 = XMVectorSet(1.9f, 3.5f, stage3z, 1);
		//右1
		triangle3M3.p0 = XMVectorSet(2.9f, 3.6f, stage3z, 1);
		triangle3M3.p1 = XMVectorSet(2.9f, -5.3f, stage3z, 1);
		triangle3M3.p2 = XMVectorSet(7, -5.3f, stage3z, 1);
		//右2
		triangle3M4.p0 = XMVectorSet(2.9f, 3.6f, stage3z, 1);
		triangle3M4.p1 = XMVectorSet(7, -5.3f, stage3z, 1);
		triangle3M4.p2 = XMVectorSet(7, 3.5f, stage3z, 1);
	}
	//stage4
	{
		//上1
		triangle4M1.p0 = XMVectorSet(-6.9f, 3.5f, stage4z, 1);
		triangle4M1.p1 = XMVectorSet(-6.9f, -0.4f, stage4z, 1);
		triangle4M1.p2 = XMVectorSet(-2.9f, -0.4f, stage4z, 1);
		//上2
		triangle4M2.p0 = XMVectorSet(-6.9f, 3.5f, stage4z, 1);
		triangle4M2.p1 = XMVectorSet(-2.9f, -0.4f, stage4z, 1);
		triangle4M2.p2 = XMVectorSet(-2.9f, 3.5f, stage4z, 1);
		//下1
		triangle4M3.p0 = XMVectorSet(-6.9f, -6.5f, stage4z, 1);
		triangle4M3.p1 = XMVectorSet(-6.9f, -10.3f, stage4z, 1);
		triangle4M3.p2 = XMVectorSet(-2.9f, -6.5f, stage4z, 1);
		//下2
		triangle4M4.p0 = XMVectorSet(-2.9f, -6.5f, stage4z, 1);
		triangle4M4.p1 = XMVectorSet(-6.9f, -10.3f, stage4z, 1);
		triangle4M4.p2 = XMVectorSet(-2.9f, -10.3f, stage4z, 1);
		//右1
		triangle4M5.p0 = XMVectorSet(-1.9f, 3.5f, stage4z, 1);
		triangle4M5.p1 = XMVectorSet(-1.9f, -10.3f, stage4z, 1);
		triangle4M5.p2 = XMVectorSet(6.9f, -10.3f, stage4z, 1);
		//右2
		triangle4M6.p0 = XMVectorSet(-1.9f, 3.5f, stage4z, 1);
		triangle4M6.p1 = XMVectorSet(6.9f, -10.3f, stage4z, 1);
		triangle4M6.p2 = XMVectorSet(7, 3.5f, stage4z, 1);
	}
}

void GameScene::Reset()
{
	Delta1pos = { -3.0f,0.0f,0.0f };
	Delta2pos = { -3.0f,0.0f,0.0f };
	Delta3pos = { 0.0f,-4.0f,0.0f };
	Delta4pos = { 0.0f,-4.0f,0.0f };
	Delta5pos = { 3.5f,0.8f,0.0f };
	Delta6pos = { 3.5f,0.8f,0.0f };
}

void GameScene::Update()
{
	zikipos = objZiki->GetPosition();
	zikipos2 = objZiki2->GetPosition();
	Blockpos = objBlock->GetPosition();
	Blockpos2 = objBlock2->GetPosition();
	Blockpos3 = objBlock3->GetPosition();
	Stage4pos = objStage4->GetPosition();
	Stage5pos = objStage5->GetPosition();
	Delta1pos = objDelta1->GetPosition();
	Delta2pos = objDelta2->GetPosition();
	Delta3pos = objDelta3->GetPosition();
	Delta4pos = objDelta4->GetPosition();
	Delta5pos = objDelta5->GetPosition();
	Delta6pos = objDelta6->GetPosition();

	sphere.center = XMVectorSet(zikipos.x, zikipos.y, zikipos.z, 1);
	
	objSkydome->Update();
	objGround->Update();
	objZiki->Update();
	objZiki2->Update();
	objBlock->Update();
	objBlock2->Update();
	objBlock3->Update();
	objStage4->Update();
	objStage5->Update();
	objDelta1->Update();
	objDelta2->Update();
	objDelta3->Update();
	objDelta4->Update();
	objDelta5->Update();
	objDelta6->Update();
	objDelta1->SetRotation({ 0,0,60 });
	objDelta2->SetRotation({ 0,0,60 });
	objDelta5->SetRotation({ 0,0,125 });
	objDelta6->SetRotation({ 0,0,125 });
	objBlock->SetRotation({ -90,0,0 });
	objBlock->SetScale({ 3,1,3 });
	objBlock2->SetRotation({ -90,0,0 });
	objBlock2->SetScale({ 3,1,3 });
	objBlock3->SetRotation({ -90,0,0 });
	objBlock3->SetScale({ 3,1,3 });
	objStage4->SetRotation({ -90,0,0 });
	objStage4->SetScale({ 3,1,3 });
	/*Object3d::SetEye({ 0.0f, 3.0f, -10.0f });
	Object3d::SetTarget({ 0,0,0 });*/
	
	//自機移動処理
	{
		if (input->PushKey(DIK_LEFT))
		{
			if (zikipos.x > -9)
			{
				zikipos.x -= 0.1f;
			}
		}
		if (input->PushKey(DIK_RIGHT))
		{
			if (zikipos.x < 9)
			{
				zikipos.x += 0.1f;
			}
		}
		if (input->PushKey(DIK_UP))
		{
			if (zikipos.y < 6)
			{
				zikipos.y += 0.1f;
			}
		}
		if (input->PushKey(DIK_DOWN))
		{
			if (zikipos.y > -12)
			{
				zikipos.y -= 0.1f;
			}
		}
		if (input->PushKey(DIK_W))
		{
			zikipos.z -= 0.1f;
		}
		if (input->PushKey(DIK_S))
		{
			zikipos.z += 0.1f;
		}
		
		//自機２移動処理
		zikipos2 = zikipos;

		if (input->TriggerKey(DIK_SPACE) && charaChange == false)
		{
			charaChange = true;
		}
		else if (input->TriggerKey(DIK_SPACE) && charaChange == true)
		{
			charaChange = false;
		}
	}

	//古い当たり判定
	{
		//if (zikipos.x <= Blockpos.x+5&&
	//	Blockpos.x <= zikipos.x+5&&
	//	zikipos.y <= Blockpos.y+2&&
	//	Blockpos.y <= zikipos.y+2&&
	//	zikipos.z <= Blockpos.z+1&&
	//	Blockpos.z <= zikipos.z+1)
	//{
	//	zikipos.z = Blockpos.z-1;
	//}
	//if (zikipos.x <= Blockpos2.x + 5 &&
	//	Blockpos2.x <= zikipos.x + 5 &&
	//	zikipos.y <= Blockpos2.y + 2 &&
	//	Blockpos2.y <= zikipos.y + 2 &&
	//	zikipos.z <= Blockpos2.z + 1 &&
	//	Blockpos2.z <= zikipos.z + 1)
	//{
	//	zikipos.z = Blockpos2.z - 1;
	//}
	//if (zikipos.x <= Blockpos3.x + 5 &&
	//	Blockpos3.x <= zikipos.x + 5 &&
	//	zikipos.y <= Blockpos3.y + 2 &&
	//	Blockpos3.y <= zikipos.y + 2 &&
	//	zikipos.z <= Blockpos3.z + 1 &&
	//	Blockpos3.z <= zikipos.z + 1)
	//{
	//	zikipos.z = Blockpos3.z - 1;
	//}
	}

	//Delta当たり判定処理
	{
		/*XMVECTOR inter;
		bool hit = Collision::CheckSphere2Triangle(sphere, triangle, &inter);
		if (hit) {
			debugText.Print("HIT", 50, 200, 1.0f);
			zikipos.z = Delta1pos.z - 1;
		}

		XMVECTOR inter2;
		bool hit2 = Collision::CheckSphere2Triangle(sphere, triangle2, &inter2);
		if (hit2) {
			debugText.Print("HIT", 50, 220, 1.0f);
			zikipos.z = Delta2pos.z - 1;
		}

		XMVECTOR inter3;
		bool hit3 = Collision::CheckSphere2Triangle(sphere, triangle3, &inter3);
		if (hit3) {
			debugText.Print("HIT", 50, 240, 1.0f);
			zikipos.z = Delta3pos.z - 1;
		}*/
	}
	
	//ステージ１当たり判定処理
	{
		XMVECTOR stage1;
		bool Mhit = Collision::CheckSphere2Triangle(sphere, triangleM1, &stage1);
		if (Mhit) {
			debugText.Print("1HIT", 50, 260, 1.0f);
			zikipos.z = Blockpos.z - 1;
		}

		XMVECTOR stage2;
		bool Mhit2 = Collision::CheckSphere2Triangle(sphere, triangleM2, &stage2);
		if (Mhit2) {
			debugText.Print("2HIT", 50, 280, 1.0f);
			zikipos.z = Blockpos.z - 1;
		}

		XMVECTOR stage3;
		bool Mhit3 = Collision::CheckSphere2Triangle(sphere, triangleM3, &stage3);
		if (Mhit3) {
			debugText.Print("3HIT", 50, 300, 1.0f);
			zikipos.z = Blockpos.z - 1;
		}

		XMVECTOR stage4;
		bool Mhit4 = Collision::CheckSphere2Triangle(sphere, triangleM4, &stage4);
		if (Mhit4) {
			debugText.Print("4HIT", 50, 320, 1.0f);
			zikipos.z = Blockpos.z - 1;
		}

		XMVECTOR stage5;
		bool Mhit5 = Collision::CheckSphere2Triangle(sphere, triangleM5, &stage5);
		if (Mhit5) {
			debugText.Print("5HIT", 50, 340, 1.0f);
			zikipos.z = Blockpos.z - 1;
		}

		XMVECTOR stage6;
		bool Mhit6 = Collision::CheckSphere2Triangle(sphere, triangleM6, &stage6);
		if (Mhit6) {
			debugText.Print("6HIT", 50, 360, 1.0f);
			zikipos.z = Blockpos.z - 1;
		}

		XMVECTOR stage7;
		bool Mhit7 = Collision::CheckSphere2Triangle(sphere, triangleM7, &stage7);
		if (Mhit7) {
			debugText.Print("7HIT", 50, 400, 1.0f);
			zikipos.z = Blockpos.z - 1;
		}

		XMVECTOR stage8;
		bool Mhit8 = Collision::CheckSphere2Triangle(sphere, triangleM8, &stage8);
		if (Mhit8) {
			debugText.Print("8HIT", 50, 420, 1.0f);
			zikipos.z = Blockpos.z - 1;
		}
	}
	//ステージ2当たり判定処理
	{
		XMVECTOR M2stage1;
		bool M2hit = Collision::CheckSphere2Triangle(sphere, triangle2M1, &M2stage1);
		if (M2hit) {
			debugText.Print("1HIT", 50, 260, 1.0f);
			zikipos.z = Blockpos2.z - 1;
		}

		XMVECTOR M2stage2;
		bool M2hit2 = Collision::CheckSphere2Triangle(sphere, triangle2M2, &M2stage2);
		if (M2hit2) {
			debugText.Print("2HIT", 50, 280, 1.0f);
			zikipos.z = Blockpos2.z - 1;
		}

		XMVECTOR M2stage3;
		bool M2hit3 = Collision::CheckSphere2Triangle(sphere, triangle2M3, &M2stage3);
		if (M2hit3) {
			debugText.Print("3HIT", 50, 300, 1.0f);
			zikipos.z = Blockpos2.z - 1;
		}

		XMVECTOR M2stage4;
		bool M2hit4 = Collision::CheckSphere2Triangle(sphere, triangle2M4, &M2stage4);
		if (M2hit4) {
			debugText.Print("4HIT", 50, 320, 1.0f);
			zikipos.z = Blockpos2.z - 1;
		}

		XMVECTOR M2stage5;
		bool M2hit5 = Collision::CheckSphere2Triangle(sphere, triangle2M5, &M2stage5);
		if (M2hit5) {
			debugText.Print("5HIT", 50, 340, 1.0f);
			zikipos.z = Blockpos2.z - 1;
		}

		XMVECTOR M2stage6;
		bool M2hit6 = Collision::CheckSphere2Triangle(sphere, triangle2M6, &M2stage6);
		if (M2hit6) {
			debugText.Print("6HIT", 50, 360, 1.0f);
			zikipos.z = Blockpos2.z - 1;
		}

		XMVECTOR M2stage7;
		bool M2hit7 = Collision::CheckSphere2Triangle(sphere, triangle2M7, &M2stage7);
		if (M2hit7) {
			debugText.Print("7HIT", 50, 400, 1.0f);
			zikipos.z = Blockpos2.z - 1;
		}

		XMVECTOR M2stage8;
		bool M2hit8 = Collision::CheckSphere2Triangle(sphere, triangle2M8, &M2stage8);
		if (M2hit8) {
			debugText.Print("8HIT", 50, 420, 1.0f);
			zikipos.z = Blockpos2.z - 1;
		}
	}
	//ステージ3当たり判定処理
	{
		XMVECTOR M3stage1;
		bool M3hit = Collision::CheckSphere2Triangle(sphere, triangle3M1, &M3stage1);
		if (M3hit) {
			debugText.Print("1HIT", 50, 260, 1.0f);
			zikipos.z = Blockpos3.z - 1;
		}

		XMVECTOR M3stage2;
		bool M3hit2 = Collision::CheckSphere2Triangle(sphere, triangle3M2, &M3stage2);
		if (M3hit2) {
			debugText.Print("2HIT", 50, 280, 1.0f);
			zikipos.z = Blockpos3.z - 1;
		}

		XMVECTOR M3stage3;
		bool M3hit3 = Collision::CheckSphere2Triangle(sphere, triangle3M3, &M3stage3);
		if (M3hit3) {
			debugText.Print("3HIT", 50, 300, 1.0f);
			zikipos.z = Blockpos3.z - 1;
		}

		XMVECTOR M3stage4;
		bool M3hit4 = Collision::CheckSphere2Triangle(sphere, triangle3M4, &M3stage4);
		if (M3hit4) {
			debugText.Print("4HIT", 50, 320, 1.0f);
			zikipos.z = Blockpos3.z - 1;
		}
	}
	//ステージ4当たり判定処理
	{
		XMVECTOR M4stage1;
		bool M4hit = Collision::CheckSphere2Triangle(sphere, triangle4M1, &M4stage1);
		if (M4hit) {
			debugText.Print("1HIT", 50, 260, 1.0f);
			zikipos.z = Stage4pos.z - 1;
		}

		XMVECTOR M4stage2;
		bool M4hit2 = Collision::CheckSphere2Triangle(sphere, triangle4M2, &M4stage2);
		if (M4hit2) {
			debugText.Print("2HIT", 50, 280, 1.0f);
			zikipos.z = Stage4pos.z - 1;
		}

		XMVECTOR M4stage3;
		bool M4hit3 = Collision::CheckSphere2Triangle(sphere, triangle4M3, &M4stage3);
		if (M4hit3) {
			debugText.Print("3HIT", 50, 300, 1.0f);
			zikipos.z = Stage4pos.z - 1;
		}

		XMVECTOR M4stage4;
		bool M4hit4 = Collision::CheckSphere2Triangle(sphere, triangle4M4, &M4stage4);
		if (M4hit4) {
			debugText.Print("4HIT", 50, 320, 1.0f);
			zikipos.z = Stage4pos.z - 1;
		}

		XMVECTOR M4stage5;
		bool M4hit5 = Collision::CheckSphere2Triangle(sphere, triangle4M5, &M4stage5);
		if (M4hit5) {
			debugText.Print("5HIT", 50, 340, 1.0f);
			zikipos.z = Stage4pos.z - 1;
		}

		XMVECTOR M4stage6;
		bool M4hit6 = Collision::CheckSphere2Triangle(sphere, triangle4M6, &M4stage6);
		if (M4hit6) {
			debugText.Print("6HIT", 50, 360, 1.0f);
			zikipos.z = Stage4pos.z - 1;
		}
	}

	//三角形コメント
	{
		std::ostringstream tri1;
		tri1 << "ziki"
			<< "("
			<< std::fixed << std::setprecision(2)
			<< zikipos.x << ","
			<< zikipos.y << ","
			<< zikipos.z << ")";

		debugText.Print(tri1.str(), 50, 150, 1.0f);
	}
	
	
	//三角形当たり判定座標
	{
		triangle.p0 = XMVectorSet(-5, -4, delta1z, 1);//左手前
		triangle.p1 = XMVectorSet(-6, -4, delta1z, 1);//右奥
		triangle.p2 = XMVectorSet(-1, 4.1f, delta1z, 1);//右手前

		triangle2.p0 = XMVectorSet(-4.7f, -2.7f, delta1z, 1);//左手前
		triangle2.p1 = XMVectorSet(-4.7f, -4.1f, delta1z, 1);//右奥
		triangle2.p2 = XMVectorSet(4.9f, -4.1f, delta1z, 1);//右手前

		triangle3.p0 = XMVectorSet(-0.3f, 3.8f, delta1z, 1);//左手前
		triangle3.p1 = XMVectorSet(0.9f, 4.1f, delta1z, 1);//右奥
		triangle3.p2 = XMVectorSet(6, -3.8f, delta1z, 1);//右手前
	}

	//ステージ１当たり判定座標、Z座標注意
	{
		////左辺
		//triangleM1.p0 = XMVectorSet(-7, 3.5f, stage1z, 1);
		//triangleM1.p1 = XMVectorSet(-7, -10, stage1z, 1);
		//triangleM1.p2 = XMVectorSet(-5.7f, -3.3f, stage1z, 1);
		////右辺
		//triangleM2.p0 = XMVectorSet(7, 3.5f, stage1z, 1);
		//triangleM2.p1 = XMVectorSet(7, -10, stage1z, 1);
		//triangleM2.p2 = XMVectorSet(5.7f, -3.3f, stage1z, 1);
		////上
		//triangleM3.p0 = XMVectorSet(-7, 3.5f, stage1z, 1);
		//triangleM3.p1 = XMVectorSet(7, 3.5f, stage1z, 1);
		//triangleM3.p2 = XMVectorSet(0, 2.1f, stage1z, 1);
		////下
		//triangleM4.p0 = XMVectorSet(-7, -10.5f, stage1z, 1);
		//triangleM4.p1 = XMVectorSet(7, -10.5f, stage1z, 1);
		//triangleM4.p2 = XMVectorSet(0, -9.1f, stage1z, 1);
		////真ん中縦1
		//triangleM7.p0 = XMVectorSet(-1.9f,1, stage1z, 1);
		//triangleM7.p1 = XMVectorSet(2,1, stage1z, 1);
		//triangleM7.p2 = XMVectorSet(-2,-8, stage1z, 1);
		////真ん中縦2
		//triangleM8.p0 = XMVectorSet(-2,-8, stage1z, 1);
		//triangleM8.p1 = XMVectorSet(2,-8, stage1z, 1);
		//triangleM8.p2 = XMVectorSet(2,1, stage1z, 1);
		////真ん中横1
		//triangleM5.p0 = XMVectorSet(-4.6f,-1.6f, stage1z, 1);
		//triangleM5.p1 = XMVectorSet(-4.6f,-5.3f, stage1z, 1);
		//triangleM5.p2 = XMVectorSet(4.5f,-5.3f, stage1z, 1);
		////真ん中横2
		//triangleM6.p0 = XMVectorSet(-4.6f,-1.6f, stage1z, 1);
		//triangleM6.p1 = XMVectorSet(4.5f,-5.3f, stage1z, 1);
		//triangleM6.p2 = XMVectorSet(4.5f,-1.6f, stage1z, 1);
	}
	//ステージ2当たり判定座標、Z座標注意
	{
		//上1
		triangle2M1.p0 = XMVectorSet(-6.9f, 3.5f, stage2z, 1);
		triangle2M1.p1 = XMVectorSet(-6.9f, -0.5f, stage2z, 1);
		triangle2M1.p2 = XMVectorSet(6.9f, 3.5f, stage2z, 1);
		//上2
		triangle2M2.p0 = XMVectorSet(6.9f, 3.5f, stage2z, 1);
		triangle2M2.p1 = XMVectorSet(-6.9f, -0.5f, stage2z, 1);
		triangle2M2.p2 = XMVectorSet(6.9f, -0.5f, stage2z, 1);
		//下1
		triangle2M3.p0 = XMVectorSet(-6.9f, -6.6f, stage2z, 1);
		triangle2M3.p1 = XMVectorSet(6.9f, -6.6f, stage2z, 1);
		triangle2M3.p2 = XMVectorSet(6.9f, -10.20f, stage2z, 1);
		//下2
		triangle2M4.p0 = XMVectorSet(6.9f, -10.20f, stage2z, 1);
		triangle2M4.p1 = XMVectorSet(-6.9f, -10.20f, stage2z, 1);
		triangle2M4.p2 = XMVectorSet(-6.9f, -6.6f, stage2z, 1);
		//右1
		triangle2M5.p0 = XMVectorSet(6.9f, -10.20f, stage2z, 1);
		triangle2M5.p1 = XMVectorSet(3, -10.20f, stage2z, 1);
		triangle2M5.p2 = XMVectorSet(3, 3.5f, stage2z, 1);
		//右2
		triangle2M6.p0 = XMVectorSet(3, 3.5f, stage2z, 1);
		triangle2M6.p1 = XMVectorSet(6.9f, 3.5f, stage2z, 1);
		triangle2M6.p2 = XMVectorSet(6.9f, -10.20f, stage2z, 1);
		//左1
		triangle2M7.p0 = XMVectorSet(-6.9f, -10.20f, stage2z, 1);
		triangle2M7.p1 = XMVectorSet(-6.9f, 3.5f, stage2z, 1);
		triangle2M7.p2 = XMVectorSet(-3, 3.5f, stage2z, 1);
		//左2
		triangle2M8.p0 = XMVectorSet(-3, 3.5f, stage2z, 1);
		triangle2M8.p1 = XMVectorSet(-3, -10.20f, stage2z, 1);
		triangle2M8.p2 = XMVectorSet(-6.9f, -10.20f, stage2z, 1);
	}
	//ステージ3当たり判定座標、Z座標注意
	{
		//左1
		triangle3M1.p0 = XMVectorSet(-6.9f, 3.5f, stage3z, 1);
		triangle3M1.p1 = XMVectorSet(-6.9f, -10.4f, stage3z, 1);
		triangle3M1.p2 = XMVectorSet(1.9f, -10.4f, stage3z, 1);
		//左2
		triangle3M2.p0 = XMVectorSet(-6.9f, 3.5f, stage3z, 1);
		triangle3M2.p1 = XMVectorSet(1.9f, -10.3f, stage3z, 1);
		triangle3M2.p2 = XMVectorSet(1.9f, 3.5f, stage3z, 1);
		//右1
		triangle3M3.p0 = XMVectorSet(2.9f, 3.6f, stage3z, 1);
		triangle3M3.p1 = XMVectorSet(2.9f, -5.3f, stage3z, 1);
		triangle3M3.p2 = XMVectorSet(7, -5.3f, stage3z, 1);
		//右2
		triangle3M4.p0 = XMVectorSet(2.9f, 3.6f, stage3z, 1);
		triangle3M4.p1 = XMVectorSet(7, -5.3f, stage3z, 1);
		triangle3M4.p2 = XMVectorSet(7, 3.5f, stage3z, 1);
	}
	//ステージ4当たり判定座標、Z座標注意
	{
		//上1
		triangle4M1.p0 = XMVectorSet(-6.9f, 3.5f, stage4z, 1);
		triangle4M1.p1 = XMVectorSet(-6.9f, -0.4f, stage4z, 1);
		triangle4M1.p2 = XMVectorSet(-2.9f, -0.4f, stage4z, 1);
		//上2
		triangle4M2.p0 = XMVectorSet(-6.9f, 3.5f, stage4z, 1);
		triangle4M2.p1 = XMVectorSet(-2.9f, -0.4f, stage4z, 1);
		triangle4M2.p2 = XMVectorSet(-2.9f, 3.5f, stage4z, 1);
		//下1
		triangle4M3.p0 = XMVectorSet(-6.9f, -6.5f, stage4z, 1);
		triangle4M3.p1 = XMVectorSet(-6.9f, -10.3f, stage4z, 1);
		triangle4M3.p2 = XMVectorSet(-2.9f, -6.5f, stage4z, 1);
		//下2
		triangle4M4.p0 = XMVectorSet(-2.9f, -6.5f, stage4z, 1);
		triangle4M4.p1 = XMVectorSet(-6.9f, -10.3f, stage4z, 1);
		triangle4M4.p2 = XMVectorSet(-2.9f, -10.3f, stage4z, 1);
		//右1
		triangle4M5.p0 = XMVectorSet(-1.9f, 3.5f, stage4z, 1);
		triangle4M5.p1 = XMVectorSet(-1.9f, -10.3f, stage4z, 1);
		triangle4M5.p2 = XMVectorSet(6.9f, -10.3f, stage4z, 1);
		//右2
		triangle4M6.p0 = XMVectorSet(-1.9f, 3.5f, stage4z, 1);
		triangle4M6.p1 = XMVectorSet(6.9f, -10.3f, stage4z, 1);
		triangle4M6.p2 = XMVectorSet(7, 3.5f, stage4z, 1);
	}

	//回転処理
	{
		radius = angle * 3.14f / 180.0f;
		add_X = cos(radius)*length;
		add_Y = sin(radius)*length;
		
		Blockpos.x = centerX + add_X;
		Blockpos.y = centerY + add_Y;
		/*Blockpos2.x = centerX + add_X;
		Blockpos2.y = centerY + add_Y;
		Blockpos3.x = centerX + add_X;
		Blockpos3.y = centerY + add_Y;*/

		//triangle.p0 = XMVectorSet(-5 + centerX + add_X, -4 + centerY + add_Y, delta1z, 1);//左手前
		//triangle.p1 = XMVectorSet(-6 + centerX + add_X, -4 + centerY + add_Y, delta1z, 1);//右奥
		//triangle.p2 = XMVectorSet(-1 + centerX + add_X, 4.1f + centerY + add_Y, delta1z, 1);//右手前

		

		angle += 0.5f;
	}


	//画面に迫ってくる処理
	/*Delta1pos.z -= 0.01f;
	Delta2pos.z -= 0.01f;
	Delta3pos.z -= 0.01f;
	Delta4pos.z -= 0.01f;
	Delta5pos.z -= 0.01f;
	Delta6pos.z -= 0.01f;
	
	delta1z -= 0.01f;
	delta2z -= 0.01f;
	delta3z -= 0.01f;*/

	//画面に迫ってくる処理
	////stage1
	//if (stage1z < 20)
	//{
	//	Blockpos.y -= 0.03f;
	//	Blockpos.z -= 0.03f;
	//}
	//stage1z -= stagevel;
	//Blockpos.z -= stagevel;
	////stage2
	//if (Blockpos2.y <= -3.0f)
	//{
	//	Blockpos2.y += 0.01f;
	//}
	//
	//if (stage2z < 20)
	//{
	//	Blockpos2.y -= 0.04f;
	//	Blockpos2.z -= 0.03f;
	//}
	//stage2z -= stagevel;
	//Blockpos2.z -= stagevel;
	////stage3
	//if (Blockpos3.y <= -3.0f)
	//{
	//	Blockpos3.y += 0.01f;
	//}
	//
	//if (stage3z < 20)
	//{
	//	Blockpos3.y -= 0.04f;
	//	Blockpos3.z -= 0.03f;
	//}
	//stage3z -= stagevel;
	//Blockpos3.z -= stagevel;
	////stage4
	//if (Stage4pos.y <= -3.0f)
	//{
	//	Stage4pos.y += 0.01f;
	//}
	//
	//if (stage4z < 20)
	//{
	//	Stage4pos.y -= 0.04f;
	//	Stage4pos.z -= 0.03f;
	//}
	//stage4z -= stagevel;
	//Stage4pos.z -= stagevel;
	//stage5

	if (input->PushKey(DIK_Z))
	{
		stagevel = 0.001f;
	}
	else
	{
		stagevel = 0.01f;
	}

	if (zikipos.z < 20)
	{
		zikipos.z = 29;
	}
	
	objZiki->SetPosition(zikipos);
	objZiki2->SetPosition(zikipos2);
	objBlock->SetPosition(Blockpos);
	objBlock2->SetPosition(Blockpos2);
	objBlock3->SetPosition(Blockpos3);
	objStage4->SetPosition(Stage4pos);
	objStage5->SetPosition(Stage5pos);
	objDelta1->SetPosition(Delta1pos);
	objDelta2->SetPosition(Delta2pos);
	objDelta3->SetPosition(Delta3pos);
	objDelta4->SetPosition(Delta4pos);
	objDelta5->SetPosition(Delta5pos);
	objDelta6->SetPosition(Delta6pos);
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	//spriteBG->Draw();

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(cmdList);

	
	// 3Dオブクジェクトの描画
	objSkydome->Draw();
	//objGround->Draw();
	if (charaChange == true)
	{
		objZiki2->Draw();
	}
	if (charaChange == false)
	{
		objZiki->Draw();
	}	

	objBlock->Draw();
	objBlock2->Draw();
	objBlock3->Draw();
	objStage4->Draw();
	
	//objStage5->Draw();
	objDelta1->Draw();
	objDelta2->Draw();
	objDelta3->Draw();
	objDelta4->Draw();
	objDelta5->Draw();
	objDelta6->Draw();
	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	//// 描画
	//sprite1->Draw();
	//sprite2->Draw();

	// デバッグテキストの描画
	debugText.DrawAll(cmdList);

	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}
