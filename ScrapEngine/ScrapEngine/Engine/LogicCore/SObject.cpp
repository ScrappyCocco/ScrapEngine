#include <Engine/LogicCore/SObject.h>

ScrapEngine::Core::SObject::SObject(const std::string& input_object_name) : object_name_(input_object_name)
{
}

ScrapEngine::Core::SObject::~SObject()
{
	//Empty here
}

std::string ScrapEngine::Core::SObject::to_string() const
{
	return object_name_;
}
