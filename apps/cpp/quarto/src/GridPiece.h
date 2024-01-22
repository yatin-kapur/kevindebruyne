#pragma once

#include <iostream>
#include <string>
#include <bitset>
#include <unordered_map>
#include <vector>

#include "Piece.h"

struct GridPiece
{
    GridPiece(int row, int col):
        m_row{row},
        m_col{col},
        m_piece{std::make_shared<Piece>(0)},
        m_available{true}
    {
    };

    std::shared_ptr<GridPiece> get_neighbour(const int& direction)
    {
        return m_neighbours[direction];
    }

    void place(std::shared_ptr<Piece> piece)
    {
        m_piece = piece;
        m_available = false;
    }

    bool available()
    {
        return m_available;
    }

    int m_row;
    int m_col;
    std::shared_ptr<Piece> m_piece;

    // map of the neighbours of this peiece based on the side of the neighbour
    // 0->7 (top topright right bottomright bottom bottomleft left topleft)
    std::vector<std::shared_ptr<GridPiece> > m_neighbours;

    bool m_available;
};
