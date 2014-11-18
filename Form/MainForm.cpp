#include "MainForm.h"
#include "..\stdafx.h"
//Compability to VSC++ 2013
//Enabled /clr
//Disabled /EHsc
using namespace MyAdmin;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	// Create the main window and run it

	Application::Run(gcnew MainForm());

	return 0;
}
