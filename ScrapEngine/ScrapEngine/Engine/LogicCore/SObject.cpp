#include <Engine/LogicCore/SObject.h>
#include <glm/gtx/transform.hpp>

glm::mat4 ScrapEngine::Core::SObject::generate_transform_matrix(const STransform& transform) const
{
	//Generate the unscaled transform matrix
	glm::mat4 transf = generate_unscaled_transform_matrix(transform);

	//Now also scale it
	transf = scale(transf, transform.get_scale().get_glm_vector());

	return transf;
}

glm::mat4 ScrapEngine::Core::SObject::generate_unscaled_transform_matrix(const STransform& transform) const
{
	glm::mat4 transf(1.0f);

	transf = translate(transf, transform.get_position().get_glm_vector());

	transf = rotate(transf, glm::radians(transform.get_rotation().get_x()), glm::vec3(1.0f, 0.0f, 0.0f));
	transf = rotate(transf, glm::radians(transform.get_rotation().get_y()), glm::vec3(0.0f, 1.0f, 0.0f));
	transf = rotate(transf, glm::radians(transform.get_rotation().get_z()), glm::vec3(0.0f, 0.0f, 1.0f));

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
