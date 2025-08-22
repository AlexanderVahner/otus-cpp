#pragma once

#include <IDrawingContext.h>

class IShape : IInterface
{
public:
    virtual void Render(IDrawingContext* context) = 0;
};
