#include "Diagram.h"

Diagram::Diagram(HWND hwnd, int width, int height)
    :target(hwnd), targetWidth(width), targetHeight(height) {

    HRESULT hr = D2D1CreateFactory(
        D2D1_FACTORY_TYPE_SINGLE_THREADED,
        &pD2DFactory
    );

    hr = pD2DFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(
            this->target,
            D2D1::SizeU(targetWidth, targetHeight)), &pRT
    );
}

void Diagram::SetData(std::vector<std::pair<std::wstring, int>> data)
{
    pairsNameSize = std::move(data);

    srand(time(NULL));

    brushes.clear();
    for (const auto& _ : pairsNameSize) {
        CComPtr<ID2D1SolidColorBrush> temp;

        pRT->CreateSolidColorBrush(
            D2D1::ColorF(
                (rand() % 100 + 1)/100.f,
                (rand() % 100 + 1)/100.f,
                (rand() % 100 + 1)/ 100.f),
            &temp
        );
        brushes.push_back(temp);
    }
}