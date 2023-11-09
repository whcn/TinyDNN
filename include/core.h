#pragma once

#include <iostream>

class Function;

class Variable {
public:
    explicit Variable(int data);

    int GetData() const;

    float GetGrad() const;

    void SetGrad(float grad);

    void SetCreator(Function *func);

    Function *GetCreator();

    void Backward();

private:
    int data_;
    float grad_;
    Function *creator_;
};

class Function {
public:
    Variable operator()(std::vector<Variable *> &args);

    virtual Variable Forward(std::vector<Variable *> args) = 0;

    virtual std::vector<float> Backward(float &grad) = 0;

    virtual void SetGrads(std::vector<float> &grads) = 0;

    virtual std::vector<Variable *> GetInputs() { return inputs_; };

protected:
    std::vector<Variable *> inputs_;
};

class Add : public Function {
public:
    Variable Forward(std::vector<Variable *> args) override;

    std::vector<float> Backward(float &grad) override;

    void SetGrads(std::vector<float> &grads) override;
};