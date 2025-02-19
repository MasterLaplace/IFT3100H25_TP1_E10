#include "Invoker.hpp"

inline void Invoker::AddCommand(std::shared_ptr<Command> command) { _commandQueue.push(command); }

inline bool Invoker::InHistory(std::shared_ptr<Command> command)
{
    return std::find(_commandHistory.begin(), _commandHistory.end(), command) != _commandHistory.end();
}
