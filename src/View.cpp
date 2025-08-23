#include <system/Traits.h>
#include <contracts/IView.h>
#include <contracts/IDrawingContext.h>
#include <model/IDocument.h>

class View : public IView
{
private:
    IDrawingContext* drawingContext;

    ICommand<std::string>* openDocumentCommand;
    ICommand<std::string>* saveDocumentCommand;

    ICommand<std::string>* addLineCommand;
    ICommand<std::string>* addRectCommand;
    ICommand<std::string>* addPolygonCommand;
    ICommand<std::string>* removeByNameCommand;

public:
    ~View() = default;

    View(IDrawingContext* context) : drawingContext(context)
    {

    }

    void SetOpenDocumentCommand(ICommand<std::string>* command) override
    {
        openDocumentCommand = command;
    }

    void SetSaveDocumentCommand(ICommand<std::string>* command) override
    {
        saveDocumentCommand = command;
    }

    void SetAddLineCommand(ICommand<std::string>* command) override
    {
        addLineCommand = command;
    }

    void SetAddRectCommand(ICommand<std::string>* command) override
    {
        addRectCommand = command;
    }

    void SetAddPolygonCommand(ICommand<std::string>* command) override
    {
        addPolygonCommand = command;
    }

    void SetRemoveByNameCommand(ICommand<std::string>* command) override
    {
        removeByNameCommand = command;
    }

    void OpenDocument(std::string filePath) override
    {
        if (openDocumentCommand) openDocumentCommand->Execute(filePath);
    }

    void SaveDocument(std::string filePath) override
    {
        if (saveDocumentCommand) saveDocumentCommand->Execute(filePath);
    }

    void AddLine(std::string name) override
    {
        if (addLineCommand) addLineCommand->Execute(name);
    }

    void AddRect(std::string name) override
    {
        if (addRectCommand) addRectCommand->Execute(name);
    }

    void AddPolygon(std::string name) override
    {
        if (addPolygonCommand) addPolygonCommand->Execute(name);
    }

    void RemoveByName(std::string name) override
    {
        if (removeByNameCommand) removeByNameCommand->Execute(name);
    }

    void Render(IDocument* document) override
    {
        for(auto obj : document->GetObjects())
        {
            obj->Render(drawingContext);
        }
    }

    void Dispose() override
    {
        delete this;
    }
};
