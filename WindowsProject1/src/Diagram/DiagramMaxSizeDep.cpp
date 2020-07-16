#include "DiagramMaxSizeDep.h"



DiagramMaxSizeDep::DiagramMaxSizeDep(HWND hwnd, int width, int height):Diagram(hwnd, width, height){}

void DiagramMaxSizeDep::SetData(std::vector<std::pair<std::wstring, int>> data)
{
    Diagram::SetData(data);
	/*pairsNameSize = std::move(data);*/
	for (auto& p : pairsNameSize) {
		maxValueOfSIze = (p.second > maxValueOfSIze) ? p.second : maxValueOfSIze;
	}
    widthOfElment =( targetWidth / static_cast<float>(pairsNameSize.size()))- targetWidth/100;
}

void DiagramMaxSizeDep::Draw() {

    pRT->BeginDraw();
    
    for (int i = 0; i < pairsNameSize.size(); i++) {
        pRT->FillRectangle(
            D2D1::RectF(i * widthOfElment + i * targetWidth / 100,
                targetHeight - pairsNameSize[i].second * (targetHeight / static_cast<float>(maxValueOfSIze)),
                (i + 1) * widthOfElment + i * targetWidth / 100, targetHeight),
            brushes[i]);
    }

    pRT->EndDraw();

}
