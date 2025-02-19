/*
** EPITECH PROJECT, 2025
** IFT3100H25_TP1_E10 [WSL : Ubuntu]
** File description:
** Command
*/

#ifndef COMMAND_HPP_
#define COMMAND_HPP_

#include <cstdint>

namespace plugin::transformation::history {

class Command {
public:
    Command(uint32_t id) : _id(id) {}
    virtual ~Command() = default;

    /**
     * @brief Execute the command
     */
    virtual void Execute() = 0;

    /**
     * @brief Undo the command
     */
    virtual void Undo() = 0;

    uint32_t GetId() const { return _id; }

private:
    uint32_t _id;
};

} // namespace plugin::transformation::history

#endif /* !COMMAND_HPP_ */
