#include <torch/torch.h>
#include <torch/script.h>
#include <iostream>
#include <vector>
#include "AI_model.h"

AI_model::AI_model() : device(torch::kCPU), model_loaded(false) {}

bool AI_model::loadModel(const std::string& model_path) {
    try {
        std::cout << "loading model: " << model_path << std::endl;
        model = torch::jit::load(model_path);
        model.eval();
        model_loaded = true;
        std::cout << "Model Loaded!" << std::endl;
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Fails to load!" << e.what() << std::endl;
        return false;
    }
}


//(CPU/GPU)
void AI_model::setDevice(const std::string& device_type) {
    if (device_type == "cuda" && torch::cuda::is_available()) {
        device = torch::kCUDA;
        std::cout << "Is Using GPU" << std::endl;
    }
    else {
        device = torch::kCPU;
        std::cout << "Is Using CPU" << std::endl;
    }
    if (model_loaded) {
        model.to(device);
    }
}

//AI action choice

int AI_model::makeDecision(const std::vector<float>& game_state, const std::vector<int>& valid_actions) {
    if (!model_loaded) {
        std::cerr << "Model not loaded!" << std::endl;
        return valid_actions.empty() ? 0 : valid_actions[0];
    }
    torch::Tensor state_tensor = torch::from_blob(const_cast<float*>(game_state.data()),{ 1, static_cast<long>(game_state.size()) },torch::kFloat32).to(device); 
    //按照规定格式输入模型

    std::vector<torch::jit::IValue> inputs;
    inputs.push_back(state_tensor);

    torch::Tensor output = model.forward(inputs).toTensor();

    int best_action = valid_actions[0];
    float best_q_value = -999999.0f;

    for (int action : valid_actions) {
        if (action < output.size(1)) {
            float q_value = output[0][action].item<float>();
            if (q_value > best_q_value) {
                 best_q_value = q_value;
                 best_action = action;
            }
        }
    }

    std::cout << "AI choice: " << best_action << " (Qֵ: " << best_q_value << ")" << std::endl;
    return best_action;
}

void AI_model::test() {
    if (!model_loaded) {
        std::cout << "Model not loaded!" << std::endl;
        return;
    }
    std::cout << "Model loaded" << std::endl;
    std::vector<float> test_state(612, 0.5f);  
    std::vector<int> test_actions = { 0, 1, 2, 5, 10 }; 
    std::cout << "\n=== AI Action Choice ===" << std::endl;
    int decision = makeDecision(test_state, test_actions);
    std::cout << "AI chose: " << decision << std::endl;
}

