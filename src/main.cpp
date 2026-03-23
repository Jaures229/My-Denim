#include "../include/Board.hpp"

int main()
{
    int w = 10, h = 10, m = 5;
    Board game(w, h, m);

    game.initgame();

    bool gameOver = false;

    // Boucle Principal 
    while (!gameOver) {
        game.draw();

        int x, y;
        char action;
        std::cout << "Action (r pour reveler, f pour drapeau) et Coordonnees (x y) : ";
        std::cin >> action >> x >> y;

        if (action == 'r') {
            if (!game.isWithinBounds(x, y)) {
                std::cout << "Coordonnees (x y) hors de porté de la grille !!!." << std::endl << std::endl;
            }
            else {
                game.revealCell(x, y);
                
                if (game.checkLoss()) { // Condition de défaite 
                    game.draw();
                    std::cout << "BOOM ! Vous avez touche une mine. GAME OVER" << std::endl;
                    gameOver = true;
                }
            }
        } else if (action == 'f') {
            game.toggleFlag(x, y);
        }

        if (!gameOver && game.checkWin()) {
            game.draw();
            std::cout << "FELICITATIONS ! YOU WIN" << std::endl;
            gameOver = true;
        }
    }

    return 0;
}