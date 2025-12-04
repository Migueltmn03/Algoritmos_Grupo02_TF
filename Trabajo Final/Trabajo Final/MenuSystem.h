// MenuSystem.h - Sistema de menús con integración al juego
#pragma once
#include "GameForm.h"

namespace GameProject {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    // ============================================
    // FORMULARIO DE CRÉDITOS
    // ============================================
    public ref class CreditsForm : public System::Windows::Forms::Form
    {
    public:
        CreditsForm(void)
        {
            InitializeComponent();
        }

    protected:
        ~CreditsForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;
        Label^ lblTitle;
        Label^ lblCredits;
        Button^ btnBack;

        void InitializeComponent(void)
        {
            this->lblTitle = (gcnew Label());
            this->lblCredits = (gcnew Label());
            this->btnBack = (gcnew Button());
            this->SuspendLayout();

            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(500, 400);
            this->BackColor = System::Drawing::Color::FromArgb(20, 20, 40);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Créditos";

            this->lblTitle->AutoSize = false;
            this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 24, System::Drawing::FontStyle::Bold));
            this->lblTitle->ForeColor = System::Drawing::Color::White;
            this->lblTitle->Location = System::Drawing::Point(0, 40);
            this->lblTitle->Size = System::Drawing::Size(500, 50);
            this->lblTitle->Text = L"CRÉDITOS";
            this->lblTitle->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

            this->lblCredits->AutoSize = false;
            this->lblCredits->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16));
            this->lblCredits->ForeColor = System::Drawing::Color::FromArgb(100, 200, 255);
            this->lblCredits->Location = System::Drawing::Point(50, 130);
            this->lblCredits->Size = System::Drawing::Size(400, 150);
            this->lblCredits->Text = L"• Miguel Málaga\n• Lucas Benites\n• Justin Maturrano";
            this->lblCredits->TextAlign = System::Drawing::ContentAlignment::TopCenter;

            this->btnBack->BackColor = System::Drawing::Color::FromArgb(70, 70, 90);
            this->btnBack->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnBack->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold));
            this->btnBack->ForeColor = System::Drawing::Color::White;
            this->btnBack->Location = System::Drawing::Point(175, 320);
            this->btnBack->Size = System::Drawing::Size(150, 45);
            this->btnBack->Text = L"Volver";
            this->btnBack->UseVisualStyleBackColor = false;
            this->btnBack->Click += gcnew System::EventHandler(this, &CreditsForm::btnBack_Click);

            this->Controls->Add(this->lblTitle);
            this->Controls->Add(this->lblCredits);
            this->Controls->Add(this->btnBack);
            this->ResumeLayout(false);
        }

        void btnBack_Click(System::Object^ sender, System::EventArgs^ e)
        {
            this->Close();
        }
    };

    // ============================================
    // FORMULARIO DE REGLAS
    // ============================================
    public ref class RulesForm : public System::Windows::Forms::Form
    {
    public:
        RulesForm(void)
        {
            InitializeComponent();
        }

    protected:
        ~RulesForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;
        Label^ lblTitle;
        RichTextBox^ txtRules;
        Button^ btnBack;

        void InitializeComponent(void)
        {
            this->lblTitle = (gcnew Label());
            this->txtRules = (gcnew RichTextBox());
            this->btnBack = (gcnew Button());
            this->SuspendLayout();

            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(600, 500);
            this->BackColor = System::Drawing::Color::FromArgb(20, 20, 40);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Reglas del Juego";

            this->lblTitle->AutoSize = false;
            this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 24, System::Drawing::FontStyle::Bold));
            this->lblTitle->ForeColor = System::Drawing::Color::White;
            this->lblTitle->Location = System::Drawing::Point(0, 30);
            this->lblTitle->Size = System::Drawing::Size(600, 50);
            this->lblTitle->Text = L"REGLAS";
            this->lblTitle->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

            this->txtRules->BackColor = System::Drawing::Color::FromArgb(40, 40, 60);
            this->txtRules->BorderStyle = System::Windows::Forms::BorderStyle::None;
            this->txtRules->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
            this->txtRules->ForeColor = System::Drawing::Color::White;
            this->txtRules->Location = System::Drawing::Point(50, 100);
            this->txtRules->ReadOnly = true;
            this->txtRules->Size = System::Drawing::Size(500, 300);
            this->txtRules->Text = L"CÓMO JUGAR:\n\n"
                L"1. Usa las teclas WASD o las flechas para mover a tu personaje.\n\n"
                L"2. Explora el mapa y evita las paredes.\n\n"
                L"3. Presiona F1 para ver información de debug.\n\n"
                L"4. Presiona F2 para ver el mapa de colisiones.\n\n"
                L"5. Presiona ESC para volver al menú.\n\n"
                L"¡Buena suerte explorando la estación espacial!";

            this->btnBack->BackColor = System::Drawing::Color::FromArgb(70, 70, 90);
            this->btnBack->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnBack->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold));
            this->btnBack->ForeColor = System::Drawing::Color::White;
            this->btnBack->Location = System::Drawing::Point(225, 420);
            this->btnBack->Size = System::Drawing::Size(150, 45);
            this->btnBack->Text = L"Volver";
            this->btnBack->UseVisualStyleBackColor = false;
            this->btnBack->Click += gcnew System::EventHandler(this, &RulesForm::btnBack_Click);

            this->Controls->Add(this->lblTitle);
            this->Controls->Add(this->txtRules);
            this->Controls->Add(this->btnBack);
            this->ResumeLayout(false);
        }

        void btnBack_Click(System::Object^ sender, System::EventArgs^ e)
        {
            this->Close();
        }
    };

    // ============================================
    // FORMULARIO DE INTRODUCCIÓN
    // ============================================
    public ref class IntroForm : public System::Windows::Forms::Form
    {
    public:
        IntroForm(void)
        {
            InitializeComponent();
            StartTypewriterEffect();
        }

    protected:
        ~IntroForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;
        PictureBox^ picGif;
        Label^ lblStory;
        Timer^ typewriterTimer;
        String^ fullText;
        int currentCharIndex;

        void InitializeComponent(void)
        {
            this->picGif = (gcnew PictureBox());
            this->lblStory = (gcnew Label());
            this->typewriterTimer = (gcnew Timer());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picGif))->BeginInit();
            this->SuspendLayout();

            this->fullText = L"En un rígido mundo futurista, un robot le presenta a su compañero humano la ruta a seguir, "
                L"avalado por un 99.8% de éxito y calificado como la única opción lógica. A pesar de la certeza de los datos, "
                L"el humano desconfía. La predictibilidad del sistema le hace sentir que hay una trampa que la intuición "
                L"puede detectar, pero la máquina no.\n\n"
                L"Durante un combate contra enemigos idénticos y predecibles, Alex intenta ejecutar una estrategia creativa "
                L"y sorpresiva. Su plan es inmediatamente rechazado por el robot, quien impone el protocolo de combate estándar, "
                L"argumentando que es más eficiente y que la cooperación debe maximizar el rendimiento.\n\n"
                L"Presiona cualquier tecla para comenzar...";

            this->currentCharIndex = 0;

            this->picGif->Location = System::Drawing::Point(200, 50);
            this->picGif->Size = System::Drawing::Size(400, 400);
            this->picGif->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
            this->picGif->BackColor = System::Drawing::Color::Transparent;

            try {
                this->picGif->Image = Image::FromFile("earth.gif");
            }
            catch (Exception^) {
                // GIF no encontrado, continuar sin imagen
            }

            this->lblStory->AutoSize = false;
            this->lblStory->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Regular));
            this->lblStory->ForeColor = System::Drawing::Color::White;
            this->lblStory->Location = System::Drawing::Point(50, 470);
            this->lblStory->Size = System::Drawing::Size(900, 200);
            this->lblStory->Text = L"";
            this->lblStory->BackColor = System::Drawing::Color::Transparent;

            this->typewriterTimer->Interval = 30;
            this->typewriterTimer->Tick += gcnew System::EventHandler(this, &IntroForm::typewriterTimer_Tick);

            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1000, 700);
            this->BackColor = System::Drawing::Color::Black;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Introducción";
            this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &IntroForm::IntroForm_KeyDown);
            this->Click += gcnew System::EventHandler(this, &IntroForm::IntroForm_Click);

            this->Controls->Add(this->lblStory);
            this->Controls->Add(this->picGif);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picGif))->EndInit();
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
            }
        }

        void IntroForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
        {
            if (e->KeyCode == Keys::Space || e->KeyCode == Keys::Enter || e->KeyCode == Keys::Escape)
            {
                this->Close();
            }
        }

        void IntroForm_Click(System::Object^ sender, System::EventArgs^ e)
        {
            this->Close();
        }
    };

    // ============================================
    // FORMULARIO PRINCIPAL DEL MENÚ
    // ============================================
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

            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(600, 500);
            this->BackColor = System::Drawing::Color::FromArgb(20, 20, 40);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Menú Principal";

            this->lblTitle->AutoSize = false;
            this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 24, System::Drawing::FontStyle::Bold));
            this->lblTitle->ForeColor = System::Drawing::Color::FromArgb(100, 200, 255);
            this->lblTitle->Location = System::Drawing::Point(0, 50);
            this->lblTitle->Size = System::Drawing::Size(600, 80);
            this->lblTitle->Text = L"IA vs Pensamiento Crítico";
            this->lblTitle->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

            this->btnPlay->BackColor = System::Drawing::Color::FromArgb(50, 150, 250);
            this->btnPlay->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnPlay->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold));
            this->btnPlay->ForeColor = System::Drawing::Color::White;
            this->btnPlay->Location = System::Drawing::Point(200, 170);
            this->btnPlay->Size = System::Drawing::Size(200, 50);
            this->btnPlay->Text = L"Jugar";
            this->btnPlay->UseVisualStyleBackColor = false;
            this->btnPlay->Click += gcnew System::EventHandler(this, &MainMenuForm::btnPlay_Click);

            this->btnRules->BackColor = System::Drawing::Color::FromArgb(70, 70, 90);
            this->btnRules->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnRules->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14));
            this->btnRules->ForeColor = System::Drawing::Color::White;
            this->btnRules->Location = System::Drawing::Point(200, 240);
            this->btnRules->Size = System::Drawing::Size(200, 50);
            this->btnRules->Text = L"Reglas";
            this->btnRules->UseVisualStyleBackColor = false;
            this->btnRules->Click += gcnew System::EventHandler(this, &MainMenuForm::btnRules_Click);

            this->btnCredits->BackColor = System::Drawing::Color::FromArgb(70, 70, 90);
            this->btnCredits->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnCredits->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14));
            this->btnCredits->ForeColor = System::Drawing::Color::White;
            this->btnCredits->Location = System::Drawing::Point(200, 310);
            this->btnCredits->Size = System::Drawing::Size(200, 50);
            this->btnCredits->Text = L"Créditos";
            this->btnCredits->UseVisualStyleBackColor = false;
            this->btnCredits->Click += gcnew System::EventHandler(this, &MainMenuForm::btnCredits_Click);

            this->btnExit->BackColor = System::Drawing::Color::FromArgb(200, 50, 50);
            this->btnExit->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnExit->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14));
            this->btnExit->ForeColor = System::Drawing::Color::White;
            this->btnExit->Location = System::Drawing::Point(200, 380);
            this->btnExit->Size = System::Drawing::Size(200, 50);
            this->btnExit->Text = L"Salir";
            this->btnExit->UseVisualStyleBackColor = false;
            this->btnExit->Click += gcnew System::EventHandler(this, &MainMenuForm::btnExit_Click);

            this->Controls->Add(this->lblTitle);
            this->Controls->Add(this->btnPlay);
            this->Controls->Add(this->btnRules);
            this->Controls->Add(this->btnCredits);
            this->Controls->Add(this->btnExit);
            this->ResumeLayout(false);
        }

        void btnPlay_Click(System::Object^ sender, System::EventArgs^ e)
        {
            // Mostrar la introducción
            IntroForm^ intro = gcnew IntroForm();
            intro->ShowDialog();

            // Después de la introducción, abrir el juego
            GameForm^ game = gcnew GameForm();
            game->ShowDialog();
        }

        void btnRules_Click(System::Object^ sender, System::EventArgs^ e)
        {
            RulesForm^ rules = gcnew RulesForm();
            rules->ShowDialog();
        }

        void btnCredits_Click(System::Object^ sender, System::EventArgs^ e)
        {
            CreditsForm^ credits = gcnew CreditsForm();
            credits->ShowDialog();
        }

        void btnExit_Click(System::Object^ sender, System::EventArgs^ e)
        {
            Application::Exit();
        }
    };
}