#pragma once

namespace GameIntro {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
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
        System::ComponentModel::Container^ components;
        Timer^ gameTimer;
        PictureBox^ gameCanvas;

        // Jugador
        int playerX, playerY;
        int playerWidth, playerHeight;
        int playerSpeed;
        int playerDirection; // 0=abajo, 1=izquierda, 2=derecha, 3=arriba

        // Controles
        bool keyUp, keyDown, keyLeft, keyRight;

        // Mapa (0 = piso, 1 = muro)
        array<int, 2>^ gameMap;
        int tileSize;
        int mapWidth, mapHeight;

        // Assets - Imágenes
        Bitmap^ mapImage;
        Bitmap^ playerSprites;
        array<Rectangle>^ playerFrames; // 0=abajo, 1=derecha, 2=arriba, 3=izquierda

        // Animación
        int animationFrame;
        int animationCounter;

        void InitializeComponent(void)
        {
            this->gameCanvas = (gcnew PictureBox());
            this->gameTimer = (gcnew Timer());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gameCanvas))->BeginInit();
            this->SuspendLayout();

            // gameCanvas
            this->gameCanvas->BackColor = System::Drawing::Color::Black;
            this->gameCanvas->Location = System::Drawing::Point(0, 0);
            this->gameCanvas->Size = System::Drawing::Size(1216, 926);
            this->gameCanvas->TabStop = false;
            this->gameCanvas->Paint += gcnew PaintEventHandler(this, &GameForm::gameCanvas_Paint);

            // gameTimer
            this->gameTimer->Interval = 16; // ~60 FPS
            this->gameTimer->Tick += gcnew EventHandler(this, &GameForm::gameTimer_Tick);

            // GameForm
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1216, 926);
            this->BackColor = System::Drawing::Color::Black;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"IA vs Pensamiento Crítico - Juego";
            this->KeyDown += gcnew KeyEventHandler(this, &GameForm::GameForm_KeyDown);
            this->KeyUp += gcnew KeyEventHandler(this, &GameForm::GameForm_KeyUp);

            this->Controls->Add(this->gameCanvas);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gameCanvas))->EndInit();
            this->ResumeLayout(false);
        }

        void InitializeGame()
        {
            // Inicializar variables
            tileSize = 16; // Tamaño de tile más pequeño para este mapa
            mapWidth = 76;  // Mapa más grande
            mapHeight = 56;

            playerWidth = 12; // Tamaño ajustado para el sprite
            playerHeight = 12;
            playerSpeed = 2;
            playerDirection = 0;
            animationFrame = 0;
            animationCounter = 0;

            // Posición inicial del jugador (centro del mapa)
            playerX = 600;
            playerY = 450;

            // Controles
            keyUp = keyDown = keyLeft = keyRight = false;

            // Cargar assets
            LoadAssets();

            // Crear mapa basado en la imagen
            gameMap = gcnew array<int, 2>(mapHeight, mapWidth);
            CreateMapFromImage();

            // Iniciar timer
            gameTimer->Start();
        }

        void LoadAssets()
        {
            try {
                // Cargar imagen del mapa
                mapImage = gcnew Bitmap("map.jpeg");

                // Cargar sprites del personaje
                playerSprites = gcnew Bitmap("player.png");

                // Definir frames del sprite (según la imagen que pasaste)
                // Imagen tiene 4 sprites: arriba-izq, arriba-der, abajo-izq, abajo-der
                playerFrames = gcnew array<Rectangle>(4);

                // Sprite mirando hacia atrás (arriba-izq)
                playerFrames[0] = Rectangle(0, 0, 16, 16);

                // Sprite mirando hacia la derecha (arriba-der)
                playerFrames[1] = Rectangle(16, 0, 16, 16);

                // Sprite mirando hacia adelante (abajo-izq)
                playerFrames[2] = Rectangle(0, 16, 16, 16);

                // Sprite mirando hacia la izquierda (abajo-der)
                playerFrames[3] = Rectangle(16, 16, 16, 16);

            }
            catch (Exception^ ex) {
                MessageBox::Show(
                    "Error al cargar los assets. Asegúrate de tener:\n\n" +
                    "• map.png (imagen del mapa)\n" +
                    "• player.png (sprites del personaje)\n\n" +
                    "en la carpeta del proyecto.\n\nError: " + ex->Message,
                    "Error al cargar assets",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Error
                );

                // Crear imágenes por defecto si no se pueden cargar
                mapImage = gcnew Bitmap(mapWidth * tileSize, mapHeight * tileSize);
                playerSprites = gcnew Bitmap(32, 32);
            }
        }

        void CreateMapFromImage()
        {
            // Si tenemos la imagen del mapa, analizar sus píxeles
            if (mapImage != nullptr && mapImage->Width > 0 && mapImage->Height > 0)
            {
                // Crear un mapa MUCHO MÁS PERMISIVO - solo paredes exteriores
                for (int y = 0; y < mapHeight; y++)
                {
                    for (int x = 0; x < mapWidth; x++)
                    {
                        // Muestrear el centro del tile
                        int pixelX = ((x * mapImage->Width) / mapWidth) + (mapImage->Width / (mapWidth * 2));
                        int pixelY = ((y * mapImage->Height) / mapHeight) + (mapImage->Height / (mapHeight * 2));

                        if (pixelX < mapImage->Width && pixelY < mapImage->Height && pixelX >= 0 && pixelY >= 0)
                        {
                            Color pixelColor = mapImage->GetPixel(pixelX, pixelY);

                            int brightness = (pixelColor.R + pixelColor.G + pixelColor.B) / 3;

                            // SOLO detectar paredes EXTERNAS muy oscuras (casi negras)
                            bool isExternalWall = (brightness < 25);

                            if (isExternalWall)
                            {
                                gameMap[y, x] = 1; // Muro
                            }
                            else
                            {
                                gameMap[y, x] = 0; // Todo lo demás es transitable
                            }
                        }
                        else
                        {
                            gameMap[y, x] = 0;
                        }
                    }
                }

                // Solo agregar bordes externos del mapa
                for (int x = 0; x < mapWidth; x++)
                {
                    gameMap[0, x] = 1;
                    gameMap[mapHeight - 1, x] = 1;
                }
                for (int y = 0; y < mapHeight; y++)
                {
                    gameMap[y, 0] = 1;
                    gameMap[y, mapWidth - 1] = 1;
                }
            }
            else
            {
                // Crear mapa por defecto si no hay imagen
                CreateDefaultMap();
            }
        }

        void CreateDefaultMap()
        {
            // Llenar todo con piso (muy permisivo)
            for (int y = 0; y < mapHeight; y++)
            {
                for (int x = 0; x < mapWidth; x++)
                {
                    gameMap[y, x] = 0;
                }
            }

            // Solo crear bordes externos
            for (int x = 0; x < mapWidth; x++)
            {
                gameMap[0, x] = 1;
                gameMap[1, x] = 1;
                gameMap[mapHeight - 1, x] = 1;
                gameMap[mapHeight - 2, x] = 1;
            }
            for (int y = 0; y < mapHeight; y++)
            {
                gameMap[y, 0] = 1;
                gameMap[y, 1] = 1;
                gameMap[y, mapWidth - 1] = 1;
                gameMap[y, mapWidth - 2] = 1;
            }

            // Agregar algunas paredes internas simples para referencia
            // Habitación superior izquierda
            for (int x = 4; x < 10; x++)
            {
                gameMap[4, x] = 1;
                gameMap[11, x] = 1;
            }
            for (int y = 4; y < 11; y++)
            {
                gameMap[y, 4] = 1;
                gameMap[y, 10] = 1;
            }
            // Puerta
            gameMap[7, 10] = 0;
        }

        bool CheckCollision(int x, int y, int width, int height)
        {
            // Hitbox mucho más pequeña - solo el centro del personaje
            int hitboxSize = 6;

            // Solo verificar el punto central del personaje
            int tileX = x / tileSize;
            int tileY = y / tileSize;

            // Verificar límites del mapa
            if (tileX < 0 || tileX >= mapWidth || tileY < 0 || tileY >= mapHeight)
                return true;

            // Verificar colisión con muros
            return (gameMap[tileY, tileX] == 1);
        }

        void GameForm_KeyDown(Object^ sender, KeyEventArgs^ e)
        {
            if (e->KeyCode == Keys::W || e->KeyCode == Keys::Up) keyUp = true;
            if (e->KeyCode == Keys::S || e->KeyCode == Keys::Down) keyDown = true;
            if (e->KeyCode == Keys::A || e->KeyCode == Keys::Left) keyLeft = true;
            if (e->KeyCode == Keys::D || e->KeyCode == Keys::Right) keyRight = true;
            if (e->KeyCode == Keys::Escape) this->Close();
        }

        void GameForm_KeyUp(Object^ sender, KeyEventArgs^ e)
        {
            if (e->KeyCode == Keys::W || e->KeyCode == Keys::Up) keyUp = false;
            if (e->KeyCode == Keys::S || e->KeyCode == Keys::Down) keyDown = false;
            if (e->KeyCode == Keys::A || e->KeyCode == Keys::Left) keyLeft = false;
            if (e->KeyCode == Keys::D || e->KeyCode == Keys::Right) keyRight = false;
        }

        void gameTimer_Tick(Object^ sender, EventArgs^ e)
        {
            // Movimiento del jugador
            int newX = playerX;
            int newY = playerY;

            bool isMoving = false;

            if (keyUp)
            {
                newY -= playerSpeed;
                playerDirection = 2; // Arriba
                isMoving = true;
            }
            if (keyDown)
            {
                newY += playerSpeed;
                playerDirection = 0; // Abajo
                isMoving = true;
            }
            if (keyLeft)
            {
                newX -= playerSpeed;
                playerDirection = 3; // Izquierda
                isMoving = true;
            }
            if (keyRight)
            {
                newX += playerSpeed;
                playerDirection = 1; // Derecha
                isMoving = true;
            }

            // Verificar colisiones en X
            if (!CheckCollision(newX, playerY, playerWidth, playerHeight))
            {
                playerX = newX;
            }
            else
            {
                // Si hay colisión, intentar deslizarse
                bool canSlideUp = !CheckCollision(newX, playerY - 1, playerWidth, playerHeight);
                bool canSlideDown = !CheckCollision(newX, playerY + 1, playerWidth, playerHeight);

                if (canSlideUp && (keyLeft || keyRight))
                {
                    playerX = newX;
                    playerY -= 1;
                }
                else if (canSlideDown && (keyLeft || keyRight))
                {
                    playerX = newX;
                    playerY += 1;
                }
            }

            // Verificar colisiones en Y
            if (!CheckCollision(playerX, newY, playerWidth, playerHeight))
            {
                playerY = newY;
            }
            else
            {
                // Si hay colisión, intentar deslizarse
                bool canSlideLeft = !CheckCollision(playerX - 1, newY, playerWidth, playerHeight);
                bool canSlideRight = !CheckCollision(playerX + 1, newY, playerWidth, playerHeight);

                if (canSlideLeft && (keyUp || keyDown))
                {
                    playerY = newY;
                    playerX -= 1;
                }
                else if (canSlideRight && (keyUp || keyDown))
                {
                    playerY = newY;
                    playerX += 1;
                }
            }

            // Animación simple
            if (isMoving)
            {
                animationCounter++;
                if (animationCounter > 10)
                {
                    animationFrame = (animationFrame + 1) % 2;
                    animationCounter = 0;
                }
            }

            // Redibujar
            gameCanvas->Invalidate();
        }

        void gameCanvas_Paint(Object^ sender, PaintEventArgs^ e)
        {
            Graphics^ g = e->Graphics;
            g->InterpolationMode = System::Drawing::Drawing2D::InterpolationMode::NearestNeighbor;
            g->PixelOffsetMode = System::Drawing::Drawing2D::PixelOffsetMode::Half;

            // Dibujar el mapa completo desde la imagen
            if (mapImage != nullptr && mapImage->Width > 0)
            {
                // Escalar la imagen del mapa al tamaño del canvas
                g->DrawImage(mapImage, 0, 0, mapWidth * tileSize, mapHeight * tileSize);
            }
            else
            {
                // Dibujar mapa con colores si no hay imagen
                for (int y = 0; y < mapHeight; y++)
                {
                    for (int x = 0; x < mapWidth; x++)
                    {
                        Color tileColor = (gameMap[y, x] == 1) ? Color::FromArgb(60, 60, 80) : Color::FromArgb(40, 40, 50);
                        SolidBrush^ brush = gcnew SolidBrush(tileColor);
                        g->FillRectangle(brush, x * tileSize, y * tileSize, tileSize, tileSize);
                    }
                }
            }

            // Calcular tamaño de renderizado del jugador - más grande y proporcional
            int renderWidth = 24;  // Tamaño fijo visible
            int renderHeight = 24;

            // Dibujar jugador con sprite
            if (playerSprites != nullptr && playerSprites->Width > 0)
            {
                Rectangle sourceRect = playerFrames[playerDirection];
                Rectangle destRect = Rectangle(playerX - renderWidth / 2, playerY - renderHeight / 2, renderWidth, renderHeight);

                g->DrawImage(playerSprites, destRect, sourceRect, GraphicsUnit::Pixel);
            }
            else
            {
                // Dibujar jugador con gráficos mejorados si no hay sprite
                int centerX = playerX;
                int centerY = playerY;

                // Sombra
                SolidBrush^ shadowBrush = gcnew SolidBrush(Color::FromArgb(120, 0, 0, 0));
                g->FillEllipse(shadowBrush, centerX - 10, centerY + 8, 20, 6);

                // Piernas (pantalón negro)
                SolidBrush^ legBrush = gcnew SolidBrush(Color::FromArgb(40, 40, 50));
                g->FillRectangle(legBrush, centerX - 6, centerY + 3, 5, 8);  // Pierna izquierda
                g->FillRectangle(legBrush, centerX + 1, centerY + 3, 5, 8);  // Pierna derecha

                // Cuerpo (torso azul)
                SolidBrush^ bodyBrush = gcnew SolidBrush(Color::FromArgb(50, 100, 200));
                g->FillRectangle(bodyBrush, centerX - 7, centerY - 3, 14, 8);

                // Brazos
                SolidBrush^ armBrush = gcnew SolidBrush(Color::FromArgb(200, 150, 100));
                g->FillRectangle(armBrush, centerX - 10, centerY - 2, 3, 8);  // Brazo izquierdo
                g->FillRectangle(armBrush, centerX + 7, centerY - 2, 3, 8);  // Brazo derecho

                // Cabeza (piel)
                SolidBrush^ headBrush = gcnew SolidBrush(Color::FromArgb(200, 150, 100));
                g->FillEllipse(headBrush, centerX - 6, centerY - 11, 12, 12);

                // Cabello
                SolidBrush^ hairBrush = gcnew SolidBrush(Color::FromArgb(80, 50, 30));
                g->FillEllipse(hairBrush, centerX - 6, centerY - 12, 12, 7);

                // Ojos según dirección
                SolidBrush^ eyeBrush = gcnew SolidBrush(Color::Black);
                if (playerDirection == 1) // Derecha
                {
                    g->FillEllipse(eyeBrush, centerX + 1, centerY - 7, 2, 2);
                    g->FillEllipse(eyeBrush, centerX + 4, centerY - 7, 2, 2);
                }
                else if (playerDirection == 3) // Izquierda
                {
                    g->FillEllipse(eyeBrush, centerX - 6, centerY - 7, 2, 2);
                    g->FillEllipse(eyeBrush, centerX - 3, centerY - 7, 2, 2);
                }
                else // Frente o atrás
                {
                    g->FillEllipse(eyeBrush, centerX - 4, centerY - 7, 2, 2);
                    g->FillEllipse(eyeBrush, centerX + 2, centerY - 7, 2, 2);
                }

                // Borde blanco para hacerlo más visible
                Pen^ outlinePen = gcnew Pen(Color::FromArgb(200, 255, 255, 255), 1.5f);
                g->DrawEllipse(outlinePen, centerX - 6, centerY - 11, 12, 12);
            }

            // Información con mejor visibilidad
            String^ info = String::Format("Pos: ({0}, {1}) Tile: ({2}, {3}) | WASD/Flechas para mover | ESC para salir",
                playerX, playerY, playerX / tileSize, playerY / tileSize);

            // Fondo para el texto
            SolidBrush^ textBg = gcnew SolidBrush(Color::FromArgb(220, 0, 0, 0));
            g->FillRectangle(textBg, 0, mapHeight * tileSize, 1216, 30);

            g->DrawString(info, gcnew System::Drawing::Font("Segoe UI", 9, FontStyle::Bold), Brushes::White, 10, mapHeight * tileSize + 8);
        }
    };

    // Modificar el MainMenuForm para abrir el juego
    public ref class MainMenuForm : public System::Windows::Forms::Form
    {
    public:
        MainMenuForm(void)
        {
            InitializeComponent();
        }

    protected:
        ~MainMenuForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;
        Label^ lblTitle;
        Button^ btnPlay;
        Button^ btnRules;
        Button^ btnCredits;
        Button^ btnExit;

        void InitializeComponent(void)
        {
            this->lblTitle = (gcnew Label());
            this->btnPlay = (gcnew Button());
            this->btnRules = (gcnew Button());
            this->btnCredits = (gcnew Button());
            this->btnExit = (gcnew Button());
            this->SuspendLayout();

            // Form
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(600, 500);
            this->BackColor = System::Drawing::Color::FromArgb(20, 20, 40);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Menú Principal";

            // lblTitle
            this->lblTitle->AutoSize = false;
            this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 28, System::Drawing::FontStyle::Bold));
            this->lblTitle->ForeColor = System::Drawing::Color::FromArgb(100, 200, 255);
            this->lblTitle->Location = System::Drawing::Point(0, 50);
            this->lblTitle->Size = System::Drawing::Size(600, 80);
            this->lblTitle->Text = L"IA vs Pensamiento Crítico";
            this->lblTitle->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

            // btnPlay
            this->btnPlay->BackColor = System::Drawing::Color::FromArgb(50, 150, 250);
            this->btnPlay->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnPlay->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold));
            this->btnPlay->ForeColor = System::Drawing::Color::White;
            this->btnPlay->Location = System::Drawing::Point(200, 170);
            this->btnPlay->Size = System::Drawing::Size(200, 50);
            this->btnPlay->Text = L"Jugar";
            this->btnPlay->UseVisualStyleBackColor = false;
            this->btnPlay->Click += gcnew System::EventHandler(this, &MainMenuForm::btnPlay_Click);

            // btnRules
            this->btnRules->BackColor = System::Drawing::Color::FromArgb(70, 70, 90);
            this->btnRules->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnRules->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14));
            this->btnRules->ForeColor = System::Drawing::Color::White;
            this->btnRules->Location = System::Drawing::Point(200, 240);
            this->btnRules->Size = System::Drawing::Size(200, 50);
            this->btnRules->Text = L"Reglas";
            this->btnRules->UseVisualStyleBackColor = false;

            // btnCredits
            this->btnCredits->BackColor = System::Drawing::Color::FromArgb(70, 70, 90);
            this->btnCredits->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnCredits->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14));
            this->btnCredits->ForeColor = System::Drawing::Color::White;
            this->btnCredits->Location = System::Drawing::Point(200, 310);
            this->btnCredits->Size = System::Drawing::Size(200, 50);
            this->btnCredits->Text = L"Créditos";
            this->btnCredits->UseVisualStyleBackColor = false;

            // btnExit
            this->btnExit->BackColor = System::Drawing::Color::FromArgb(200, 50, 50);
            this->btnExit->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnExit->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14));
            this->btnExit->ForeColor = System::Drawing::Color::White;
            this->btnExit->Location = System::Drawing::Point(200, 380);
            this->btnExit->Size = System::Drawing::Size(200, 50);
            this->btnExit->Text = L"Salir";
            this->btnExit->UseVisualStyleBackColor = false;
            this->btnExit->Click += gcnew System::EventHandler(this, &MainMenuForm::btnExit_Click);

            // Add controls
            this->Controls->Add(this->lblTitle);
            this->Controls->Add(this->btnPlay);
            this->Controls->Add(this->btnRules);
            this->Controls->Add(this->btnCredits);
            this->Controls->Add(this->btnExit);
            this->ResumeLayout(false);
        }

        void btnPlay_Click(System::Object^ sender, System::EventArgs^ e)
        {
            GameForm^ game = gcnew GameForm();
            this->Hide();
            game->ShowDialog();
            this->Show();
        }

        void btnExit_Click(System::Object^ sender, System::EventArgs^ e)
        {
            Application::Exit();
        }
    };
}