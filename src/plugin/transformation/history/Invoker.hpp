/*
** EPITECH PROJECT, 2025
** IFT3100H25_TP1_E10 [WSL : Ubuntu]
** File description:
** Il est possible d’annuler ou de refaire (undo / redo) les dernières actions
** interactives qui ont un impact sur la transformation des éléments visuels
** présents dans une scène.
*/

#ifndef INVOKER_HPP_
#define INVOKER_HPP_

#include <algorithm>
#include <list>
#include <memory>
#include <queue>

#include "Command.hpp"

namespace plugin::transformation::history {

/**
 * @brief The invoker class is responsible for managing the command queue and history
 *
 * @example Usage:
 * @code {.cpp}
 * Invoker invoker();
 * auto command = std::make_shared<Command>();
 * invoker.AddCommand(command);
 * invoker.Update();
 * @endcode
 */
class Invoker {
public:
    Invoker() = default;
    ~Invoker() = default;

    /**
     * @brief Add a command to the queue
     *
     * @param command  The command to add
     */
    void AddCommand(std::shared_ptr<Command> command);

    /**
     * @brief Execute the command at the front of the queue
     */
    void Update();

    /**
     * @brief Check if a command is in the history
     *
     * @param command  The command to check
     * @return true if the command is in the history, false otherwise
     */
    bool InHistory(std::shared_ptr<Command> command);

    /**
     * @brief Delete a command from the history
     *
     * @param commandId  The id of the command to delete
     */
    void DeleteFromHistory(uint32_t commandId);

private:
    std::queue<std::shared_ptr<Command>> _commandQueue;
    std::list<std::shared_ptr<Command>> _commandHistory;
};

#include "Invoker.inl"

} // namespace plugin::transformation::history

#endif /* !INVOKER_HPP_ */
