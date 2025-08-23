#pragma once

#include <string>
#include <IInterface.h>

template <class T>
class ISerializer : public IInterface
{
public:
    virtual void SerializeToFile(T* value, std::string filePath) = 0;
    virtual T* DeserializeFromFile(std::string filePath) = 0;
};
