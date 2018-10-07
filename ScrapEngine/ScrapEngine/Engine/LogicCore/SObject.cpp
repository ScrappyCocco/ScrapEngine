#include "SObject.h"

ScrapEngine::SObject::SObject(std::string input_object_name) : object_name(input_object_name)
{

}

ScrapEngine::SObject::~SObject()
{

}

std::string ScrapEngine::SObject::toString() const
{
	return object_name;
}
