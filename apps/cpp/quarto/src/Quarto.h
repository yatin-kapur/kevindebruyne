#pragma once

#include <string>
#include <ostream>

#include "lib/logger/log.h"

#include "Piece.h"
#include "Player.h"
#include "GridPiece.h"

struct Quarto
{
    Quarto(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2):
        m_p1{p1},
        m_p2{p2},
        m_log("Quarto")
    {
        std::ostringstream os;
        os << "Quarto created with p1: " << *p1 << ", p2: " << *p2;
        m_log.info(os.str());

        // choose who goes first, default to p1 rn
        m_play_p1 = true;

        for (int i = 0; i < 16; ++i)
        {
            m_available[i] = true;
        }

        // initialize pieces on grid
        for (int r = 0; r < 4; ++r)
        {
            for (int c = 0; c < 4; ++c)
            {
                m_grid[r][c] = std::make_shared<GridPiece>(r, c);
            }
        }

        // all spots on the grid are available
        for (int i = 0; i < 16; ++i)
        {
            int c = i % 4;
            int r = i / 4;
            
            add_neighbour(r, c, r, c-1);
            add_neighbour(r, c, r, c+1);
            add_neighbour(r, c, r-1, c);
            add_neighbour(r, c, r+1, c);
            add_neighbour(r, c, r-1, c+1);
            add_neighbour(r, c, r+1, c-1);
            add_neighbour(r, c, r-1, c-1);
            add_neighbour(r, c, r+1, c+1);
        }
    };

    void add_neighbour(const int& r, const int& c, const int& ri, const int& ci)
    {
        if (ri >=0 && ri < 4 && ci >= 0 && ci < 4)
        {
            m_grid[r][c]->m_neighbours.push_back(m_grid[ri][ci]);
        }
    }

    std::ostringstream print_board() 
    {
        std::ostringstream ss;
        ss << "current board looks like: \n---- ---- ---- ----\n";

        for (int r = 0; r < 4; ++r)
        {
            for (int c = 0; c < 4; ++c)
            {
                ss << m_grid[r][c]->m_piece->m_lo_nibble << " ";
            }
            ss << "\n";
        }
        ss << "---- ---- ---- ----";

        return ss;
    }

    std::shared_ptr<Player> get_playing()
    {
        return m_play_p1 ? m_p1 : m_p2;
    }

    void validate_position(std::shared_ptr<Piece> piece, int& position, std::shared_ptr<Player> p)
    {
        int c = position % 4;
        int r = position / 4;
        while (!((position >= 0) && (position < 16) && (m_grid[r][c]->available())))
        {
            m_log.error("Invalid position [" + std::to_string(position) + "] for piece [" + std::to_string(piece->m_piece) + "(" + piece->m_lo_nibble + ")]");
            position = p->ask_for_position(piece);
        }
    }

    void validate_piece(std::shared_ptr<Piece> piece, std::shared_ptr<Player> p)
    {
        while (!((piece->m_piece < 16) && (piece->m_piece >= 0) && (m_available[piece->m_piece])))
        {
            m_log.error("Piece [" + std::to_string(piece->m_piece) + "(" + piece->m_lo_nibble + ")] is either an invalid piece or is already in play");
            piece = p->ask_for_piece();
        }
    }

    void place_piece_on_position(std::shared_ptr<Piece> piece, const int& position, std::shared_ptr<Player> p)
    {
        int c = position % 4;
        int r = position / 4;
        m_grid[r][c]->place(piece);
        m_log.info(p->name() + " played " + std::to_string(piece->m_piece) + "(" + piece->m_lo_nibble + ") at " + std::to_string(position));
    }

    void evaluate_game_state()
    {
        m_finished = false;
    }

    void play()
    {
        std::shared_ptr<Player> p = get_playing();
        int position = 0;
        std::shared_ptr<Piece> piece;

        while (!m_finished)
        {
            // ask for next piece to play for opponent
            piece = p->ask_for_piece();
            validate_piece(piece, p);

            // get the opposite player to place the piece
            m_play_p1 = !m_play_p1;
            p = get_playing();

            // ask for position from player
            position = p->ask_for_position(piece);
            validate_position(piece, position, p);

            place_piece_on_position(piece, position, p);
            m_log.info(print_board().str());

            // evaluate if this game is at a terminal state
            evaluate_game_state();
        }
    }

    bool finished()
    {
        return m_finished;
    }

    std::shared_ptr<Player> winner()
    {
        return m_p1;
    }

    std::shared_ptr<GridPiece> m_grid[4][4];
    bool m_finished = false;
    bool m_available[16];

    std::shared_ptr<Player> m_p1;
    std::shared_ptr<Player> m_p2;
    bool m_play_p1;

    Log m_log;
};
