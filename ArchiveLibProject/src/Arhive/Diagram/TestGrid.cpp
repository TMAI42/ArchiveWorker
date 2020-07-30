#include "TestGrid.h"


TestGrid::TestGrid(HWND hwnd, int width, int height) :IDiagram(hwnd, width, height) {}

void TestGrid::SetData(std::vector<std::pair<std::wstring, int>> data)
{
}

void TestGrid::Draw() {


    CComPtr<ID2D1SolidColorBrush> m_pLightSlateGrayBrush;

    pRT->CreateSolidColorBrush(
        D2D1::ColorF(D2D1::ColorF::LightSlateGray),
        &m_pLightSlateGrayBrush
    );

    pRT->BeginDraw();


    D2D1_SIZE_F rtSize = pRT->GetSize();

    int width = static_cast<int>(rtSize.width);
    int height = static_cast<int>(rtSize.height);


    for (int x = 0; x < width; x += 100)
    {
        pRT->DrawLine(
            D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
            D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
            m_pLightSlateGrayBrush,
            0.5f
        );
    }

    for (int y = 0; y < height; y += 100)
    {
        pRT->DrawLine(
            D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
            D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
            m_pLightSlateGrayBrush,
            0.5f
        );
    }

    pRT->SetTransform(D2D1::Matrix3x2F::Identity());

    pRT->EndDraw();

}
