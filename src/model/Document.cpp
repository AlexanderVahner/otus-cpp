#include <vector>
#include <iostream>
#include <algorithm>
#include <model/IDocument.h>

class Document : public IDocument
{
private:
    std::vector<IGraphicalObject*> graphicalObjects;

public:
    const std::vector<IGraphicalObject*>& GetObjects() override
    {
        return graphicalObjects;
    }

    IDocument* AddObject(IGraphicalObject* obj) override
    {
        graphicalObjects.push_back(obj);

        std::cout << "Object '" << obj->Name <<"' added." << std::endl;
        return this;
    }

    IDocument* RemoveObject(IGraphicalObject* obj) override
    {
        graphicalObjects.erase(std::find(graphicalObjects.begin(), graphicalObjects.end(),obj));        
        std::cout << "Object '" << obj->Name << "' removed." << std::endl;
        obj->Dispose();
        return this;
    }

    IDocument* RemoveObject(std::string name) override
    {
        auto obj = std::find_if(graphicalObjects.begin(), graphicalObjects.end(), [name](IGraphicalObject* o)
        {
            return o->Name == name;
        });
        return RemoveObject(*obj);
    }

    void Dispose() override
    {
        for(auto obj : graphicalObjects){
            obj->Dispose();
        }
    }
};
