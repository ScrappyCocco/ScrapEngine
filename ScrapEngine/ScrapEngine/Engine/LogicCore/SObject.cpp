#include <Engine/LogicCore/SObject.h>
#include <glm/ext/matrix_transform.inl>
#include <glm/detail/func_trigonometric.inl>

glm::mat4 ScrapEngine::Core::SObject::generate_transform_matrix(const ScrapEngine::Transform& transform) const
{
	glm::mat4 transf(1.0f);

	transf = glm::translate(transf, transform.location);

	transf = glm::rotate(transf, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	transf = glm::rotate(transf, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	transf = glm::rotate(transf, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	transf = glm::scale(transf, transform.scale);

	return transf;
}

glm::mat4 ScrapEngine::Core::SObject::generate_unscaled_transform_matrix(const ScrapEngine::Transform& transform) const
{
	glm::mat4 transf(1.0f);

	transf = glm::translate(transf, transform.location);

	transf = glm::rotate(transf, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	transf = glm::rotate(transf, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	transf = glm::rotate(transf, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	return transf;
}

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
