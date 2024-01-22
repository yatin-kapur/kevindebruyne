#include <iostream>
#include <memory>
#include <string>

#include "lib/logger/log.h"

#include "Piece.h"
#include "Player.h"
#include "Quarto.h"

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