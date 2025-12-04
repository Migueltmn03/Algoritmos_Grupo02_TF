// GameForm.h - Sistema de juego con movimiento, colisiones, orbes móviles y tiempo límite
#pragma once

namespace GameProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	// ============================================
	// FORMULARIO DE TRANSICIÓN ENTRE NIVELES
	// ============================================
	public ref class TransitionForm : public System::Windows::Forms::Form
	{
	public:
		TransitionForm(void)
		{
			InitializeComponent();
			StartTypewriterEffect();
		}

	protected:
		~TransitionForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::ComponentModel::Container^ components;
		Label^ lblStory;
		Timer^ typewriterTimer;
		Timer^ autoCloseTimer;
		String^ fullText;
		int currentCharIndex;

		void InitializeComponent(void)
		{
			this->lblStory = (gcnew Label());
			this->typewriterTimer = (gcnew Timer());
			this->autoCloseTimer = (gcnew Timer());
			this->SuspendLayout();

			this->fullText = L"La vulnerabilidad del mundo humano se hace evidente cuando "
				L"Alex y Elara deben esconderse de una bestia caótica que los "
				L"acecha en las penumbras. Más se siente impotente. La falta de "
				L"información de Elara enseña la nueva regla de supervivencia: su "
				L"debilidad física debe ser compensada con astucia, sentidos más "
				L"agudos y la falta de inteligencia del enemigo a su favor.\n\n"
				L"Presiona cualquier tecla para continuar...";

			this->currentCharIndex = 0;

			this->lblStory->AutoSize = false;
			this->lblStory->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Regular));
			this->lblStory->ForeColor = System::Drawing::Color::White;
			this->lblStory->Location = System::Drawing::Point(100, 250);
			this->lblStory->Size = System::Drawing::Size(800, 300);
			this->lblStory->Text = L"";
			this->lblStory->BackColor = System::Drawing::Color::Transparent;

			this->typewriterTimer->Interval = 30;
			this->typewriterTimer->Tick += gcnew System::EventHandler(this, &TransitionForm::typewriterTimer_Tick);

			this->autoCloseTimer->Interval = 5000;
			this->autoCloseTimer->Tick += gcnew System::EventHandler(this, &TransitionForm::autoCloseTimer_Tick);

			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1000, 700);
			this->BackColor = System::Drawing::Color::Black;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Transición";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &TransitionForm::TransitionForm_KeyDown);
			this->Click += gcnew System::EventHandler(this, &TransitionForm::TransitionForm_Click);

			this->Controls->Add(this->lblStory);
			this->ResumeLayout(false);
		}

		void StartTypewriterEffect()
		{
			this->typewriterTimer->Start();
		}

		void typewriterTimer_Tick(System::Object^ sender, System::EventArgs^ e)
		{
			if (currentCharIndex < fullText->Length)
			{
				lblStory->Text = fullText->Substring(0, currentCharIndex + 1);
				currentCharIndex++;
			}
			else
			{
				typewriterTimer->Stop();
				autoCloseTimer->Start();
			}
		}

		void autoCloseTimer_Tick(System::Object^ sender, System::EventArgs^ e)
		{
			this->Close();
		}

		void TransitionForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
		{
			this->Close();
		}

		void TransitionForm_Click(System::Object^ sender, System::EventArgs^ e)
		{
			this->Close();
		}
	};

	// ============================================
	// ESTRUCTURAS DEL JUEGO
	// ============================================

	// Estructura para los orbes con movimiento
	ref class Orb {
	public:
		float x, y;
		bool collected;
		float pulsePhase;
		// Nuevas propiedades para movimiento
		float velocityX, velocityY;
		float targetX, targetY;
		float moveTimer;

		Orb(float posX, float posY) {
			x = posX;
			y = posY;
			collected = false;
			pulsePhase = 0.0f;
			velocityX = 0.0f;
			velocityY = 0.0f;
			targetX = posX;
			targetY = posY;
			moveTimer = 0.0f;
		}

		void SetRandomTarget(Random^ rand, int mapWidth, int mapHeight) {
			targetX = (float)(rand->Next(100, mapWidth - 100));
			targetY = (float)(rand->Next(100, mapHeight - 100));
			moveTimer = (float)(rand->Next(60, 180)); // 1-3 segundos a 60 FPS
		}

		void UpdateMovement(float deltaTime) {
			if (collected) return;

			moveTimer -= deltaTime;

			// Movimiento suave hacia el objetivo
			float dx = targetX - x;
			float dy = targetY - y;
			float distance = Math::Sqrt(dx * dx + dy * dy);

			if (distance > 5.0f) {
				velocityX = (dx / distance) * 1.5f; // Velocidad de movimiento
				velocityY = (dy / distance) * 1.5f;

				x += velocityX;
				y += velocityY;
			}
		}
	};

	// Estructura para el portal
	ref class Portal {
	public:
		float x, y;
		bool isActive;
		float animPhase;

		Portal(float posX, float posY) {
			x = posX;
			y = posY;
			isActive = false;
			animPhase = 0.0f;
		}
	};

	// ============================================
	// FORMULARIO PRINCIPAL DEL JUEGO
	// ============================================
	public ref class GameForm : public System::Windows::Forms::Form
	{
	public:
		GameForm(void)
		{
			InitializeComponent();
			InitializeGame();
		}

	protected:
		~GameForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::ComponentModel::IContainer^ components;

		// Controles del juego
		System::Windows::Forms::PictureBox^ gameCanvas;
		System::Windows::Forms::Timer^ gameTimer;

		// Recursos del juego
		Bitmap^ mapImage;
		Bitmap^ characterSprite;

		// Mapa de colisiones
		array<bool, 2>^ collisionMap;
		int mapTileWidth;
		int mapTileHeight;
		const int TILE_SIZE = 16;

		// Posición y movimiento del personaje
		float playerX;
		float playerY;
		const float MOVE_SPEED = 2.0f;

		// Tamaño del sprite
		const int SPRITE_WIDTH = 16;
		const int SPRITE_HEIGHT = 16;

		// Control de teclas
		bool keyUp, keyDown, keyLeft, keyRight;

		// Animación
		int currentFrame;
		int frameCounter;
		const int FRAME_DELAY = 8;
		int direction;

		// Sistema de orbes y portal
		System::Collections::Generic::List<Orb^>^ orbs;
		Portal^ portal;
		const int TOTAL_ORBS = 5;
		const int ORB_SIZE = 12;
		const int PORTAL_SIZE = 48;
		const float COLLECTION_DISTANCE = 20.0f;

		// Sistema de tiempo límite (en segundos)
		float timeLimit;
		float currentTime;
		const float LEVEL1_TIME = 60.0f; // 60 segundos para el nivel 1
		const float LEVEL2_TIME = 90.0f; // 90 segundos para el nivel 2

		// Random para movimiento de orbes
		Random^ random;

		// Debug
		bool showDebug;
		bool showCollisionMap;

		// Victoria y derrota
		bool gameWon;
		bool gameLost;
		bool isSecondMap;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = gcnew System::ComponentModel::Container();

			// gameCanvas
			this->gameCanvas = gcnew System::Windows::Forms::PictureBox();
			this->gameCanvas->Location = System::Drawing::Point(0, 0);
			this->gameCanvas->Name = L"gameCanvas";
			this->gameCanvas->Size = System::Drawing::Size(1211, 980);
			this->gameCanvas->TabIndex = 0;
			this->gameCanvas->TabStop = false;
			this->gameCanvas->BackColor = System::Drawing::Color::Black;

			// gameTimer
			this->gameTimer = gcnew System::Windows::Forms::Timer(this->components);
			this->gameTimer->Interval = 16; // ~60 FPS
			this->gameTimer->Tick += gcnew System::EventHandler(this, &GameForm::GameTimer_Tick);

			// GameForm
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1211, 980);
			this->Controls->Add(this->gameCanvas);
			this->Name = L"GameForm";
			this->Text = L"IA vs Pensamiento Crítico - ¡Colecta todos los orbes antes de que se acabe el tiempo!";
			this->KeyPreview = true;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &GameForm::GameForm_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &GameForm::GameForm_KeyUp);

			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gameCanvas))->EndInit();
			this->ResumeLayout(false);
		}
#pragma endregion

		void InitializeGame()
		{
			showDebug = true;
			showCollisionMap = false;
			gameWon = false;
			gameLost = false;
			isSecondMap = false;
			random = gcnew Random();

			// Inicializar tiempo
			timeLimit = LEVEL1_TIME;
			currentTime = timeLimit;

			// Cargar el mapa desde archivo
			try {
				mapImage = gcnew Bitmap("map.png");
			}
			catch (Exception^) {
				CreateTestMap();
			}

			// Crear sprite del personaje
			CreateVisibleSprite();

			// Inicializar mapa de colisiones
			mapTileWidth = mapImage->Width / TILE_SIZE;
			mapTileHeight = mapImage->Height / TILE_SIZE;
			GenerateCollisionMap();

			// Posición inicial
			playerX = 100.0f;
			playerY = 100.0f;

			// Verificar posición válida
			if (CheckCollision((int)playerX, (int)playerY)) {
				for (int y = 64; y < mapImage->Height - 64; y += TILE_SIZE) {
					for (int x = 64; x < mapImage->Width - 64; x += TILE_SIZE) {
						if (!CheckCollision(x, y)) {
							playerX = (float)x;
							playerY = (float)y;
							goto foundPosition;
						}
					}
				}
			foundPosition:;
			}

			// Crear orbes con movimiento aleatorio
			orbs = gcnew System::Collections::Generic::List<Orb^>();
			int minMargin = 100;
			int maxMargin = 100;

			if (mapImage->Width < 300) {
				minMargin = 50;
				maxMargin = 50;
			}
			if (mapImage->Height < 300) {
				minMargin = 50;
				maxMargin = 50;
			}

			int minX = Math::Min(minMargin, mapImage->Width / 4);
			int maxX = Math::Max(minX + 1, mapImage->Width - maxMargin);
			int minY = Math::Min(minMargin, mapImage->Height / 4);
			int maxY = Math::Max(minY + 1, mapImage->Height - maxMargin);

			for (int i = 0; i < TOTAL_ORBS; i++) {
				bool validPosition = false;
				float orbX, orbY;
				int attempts = 0;
				const int MAX_ATTEMPTS = 100;

				while (!validPosition && attempts < MAX_ATTEMPTS) {
					orbX = (float)(random->Next(minX, maxX));
					orbY = (float)(random->Next(minY, maxY));

					if (!CheckCollision((int)orbX, (int)orbY)) {
						float distToPlayer = Math::Sqrt(Math::Pow(orbX - playerX, 2) + Math::Pow(orbY - playerY, 2));
						if (distToPlayer > 150.0f) {
							validPosition = true;
						}
					}
					attempts++;
				}

				if (!validPosition) {
					for (int y = minY; y < maxY; y += TILE_SIZE) {
						for (int x = minX; x < maxX; x += TILE_SIZE) {
							if (!CheckCollision(x, y)) {
								orbX = (float)x;
								orbY = (float)y;
								validPosition = true;
								goto foundOrbPosition;
							}
						}
					}
				foundOrbPosition:;
				}

				Orb^ newOrb = gcnew Orb(orbX, orbY);
				newOrb->SetRandomTarget(random, mapImage->Width, mapImage->Height);
				orbs->Add(newOrb);
			}

			// Crear portal
			int portalX = Math::Max(minX, Math::Min(maxX - PORTAL_SIZE, mapImage->Width / 2));
			int portalY = Math::Max(minY, Math::Min(maxY - PORTAL_SIZE, mapImage->Height / 2));
			portal = gcnew Portal((float)portalX, (float)portalY);

			if (CheckCollision((int)portal->x, (int)portal->y)) {
				for (int y = minY; y < maxY; y += TILE_SIZE) {
					for (int x = minX; x < maxX; x += TILE_SIZE) {
						if (!CheckCollision(x, y)) {
							portal->x = (float)x;
							portal->y = (float)y;
							goto foundPortalPos;
						}
					}
				}
			foundPortalPos:;
			}

			keyUp = keyDown = keyLeft = keyRight = false;
			currentFrame = 0;
			frameCounter = 0;
			direction = 0;

			gameCanvas->Paint += gcnew PaintEventHandler(this, &GameForm::GameCanvas_Paint);
			gameTimer->Start();
		}

		void LoadSecondMap()
		{
			try {
				delete mapImage;
				mapImage = gcnew Bitmap("map2.png");
			}
			catch (Exception^) {
				CreateSecondTestMap();
			}

			// Reiniciar tiempo para el segundo nivel
			timeLimit = LEVEL2_TIME;
			currentTime = timeLimit;

			mapTileWidth = mapImage->Width / TILE_SIZE;
			mapTileHeight = mapImage->Height / TILE_SIZE;
			GenerateCollisionMap();

			playerX = 100.0f;
			playerY = 100.0f;

			if (CheckCollision((int)playerX, (int)playerY)) {
				for (int y = 64; y < mapImage->Height - 64; y += TILE_SIZE) {
					for (int x = 64; x < mapImage->Width - 64; x += TILE_SIZE) {
						if (!CheckCollision(x, y)) {
							playerX = (float)x;
							playerY = (float)y;
							goto foundPosition2;
						}
					}
				}
			foundPosition2:;
			}

			orbs->Clear();

			for (int i = 0; i < TOTAL_ORBS; i++) {
				bool validPosition = false;
				float orbX, orbY;

				while (!validPosition) {
					orbX = (float)(random->Next(100, mapImage->Width - 100));
					orbY = (float)(random->Next(100, mapImage->Height - 100));

					if (!CheckCollision((int)orbX, (int)orbY)) {
						float distToPlayer = Math::Sqrt(Math::Pow(orbX - playerX, 2) + Math::Pow(orbY - playerY, 2));
						if (distToPlayer > 150.0f) {
							validPosition = true;
						}
					}
				}

				Orb^ newOrb = gcnew Orb(orbX, orbY);
				newOrb->SetRandomTarget(random, mapImage->Width, mapImage->Height);
				orbs->Add(newOrb);
			}

			portal->x = mapImage->Width / 2.0f;
			portal->y = mapImage->Height / 2.0f;
			portal->isActive = false;

			if (CheckCollision((int)portal->x, (int)portal->y)) {
				for (int y = mapImage->Height / 2; y < mapImage->Height - 100; y += TILE_SIZE) {
					for (int x = mapImage->Width / 2; x < mapImage->Width - 100; x += TILE_SIZE) {
						if (!CheckCollision(x, y)) {
							portal->x = (float)x;
							portal->y = (float)y;
							goto foundPortalPos2;
						}
					}
				}
			foundPortalPos2:;
			}

			gameWon = false;
			gameLost = false;
			isSecondMap = true;
		}

		void CreateTestMap()
		{
			mapImage = gcnew Bitmap(1211, 980);
			Graphics^ g = Graphics::FromImage(mapImage);
			g->Clear(Color::FromArgb(45, 52, 64));

			SolidBrush^ wallBrush = gcnew SolidBrush(Color::FromArgb(30, 35, 45));
			g->FillRectangle(wallBrush, 0, 0, mapImage->Width, 48);
			g->FillRectangle(wallBrush, 0, 0, 48, mapImage->Height);
			g->FillRectangle(wallBrush, mapImage->Width - 48, 0, 48, mapImage->Height);
			g->FillRectangle(wallBrush, 0, mapImage->Height - 48, mapImage->Width, 48);

			g->FillRectangle(wallBrush, 250, 150, 400, 32);
			g->FillRectangle(wallBrush, 700, 250, 32, 300);
			g->FillRectangle(wallBrush, 200, 600, 500, 32);

			Pen^ gridPen = gcnew Pen(Color::FromArgb(50, 60, 75), 1);
			for (int i = 0; i < mapImage->Width; i += 16) {
				g->DrawLine(gridPen, i, 0, i, mapImage->Height);
			}
			for (int i = 0; i < mapImage->Height; i += 16) {
				g->DrawLine(gridPen, 0, i, mapImage->Width, i);
			}

			delete wallBrush;
			delete gridPen;
			delete g;
		}

		void CreateSecondTestMap()
		{
			mapImage = gcnew Bitmap(1211, 980);
			Graphics^ g = Graphics::FromImage(mapImage);
			g->Clear(Color::FromArgb(60, 80, 60));

			SolidBrush^ wallBrush = gcnew SolidBrush(Color::FromArgb(40, 60, 40));
			g->FillRectangle(wallBrush, 0, 0, mapImage->Width, 48);
			g->FillRectangle(wallBrush, 0, 0, 48, mapImage->Height);
			g->FillRectangle(wallBrush, mapImage->Width - 48, 0, 48, mapImage->Height);
			g->FillRectangle(wallBrush, 0, mapImage->Height - 48, mapImage->Width, 48);

			g->FillRectangle(wallBrush, 150, 200, 32, 400);
			g->FillRectangle(wallBrush, 400, 150, 32, 300);
			g->FillRectangle(wallBrush, 650, 300, 32, 400);
			g->FillRectangle(wallBrush, 300, 500, 400, 32);

			Pen^ gridPen = gcnew Pen(Color::FromArgb(70, 90, 70), 1);
			for (int i = 0; i < mapImage->Width; i += 16) {
				g->DrawLine(gridPen, i, 0, i, mapImage->Height);
			}
			for (int i = 0; i < mapImage->Height; i += 16) {
				g->DrawLine(gridPen, 0, i, mapImage->Width, i);
			}

			delete wallBrush;
			delete gridPen;
			delete g;
		}

		void CreateVisibleSprite()
		{
			characterSprite = gcnew Bitmap(SPRITE_WIDTH * 4, SPRITE_HEIGHT * 4);
			Graphics^ g = Graphics::FromImage(characterSprite);
			g->Clear(Color::Transparent);

			SolidBrush^ bodyBrush = gcnew SolidBrush(Color::FromArgb(50, 100, 255));
			SolidBrush^ skinBrush = gcnew SolidBrush(Color::FromArgb(255, 220, 177));
			SolidBrush^ hairBrush = gcnew SolidBrush(Color::FromArgb(139, 90, 43));
			SolidBrush^ legBrush = gcnew SolidBrush(Color::FromArgb(60, 60, 60));
			SolidBrush^ outlineBrush = gcnew SolidBrush(Color::Black);

			for (int dir = 0; dir < 4; dir++) {
				for (int frame = 0; frame < 4; frame++) {
					int x = frame * SPRITE_WIDTH;
					int y = dir * SPRITE_HEIGHT;

					g->FillRectangle(outlineBrush, x + 3, y + 1, 10, 14);
					g->FillEllipse(hairBrush, (float)(x + 4), (float)(y + 2), 8.0f, 5.0f);
					g->FillEllipse(skinBrush, (float)(x + 5), (float)(y + 3), 6.0f, 6.0f);
					g->FillRectangle(Brushes::Black, x + 6, y + 5, 1, 1);
					g->FillRectangle(Brushes::Black, x + 9, y + 5, 1, 1);
					g->FillRectangle(bodyBrush, x + 5, y + 8, 6, 5);

					if (frame % 2 == 0) {
						g->FillRectangle(legBrush, x + 5, y + 13, 2, 2);
						g->FillRectangle(legBrush, x + 9, y + 13, 2, 2);
					}
					else {
						g->FillRectangle(legBrush, x + 6, y + 13, 2, 2);
						g->FillRectangle(legBrush, x + 8, y + 13, 2, 2);
					}

					g->FillRectangle(skinBrush, x + 3, y + 9, 2, 3);
					g->FillRectangle(skinBrush, x + 11, y + 9, 2, 3);
				}
			}

			delete bodyBrush;
			delete skinBrush;
			delete hairBrush;
			delete legBrush;
			delete outlineBrush;
			delete g;
		}

		void GenerateCollisionMap()
		{
			collisionMap = gcnew array<bool, 2>(mapTileWidth, mapTileHeight);

			for (int ty = 0; ty < mapTileHeight; ty++) {
				for (int tx = 0; tx < mapTileWidth; tx++) {
					collisionMap[tx, ty] = IsTileCollision(tx, ty);
				}
			}
		}

		bool IsTileCollision(int tileX, int tileY)
		{
			int pixelX = tileX * TILE_SIZE + TILE_SIZE / 2;
			int pixelY = tileY * TILE_SIZE + TILE_SIZE / 2;

			if (pixelX < 0 || pixelX >= mapImage->Width ||
				pixelY < 0 || pixelY >= mapImage->Height) {
				return true;
			}

			Color pixelColor = mapImage->GetPixel(pixelX, pixelY);
			int brightness = (pixelColor.R + pixelColor.G + pixelColor.B) / 3;

			return brightness < 30;
		}

		bool CheckCollision(int x, int y)
		{
			array<Point>^ checkPoints = gcnew array<Point>(4) {
				Point(x + 2, y + 2),
					Point(x + SPRITE_WIDTH - 3, y + 2),
					Point(x + 2, y + SPRITE_HEIGHT - 1),
					Point(x + SPRITE_WIDTH - 3, y + SPRITE_HEIGHT - 1)
			};

			for each (Point p in checkPoints) {
				int tileX = p.X / TILE_SIZE;
				int tileY = p.Y / TILE_SIZE;

				if (tileX < 0 || tileX >= mapTileWidth ||
					tileY < 0 || tileY >= mapTileHeight) {
					return true;
				}

				if (collisionMap[tileX, tileY]) {
					return true;
				}
			}

			return false;
		}

		int GetCollectedOrbsCount()
		{
			int count = 0;
			for each (Orb ^ orb in orbs) {
				if (orb->collected) count++;
			}
			return count;
		}

		void CheckOrbCollection()
		{
			for each (Orb ^ orb in orbs) {
				if (!orb->collected) {
					float dx = playerX + SPRITE_WIDTH / 2.0f - orb->x;
					float dy = playerY + SPRITE_HEIGHT / 2.0f - orb->y;
					float distance = Math::Sqrt(dx * dx + dy * dy);

					if (distance < COLLECTION_DISTANCE) {
						orb->collected = true;

						if (GetCollectedOrbsCount() == TOTAL_ORBS) {
							portal->isActive = true;
						}
					}
				}
			}
		}

		void CheckPortalEntry()
		{
			if (portal->isActive && !gameWon) {
				float dx = playerX + SPRITE_WIDTH / 2.0f - portal->x;
				float dy = playerY + SPRITE_HEIGHT / 2.0f - portal->y;
				float distance = Math::Sqrt(dx * dx + dy * dy);

				if (distance < PORTAL_SIZE / 2.0f) {
					gameWon = true;
					gameTimer->Stop();

					if (isSecondMap) {
						MessageBox::Show("¡Felicidades! Has completado todos los niveles.\n\nOrbes totales: " + (TOTAL_ORBS * 2),
							"¡Victoria Final!",
							MessageBoxButtons::OK,
							MessageBoxIcon::Information);
						this->Close();
					}
					else {
						TransitionForm^ transition = gcnew TransitionForm();
						transition->ShowDialog();

						LoadSecondMap();
						gameTimer->Start();
					}
				}
			}
		}

		void GameTimer_Tick(Object^ sender, EventArgs^ e)
		{
			if (gameLost || gameWon) return;

			// Actualizar tiempo
			currentTime -= 0.016f; // ~16ms por frame
			if (currentTime <= 0.0f) {
				currentTime = 0.0f;
				gameLost = true;
				gameTimer->Stop();

				MessageBox::Show("¡Se acabó el tiempo!\n\nIntenta de nuevo.",
					"Tiempo Agotado",
					MessageBoxButtons::OK,
					MessageBoxIcon::Exclamation);
				this->Close();
				return;
			}

			bool isMoving = false;
			float newX = playerX;
			float newY = playerY;

			if (keyUp) {
				newY -= MOVE_SPEED;
				direction = 3;
				isMoving = true;
			}
			if (keyDown) {
				newY += MOVE_SPEED;
				direction = 0;
				isMoving = true;
			}
			if (keyLeft) {
				newX -= MOVE_SPEED;
				direction = 1;
				isMoving = true;
			}
			if (keyRight) {
				newX += MOVE_SPEED;
				direction = 2;
				isMoving = true;
			}

			if (isMoving) {
				if (newX != playerX) {
					if (!CheckCollision((int)newX, (int)playerY)) {
						playerX = newX;
					}
				}

				if (newY != playerY) {
					if (!CheckCollision((int)playerX, (int)newY)) {
						playerY = newY;
					}
				}

				frameCounter++;
				if (frameCounter >= FRAME_DELAY) {
					frameCounter = 0;
					currentFrame = (currentFrame + 1) % 4;
				}
			}
			else {
				currentFrame = 0;
				frameCounter = 0;
			}

			// Actualizar movimiento de orbes
			for each (Orb ^ orb in orbs) {
				if (!orb->collected) {
					orb->pulsePhase += 0.1f;
					orb->UpdateMovement(1.0f);

					// Si llegó al objetivo o se acabó el timer, elegir nuevo objetivo
					if (orb->moveTimer <= 0) {
						orb->SetRandomTarget(random, mapImage->Width, mapImage->Height);
					}
				}
			}

			// Actualizar animación del portal
			if (portal->isActive) {
				portal->animPhase += 0.15f;
			}

			// Verificar colección de orbes
			CheckOrbCollection();

			// Verificar entrada al portal
			CheckPortalEntry();

			gameCanvas->Invalidate();
		}

		void GameCanvas_Paint(Object^ sender, PaintEventArgs^ e)
		{
			Graphics^ g = e->Graphics;

			g->InterpolationMode = System::Drawing::Drawing2D::InterpolationMode::NearestNeighbor;
			g->PixelOffsetMode = System::Drawing::Drawing2D::PixelOffsetMode::Half;
			g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;

			// Dibujar mapa
			if (mapImage != nullptr) {
				g->DrawImage(mapImage, 0, 0, mapImage->Width, mapImage->Height);
			}

			// Dibujar mapa de colisiones
			if (showCollisionMap) {
				SolidBrush^ collisionBrush = gcnew SolidBrush(Color::FromArgb(100, 255, 0, 0));
				for (int ty = 0; ty < mapTileHeight; ty++) {
					for (int tx = 0; tx < mapTileWidth; tx++) {
						if (collisionMap[tx, ty]) {
							g->FillRectangle(collisionBrush, tx * TILE_SIZE, ty * TILE_SIZE,
								TILE_SIZE, TILE_SIZE);
						}
					}
				}
				delete collisionBrush;
			}

			// Dibujar portal (detrás del jugador)
			if (portal->isActive) {
				float portalPulse = (float)Math::Sin(portal->animPhase) * 5.0f;

				// Círculo exterior giratorio
				for (int i = 0; i < 8; i++) {
					float angle = portal->animPhase + (i * Math::PI / 4);
					float radius = PORTAL_SIZE / 2.0f + portalPulse;
					float px = portal->x + Math::Cos(angle) * radius;
					float py = portal->y + Math::Sin(angle) * radius;

					SolidBrush^ particleBrush = gcnew SolidBrush(Color::FromArgb(150, 100, 255, 255));
					
					delete particleBrush;
				}

				// Portal principal con gradiente
				System::Drawing::Drawing2D::GraphicsPath^ portalPath = gcnew System::Drawing::Drawing2D::GraphicsPath();
				portalPath->AddEllipse(portal->x - PORTAL_SIZE / 2, portal->y - PORTAL_SIZE / 2,
					PORTAL_SIZE + portalPulse, PORTAL_SIZE + portalPulse);

				System::Drawing::Drawing2D::PathGradientBrush^ gradientBrush =
					gcnew System::Drawing::Drawing2D::PathGradientBrush(portalPath);
				gradientBrush->CenterColor = Color::FromArgb(200, 150, 100, 255);
				array<Color>^ colors = gcnew array<Color>(1) { Color::FromArgb(50, 50, 150, 255) };
				gradientBrush->SurroundColors = colors;

				g->FillPath(gradientBrush, portalPath);

				// Borde brillante
				Pen^ portalPen = gcnew Pen(Color::FromArgb(255, 200, 255), 3);
				g->DrawEllipse(portalPen, portal->x - PORTAL_SIZE / 2, portal->y - PORTAL_SIZE / 2,
					PORTAL_SIZE + portalPulse, PORTAL_SIZE + portalPulse);

				delete portalPath;
				delete gradientBrush;
				delete portalPen;
			}

			// Dibujar orbes con efecto de movimiento
			for each (Orb ^ orb in orbs) {
				if (!orb->collected) {
					float orbPulse = (float)Math::Sin(orb->pulsePhase) * 2.0f;
					float orbSize = ORB_SIZE + orbPulse;

					// Estela de movimiento
					SolidBrush^ trailBrush = gcnew SolidBrush(Color::FromArgb(30, 255, 215, 0));
					g->FillEllipse(trailBrush, orb->x - orbSize * 1.5f, orb->y - orbSize * 1.5f,
						orbSize * 3, orbSize * 3);
					delete trailBrush;

					// Brillo exterior
					SolidBrush^ glowBrush = gcnew SolidBrush(Color::FromArgb(50, 255, 215, 0));
					g->FillEllipse(glowBrush, orb->x - orbSize, orb->y - orbSize, orbSize * 2, orbSize * 2);
					delete glowBrush;

					// Orbe principal
					System::Drawing::Drawing2D::GraphicsPath^ orbPath = gcnew System::Drawing::Drawing2D::GraphicsPath();
					orbPath->AddEllipse(orb->x - orbSize / 2, orb->y - orbSize / 2, orbSize, orbSize);

					System::Drawing::Drawing2D::PathGradientBrush^ orbGradient =
						gcnew System::Drawing::Drawing2D::PathGradientBrush(orbPath);
					orbGradient->CenterColor = Color::FromArgb(255, 255, 255, 150);
					array<Color>^ orbColors = gcnew array<Color>(1) { Color::FromArgb(255, 255, 215, 0) };
					orbGradient->SurroundColors = orbColors;

					g->FillPath(orbGradient, orbPath);

					// Borde brillante
					Pen^ orbPen = gcnew Pen(Color::FromArgb(255, 255, 255), 2);
					g->DrawEllipse(orbPen, orb->x - orbSize / 2, orb->y - orbSize / 2, orbSize, orbSize);

					delete orbPath;
					delete orbGradient;
					delete orbPen;
				}
			}

			// Dibujar personaje
			if (characterSprite != nullptr) {
				// Sombra
				SolidBrush^ shadowBrush = gcnew SolidBrush(Color::FromArgb(100, 0, 0, 0));
				g->FillEllipse(shadowBrush, (float)((int)playerX + 2), (float)((int)playerY + SPRITE_HEIGHT - 2),
					(float)(SPRITE_WIDTH - 4), 3.0f);
				delete shadowBrush;

				Rectangle srcRect(currentFrame * SPRITE_WIDTH,
					direction * SPRITE_HEIGHT,
					SPRITE_WIDTH,
					SPRITE_HEIGHT);
				Rectangle destRect((int)playerX, (int)playerY,
					SPRITE_WIDTH, SPRITE_HEIGHT);

				g->DrawImage(characterSprite, destRect, srcRect, GraphicsUnit::Pixel);

				if (showDebug) {
					Pen^ debugPen = gcnew Pen(Color::Lime, 1);
					g->DrawRectangle(debugPen, (int)playerX, (int)playerY,
						SPRITE_WIDTH - 1, SPRITE_HEIGHT - 1);
					delete debugPen;
				}
			}

			// Info debug, contador de orbes y tiempo
			int collectedCount = GetCollectedOrbsCount();
			String^ orbInfo = String::Format("Orbes: {0}/{1}", collectedCount, TOTAL_ORBS);

			if (portal->isActive) {
				orbInfo += " - ¡PORTAL ABIERTO!";
			}

			// Formatear tiempo
			int minutes = (int)(currentTime / 60);
			int seconds = (int)(currentTime) % 60;
			String^ timeInfo = String::Format("Tiempo: {0:D2}:{1:D2}", minutes, seconds);

			// Color del tiempo según urgencia
			Color timeColor = Color::White;
			if (currentTime < 10.0f) {
				timeColor = Color::Red;
			}
			else if (currentTime < 30.0f) {
				timeColor = Color::Yellow;
			}

			String^ mapInfo = isSecondMap ? " [NIVEL 2]" : " [NIVEL 1]";

			if (showDebug) {
				String^ info = String::Format(
					"Pos: ({0:F0}, {1:F0}) | Tile: ({2}, {3}) | Dir: {4}\n{5}{6}\n{7}\n[F1] Debug | [F2] Collision | [ESC] Menu",
					playerX, playerY,
					(int)playerX / TILE_SIZE, (int)playerY / TILE_SIZE,
					direction, orbInfo, mapInfo, timeInfo
				);

				SolidBrush^ bgBrush = gcnew SolidBrush(Color::FromArgb(180, 0, 0, 0));
				g->FillRectangle(bgBrush, 5, 5, 550, 80);
				delete bgBrush;

				g->DrawString(info, gcnew System::Drawing::Font("Consolas", 9),
					Brushes::Lime, 10.0f, 10.0f);
			}
			else {
				// Mostrar contador de orbes y tiempo
				SolidBrush^ bgBrush = gcnew SolidBrush(Color::FromArgb(180, 0, 0, 0));
				g->FillRectangle(bgBrush, 5, 5, 350, 60);
				delete bgBrush;

				Color textColor = portal->isActive ? Color::Lime : Color::White;
				g->DrawString(orbInfo + mapInfo, gcnew System::Drawing::Font("Consolas", 12, FontStyle::Bold),
					gcnew SolidBrush(textColor), 10.0f, 10.0f);

				g->DrawString(timeInfo, gcnew System::Drawing::Font("Consolas", 14, FontStyle::Bold),
					gcnew SolidBrush(timeColor), 10.0f, 35.0f);
			}
		}

		void GameForm_KeyDown(Object^ sender, KeyEventArgs^ e)
		{
			switch (e->KeyCode) {
			case Keys::Up:
			case Keys::W:
				keyUp = true;
				e->Handled = true;
				break;
			case Keys::Down:
			case Keys::S:
				keyDown = true;
				e->Handled = true;
				break;
			case Keys::Left:
			case Keys::A:
				keyLeft = true;
				e->Handled = true;
				break;
			case Keys::Right:
			case Keys::D:
				keyRight = true;
				e->Handled = true;
				break;
			case Keys::F1:
				showDebug = !showDebug;
				gameCanvas->Invalidate();
				break;
			case Keys::F2:
				showCollisionMap = !showCollisionMap;
				gameCanvas->Invalidate();
				break;
			case Keys::Escape:
				this->Close();
				break;
			}
		}

		void GameForm_KeyUp(Object^ sender, KeyEventArgs^ e)
		{
			switch (e->KeyCode) {
			case Keys::Up:
			case Keys::W:
				keyUp = false;
				e->Handled = true;
				break;
			case Keys::Down:
			case Keys::S:
				keyDown = false;
				e->Handled = true;
				break;
			case Keys::Left:
			case Keys::A:
				keyLeft = false;
				e->Handled = true;
				break;
			case Keys::Right:
			case Keys::D:
				keyRight = false;
				e->Handled = true;
				break;
			}
		}
	};
}