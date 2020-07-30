#pragma once

#include "IDiagram.h"

class TestGrid : public IDiagram {
public:
	TestGrid(HWND hwnd, int width, int height);
	~TestGrid() = default;

	void SetData(std::vector<std::pair<std::wstring, int>> data) override;

	void Draw() final;
};

