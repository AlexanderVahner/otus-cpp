#include <IModel.h>
#include <IObservable.h>
#include "system/Observable.cpp"
#include "model/ShapeGraphicalObject.h"
#include "model/Line.h"
#include "model/Rect.h"
#include "model/Polygon.h"

class Model : public IModel
{
private:
    IDocument* currentDocument = nullptr;
    Observable<IDocument*>* documentChanged;

public:
    Model()
    {
        documentChanged = new Observable<IDocument*>();
    }

    ~Model() = default;

    IDocument* GetDocument() override
    {
        return currentDocument;
    }

    void OpenDocument(IDocument* document) override
    {
        currentDocument = document;
        documentChanged->Publish(currentDocument);
    }

    void CloseDocument() override
    {
        if (currentDocument) currentDocument->Dispose();
        currentDocument = nullptr;
    }

    void AddLine(std::string name) override
    {
        if (!currentDocument)
        {
            return;
        }

        currentDocument->AddObject(
            new ShapeGraphicalObject(
                name,
                new Line(std::move(Point {0, 0}), std::move(Point{0, 1000}))));

        documentChanged->Publish(currentDocument);
    }

    void AddRect(std::string name) override
    {
        if (!currentDocument)
        {
            return;
        }


        currentDocument->AddObject(
            new ShapeGraphicalObject(
                name,
                new Rect(std::move(Point {-5, -5}), std::move(Point{5, 5}))));

        documentChanged->Publish(currentDocument);
    }

    void AddPolygon(std::string name) override
    {
        if (!currentDocument)
        {
            return;
        }

        currentDocument->AddObject(
            new ShapeGraphicalObject(
                name,
                new Polygon(std::move(std::vector<Point> { Point {-100, 0}, Point{100, 0}, Point{0, -150} }), true)));

        documentChanged->Publish(currentDocument);
    }

    void RemoveObject(std::string name) override
    {
        if (!currentDocument)
        {
            return;
        }

        currentDocument->RemoveObject(name);

        documentChanged->Publish(currentDocument);
    }

    IDisposable* SubscribeToDocumentChanged(IObserver<IDocument*>* observer) override
    {
        return documentChanged->Subscribe(observer);
    }

    void Dispose() override
    {
        CloseDocument();
        documentChanged->Dispose();
        delete this;
    }
};
