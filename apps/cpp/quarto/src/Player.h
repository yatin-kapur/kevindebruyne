#pragma once

#include <string>
#include <ostream>

#include "lib/logger/log.h"

#include "Piece.h"

struct Player
{
    Player(const std::string name): 
        m_name{name}, 
        m_log{name + ".log"}
    {
    };

    std::shared_ptr<Piece> ask_for_piece()
    {
        m_log.info("Choose piece (0-15) for opponent");

        unsigned int p;
        std::cin >> p;

        return std::make_shared<Piece>(p);
    }

    int ask_for_position(std::shared_ptr<Piece> piece)
    {
        m_log.info("Choose position to play for piece: " + std::to_string(piece->m_piece) + "(" + piece->m_lo_nibble + ")");

        int position;
        std::cin >> position;

        return position;
    }

    std::string name() const { return m_name; };
    std::string m_name;

    Log m_log;
};

std::ostream& operator<<(std::ostream& os, const Player& p)
{
    os << p.name();
    return os;
}