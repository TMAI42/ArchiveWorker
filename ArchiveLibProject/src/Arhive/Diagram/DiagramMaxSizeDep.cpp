#include "DiagramMaxSizeDep.h"


void DiagramMaxSizeDep::SetData(std::vector<std::pair<std::wstring, int>> data)
{
    IDiagram::SetData(std::move(data));

	for (auto& p : pairsNameSize) {
		maxValueOfSIze = (p.second > maxValueOfSIze) ? p.second : maxValueOfSIze;
	}

    widthOfElment =( targetWidth / static_cast<float>(pairsNameSize.size()))- targetWidth/100;
}

void DiagramMaxSizeDep::Draw() {

    pRT->BeginDraw();

    float heightK = 0.799;
    float widthK = 0.765;

    pRT->Clear(D2D1::ColorF(D2D1::ColorF::White));

    for (int i = 0; i < pairsNameSize.size(); i++) {

        pRT->FillRectangle(
            D2D1::RectF((i * widthOfElment + i * targetWidth / 100)*widthK,
                (targetHeight - pairsNameSize[i].second * (targetHeight / static_cast<float>(maxValueOfSIze)))*heightK,
                ((i + 1) * widthOfElment + i * targetWidth / 100)*widthK, targetHeight*heightK),
            brushes[i]);
    }

    pRT->EndDraw();

}
