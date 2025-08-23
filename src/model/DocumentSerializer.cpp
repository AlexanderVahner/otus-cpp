#include <iostream>
#include <ISerializer.h>
#include <IDocument.h>
#include <Point.h>
#include "Document.cpp"
#include "Line.h"
#include "Rect.h"
#include "Polygon.h"
#include "ShapeGraphicalObject.h"

class DocumentSerializer : public ISerializer<IDocument>
{
public:
    void SerializeToFile(IDocument* doc, std::string filePath) override
    {
        std::cout << "Serializing to file: " << filePath << std::endl;
        std::string result;
        for (auto obj : doc->GetObjects())
        {
            result.append("\t").append(obj->Name).append("\n");
        }
        std::cout << result << std::endl;
        std::cout << "Serialized." << std::endl;
    }

    IDocument* DeserializeFromFile(std::string filePath) override
    {
        std::cout << "Deserializing from file: " << filePath << std::endl;
        auto doc = new Document();
        doc->AddObject(
            new ShapeGraphicalObject(
                "Very long line",
                new Line(std::move(Point {0, 0}), std::move(Point{0, 1000}))));

        doc->AddObject(
            new ShapeGraphicalObject(
                "Well centered squre",
                new Rect(std::move(Point {-5, -5}), std::move(Point{5, 5}))));

        doc->AddObject(
            new ShapeGraphicalObject(
                "Pyramid",
                new Polygon(std::move(std::vector<Point> { Point {-100, 0}, Point{100, 0}, Point{0, -150} }), true)));
        std::cout << "Deserialized." << std::endl;
        return doc;
    }

    void Dispose() override
    {
        delete this;
    }
};
