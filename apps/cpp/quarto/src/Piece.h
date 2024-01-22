#pragma once

#include <iostream>
#include <string>
#include <bitset>

struct Piece 
{
    Piece() : m_piece{0}, m_lo_nibble{"0000"}, m_placed{false} {};
    Piece(int piece): 
        m_piece{piece}, 
        m_lo_nibble{std::bitset<4>(m_piece).to_string()},
        m_placed{true} 
    {
    } 

    bool placed()
    {
        return m_placed;
    }

    int m_piece;
    std::string m_lo_nibble;
    bool m_placed;
};