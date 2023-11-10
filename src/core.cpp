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
        creator->UpdateInputGrads(grads);
        funcs.pop();
        for (auto &input: creator->GetInputs()) {
            auto input_creator = input->GetCreator();
            if (input_creator != nullptr) {
                funcs.push(input_creator);
            }
        }
    }
}

void Variable::UpdateGrad(float grad) {
    grad_ += grad;
}

Variable Variable::operator+(Variable &variable) const {
    return Variable(data_ + variable.GetData());
}

Variable Function::operator()(std::vector<Variable *> &args) {
    auto output = Forward(args);
    inputs_ = args;
    output.SetCreator(this);
    return output;
}

void Function::UpdateInputGrads(std::vector<float> &grads) {
    assert(grads.size() == inputs_.size());
    for (int i = 0; i < grads.size(); ++i) {
        inputs_[i]->UpdateGrad(grads[i]);
    }
}

std::vector<Variable *> Function::GetInputs() {
    return inputs_;;
}

Variable Add::Forward(std::vector<Variable *> args) {
    assert(args.size() == 2);
    return *(args[0]) + *(args[1]);
}

std::vector<float> Add::Backward(float &grad) {
    return {grad * 1, grad * 1};
}