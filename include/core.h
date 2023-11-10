#pragma once

#include <iostream>

using namespace std;

class Function;

class Variable {
public:
    explicit Variable(int data);

    int GetData() const;

    float GetGrad() const;

    void UpdateGrad(float grad);

    void SetCreator(Function *func);

    Function *GetCreator();

    void Backward();

    Variable &operator+(Variable &rhs) const;

private:
    int data_;
    float grad_;
    Function *creator_;
};

class Function {
public:
    Variable *operator()(vector<Variable *> &args);

    virtual Variable *Forward(vector<Variable *> args) = 0;

    virtual vector<float> Backward(float &grad) = 0;

    void UpdateInputGrads(vector<float> &grads);

    vector<Variable *> GetInputs();

protected:
    vector<Variable *> inputs_;
};

class Add : public Function {
public:
    Variable *Forward(vector<Variable *> args) override;

    vector<float> Backward(float &grad) override;
};