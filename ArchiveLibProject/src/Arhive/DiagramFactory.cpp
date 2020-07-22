#include "DiagramFactory.h"

#include "Diagram/DiagramArcSIzeDep.h"
#include "Diagram/DiagramMaxSizeDep.h"

std::unique_ptr<IDiagram> DiagramFactory::CreateDiagram(HWND hwnd, int width, int height, DiagramType diagramType)
{
	switch (diagramType) {

	case DiagramType::ArcSizeDep:
		return std::unique_ptr<IDiagram> {new DiagramArcSIzeDep(hwnd, width, height)};

	case DiagramType::MaxSizeDep:
		return std::unique_ptr<IDiagram> {new DiagramMaxSizeDep(hwnd, width, height)};

	default:
		return nullptr;
	}

}


