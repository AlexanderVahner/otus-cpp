#pragma once

#include <IInterface.h>
#include <IDocument.h>
#include <IObservable.h>

class IModel : public IInterface
{
protected:
    ~IModel() = default;

public:
    virtual IDocument* GetDocument() = 0;
    virtual void OpenDocument(IDocument* document) = 0;
    virtual void CloseDocument() = 0;

    virtual void AddLine(std::string name) = 0;
    virtual void AddRect(std::string name) = 0;
    virtual void AddPolygon(std::string name) = 0;

    virtual void RemoveObject(std::string name) = 0;

    virtual IDisposable* SubscribeToDocumentChanged(IObserver<IDocument*>* observer) = 0;
};

