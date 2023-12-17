#ifndef __CASH_IN_COMMAND_HPP__
#define __CASH_IN_COMMAND_HPP__

#include "iCommand.hpp"

class CashIn : public ICommand {
public:
    void execute() override;
};

#endif //__CASH_IN_COMMAND_HPP__