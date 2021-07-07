#include <windows.h>

int main()
{
	if(MessageBox(NULL, "Estamos preparando todo para apagar, seguro que quieres continuar?", "Preparando para apagar", MB_OKCANCEL) == IDOK)
		system("shutdown -p");
}