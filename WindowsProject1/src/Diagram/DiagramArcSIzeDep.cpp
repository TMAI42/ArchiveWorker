#include "DiagramArcSIzeDep.h"

DiagramArcSIzeDep::DiagramArcSIzeDep(HWND hwnd, int width, int height):Diagram(hwnd, width, height) {}

void DiagramArcSIzeDep::SetData(std::vector<std::pair<std::wstring, int>> data){

	Diagram::SetData(data);
	for (const auto& pair : pairsNameSize)
		arcValueOfSIze += pair.second;

	widthOfElment = (targetWidth / static_cast<float>(pairsNameSize.size())) - targetWidth / 100;

}

void DiagramArcSIzeDep::Draw() {

    pRT->BeginDraw();

    pRT->Clear(D2D1::ColorF(D2D1::ColorF::White));
    for (int i = 0; i < pairsNameSize.size(); i++) {
        auto currentHeight = pairsNameSize[i].second * targetHeight / static_cast<float>(arcValueOfSIze);

        pRT->FillRectangle(
            D2D1::RectF(i * widthOfElment + i * targetWidth / 100,
                targetHeight - currentHeight,
                (i + 1) * widthOfElment + i * targetWidth / 100, targetHeight),
            brushes[i]);
    }

    pRT->EndDraw();

}