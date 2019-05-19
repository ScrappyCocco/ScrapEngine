#include "STransform.h"

ScrapEngine::Core::STransform::
STransform(const SVector3& position, const SQuaternion& rotation, const SVector3& scale) : position_(position),
                                                                                           rotation_(rotation),
                                                                                           scale_(scale)
{
}

ScrapEngine::Core::SVector3 ScrapEngine::Core::STransform::get_position() const
{
	return { position_ };
}

ScrapEngine::Core::SQuaternion ScrapEngine::Core::STransform::get_rotation() const
{
	return { rotation_ };
}

ScrapEngine::Core::SVector3 ScrapEngine::Core::STransform::get_scale() const
{
	return { scale_ };
}

void ScrapEngine::Core::STransform::set_position(const SVector3& new_position)
{
	position_ = SVector3(new_position);
}

void ScrapEngine::Core::STransform::set_rotation(const SQuaternion& new_rotation)
{
	rotation_ = SQuaternion(new_rotation);
}

void ScrapEngine::Core::STransform::set_scale(const SVector3& new_scale)
{
	scale_ = SVector3(new_scale);
}
