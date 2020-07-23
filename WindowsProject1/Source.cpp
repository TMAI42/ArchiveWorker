#include "src/App.h"



int CALLBACK wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
	CApp app{};
	return app.run();
}