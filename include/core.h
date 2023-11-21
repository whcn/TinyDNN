#pragma once

#include <iostream>

using namespace std;

class Function;

class Variable {
public:
    explicit Variable(double data, string name = "\"\"");

    double GetData() const;

    double GetGrad() const;

    string GetName() const;

    void UpdateGrad(double grad);

    void SetCreator(Function *func);

    Function *GetCreator();

    void Backward();

    Variable &operator+(Variable &rhs) const;

    Variable &operator*(Variable &rhs) const;

    Variable &operator-(Variable &rhs) const;

    Variable &operator/(Variable &rhs) const;

private:
    double data_;
    double grad_;
    Function *creator_;
    string name_;
};

class Function {
public:
    Variable *operator()(vector<Variable *> &args);

    virtual Variable *Forward(vector<Variable *> args) = 0;

    virtual vector<double> Backward(double grad) = 0;

    void UpdateInputGrads(vector<double> &grads);

    vector<Variable *> GetInputs();

    vector<Variable *> GetOutputs();

    const string &GetClassName();

protected:
    vector<Variable *> inputs_;
    vector<Variable *> outputs_;
    string name_;
};

class Add : public Function {
public:
    Add() { name_ = "Add"; }

    Variable *Forward(vector<Variable *> args) override;

    vector<double> Backward(double grad) override;
};

class Mul : public Function {
public:
    Mul() { name_ = "Mul"; }

    Variable *Forward(vector<Variable *> args) override;

    vector<double> Backward(double grad) override;
};

class Sub : public Function {
public:
    Sub() { name_ = "Sub"; }

    Variable *Forward(vector<Variable *> args) override;

    vector<double> Backward(double grad) override;
};

class Div : public Function {
public:
    Div() { name_ = "Div"; }

    Variable *Forward(vector<Variable *> args) override;

    vector<double> Backward(double grad) override;
};
