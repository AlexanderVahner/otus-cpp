#include <model/IShape.h>
#include <model/Point.h>
#include "Rect.h"

void Rect::Render(IDrawingContext* context)
{
    Point topRight {BottomRight.X, TopLeft.Y};
    Point bottomLeft {TopLeft.X, BottomRight.Y};
    context->DrawLine(TopLeft, topRight);
    context->DrawLine(topRight, BottomRight);
    context->DrawLine(BottomRight, bottomLeft);
    context->DrawLine(bottomLeft, TopLeft);
}
