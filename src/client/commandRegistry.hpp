#ifndef __COMMAND_REGISTRY_HPP__
#define __COMMAND_REGISTRY_HPP__

#include <unordered_map>
#include "iCommand.hpp"
#include <memory>

class CommandRegistry {
public:
    using CommandPtr = std::shared_ptr<ICommand>;
    using Registry = std::unordered_map<int, CommandPtr >;
private:
    CommandRegistry();
public:
    CommandRegistry(const CommandRegistry&) = delete;
    CommandRegistry& operator=(const CommandRegistry&) = delete;

    static CommandRegistry& getCommandRegistry();
    CommandPtr findCommand(int key);

private:
    Registry _reg;

};
#endif //__COMMAND_REGISTRY_HPP__