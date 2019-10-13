#pragma once

#include <Engine/LogicCore/SObject.h>
#include <Engine/LogicCore/Math/Transform/STransform.h>

namespace ScrapEngine
{
	namespace Core
	{
		class SComponent : public SObject
		{
		private:
			STransform father_transform_;
		protected:
			STransform object_relative_transform_;
			STransform object_world_transform_;
		public:
			explicit SComponent(const std::string& component_name);
			virtual ~SComponent() = 0;

			virtual void set_component_location(const SVector3& location);
			virtual void set_component_rotation(const SVector3& rotation);
			virtual void set_component_scale(const SVector3& scale);
			virtual void add_component_rotation(const SVector3& rotation);

			//Update a value based on father_transform_
			virtual void update_component_location();
			virtual void update_component_rotation();
			virtual void update_component_scale();

			void set_father_transform(const STransform& input_father_transform);

			virtual STransform get_component_transform() const;
			virtual SVector3 get_component_location() const;
			virtual SVector3 get_component_rotation() const;
			virtual SVector3 get_component_scale() const;

			SVector3 get_component_relative_location() const;
			SVector3 get_component_relative_rotation() const;
			SVector3 get_component_relative_scale() const;
		};
	}
}
