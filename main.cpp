#pragma once
#include "Audio.h"
#include "AxisIndicator.h"
#include "DirectXCommon.h"
#include "GameScene.h"
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "WinApp.h"
#include "SceneState.h" 
#include "TitleScene.h"
#include "OverScene.h"
#include "EndedScene.h"
#include <Xinput.h>
#include <Player.h>
SceneState currentScene = SceneState::Title;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	WinApp* win = nullptr;
	DirectXCommon* dxCommon = nullptr;
	// 汎用機能
	Input* input = nullptr;
	Audio* audio = nullptr;
	AxisIndicator* axisIndicator = nullptr;
	PrimitiveDrawer* primitiveDrawer = nullptr;
	GameScene* gameScene = nullptr;
	TitleScene* titleScene = nullptr;
	OverScene* overScene = nullptr;
	EndedScene* endedScene = nullptr;
	// ゲームウィンドウの作成
	win = WinApp::GetInstance();
	win->CreateGameWindow(L"AL3_LE2B_21_パク_イジュン");

	// DirectX初期化処理
	dxCommon = DirectXCommon::GetInstance();
	dxCommon->Initialize(win);

	

#pragma region 汎用機能初期化
	// ImGuiの初期化
	ImGuiManager* imguiManager = ImGuiManager::GetInstance();
	imguiManager->Initialize(win, dxCommon);

	// 入力の初期化
	input = Input::GetInstance();
	input->Initialize();

	// オーディオの初期化
	audio = Audio::GetInstance();
	audio->Initialize();

	// テクスチャマネージャの初期化
	TextureManager::GetInstance()->Initialize(dxCommon->GetDevice());
	TextureManager::Load("white1x1.png");

	// スプライト静的初期化
	Sprite::StaticInitialize(dxCommon->GetDevice(), WinApp::kWindowWidth, WinApp::kWindowHeight);

	// 3Dモデル静的初期化
	Model::StaticInitialize();

	// 軸方向表示初期化
	axisIndicator = AxisIndicator::GetInstance();
	axisIndicator->Initialize();

	primitiveDrawer = PrimitiveDrawer::GetInstance();
	primitiveDrawer->Initialize();
#pragma endregion

	// ゲームシーンの初期化
	titleScene = new TitleScene();
	titleScene->Initialize();

	gameScene = new GameScene();
	gameScene->Initialize();

	overScene = new OverScene();
	overScene->Initialize();

	endedScene = new EndedScene();
	endedScene->Initialize();

	BYTE preButtons = 0;

	

	// メインループ
	while (true) {
		// メッセージ処理
		if (win->ProcessMessage()) {
			break;
		}

		// ImGui受付開始
		imguiManager->Begin();
		// 入力関連の毎フレーム処理
		input->Update();
		// ゲームシーンの毎フレーム処理

		XINPUT_STATE state;

		switch (currentScene) {
		case SceneState::Title:
			titleScene->Update();
			if (XInputGetState(0, &state) == ERROR_SUCCESS) {
				WORD currentButtons = state.Gamepad.wButtons;
				if ((preButtons & XINPUT_GAMEPAD_X) == 0 && (currentButtons & XINPUT_GAMEPAD_X) != 0) {
					currentScene = SceneState::Stage;
				}
				preButtons = static_cast<BYTE>(currentButtons); 
			}
			//if (input->TriggerKey(DIK_SPACE) && input->PushKey(DIK_SPACE)) {
			//	currentScene = SceneState::Stage;
			//}
			break;
		case SceneState::Stage:
			gameScene->Update();
			if (gameScene->GetPlayerHP() <= 0) {
				currentScene = SceneState::Over;
			} else if (gameScene->IsAllEnemiesDefeated()) {
				currentScene = SceneState::Ended;
			} else if (gameScene->IsTimeOver()) {
				currentScene = SceneState::Over;
			}
			break;
		case SceneState::Over:
			overScene->Update();
		
			if (XInputGetState(0, &state) == ERROR_SUCCESS) {
				WORD currentButtons = state.Gamepad.wButtons;
				if ((preButtons & XINPUT_GAMEPAD_Y) == 0 && (currentButtons & XINPUT_GAMEPAD_Y) != 0) {
					delete gameScene;
				
					gameScene = new GameScene();
					gameScene->Initialize();
					currentScene = SceneState::Stage;
				}
				preButtons = static_cast<BYTE>(currentButtons);
			}
			if (input->TriggerKey(DIK_SPACE) && input->PushKey(DIK_SPACE)) {
				currentScene = SceneState::Stage;
			}
			break;
		case SceneState::Ended:
			endedScene->Update();
			if (XInputGetState(0, &state) == ERROR_SUCCESS) {
				WORD currentButtons = state.Gamepad.wButtons;
				if ((preButtons & XINPUT_GAMEPAD_B) == 0 && (currentButtons & XINPUT_GAMEPAD_B) != 0) {
					delete gameScene;

					gameScene = new GameScene();
					gameScene->Initialize();
					currentScene = SceneState::Title;
				}
				preButtons = static_cast<BYTE>(currentButtons);
			}
			if (input->TriggerKey(DIK_SPACE) && input->PushKey(DIK_SPACE)) {
				currentScene = SceneState::Title;
			}
			break;
		default:
			break;
		}

		
		// 軸表示の更新
		axisIndicator->Update();
		// ImGui受付終了
		imguiManager->End();

		// 描画開始
		dxCommon->PreDraw();
		// ゲームシーンの描画

		switch (currentScene) {
		case SceneState::Title:
			titleScene->Draw();
			break;
		case SceneState::Stage:
			gameScene->Draw();
			break;
		case SceneState::Over:
			overScene->Draw();
			break;
		case SceneState::Ended:
			endedScene->Draw();
			break;
		default:
			break;
		}

		
		// 軸表示の描画
		axisIndicator->Draw();
		// プリミティブ描画のリセット
		primitiveDrawer->Reset();
		// ImGui描画
		imguiManager->Draw();
		// 描画終了
		dxCommon->PostDraw();
	}

	// 各種解放
	delete endedScene;
	delete overScene;
	delete gameScene;
	delete titleScene;
	// 3Dモデル解放
	Model::StaticFinalize();
	audio->Finalize();
	// ImGui解放
	imguiManager->Finalize();

	// ゲームウィンドウの破棄
	win->TerminateGameWindow();

	return 0;
}