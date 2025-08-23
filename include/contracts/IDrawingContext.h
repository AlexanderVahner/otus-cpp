#pragma once

#include <IInterface.h>
#include <Point.h>

class IDrawingContext : public IInterface
{
public:
    virtual void DrawLine(Point& start, Point& end) = 0;
};
