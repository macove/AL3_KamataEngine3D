
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
	//delete debugCamera_;
	delete groundSpring_;
	delete modelGroundSpring_;
	delete groundSummer_;
	delete modelGroundSummer_;
	delete groundAutumn_;
	delete modelGroundAutumn_;
	delete groundWinter_;
	delete modelGroundWinter_;
	delete skyDomeSpring_;
	delete modelSkyDomeSpring_;
	delete skyDomeSummer_;
	delete modelSkyDomeSummer_;
	delete skyDomeAutumn_;
	delete modelSkyDomeAutumn_;
	delete skyDomeWinter_;
	delete modelSkyDomeWinter_;
	delete railCamera_;
	delete playerHP_;
	delete playerX_;
	delete SpriteX0_;
	delete SpriteX1_;
	delete SpriteX3_;
	delete SpriteX4_;
	delete SpriteX5_;
	delete SpriteX6_;
	delete SpriteX7_;
	delete SpriteX8_;
	delete SpriteX9_;
	delete SpriteX2_;

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
	
	

	ViewProjection_ = new ViewProjection();


	TextureManager::Load("./Resources/reticle.png");

	playerModel_ = Model::CreateFromOBJ("player", true);
	
	ViewProjection_->Initialize();
	
	enemyModel_ = Model::CreateFromOBJ("enemy", true);
	
	LoadEnemyPopData();
	//debugCamera_ = new DebugCamera(1920, 1080);
	//
	//AxisIndicator::GetInstance()->SetVisible(true);
	//AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());


	skyDomeSpring_ = new Skydome();
	modelSkyDomeSpring_ = Model::CreateFromOBJ("skyDomeSpring", true);
	skyDomeSpring_->Initialize(modelSkyDomeSpring_, ViewProjection_);

	skyDomeSummer_ = new Skydome();
	modelSkyDomeSummer_ = Model::CreateFromOBJ("skyDomeSummer", true);
	skyDomeSummer_->Initialize(modelSkyDomeSummer_, ViewProjection_);

	skyDomeAutumn_ = new Skydome();
	modelSkyDomeAutumn_ = Model::CreateFromOBJ("skyDomeAutumn", true);
	skyDomeAutumn_->Initialize(modelSkyDomeAutumn_, ViewProjection_);

	skyDomeWinter_ = new Skydome();
	modelSkyDomeWinter_ = Model::CreateFromOBJ("skyDomeWinter", true);
	skyDomeWinter_->Initialize(modelSkyDomeWinter_, ViewProjection_);

	groundSpring_ = new Ground();
	modelGroundSpring_ = Model::CreateFromOBJ("groundSpring", true);
	groundSpring_->Initialize(modelGroundSpring_, ViewProjection_);

	groundSummer_ = new Ground();
	modelGroundSummer_ = Model::CreateFromOBJ("groundSummer", true);
	groundSummer_->Initialize(modelGroundSummer_, ViewProjection_);

	groundAutumn_ = new Ground();
	modelGroundAutumn_ = Model::CreateFromOBJ("groundAutumn", true);
	groundAutumn_->Initialize(modelGroundAutumn_, ViewProjection_);

	groundWinter_ = new Ground();
	modelGroundWinter_ = Model::CreateFromOBJ("groundWinter", true);
	groundWinter_->Initialize(modelGroundWinter_, ViewProjection_);


	railCamera_ = new RailCamera();
	railCamera_->Initialize();
	
	player_->SetParent(&railCamera_->GetWorldTransform());

	Vector3 playerPosition(0, 0, 0.0f);
	player_->Initialize(playerModel_, ViewProjection_, playerPosition);
	
	playerHPSprite_ = TextureManager::Load("./Resources/playerHP.png");

	playerHP_ = Sprite::Create(playerHPSprite_, {0, 0});

	playerXSprite_ = TextureManager::Load("./Resources/playerX.png");

	playerX_ = Sprite::Create(playerXSprite_, {55, 12});

	Sprite0_ = TextureManager::Load("./Resources/0.png");
	SpriteX0_ = Sprite::Create(Sprite0_, {90, 5});

	Sprite1_ = TextureManager::Load("./Resources/1.png");
	SpriteX1_ = Sprite::Create(Sprite1_, {70, 5});

	Sprite2_ = TextureManager::Load("./Resources/2.png");
	SpriteX2_ = Sprite::Create(Sprite2_, {79, 5});

	Sprite4_ = TextureManager::Load("./Resources/4.png");
	SpriteX4_ = Sprite::Create(Sprite4_, {79, 5});

	Sprite5_ = TextureManager::Load("./Resources/5.png");
	SpriteX5_ = Sprite::Create(Sprite5_, {79, 5});

	Sprite6_ = TextureManager::Load("./Resources/6.png");
	SpriteX6_ = Sprite::Create(Sprite6_, {79, 5});

	Sprite7_ = TextureManager::Load("./Resources/7.png");
	SpriteX7_ = Sprite::Create(Sprite7_, {79, 5});

	Sprite8_ = TextureManager::Load("./Resources/8.png");
	SpriteX8_ = Sprite::Create(Sprite8_, {79, 5});

	Sprite9_ = TextureManager::Load("./Resources/9.png");
	SpriteX9_ = Sprite::Create(Sprite9_, {79, 5});

	Sprite3_ = TextureManager::Load("./Resources/3.png");
	SpriteX3_ = Sprite::Create(Sprite3_, {79, 5});

	   gameTimer_ = 0.0f;
	 maxTime_ = 7200.0f;

       isWaiting_ = false;
	  waitTimer_ = 0;
}

void GameScene::Update() {

	if (player_ != nullptr) {
		player_->Update();
	}
	railCamera_->Update(); 
	
	gameTimer_ += 1.0f; 
	

	#ifdef _DEBUG
	 
		ViewProjection_->UpdateMatrix();
		ViewProjection_->matView = railCamera_->GetViewProjection().matView;
		ViewProjection_->matProjection = railCamera_->GetViewProjection().matProjection;
		ViewProjection_->TransferMatrix();
	
	
    #endif
	if (gameTimer_ >= 0 && gameTimer_ < 1800) {
		skyDomeSpring_->Update();
	}
	if (gameTimer_ >= 1800 && gameTimer_ < 3600) {
		skyDomeSummer_->Update();
	}
	if (gameTimer_ >= 3600 && gameTimer_ < 5400) {
		skyDomeAutumn_->Update();
	}
	if (gameTimer_ >= 5400 && gameTimer_ < 7200) {
		skyDomeWinter_->Update();
	}
	
	
	
	

	if (gameTimer_ >= 0 && gameTimer_ < 1800) {
		groundSpring_->Update();
	}
	if (gameTimer_ >= 1800 && gameTimer_ < 3600) {
		groundSummer_->Update();
	}
	if (gameTimer_ >= 3600 && gameTimer_ < 5400) {
		groundAutumn_->Update();
	}
	if (gameTimer_ >= 5400 && gameTimer_ < 7200) {
		groundWinter_->Update();
	}
	
	
	
	

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
	//ImGui::Begin("game");
	//ImGui::Text("gameCount %d", gameTimer_);
	//ImGui::End();
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

	 if (gameTimer_ >= 0 && gameTimer_ < 1800) {skyDomeSpring_->Draw();}
	 if (gameTimer_ >= 1800 && gameTimer_ < 3600) {
		 skyDomeSummer_->Draw();
	 }
	 if (gameTimer_ >= 3600 && gameTimer_ < 5400) {
		 skyDomeAutumn_->Draw();
	 }
	 if (gameTimer_ >= 5400 && gameTimer_ < 7200) {
		 skyDomeWinter_->Draw();
	 }

	 if (gameTimer_ >= 0 && gameTimer_ < 1800) {
		 groundSpring_->Draw();
	 }
	 if (gameTimer_ >= 1800 && gameTimer_ < 3600) {
		 groundSummer_->Draw();
	 }
	 if (gameTimer_ >= 3600 && gameTimer_ < 5400) {
		 groundAutumn_->Draw();
	 }
	 if (gameTimer_ >= 5400 && gameTimer_ < 7200) {
		 groundWinter_->Draw();
	 }
	
	
	
	

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion



#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	playerHP_->Draw();
	playerX_->Draw();
	if (GetPlayerHP() == 10) {
		SpriteX1_->Draw();
		SpriteX0_->Draw();
	}
	if (GetPlayerHP() == 9) {SpriteX9_->Draw();}
	if (GetPlayerHP() == 8) {SpriteX8_->Draw();}
	if (GetPlayerHP() == 7) {SpriteX7_->Draw();}
	if (GetPlayerHP() == 6) {SpriteX6_->Draw();}
	if (GetPlayerHP() == 5) {SpriteX5_->Draw();}
	if (GetPlayerHP() == 4) {SpriteX4_->Draw();}
	if (GetPlayerHP() == 3) {SpriteX3_->Draw();}
	if (GetPlayerHP() == 2) {SpriteX2_->Draw();}
	if (GetPlayerHP() == 1) {SpriteX1_->Draw();}
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
			player_->OnCollision();
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

void GameScene::RemoveEnemy(Enemy* enemy) {

	enemies_.remove(enemy);
	delete enemy;
}
