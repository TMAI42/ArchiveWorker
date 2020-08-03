#pragma once

#include "IDiagram.h"

class DiagramMaxSizeDep : public IDiagram{

public:

	using IDiagram::IDiagram; 
	~DiagramMaxSizeDep() = default;

	void SetData(std::vector<std::pair<std::wstring, int>> data) override;

	void Draw() final;

private:
	
	int maxValueOfSIze = 0;
	float widthOfElment;

};

