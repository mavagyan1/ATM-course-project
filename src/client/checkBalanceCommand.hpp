#ifndef __CHECK_BALANCE_COMMAND_HPP__
#define __CHECK_BALANCE_COMMAND_HPP__

#include "iCommand.hpp"
class CheckBalance : public ICommand {
public:
    void execute() override;
};
#endif //__CHECK_BALANCE_COMMAND_HPP__