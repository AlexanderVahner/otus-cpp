#include <iostream>
#include <contracts/IDrawingContext.h>

class ConsoleDrawingContext : public IDrawingContext
{
public:
    void DrawLine(Point& start, Point& end) override
    {
        std::cout << "\tDrawing line from {" << start.X << ", " << start.Y << "} to {" << end.X << ", " << end.Y << "}" << std::endl;
    }

    void Dispose() override
    {
        delete this;
    }
};
