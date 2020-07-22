#pragma once

#include "IDiagram.h"

class DiagramMaxSizeDep : public IDiagram{

public:

	DiagramMaxSizeDep(HWND hwnd, int width, int height);
	~DiagramMaxSizeDep() = default;

	void SetData(std::vector<std::pair<std::wstring, int>> data) override;

	void Draw() final;

private:
	
	int maxValueOfSIze = 0;
	float widthOfElment;

};

