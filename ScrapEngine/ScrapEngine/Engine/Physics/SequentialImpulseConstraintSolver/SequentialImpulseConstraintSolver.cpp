#include <Engine/Physics/SequentialImpulseConstraintSolver/SequentialImpulseConstraintSolver.h>

ScrapEngine::Physics::SequentialImpulseConstraintSolver::SequentialImpulseConstraintSolver()
{
	solver_ = new btSequentialImpulseConstraintSolver();
}

ScrapEngine::Physics::SequentialImpulseConstraintSolver::~SequentialImpulseConstraintSolver()
{
	delete solver_;
}

btSequentialImpulseConstraintSolver* ScrapEngine::Physics::SequentialImpulseConstraintSolver::get_solver() const
{
	return solver_;
}
