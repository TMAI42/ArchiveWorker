#pragma once

#include "Diagram/IDiagram.h"
#include "DiagramTypes.h"
#include <memory>

class DiagramFactory{

public:
	static std::unique_ptr<IDiagram> CreateDiagram(HWND hwnd, int width, int height, DiagramType diagramType);

};

