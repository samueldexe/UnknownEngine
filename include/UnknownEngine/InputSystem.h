
#pragma once
#include <string>
#include <vector>
#include <memory> 

namespace UnknownEngine {
    // User-facing API only
    class InputSystem {
    public:
        InputSystem();
        ~InputSystem();

        void BindAction(const std::string& action, const std::string& keyName);
        void BindAction(const std::string& action, const std::vector<std::string>& keyNames);
        bool IsActionPressed(const std::string& action) const;

    private:
        struct Impl;
        friend class Engine;
        std::unique_ptr<Impl> impl;
    };
}