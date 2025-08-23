#pragma once

#include <vector>
#include <IGraphicalObject.h>

class IDocument : public IDisposable
{
public:
    virtual const std::vector<IGraphicalObject*>& GetObjects() = 0;
    virtual IDocument* AddObject(IGraphicalObject* obj) = 0;
    virtual IDocument* RemoveObject(IGraphicalObject* obj) = 0;
    virtual IDocument* RemoveObject(std::string name) = 0;
};
