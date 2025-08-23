#pragma once
#include <model/IShape.h>
#include <model/Point.h>

class Rect : public IShape
{
public:

    Point TopLeft;
    Point BottomRight;
    Rect(Point topLeft, Point bottomRight) : TopLeft(topLeft), BottomRight(bottomRight) { }

    ~Rect() = default;

    void Render(IDrawingContext* context) override;
    void Dispose() override
    {
        delete this;
    }
};
