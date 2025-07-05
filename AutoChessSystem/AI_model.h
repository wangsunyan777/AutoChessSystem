#ifndef AI_model_H
#define AI_model_H 
#include <torch/torch.h>
#include <torch/script.h>
#include <iostream>
#include <vector>

class AI_model {
private:
    torch::jit::script::Module model;
    torch::Device device;
    bool model_loaded;
public:
    AI_model();
    bool loadModel(const std::string& model_path);
    void setDevice(const std::string& device_type);
    int makeDecision(const std::vector<float>& game_state, const std::vector<int>& valid_actions);
    void test();
};
#endif
