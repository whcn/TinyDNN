#include <queue>

#include "core.h"
#include "operator.h"

Variable::Variable(double data, string name) : data_(data), grad_(nullptr), creator_(nullptr), name_(name) {}

double Variable::GetData() const {
    return data_;
}

void Variable::SetData(double data) {
    data_ = data;
}

void Variable::SetCreator(Function *func) {
    creator_ = func;
}

Function *Variable::GetCreator() {
    return creator_;
}

Variable *Variable::GetGrad() {
    if (grad_ == nullptr) {
        grad_ = new Variable(0);
    }
    return grad_;
}

void Variable::SetGrad(Variable *grad) {
    grad_ = grad;
}

void Variable::Backward() {
    creator_->GetOutputs()[0]->GetGrad()->SetData(1);
    creator_->GetOutputs()[0]->GetGrad()->SetName("gy");
    queue<Function *> funcs;
    funcs.push(creator_);
    while (!funcs.empty()) {
        Function *creator = funcs.front();
        assert(creator != nullptr);
        Variable *output_grad = creator->GetOutputs()[0]->GetGrad();
        vector<Variable *> grads = creator->Backward(output_grad);
        vector<Variable *> inputs = creator->GetInputs();
        assert(grads.size() == inputs.size());
        for (int i = 0; i < inputs.size(); ++i) {
            Variable *input_grad = inputs[i]->GetGrad();
            Variable *backward_grad = grads[i];
            Variable &updated_grad = *input_grad + *backward_grad;
            inputs[i]->SetGrad(&updated_grad);
            auto input_creator = inputs[i]->GetCreator();
            if (input_creator != nullptr) {
                funcs.push(input_creator);
            }
        }
        funcs.pop();
    }
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

void Variable::SetName(const string &name) {
    name_ = name;
}

Variable *Function::operator()(vector<Variable *> &args) {
    Variable *output = Forward(args);
    output->SetCreator(this);
    inputs_ = args;
    outputs_.push_back(output);
    return output;
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

vector<Variable *> Add::Backward(Variable *grad) {
    Variable &gx0 = 1 * (*grad);
    Variable &gx1 = 1 * (*grad);
    return {&gx0, &gx1};
}

Variable *Mul::Forward(vector<Variable *> args) {
    assert(args.size() == 2);
    int res = args[0]->GetData() * args[1]->GetData();
    Variable *output = new Variable(res);
    return output;
}

vector<Variable *> Mul::Backward(Variable *grad) {
    Variable *x0 = inputs_[0];
    Variable *x1 = inputs_[1];
    Variable &gx0 = (*x1) * (*grad);
    Variable &gx1 = (*x0) * (*grad);
    return {&gx0, &gx1};
}

Variable *Sub::Forward(vector<Variable *> args) {
    assert(args.size() == 2);
    int res = args[0]->GetData() - args[1]->GetData();
    Variable *output = new Variable(res);
    return output;
}

vector<Variable *> Sub::Backward(Variable *grad) {
    Variable &gx0 = 1 * (*grad);
    Variable &gx1 = -1 * (*grad);
    return {&gx0, &gx1};
}

Variable *Div::Forward(vector<Variable *> args) {
    assert(args.size() == 2);
    double res = args[0]->GetData() / args[1]->GetData();
    Variable *output = new Variable(res);
    return output;
}

vector<Variable *> Div::Backward(Variable *grad) {
    Variable *x0 = inputs_[0];
    Variable *x1 = inputs_[1];
    Variable &gx0 = 1.0 / (*x1) * (*grad);
    Variable &gx1 = -1 * (*x0) / ((*x1) * (*x1)) * (*grad);
    return {&gx0, &gx1};
}
