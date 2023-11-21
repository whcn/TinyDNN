#include <queue>

#include "core.h"

Variable::Variable(double data, string name) : data_(data), grad_(0), creator_(nullptr), name_(name) {}

double Variable::GetData() const {
    return data_;
}

void Variable::SetCreator(Function *func) {
    creator_ = func;
}

Function *Variable::GetCreator() {
    return creator_;
}

double Variable::GetGrad() const {
    return grad_;
}

void Variable::Backward() {
    GetCreator()->GetOutputs()[0]->grad_ = 1;
    queue<Function *> funcs;
    funcs.push(creator_);
    while (!funcs.empty()) {
        auto creator = funcs.front();
        assert(creator != nullptr);
        double grad = creator->GetOutputs()[0]->GetGrad();
        auto grads = creator->Backward(grad);
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

void Variable::UpdateGrad(double grad) {
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

Variable &Variable::operator*(Variable &variable) const {
    Function *mul = new Mul();
    Variable *lhs = const_cast<Variable *>(this);
    Variable *rhs = &variable;
    vector<Variable *> args{lhs, rhs};
    Variable *output = (*mul)(args);
    return *output;
}

Variable &Variable::operator-(Variable &variable) const {
    Function *sub = new Sub();
    Variable *lhs = const_cast<Variable *>(this);
    Variable *rhs = &variable;
    vector<Variable *> args{lhs, rhs};
    Variable *output = (*sub)(args);
    return *output;
}

Variable &Variable::operator/(Variable &variable) const {
    Function *div = new Div();
    Variable *lhs = const_cast<Variable *>(this);
    Variable *rhs = &variable;
    vector<Variable *> args{lhs, rhs};
    Variable *output = (*div)(args);
    return *output;
}

string Variable::GetName() const {
    return name_;
}

Variable *Function::operator()(vector<Variable *> &args) {
    Variable *output = Forward(args);
    output->SetCreator(this);
    inputs_ = args;
    outputs_.push_back(output);
    return output;
}

void Function::UpdateInputGrads(vector<double> &grads) {
    assert(grads.size() == inputs_.size());
    for (int i = 0; i < grads.size(); ++i) {
        inputs_[i]->UpdateGrad(grads[i]);
    }
}

vector<Variable *> Function::GetInputs() {
    return inputs_;;
}

vector<Variable *> Function::GetOutputs() {
    return outputs_;
}

const string &Function::GetClassName() {
    return name_;
}

Variable *Add::Forward(vector<Variable *> args) {
    assert(args.size() == 2);
    int res = args[0]->GetData() + args[1]->GetData();
    Variable *output = new Variable(res);
    return output;
}

vector<double> Add::Backward(double grad) {
    return {grad, grad};
}

Variable *Mul::Forward(vector<Variable *> args) {
    assert(args.size() == 2);
    int res = args[0]->GetData() * args[1]->GetData();
    Variable *output = new Variable(res);
    return output;
}

vector<double> Mul::Backward(double grad) {
    return {inputs_[1]->GetData() * grad, inputs_[0]->GetData() * grad};
}

Variable *Sub::Forward(vector<Variable *> args) {
    assert(args.size() == 2);
    int res = args[0]->GetData() - args[1]->GetData();
    Variable *output = new Variable(res);
    return output;
}

vector<double> Sub::Backward(double grad) {
    return {grad, -grad};
}

Variable *Div::Forward(vector<Variable *> args) {
    assert(args.size() == 2);
    double res = args[0]->GetData() / args[1]->GetData();
    Variable *output = new Variable(res);
    return output;
}

vector<double> Div::Backward(double grad) {
    double x1 = inputs_[0]->GetData();
    double x2 = inputs_[1]->GetData();
    return {1.0 / x2 * grad, -x1 / (x2 * x2) * grad};
}
