#include "SObject.h"

ScrapEngine::SObject::SObject(const std::string& input_object_name) : object_name(input_object_name)
{

}

ScrapEngine::SObject::~SObject()
{
	//Empty here
}

std::string ScrapEngine::SObject::toString() const
{
	return object_name;
}
