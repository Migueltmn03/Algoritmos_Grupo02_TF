#pragma once

namespace GameIntro {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    // Forward declaration
    ref class IntroForm;

    // Formulario de Créditos
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

            // Form
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(500, 400);
            this->BackColor = System::Drawing::Color::FromArgb(20, 20, 40);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Créditos";

            // lblTitle
            this->lblTitle->AutoSize = false;
            this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 24, System::Drawing::FontStyle::Bold));
            this->lblTitle->ForeColor = System::Drawing::Color::White;
            this->lblTitle->Location = System::Drawing::Point(0, 40);
            this->lblTitle->Size = System::Drawing::Size(500, 50);
            this->lblTitle->Text = L"CRÉDITOS";
            this->lblTitle->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

            // lblCredits
            this->lblCredits->AutoSize = false;
            this->lblCredits->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16));
            this->lblCredits->ForeColor = System::Drawing::Color::FromArgb(100, 200, 255);
            this->lblCredits->Location = System::Drawing::Point(50, 130);
            this->lblCredits->Size = System::Drawing::Size(400, 150);
            this->lblCredits->Text = L"• Miguel Málaga\n\n• Lucas Benites\n\n• Justin Maturrano";
            this->lblCredits->TextAlign = System::Drawing::ContentAlignment::TopCenter;

            // btnBack
            this->btnBack->BackColor = System::Drawing::Color::FromArgb(70, 70, 90);
            this->btnBack->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnBack->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold));
            this->btnBack->ForeColor = System::Drawing::Color::White;
            this->btnBack->Location = System::Drawing::Point(175, 320);
            this->btnBack->Size = System::Drawing::Size(150, 45);
            this->btnBack->Text = L"Volver";
            this->btnBack->UseVisualStyleBackColor = false;
            this->btnBack->Click += gcnew System::EventHandler(this, &CreditsForm::btnBack_Click);

            // Add controls
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

    // Formulario de Reglas
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

            // Form
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(600, 500);
            this->BackColor = System::Drawing::Color::FromArgb(20, 20, 40);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Reglas del Juego";

            // lblTitle
            this->lblTitle->AutoSize = false;
            this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 24, System::Drawing::FontStyle::Bold));
            this->lblTitle->ForeColor = System::Drawing::Color::White;
            this->lblTitle->Location = System::Drawing::Point(0, 30);
            this->lblTitle->Size = System::Drawing::Size(600, 50);
            this->lblTitle->Text = L"REGLAS";
            this->lblTitle->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

            // txtRules
            this->txtRules->BackColor = System::Drawing::Color::FromArgb(40, 40, 60);
            this->txtRules->BorderStyle = System::Windows::Forms::BorderStyle::None;
            this->txtRules->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
            this->txtRules->ForeColor = System::Drawing::Color::White;
            this->txtRules->Location = System::Drawing::Point(50, 100);
            this->txtRules->ReadOnly = true;
            this->txtRules->Size = System::Drawing::Size(500, 300);
            this->txtRules->Text = L"Aquí van las reglas de tu juego:\n\n"
                L"1. Regla número uno\n\n"
                L"2. Regla número dos\n\n"
                L"3. Regla número tres\n\n"
                L"¡Diviértete jugando!";

            // btnBack
            this->btnBack->BackColor = System::Drawing::Color::FromArgb(70, 70, 90);
            this->btnBack->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnBack->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold));
            this->btnBack->ForeColor = System::Drawing::Color::White;
            this->btnBack->Location = System::Drawing::Point(225, 420);
            this->btnBack->Size = System::Drawing::Size(150, 45);
            this->btnBack->Text = L"Volver";
            this->btnBack->UseVisualStyleBackColor = false;
            this->btnBack->Click += gcnew System::EventHandler(this, &RulesForm::btnBack_Click);

            // Add controls
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

    // Formulario de Introducción con GIF
    public ref class IntroForm : public System::Windows::Forms::Form
    {
    public:
        IntroForm(void)
        {
            InitializeComponent();
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

        void InitializeComponent(void)
        {
            this->picGif = (gcnew PictureBox());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picGif))->BeginInit();
            this->SuspendLayout();

            // picGif
            this->picGif->Dock = System::Windows::Forms::DockStyle::Fill;
            this->picGif->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
            this->picGif->BackColor = System::Drawing::Color::Black;

            // Cargar el GIF (asegúrate de tener el archivo en la ruta correcta)
            try {
                this->picGif->Image = Image::FromFile("earth.gif");
            }
            catch (Exception^ ex) {
                MessageBox::Show("No se pudo cargar el GIF. Asegúrate de tener 'earth.gif' en la carpeta del proyecto.\n\nError: " + ex->Message,
                    "Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            }

            // Form
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(800, 600);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Introducción";
            this->Click += gcnew System::EventHandler(this, &IntroForm::IntroForm_Click);

            // Add controls
            this->Controls->Add(this->picGif);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picGif))->EndInit();
            this->ResumeLayout(false);
        }

        void IntroForm_Click(System::Object^ sender, System::EventArgs^ e)
        {
            // Cerrar la introducción al hacer clic
            this->Close();
        }
    };

    // Formulario Principal del Menú
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
            this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 32, System::Drawing::FontStyle::Bold));
            this->lblTitle->ForeColor = System::Drawing::Color::FromArgb(100, 200, 255);
            this->lblTitle->Location = System::Drawing::Point(0, 50);
            this->lblTitle->Size = System::Drawing::Size(600, 80);
            this->lblTitle->Text = L"MI JUEGO";
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
            this->btnRules->Click += gcnew System::EventHandler(this, &MainMenuForm::btnRules_Click);

            // btnCredits
            this->btnCredits->BackColor = System::Drawing::Color::FromArgb(70, 70, 90);
            this->btnCredits->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnCredits->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14));
            this->btnCredits->ForeColor = System::Drawing::Color::White;
            this->btnCredits->Location = System::Drawing::Point(200, 310);
            this->btnCredits->Size = System::Drawing::Size(200, 50);
            this->btnCredits->Text = L"Créditos";
            this->btnCredits->UseVisualStyleBackColor = false;
            this->btnCredits->Click += gcnew System::EventHandler(this, &MainMenuForm::btnCredits_Click);

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
            IntroForm^ intro = gcnew IntroForm();
            intro->ShowDialog();
            // Aquí puedes abrir tu juego después de la introducción
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