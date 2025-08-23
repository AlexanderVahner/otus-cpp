#pragma once
#include <vector>
#include <model/IShape.h>
#include <model/Point.h>

class Polygon : public IShape
{
public:

    std::vector<Point> Points;
    bool IsClosed;
    Polygon(std::vector<Point> points, bool isClosed) : Points(points), IsClosed(isClosed) { }

    ~Polygon() = default;

    void Render(IDrawingContext* context) override;

    void Dispose() override
    {
        delete this;
    }
};
