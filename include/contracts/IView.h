#pragma once

#include <IInterface.h>
#include <IDocument.h>
#include <ICommand.h>

class IView : public IInterface
{
protected:
    ~IView() = default;

public:
    virtual void SetOpenDocumentCommand(ICommand<std::string>* command) = 0;
    virtual void SetSaveDocumentCommand(ICommand<std::string>* command) = 0;

    virtual void SetAddLineCommand(ICommand<std::string>* command) = 0;
    virtual void SetAddRectCommand(ICommand<std::string>* command) = 0;
    virtual void SetAddPolygonCommand(ICommand<std::string>* command) = 0;

    virtual void SetRemoveByNameCommand(ICommand<std::string>* command) = 0;

    virtual void OpenDocument(std::string filePath) = 0;
    virtual void SaveDocument(std::string filePath) = 0;

    virtual void AddLine(std::string name) = 0;
    virtual void AddRect(std::string name) = 0;
    virtual void AddPolygon(std::string name) = 0;

    virtual void RemoveByName(std::string name) = 0;

    virtual void Render(IDocument* document) = 0;
};
