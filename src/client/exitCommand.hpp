#ifndef __EXIT_COMMAND_HPP__
#define __EXIT_COMMAND_HPP__

#include "iCommand.hpp" 

class Exit : public ICommand {
    void execute() override {
        _mgr.deactivate();
    }
};

#endif //__EXIT_COMMAND_HPP__