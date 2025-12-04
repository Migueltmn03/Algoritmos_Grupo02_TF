#pragma once

using namespace System;
using namespace System::Drawing;
using namespace System::Collections::Generic;

namespace GameIntro {

	// Clase para manejar sprites y animaciones del personaje
	public ref class CharacterSprite
	{
	private:
		Bitmap^ spriteSheet;
		int frameWidth;
		int frameHeight;
		int currentFrame;
		int totalFrames;
		int framesPerRow;

	public:
		CharacterSprite(String^ spritePath, int frameW, int frameH, int frames, int framesRow)
		{
			try {
				spriteSheet = gcnew Bitmap(spritePath);
				frameWidth = frameW;
				frameHeight = frameH;
				totalFrames = frames;
				framesPerRow = framesRow;
				currentFrame = 0;
			}
			catch (Exception^ ex) {
				MessageBox::Show("Error cargando sprite: " + ex->Message);
			}
		}

		// Obtener el frame actual
		Bitmap^ GetCurrentFrame()
		{
			if (spriteSheet == nullptr) return nullptr;

			int row = currentFrame / framesPerRow;
			int col = currentFrame % framesPerRow;

			Rectangle srcRect(col * frameWidth, row * frameHeight, frameWidth, frameHeight);
			Bitmap^ frame = gcnew Bitmap(frameWidth, frameHeight);

			Graphics^ g = Graphics::FromImage(frame);
			g->DrawImage(spriteSheet,
				Rectangle(0, 0, frameWidth, frameHeight),
				srcRect,
				GraphicsUnit::Pixel);
			delete g;

			return frame;
		}

		void NextFrame()
		{
			currentFrame = (currentFrame + 1) % totalFrames;
		}

		void SetFrame(int frame)
		{
			if (frame >= 0 && frame < totalFrames)
				currentFrame = frame;
		}

		property int FrameWidth { int get() { return frameWidth; } }
		property int FrameHeight { int get() { return frameHeight; } }
	};

	// Clase para el personaje jugador
	public ref class Player
	{
	private:
		CharacterSprite^ sprite;
		float x, y;
		float speed;
		int direction; // 0=down, 1=left, 2=right, 3=up
		bool isMoving;

	public:
		Player(float startX, float startY)
		{
			// Cargar el sprite del personaje (ajusta el path según tu estructura)
			sprite = gcnew CharacterSprite("character_sprite.png", 32, 32, 16, 4);
			x = startX;
			y = startY;
			speed = 3.0f;
			direction = 0;
			isMoving = false;
		}

		void Move(int dx, int dy)
		{
			if (dx != 0 || dy != 0)
			{
				isMoving = true;
				x += dx * speed;
				y += dy * speed;

				// Actualizar dirección
				if (dy > 0) direction = 0; // Abajo
				else if (dx < 0) direction = 1; // Izquierda
				else if (dx > 0) direction = 2; // Derecha
				else if (dy < 0) direction = 3; // Arriba

				sprite->NextFrame();
			}
			else
			{
				isMoving = false;
			}
		}

		void Draw(Graphics^ g, int offsetX, int offsetY)
		{
			Bitmap^ frame = sprite->GetCurrentFrame();
			if (frame != nullptr)
			{
				// Dibujar con escala 2x para mejor visualización
				g->DrawImage(frame,
					Rectangle((int)x + offsetX, (int)y + offsetY,
						sprite->FrameWidth * 2, sprite->FrameHeight * 2));
			}
		}

		property float X { float get() { return x; } void set(float value) { x = value; } }
		property float Y { float get() { return y; } void set(float value) { y = value; } }
		property int Direction { int get() { return direction; } }
	};

	// Clase para manejar el mapa
	public ref class GameMap
	{
	private:
		Bitmap^ mapImage;
		int tileSize;
		int mapWidth;
		int mapHeight;

	public:
		GameMap(String^ mapPath, int tSize)
		{
			try {
				mapImage = gcnew Bitmap(mapPath);
				tileSize = tSize;
				mapWidth = mapImage->Width;
				mapHeight = mapImage->Height;
			}
			catch (Exception^ ex) {
				MessageBox::Show("Error cargando mapa: " + ex->Message);
			}
		}

		void Draw(Graphics^ g, int offsetX, int offsetY, int viewWidth, int viewHeight)
		{
			if (mapImage != nullptr)
			{
				// Dibujar solo la porción visible del mapa
				g->DrawImage(mapImage,
					Rectangle(0, 0, viewWidth, viewHeight),
					Rectangle(-offsetX, -offsetY, viewWidth, viewHeight),
					GraphicsUnit::Pixel);
			}
		}

		property int Width { int get() { return mapWidth; } }
		property int Height { int get() { return mapHeight; } }
		property int TileSize { int get() { return tileSize; } }
	};

	// Formulario del Juego
	public ref class GameForm : public System::Windows::Forms::Form
	{
	private:
		System::ComponentModel::Container^ components;
		Player^ player;
		GameMap^ gameMap;
		Timer^ gameTimer;
		bool keyUp, keyDown, keyLeft, keyRight;
		int cameraX, cameraY;

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
		void InitializeComponent(void)
		{
			this->gameTimer = gcnew Timer();
			this->SuspendLayout();

			// GameTimer
			this->gameTimer->Interval = 16; // ~60 FPS
			this->gameTimer->Tick += gcnew System::EventHandler(this, &GameForm::gameTimer_Tick);

			// GameForm
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1024, 768);
			this->BackColor = System::Drawing::Color::Black;
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"IA vs Pensamiento Crítico - Juego";
			this->KeyPreview = true;
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &GameForm::GameForm_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &GameForm::GameForm_KeyUp);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &GameForm::GameForm_Paint);

			this->ResumeLayout(false);
		}

		void InitializeGame()
		{
			// Inicializar el jugador en el centro de la pantalla
			player = gcnew Player(400, 300);

			// Cargar el mapa (ajusta el path según tu estructura)
			gameMap = gcnew GameMap("game_map.png", 32);

			// Inicializar controles
			keyUp = keyDown = keyLeft = keyRight = false;
			cameraX = cameraY = 0;

			// Iniciar el timer del juego
			gameTimer->Start();
		}

		void gameTimer_Tick(System::Object^ sender, System::EventArgs^ e)
		{
			// Procesar movimiento
			int dx = 0, dy = 0;

			if (keyLeft) dx -= 1;
			if (keyRight) dx += 1;
			if (keyUp) dy -= 1;
			if (keyDown) dy += 1;

			player->Move(dx, dy);

			// Actualizar cámara para seguir al jugador
			cameraX = (int)player->X - this->ClientSize.Width / 2;
			cameraY = (int)player->Y - this->ClientSize.Height / 2;

			// Limitar cámara a los bordes del mapa
			if (cameraX < 0) cameraX = 0;
			if (cameraY < 0) cameraY = 0;
			if (cameraX > gameMap->Width - this->ClientSize.Width)
				cameraX = gameMap->Width - this->ClientSize.Width;
			if (cameraY > gameMap->Height - this->ClientSize.Height)
				cameraY = gameMap->Height - this->ClientSize.Height;

			// Redibujar
			this->Invalidate();
		}

		void GameForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
		{
			Graphics^ g = e->Graphics;
			g->InterpolationMode = System::Drawing::Drawing2D::InterpolationMode::NearestNeighbor;
			g->PixelOffsetMode = System::Drawing::Drawing2D::PixelOffsetMode::Half;

			// Dibujar mapa
			if (gameMap != nullptr)
			{
				gameMap->Draw(g, cameraX, cameraY, this->ClientSize.Width, this->ClientSize.Height);
			}

			// Dibujar jugador
			if (player != nullptr)
			{
				player->Draw(g, -cameraX, -cameraY);
			}

			// Dibujar HUD
			DrawHUD(g);
		}

		void DrawHUD(Graphics^ g)
		{
			// Fondo semi-transparente para el HUD
			SolidBrush^ hudBrush = gcnew SolidBrush(Color::FromArgb(180, 0, 0, 0));
			g->FillRectangle(hudBrush, 10, 10, 250, 80);

			// Texto del HUD
			System::Drawing::Font^ font = gcnew System::Drawing::Font("Segoe UI", 12);
			SolidBrush^ textBrush = gcnew SolidBrush(Color::White);

			String^ posText = String::Format("Posición: ({0:F0}, {1:F0})", player->X, player->Y);
			g->DrawString(posText, font, textBrush, 20, 20);
			g->DrawString("Controles: WASD o Flechas", font, textBrush, 20, 45);
			g->DrawString("ESC: Salir", font, textBrush, 20, 70);

			delete hudBrush;
			delete font;
			delete textBrush;
		}

		void GameForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
		{
			switch (e->KeyCode)
			{
			case Keys::W:
			case Keys::Up:
				keyUp = true;
				break;
			case Keys::S:
			case Keys::Down:
				keyDown = true;
				break;
			case Keys::A:
			case Keys::Left:
				keyLeft = true;
				break;
			case Keys::D:
			case Keys::Right:
				keyRight = true;
				break;
			case Keys::Escape:
				this->Close();
				break;
			}
		}

		void GameForm_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
		{
			switch (e->KeyCode)
			{
			case Keys::W:
			case Keys::Up:
				keyUp = false;
				break;
			case Keys::S:
			case Keys::Down:
				keyDown = false;
				break;
			case Keys::A:
			case Keys::Left:
				keyLeft = false;
				break;
			case Keys::D:
			case Keys::Right:
				keyRight = false;
				break;
			}
		}
	};
}