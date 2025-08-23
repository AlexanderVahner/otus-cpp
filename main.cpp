#include "src/Model.cpp"
#include "src/View.cpp"
#include "src/system/Command.cpp"
#include "src/system/Observer.cpp"
#include "src/ConsoleDrawingContext.cpp"
#include "src/model/DocumentSerializer.cpp"

int main(int, char const**)
{
    auto model = new Model();
    auto drawingContext = new ConsoleDrawingContext();
    auto view = new View(drawingContext);
    auto documentSerializer = new DocumentSerializer();

    // Subscribing to model changes
    auto onDocumentChangedObserver = new Observer<IDocument*>([view](IDocument* doc)
    {
        view->Render(doc);
    });

    model->SubscribeToDocumentChanged(onDocumentChangedObserver);

    // Setting up view commands
    auto openDocCommand = new Command<std::string>([model, documentSerializer](std::string parameter)
    {
        model->CloseDocument();
        auto doc = documentSerializer->DeserializeFromFile(parameter);
        model->OpenDocument(doc);
    });

    auto saveDocCommand = new Command<std::string>([model, documentSerializer](std::string parameter)
    {
        documentSerializer->SerializeToFile(model->GetDocument(), parameter);
    });

    auto addLineCommand = new Command<std::string>([model](std::string parameter)
    {
        model->AddLine(parameter);
    });

    auto addRectCommand = new Command<std::string>([model](std::string parameter)
    {
        model->AddRect(parameter);
    });

    auto addPolygonCommand = new Command<std::string>([model](std::string parameter)
    {
        model->AddPolygon(parameter);
    });

    auto removeByNameCommand = new Command<std::string>([model](std::string parameter)
    {
        model->RemoveObject(parameter);
    });

    view->SetOpenDocumentCommand(openDocCommand);
    view->SetSaveDocumentCommand(saveDocCommand);
    view->SetAddLineCommand(addLineCommand);
    view->SetAddRectCommand(addRectCommand);
    view->SetAddPolygonCommand(addPolygonCommand);
    view->SetRemoveByNameCommand(removeByNameCommand);

    // Do some actions
    view->OpenDocument("/path/to/doc.svg");
    view->AddLine("New line");
    view->AddRect("New rect");
    view->AddPolygon("New polygon");
    view->RemoveByName("New rect");
    view->SaveDocument("/path/to/new_doc.svg");

    // Cleaning up
    view->Dispose();
    drawingContext->Dispose();
    model->Dispose();
    documentSerializer->Dispose();
    return 0;
}
