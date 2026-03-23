#include "../include/Board.hpp"

#include <iostream>

Board::Board(int w, int h, int m) : width(w), height(h), mineCount(m)
{
    // Allocation du tableau de pointeurs (les lignes) 
    grid = new Cell* [height];

    // Allocation d'un tableau de cellules pour chaque collones
    for (int i = 0; i < height; ++i) {
        grid[i] = new Cell[width];
    }

    // Initialiser la grille de jeu
    initializeGrid();
}

void Board::placeMines()
{
    int placed = 0;
    
    // Initialisation du  générateur de nombres aléatoires à partir du temps actuel

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    while (placed < mineCount) {
        // Générer des coordonnées aléatoires
        int x = std::rand() % width;
        int y = std::rand() % height;

        // Vérifier si la case n'est pas déjà une mine
        if (!grid[y][x].isMine) {
            grid[y][x].isMine = true;
            placed++;
        }
    }
    std::cout << "Nombre de mines placées: " << mineCount << std::endl;
}

void Board::calculateNeighbors()
{
    // On parcourt toute la grille à la recherche de mines
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            
            // Si on trouve une mine, on ajoute +1 aux voisins
            if (grid[y][x].isMine) {
                
                // Parcourir les 8 cases autour de cette mine
                for (int i = -1; i <= 1; ++i) {
                    for (int j = -1; j <= 1; ++j) {
                        
                        // Ignorer la case de la mine elle-même
                        if (i == 0 && j == 0) continue;

                        int ni = y + i;
                        int nj = x + j;

                        // Vérifier si le voisin est dans la grille 
                        if (isWithinBounds(nj, ni)) {
                            grid[ni][nj].neighboringMines++;
                        }
                    }
                }
            }
        }
    }
}

void Board::initializeGrid()
{
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            grid[y][x].isMine = false;
            grid[y][x].isRevealed = false;
            grid[y][x].hasFlag = false;
            grid[y][x].neighboringMines = 0;
        }
    }
}

void Board::initgame()
{
    placeMines();
    calculateNeighbors();
}

void Board::draw() const
{
    std::cout << "   ";
    for (int x = 0; x < width; ++x) std::cout << x << " ";
    std::cout << std::endl;

    for (int y = 0; y < height; ++y) {
        // Afficher le numéro de ligne
        std::cout << y << " |";

        for (int x = 0; x < width; ++x) {
            const Cell& c = grid[y][x];

            if (!c.isRevealed) {
                if (c.hasFlag) {
                    std::cout << "F "; // Drapeau
                } else {
                    std::cout << ". "; // Case cachée
                }
            } else {
                if (c.isMine) {
                    std::cout << "* "; // Mine
                } else if (c.neighboringMines > 0) {
                    std::cout << c.neighboringMines << " "; // Chiffre
                } else {
                    std::cout << "  "; // Case vide
                }
            }
        }
        std::cout << "|" << std::endl;
    }
}

bool Board::isWithinBounds(int x, int y) const
{
    return (x >= 0 && x < width && y >= 0 && y < height);
}

void Board::revealCell(int x, int y)
{
    // Vérifier les limites et si la case est déjà révélée
    if (!isWithinBounds(x, y) || grid[y][x].isRevealed || grid[y][x].hasFlag) {
        return;
    }

    // Révéler la case actuelle
    grid[y][x].isRevealed = true;

    // Si c'est une mine, le jeu s'arrêtera
    if (grid[y][x].isMine) {
        return;
    }

    // 4. Si la case est vide,  on propage
    if (grid[y][x].neighboringMines == 0) {
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                // EViter de se propager soi-meme 
                if (i == 0 && j == 0) continue;
                
                revealCell(x + j, y + i); // Appel récursif
            }
        }
    }
}

bool Board::checkLoss() const
{
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Si une mine est révélée le jeu est perdu
            if (grid[y][x].isMine && grid[y][x].isRevealed) {
                return true;
            }
        }
    }
    return false;
}

bool Board::checkWin() const
{
    int hiddenSafeCells = 0;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (!grid[y][x].isMine && !grid[y][x].isRevealed) {
                hiddenSafeCells++;
            }
        }
    }

    return (hiddenSafeCells == 0);
}

void Board::toggleFlag(int x, int y)
{
    if (!isWithinBounds(x, y)) {
        return;
    }

    if (!grid[y][x].isRevealed) {
        // inverser l'état du flag
        grid[y][x].hasFlag = !grid[y][x].hasFlag;
    }
}

Board::~Board()
{
    // Liberer chaque collone
    for (int i = 0; i < height; ++i) {
        delete[] grid[i];
    }

    // Liberation du tableau
    delete[] grid;
}
