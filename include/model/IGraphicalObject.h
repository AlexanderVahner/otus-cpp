#pragma once

#include <IDrawingContext.h>
#include <ISerializer.h>

class IGraphicalObject : public IDisposable
{
public:
    std::string Name;
    virtual void Render(IDrawingContext* context) = 0;
};
