#ifndef POSSYMLINSYSTEM_H
#define POSSYMLINSYSTEM_H

#include "LinearSystem.h"
#include <cassert>
#include <cmath>

class PosSymLinSystem : public LinearSystem {
public:
    PosSymLinSystem(const Matrix& A, const Vector& b);
    Vector Solve() override;
};

#endif // POSSYMLINSYSTEM_H
