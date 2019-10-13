#pragma once

#include <Engine/LogicCore/SObject.h>
#include <Engine/LogicCore/GameObject/SGameObject.h>
#include <Engine/LogicCore/Math/Transform/STransform.h>

namespace ScrapEngine
{
	namespace Core
	{
		//Forward declaration to avoid include-loop
		class SGameObject;

		class SComponent : public SObject
		{
			//Friend class to update relative transform
			//Accessing private methods the user shouldn't see and use
			friend class SGameObject;
		private:
			//The current owner of this component
			//Should never be null
			SGameObject* owner_ = nullptr;
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

			virtual STransform get_component_transform() const;
			virtual SVector3 get_component_location() const;
			virtual SVector3 get_component_rotation() const;
			virtual SVector3 get_component_scale() const;

			SGameObject* get_owner() const;

			SVector3 get_component_relative_location() const;
			SVector3 get_component_relative_rotation() const;
			SVector3 get_component_relative_scale() const;
		protected:
			//Update the relative values based on owner_ transform
			virtual void update_relative_location();
			virtual void update_relative_rotation();
			virtual void update_relative_scale();

			virtual void update_component_location();
			virtual void update_component_rotation();
			virtual void update_component_scale();
		};
	}
}
