#pragma once
#include <model/IShape.h>
#include <model/Point.h>

class Line : public IShape
{
public:

    Point Start;
    Point End;

    Line(Point start, Point end) : Start(start), End(end) { }

    ~Line() = default;

    void Render(IDrawingContext* context) override;
    void Dispose() override
    {
        delete this;
    }
};
