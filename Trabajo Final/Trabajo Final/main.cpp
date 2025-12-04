#include "MenuSystem.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	// Iniciar con el menú principal
	Application::Run(gcnew GameProject::MainMenuForm());

	return 0;
}