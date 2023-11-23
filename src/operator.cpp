#include "operator.h"


Variable &operator+(Variable &lhs, double val) {
    val = std::round(val * 10.0) / 10.0;
    Variable *rhs = new Variable(val);
    return lhs + (*rhs);
}

Variable &operator+(double val, Variable &rhs) {
    return rhs + val;
}

Variable &operator*(Variable &lhs, double val) {
    Variable *rhs = new Variable(val);
    return lhs * (*rhs);
}

Variable &operator*(double val, Variable &rhs) {
    return rhs * val;
}

Variable &operator-(Variable &lhs, double val) {
    Variable *rhs = new Variable(val);
    return lhs - (*rhs);
}

Variable &operator-(double val, Variable &rhs) {
    Variable *lhs = new Variable(val);
    return (*lhs) - rhs;
}

Variable &operator/(Variable &lhs, double val) {
    Variable *rhs = new Variable(val);
    return lhs / (*rhs);
}

Variable &operator/(double val, Variable &rhs) {
    Variable *lhs = new Variable(val);
    return (*lhs) / rhs;
}
