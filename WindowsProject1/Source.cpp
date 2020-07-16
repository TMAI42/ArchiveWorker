#include "src/App.h"
#include "src/Arhive/Archive.h"


int CALLBACK wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
	CApp app{};
	return app.run();
}