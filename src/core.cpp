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
    queue<Function *> funcs;
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

Variable &Variable::operator+(Variable &variable) const {
    Function *add = new Add();
    Variable *lhs = const_cast<Variable *>(this);
    Variable *rhs = &variable;
    vector<Variable *> args{lhs, rhs};
    Variable *output = (*add)(args);
    return *output;
}

Variable *Function::operator()(vector<Variable *> &args) {
    Variable *output = Forward(args);
    inputs_ = args;
    output->SetCreator(this);
    return output;
}

void Function::UpdateInputGrads(vector<float> &grads) {
    assert(grads.size() == inputs_.size());
    for (int i = 0; i < grads.size(); ++i) {
        inputs_[i]->UpdateGrad(grads[i]);
    }
}

vector<Variable *> Function::GetInputs() {
    return inputs_;;
}

Variable *Add::Forward(vector<Variable *> args) {
    assert(args.size() == 2);
    int res = args[0]->GetData() + args[1]->GetData();
    Variable *output = new Variable(res);
    return output;
}

vector<float> Add::Backward(float &grad) {
    return {grad * 1, grad * 1};
}