#include <queue>
#include <fstream>

#include "core.h"

void CreateDotFile(Variable &var, const string &file_name) {
    ofstream ofs(file_name);
    ofs << "digraph G {" << endl;
    queue<Function *> funcs;
    funcs.push(var.GetCreator());
    while (!funcs.empty()) {
        auto creator = funcs.front();
        assert(creator != nullptr);
        ofs << (long) creator << " [style=filled color=coral shape=box label=" << creator->GetClassName() << "]" << endl;
        for (auto &output: creator->GetOutputs()) {
            ofs << (long) creator << " -> " << (long) output << ";" << endl;
            ofs << (long) output << " [style=filled color=steelblue1 shape=circle label=" << output->GetName() << "] " << endl;
        }
        for (auto &input: creator->GetInputs()) {
            ofs << (long) input << " -> " << (long) creator << ";" << endl;
            ofs << (long) input << " [style=filled color=steelblue1 shape=circle label=" << input->GetName() << "] " << endl;
            auto input_creator = input->GetCreator();
            if (input_creator != nullptr) {
                funcs.push(input_creator);
            }
        }
        funcs.pop();
    }
    ofs << "}";
    ofs.close();
}

