
#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include"ImGuiManager.h"
#include"PrimitiveDrawer.h"
#include"AxisIndicator.h"
#include <fstream>
GameScene::GameScene() {}

GameScene::~GameScene() {
	
	delete player_;
	delete playerModel_;
	delete ViewProjection_;
	delete enemyModel_;
	delete debugCamera_;
	delete skydome_;
	delete modelSkydome_;
	delete railCamera_;
	for (EnemyBullet* bullet : enemyBullets_) {
		delete bullet;
	}
	for (Enemy* enemy : enemies_) {
		delete enemy;
	}
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	player_ = new Player();
	playerModel_ = new Model();
	ViewProjection_ = new ViewProjection();

	//TextureManager::Load("./Resources/reticle.png");

	uint32_t playerTextureHandle = TextureManager::Load("./Resources/sample.png");

	playerModel_ = Model::Create();
	ViewProjection_->Initialize();
	
	

	
	enemyModel_ = new Model();
	enemyModel_ = Model::Create();
	LoadEnemyPopData();
	debugCamera_ = new DebugCamera(1920, 1080);

	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());


	skydome_ = new Skydome();

	modelSkydome_ = Model::CreateFromOBJ("skydome", true);

	skydome_->Initialize(modelSkydome_, ViewProjection_);

	railCamera_ = new RailCamera();
	railCamera_->Initialize();
	
	player_->SetParent(&railCamera_->GetWorldTransform());

	Vector3 playerPosition(0, 0, 50.0f);
	player_->Initialize(playerModel_, playerTextureHandle, ViewProjection_, playerPosition);
	
}

void GameScene::Update() {

	player_->Update();
	railCamera_->Update(); 

	#ifdef _DEBUG
	if (input_->TriggerKey(DIK_Q)) {
		isDebugCameraActive_ ^= true;
	}
	if (isDebugCameraActive_) {
		debugCamera_->Update();
		ViewProjection_->matView = debugCamera_->GetViewProjection().matView;
		ViewProjection_->matProjection = debugCamera_->GetViewProjection().matProjection;
		ViewProjection_->TransferMatrix();
	} else {
		ViewProjection_->UpdateMatrix();
		ViewProjection_->matView = railCamera_->GetViewProjection().matView;
		ViewProjection_->matProjection = railCamera_->GetViewProjection().matProjection;
		ViewProjection_->TransferMatrix();
	}
	
    #endif

	skydome_->Update();
	UpdateEnemyPopCommands();
	for (Enemy* enemy : enemies_) {
		enemy->Update();
	}
	 for (EnemyBullet* bullet : enemyBullets_) {
		bullet->Update();
	}
	enemyBullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});
	CheckAllCollisions();
	
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	//sprite_->Draw();
	
	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	player_->Draw();

	//enemy_->Draw();

	  for (Enemy* enemy : enemies_) {
		enemy->Draw();
	}

	 for (EnemyBullet* bullet : enemyBullets_) {
		bullet->Draw();
	}


	skydome_->Draw();


	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion



#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	player_->DrawUI();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollisions() {

	Vector3 posA, posB,posC, posD;
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	//const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();
	
	posA = player_->GetWorldPosition();

	for (EnemyBullet* bullet : enemyBullets_) {
		posB = bullet->GetWorldPosition();
		float distanceSq = 
			(posB.x - posA.x) * (posB.x - posA.x) + 
			(posB.y - posA.y) * (posB.y - posA.y) + 
			(posB.z - posA.z) * (posB.z - posA.z);

		float radiusSum = player_->GetRadius() + bullet->GetRadius();

		if (distanceSq <= radiusSum * radiusSum) {
			
			bullet->OnCollision();
		}
	}

	 for (Enemy* enemy : enemies_) {
		posC = enemy->GetWorldPosition();
		for (PlayerBullet* bullet : playerBullets) {
			posB = bullet->GetWorldPosition();
			float distanceSq = (posB.x - posC.x) * (posB.x - posC.x) + (posB.y - posC.y) * (posB.y - posC.y) + (posB.z - posC.z) * (posB.z - posC.z);

			float radiusSum = enemy->GetRadius() + bullet->GetRadius();

			if (distanceSq <= radiusSum * radiusSum) {
				bullet->OnCollision();
				enemy->OnCollision();
			}
		}
	}
	
	for (EnemyBullet* enemyBullet : enemyBullets_) {
	
		for (PlayerBullet* playerBullet : playerBullets) {
			posB = enemyBullet->GetWorldPosition();
			posD = playerBullet->GetWorldPosition();
	
			float distanceSq = 
				(posB.x - posD.x) * (posB.x - posD.x) + 
				(posB.y - posD.y) * (posB.y - posD.y) + 
				(posB.z - posD.z) * (posB.z - posD.z);
	
			float radiusSum = enemyBullet->GetRadius() + playerBullet->GetRadius();
	
			if (distanceSq <= radiusSum * radiusSum) {
	
				playerBullet->OnCollision();
				enemyBullet->OnCollision();
			}
		}
	
	}



}

void GameScene::AddEnemyBullet(EnemyBullet* enemyBullet) {

	 enemyBullets_.push_back(enemyBullet);

}

void GameScene::LoadEnemyPopData() {

    std::ifstream file;
	file.open("./Resources/enemyPop.csv");
    assert(file.is_open());

    enemyPopCommands << file.rdbuf();

    file.close();

}

void GameScene::UpdateEnemyPopCommands() {


	if (isWaiting_) {
		--waitTimer_;
		if (--waitTimer_ <= 0) {
			isWaiting_ = false;
		} 
		return;
	}



std::string line;

while (getline(enemyPopCommands, line)) {

std::istringstream line_stream(line);

std::string word;

getline(line_stream, word, ',');

if (word.find("//") == 0) {
	continue;
}
if (word.find("POP") == 0) {
	getline(line_stream, word, ',');
	float x = (float)std::atof(word.c_str());

	getline(line_stream, word, ',');
	float y = (float)std::atof(word.c_str());

	getline(line_stream, word, ',');
	float z = (float)std::atof(word.c_str());

	SpawnEnemy(Vector3(x, y, z));
} else if (word.find("WAIT") == 0) {

getline(line_stream, word, ',');

int32_t waitTime = atoi(word.c_str());

  isWaiting_ = true;     
  waitTimer_ = waitTime; 

break;

}


}

}

void GameScene::SpawnEnemy(const Vector3& position) {

    Enemy* newEnemy = new Enemy();
	newEnemy->Initialize(enemyModel_, position, ViewProjection_);
	newEnemy->SetGameScene(this);
	newEnemy->SetPlayer(player_);
	enemies_.push_back(newEnemy); 

}
