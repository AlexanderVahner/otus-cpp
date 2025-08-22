#include <model/IShape.h>
#include <model/Point.h>
#include "Line.h"

void Line::Render(IDrawingContext* context)
{
    context->DrawLine(Start, End);
}
