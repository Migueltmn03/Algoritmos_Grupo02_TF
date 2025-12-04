#include "GameIntro.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args)
{
    // Habilitar estilos visuales de Windows
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // Crear y mostrar el formulario del menú principal
    GameIntro::MainMenuForm^ mainMenu = gcnew GameIntro::MainMenuForm();
    Application::Run(mainMenu);

    return 0;
}
