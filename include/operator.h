#pragma once

#include "core.h"

Variable &operator+(Variable &lhs, double val);

Variable &operator+(double val, Variable &rhs);

Variable &operator*(Variable &lhs, double val);

Variable &operator*(double val, Variable &rhs);

Variable &operator-(Variable &lhs, double val);

Variable &operator-(double val, Variable &rhs);
