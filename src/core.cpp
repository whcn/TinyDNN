#include <queue>

#include "core.h"

Variable::Variable(int data) : data_(data), grad_(0), creator_(nullptr) {}

int Variable::GetData() const {
    return data_;
}

void Variable::SetCreator(Function *func) {
    creator_ = func;
}

Function *Variable::GetCreator() {
    return creator_;
}

float Variable::GetGrad() const {
    return grad_;
}

void Variable::Backward() {
    grad_ = 1;
    std::queue<Function *> funcs;
    funcs.push(creator_);
    while (!funcs.empty()) {
        auto creator = funcs.front();
        assert(creator != nullptr);
        auto grads = creator->Backward(grad_);
        creator->SetGrads(grads);
        funcs.pop();
        for (auto &input: creator->GetInputs()) {
            auto input_creator = input->GetCreator();
            if (input_creator != nullptr) {
                funcs.push(input_creator);
            }
        }
    }
}

void Variable::SetGrad(float grad) {
    grad_ = grad;
}

Variable Function::operator()(std::vector<Variable *> &args) {
    return Forward(args);
}

Variable Add::Forward(std::vector<Variable *> args) {
    assert(args.size() == 2);
    inputs_ = args;
    auto output = Variable(args[0]->GetData() + args[1]->GetData());
    output.SetCreator(this);
    return output;
}

std::vector<float> Add::Backward(float &grad) {
    return {grad * 1, grad * 1};
}

void Add::SetGrads(std::vector<float> &grads) {
    assert(grads.size() == inputs_.size());
    for (int i = 0; i < grads.size(); ++i) {
        inputs_[i]->SetGrad(grads[i]);
    }
}
