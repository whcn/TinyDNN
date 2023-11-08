#pragma once

#include <iostream>

class Variable {
public:
    explicit Variable(int data);

    int GetData() const;

private:
    int data_;
};

class Function {
public:
    Variable operator()(std::vector<Variable> &args);

    virtual Variable forward(std::vector<Variable> &args) = 0;

    virtual Variable backward() = 0;
};

class Add : public Function {
public:
    Variable forward(std::vector<Variable> &args) override;

    Variable backward() override;
};