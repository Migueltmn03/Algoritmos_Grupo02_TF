// GameForm.h - Sistema de juego con movimiento y colisiones
#pragma once

namespace GameProject {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

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

        // Debug
        bool showDebug;
        bool showCollisionMap;

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
            this->gameTimer->Interval = 16;
            this->gameTimer->Tick += gcnew System::EventHandler(this, &GameForm::GameTimer_Tick);

            // GameForm
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1211, 980);
            this->Controls->Add(this->gameCanvas);
            this->Name = L"GameForm";
            this->Text = L"IA vs Pensamiento Crítico - [F1] Debug | [F2] Collision | [ESC] Menu";
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

            // Cargar el mapa desde archivo
            try {
                mapImage = gcnew Bitmap("map.png");
            }
            catch (Exception^) {
                // Crear mapa de prueba si no existe
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

            keyUp = keyDown = keyLeft = keyRight = false;
            currentFrame = 0;
            frameCounter = 0;
            direction = 0;

            gameCanvas->Paint += gcnew PaintEventHandler(this, &GameForm::GameCanvas_Paint);
            gameTimer->Start();
        }

        void CreateTestMap()
        {
            mapImage = gcnew Bitmap(1211, 980);
            Graphics^ g = Graphics::FromImage(mapImage);
            g->Clear(Color::FromArgb(45, 52, 64));

            // Paredes exteriores
            SolidBrush^ wallBrush = gcnew SolidBrush(Color::FromArgb(30, 35, 45));
            g->FillRectangle(wallBrush, 0, 0, mapImage->Width, 48);
            g->FillRectangle(wallBrush, 0, 0, 48, mapImage->Height);
            g->FillRectangle(wallBrush, mapImage->Width - 48, 0, 48, mapImage->Height);
            g->FillRectangle(wallBrush, 0, mapImage->Height - 48, mapImage->Width, 48);

            // Habitaciones internas
            g->FillRectangle(wallBrush, 250, 150, 400, 32);
            g->FillRectangle(wallBrush, 700, 250, 32, 300);
            g->FillRectangle(wallBrush, 200, 600, 500, 32);

            // Grid para visualización
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

                    // Contorno
                    g->FillRectangle(outlineBrush, x + 3, y + 1, 10, 14);

                    // Cabello
                    g->FillEllipse(hairBrush, (float)(x + 4), (float)(y + 2), 8.0f, 5.0f);

                    // Cabeza
                    g->FillEllipse(skinBrush, (float)(x + 5), (float)(y + 3), 6.0f, 6.0f);

                    // Ojos
                    g->FillRectangle(Brushes::Black, x + 6, y + 5, 1, 1);
                    g->FillRectangle(Brushes::Black, x + 9, y + 5, 1, 1);

                    // Cuerpo
                    g->FillRectangle(bodyBrush, x + 5, y + 8, 6, 5);

                    // Piernas con animación
                    if (frame % 2 == 0) {
                        g->FillRectangle(legBrush, x + 5, y + 13, 2, 2);
                        g->FillRectangle(legBrush, x + 9, y + 13, 2, 2);
                    }
                    else {
                        g->FillRectangle(legBrush, x + 6, y + 13, 2, 2);
                        g->FillRectangle(legBrush, x + 8, y + 13, 2, 2);
                    }

                    // Brazos
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

            // Solo detectar como colisión las paredes MUY oscuras (casi negras)
            // Esto permite caminar sobre todo el suelo
            int brightness = (pixelColor.R + pixelColor.G + pixelColor.B) / 3;

            return brightness < 30; // Solo las áreas muy oscuras son paredes
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

        void GameTimer_Tick(Object^ sender, EventArgs^ e)
        {
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

            gameCanvas->Invalidate();
        }

        void GameCanvas_Paint(Object^ sender, PaintEventArgs^ e)
        {
            Graphics^ g = e->Graphics;

            g->InterpolationMode = System::Drawing::Drawing2D::InterpolationMode::NearestNeighbor;
            g->PixelOffsetMode = System::Drawing::Drawing2D::PixelOffsetMode::Half;

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

            // Info debug
            if (showDebug) {
                String^ info = String::Format(
                    "Pos: ({0:F0}, {1:F0}) | Tile: ({2}, {3}) | Dir: {4}\n[F1] Debug | [F2] Collision | [ESC] Menu",
                    playerX, playerY,
                    (int)playerX / TILE_SIZE, (int)playerY / TILE_SIZE,
                    direction
                );

                SolidBrush^ bgBrush = gcnew SolidBrush(Color::FromArgb(180, 0, 0, 0));
                g->FillRectangle(bgBrush, 5, 5, 450, 45);
                delete bgBrush;

                g->DrawString(info, gcnew System::Drawing::Font("Consolas", 9),
                    Brushes::Lime, 10.0f, 10.0f);
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