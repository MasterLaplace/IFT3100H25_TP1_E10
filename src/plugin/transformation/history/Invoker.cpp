/*
** EPITECH PROJECT, 2025
** IFT3100H25_TP1_E10 [WSL : Ubuntu]
** File description:
** Invoker
*/

#include "Invoker.hpp"

namespace plugin::transformation::history {

void Invoker::Update()
{
    if (_commandQueue.empty())
        return;

    std::shared_ptr<Command> command = _commandQueue.front();
    _commandQueue.pop();
    command->Execute();
    _commandHistory.push_back(command);
}

void Invoker::DeleteFromHistory(uint32_t commandId)
{
    auto it = std::find_if(_commandHistory.begin(), _commandHistory.end(),
                           [&commandId](std::shared_ptr<Command> command) { return command->GetId() == commandId; });

    if (it != _commandHistory.end())
        _commandHistory.erase(it);
}

} // namespace plugin::transformation::history
