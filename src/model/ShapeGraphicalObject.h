#pragma once

#include <model/IGraphicalObject.h>
#include <model/IShape.h>

class ShapeGraphicalObject : public IGraphicalObject
{
private:
    IShape* Shape;

public:

    ShapeGraphicalObject(std::string name, IShape* shape) : Shape(shape)
    {
        Name = name;
    }

    void Render(IDrawingContext* context) override
    {
        Shape->Render(context);
    }

    void Dispose() override
    {
        delete Shape;
        delete this;
    }
};
