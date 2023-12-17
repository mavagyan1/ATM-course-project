#include "commandRegistry.hpp"
#include "cashInCommand.hpp"
#include "cashOutCommand.hpp"
#include "checkBalanceCommand.hpp"
#include "exitCommand.hpp"
#include <stdexcept>
#include <iterator>

CommandRegistry::CommandRegistry() {
    _reg.insert( {1,std::make_shared<CheckBalance>()} );
    _reg.insert( {2,std::make_shared<CashIn>()} );
    _reg.insert( {3,std::make_shared<CashOut>()} );
    _reg.insert( {4,std::make_shared<Exit>()} );
}

CommandRegistry& CommandRegistry::getCommandRegistry() {
    static CommandRegistry reg;
    return reg;
}

auto CommandRegistry::findCommand(int key) -> CommandPtr {
    auto iter =_reg.find(key);
    if(iter == _reg.end()) {
        throw std::runtime_error("Incorrect option!\n");
    }
    return iter->second;
}   