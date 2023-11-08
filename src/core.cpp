#include "core.h"

Variable::Variable(int data) : data_(data) {}

int Variable::GetData() const {
    return data_;
}

Variable Function::operator()(Variable &lhs, Variable &rhs) {
    return forward(lhs, rhs);
}

Variable Add::forward(Variable &lhs, Variable &rhs) {
    return Variable(lhs.GetData() + rhs.GetData());
}

Variable Add::backward() {
    return Variable(-1);
}
