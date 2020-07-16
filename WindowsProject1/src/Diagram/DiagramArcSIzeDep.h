#pragma once
#include "Diagram.h"

class DiagramArcSIzeDep : public Diagram {

public:

	DiagramArcSIzeDep(HWND hwnd, int width, int height);
	~DiagramArcSIzeDep() = default;

	void SetData(std::vector<std::pair<std::wstring, int>> data) override;

	void Draw() final;

private:

	int arcValueOfSIze = 0;
	float widthOfElment;


};

