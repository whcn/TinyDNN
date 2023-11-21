#pragma once

#include <iostream>

using namespace std;

class Function;

class Variable {
public:
    explicit Variable(int data, string name = "\"\"");

    int GetData() const;

    float GetGrad() const;

    string GetName() const;

    void UpdateGrad(float grad);

    void SetCreator(Function *func);

    Function *GetCreator();

    void Backward();

    Variable &operator+(Variable &rhs) const;

    Variable &operator*(Variable &rhs) const;

    Variable &operator-(Variable &rhs) const;

private:
    int data_;
    float grad_;
    Function *creator_;
    string name_;
};

class Function {
public:
    Variable *operator()(vector<Variable *> &args);

    virtual Variable *Forward(vector<Variable *> args) = 0;

    virtual vector<float> Backward(float grad) = 0;

    void UpdateInputGrads(vector<float> &grads);

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

    vector<float> Backward(float grad) override;
};

class Mul : public Function {
public:
    Mul() { name_ = "Mul"; }

    Variable *Forward(vector<Variable *> args) override;

    vector<float> Backward(float grad) override;
};

class Sub : public Function {
public:
    Sub() { name_ = "Sub"; }

    Variable *Forward(vector<Variable *> args) override;

    vector<float> Backward(float grad) override;
};
