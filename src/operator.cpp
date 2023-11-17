#include "operator.h"


Variable &operator+(Variable &lhs, int val) {
    Variable *rhs = new Variable(val);
    return lhs + (*rhs);
}

Variable &operator+(int val, Variable &rhs) {
    return rhs + val;
}

Variable &operator*(Variable &lhs, int val) {
    Variable *rhs = new Variable(val);
    return lhs * (*rhs);
}

Variable &operator*(int val, Variable &rhs) {
    return rhs * val;
}
