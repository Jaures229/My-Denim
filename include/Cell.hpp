#ifndef CELL_HPP_
    #define CELL_HPP_
    struct Cell {
        bool isMine = false;
        bool isRevealed = false;
        bool hasFlag = false;
        int neighboringMines = 0;
    };

#endif /* !CELL_HPP_ */
