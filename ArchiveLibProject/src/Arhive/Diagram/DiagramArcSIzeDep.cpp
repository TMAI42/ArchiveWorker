#include "DiagramArcSIzeDep.h"

DiagramArcSIzeDep::DiagramArcSIzeDep(HWND hwnd, int width, int height) :IDiagram(hwnd, width, height) {}

void DiagramArcSIzeDep::SetData(std::vector<std::pair<std::wstring, int>> data) {

	IDiagram::SetData(data);
	for (const auto& pair : pairsNameSize)
		arcValueOfSIze += pair.second;

	widthOfElment = (targetWidth / static_cast<float>(pairsNameSize.size())) - targetWidth / 100;

}

void DiagramArcSIzeDep::Draw() {

	pRT->BeginDraw();

	pRT->Clear(D2D1::ColorF(D2D1::ColorF::White));
	for (int i = 0; i < pairsNameSize.size(); i++) {
		auto currentHeight = pairsNameSize[i].second * targetHeight / static_cast<float>(arcValueOfSIze);

		float heightK = 0.799;
		float widthK = 0.765;

		pRT->FillRectangle(
			D2D1::RectF((i * widthOfElment + i * targetWidth / 100) * widthK,
				(targetHeight - currentHeight) * heightK,
				((i + 1) * widthOfElment + i * targetWidth / 100) * widthK, targetHeight * heightK),
			brushes[i]);
	}

	pRT->EndDraw();

}