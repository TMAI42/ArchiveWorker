#pragma once
#include "IDiagram.h"

class DiagramArcSIzeDep : public IDiagram {

public:

	using IDiagram::IDiagram;
	~DiagramArcSIzeDep() = default;

	void SetData(std::vector<std::pair<std::wstring, int>> data) override;

	void Draw() final;

private:

	int arcValueOfSIze = 0;
	float widthOfElment;


};

