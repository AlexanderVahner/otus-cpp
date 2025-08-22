#include <vector>
#include <model/IShape.h>
#include <model/Point.h>
#include "Polygon.h"

void Polygon::Render(IDrawingContext* context)
{
    if (Points.size() <= 1)
    {
        return;
    }

    if (Points.size() == 2)
    {
        context->DrawLine(Points[0], Points[1]);
        return;
    }

    for (int i = 1; i < Points.size(); i++)
    {
        context->DrawLine(Points[i - 1], Points[i]);
    }

    if (IsClosed)
    {
        context->DrawLine(Points[Points.size() - 1], Points[0]);
    }
}
