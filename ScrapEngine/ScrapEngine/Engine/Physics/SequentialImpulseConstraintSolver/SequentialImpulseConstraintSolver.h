#pragma once

#include <btBulletDynamicsCommon.h>

namespace ScrapEngine
{
	namespace Physics
	{
		class SequentialImpulseConstraintSolver
		{
		private:
			btSequentialImpulseConstraintSolver* solver_ = nullptr;
		public:
			SequentialImpulseConstraintSolver();
			~SequentialImpulseConstraintSolver();

			btSequentialImpulseConstraintSolver* get_solver() const;
		};
	}
}
