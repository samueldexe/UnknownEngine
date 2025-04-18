
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

        bool isKeyPressed(std::string key);

    private:
        struct Impl;
        friend class Engine;
        std::unique_ptr<Impl> impl;
    };
}