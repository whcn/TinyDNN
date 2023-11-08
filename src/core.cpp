#include "core.h"

Variable::Variable(int data) : data_(data) {}

int Variable::GetData() const {
    return data_;
}

Variable Function::operator()(std::vector<Variable> &args) {
    return forward(args);
}

Variable Add::forward(std::vector<Variable> &args) {
    assert(args.size() == 2);
    return Variable(args[0].GetData() + args[1].GetData());
}

Variable Add::backward() {
    return Variable(-1);
}
