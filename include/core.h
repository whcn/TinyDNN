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
    Variable operator()(Variable &lhs, Variable &rhs);

    virtual Variable forward(Variable &lhs, Variable &rhs) = 0;

    virtual Variable backward() = 0;
};

class Add : public Function {
public:
    Variable forward(Variable &lhs, Variable &rhs) override;

    Variable backward() override;
};