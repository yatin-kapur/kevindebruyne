#include <iostream>
#include <memory>
#include <string>
#include <bitset>
#include "lib/logger/log.h"

struct Piece 
{
    Piece() : m_piece{0}, m_lo_nibble{"0000"} {};
    Piece(int piece): 
        m_piece{piece}, 
        m_lo_nibble{std::bitset<4>(m_piece).to_string()} 
    {
    }; 

    int m_piece;
    std::string m_lo_nibble;
};

struct Player
{
    Player(const std::string name): 
        m_name{name}, 
        m_log{name + ".log"}
    {
    };

    Piece ask_for_piece()
    {
        m_log.info("choose starting piece (0-15) for opponent");

        unsigned int p;
        std::cin >> p;

        return p;
    }

    int ask_for_position(Piece piece)
    {
        m_log.info("choose position to play for piece: " + std::to_string(piece.m_piece) + "(" + piece.m_lo_nibble + ")");

        unsigned int pos;
        std::cin >> pos;

        return pos;
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
    };

    std::ostringstream print_board() 
    {
        std::ostringstream ss;
        ss << "current board looks like: \n---- ---- ---- ----\n";
        int col = 0;
        for (const auto& i : m_grid)
        {
            ss << i.m_lo_nibble << " ";
            col++;
            if (col % 4 == 0)
            {
                ss << "\n";
            }
        }
        ss << "---- ---- ---- ----";

        return ss;
    }

    std::shared_ptr<Player> get_playing()
    {
        return m_play_p1 ? m_p1 : m_p2;
    }

    void play()
    {
        auto p = get_playing();
        auto pos = -1;
        auto piece = p->ask_for_piece();
        m_play_p1 = !m_play_p1;

        while (!m_finished)
        {
            p = get_playing();
            pos = p->ask_for_position(piece);

            m_grid[pos] = piece;
            m_log.info(p->name() + " played " + std::to_string(piece.m_piece) + "(" + piece.m_lo_nibble + ") at " + std::to_string(pos));
            m_log.info("current board:");
            m_log.info(print_board().str());
            m_available[piece.m_piece] = false;

            piece = p->ask_for_piece();
            while (!m_available[piece.m_piece])
            {
                m_log.error("Piece is already being used");
                piece = p->ask_for_piece();
            }

            m_play_p1 = !m_play_p1;
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

    Piece m_grid[16];
    bool m_available[16]; 

    bool m_finished = false;

    std::shared_ptr<Player> m_p1;
    std::shared_ptr<Player> m_p2;
    bool m_play_p1;

    Log m_log;
};

int main()
{
    Log log("quarto");
    log.info("Starting Quarto...");

    auto p1 = std::make_shared<Player>("Yatin");
    auto p2 = std::make_shared<Player>("Sarthak");

    Quarto q{p1, p2};
    q.play();

    log.info("game finished!");
    log.info(q.winner()->name() + " won");

    return 0;
}