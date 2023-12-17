#ifndef __CASHOUT_H__
#define __CASHOUT_H__

#include "iCommand.hpp"

class CashOut : public ICommand {
public:
    void execute() override;
};

#endif //__CASHOUT_H__