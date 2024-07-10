#include "Sudoku.hpp"
#include "SudokuSolver.hpp"

//for git:
int main()
{
    std::cout << "Sudoku Puzzle" << std::endl;

    // initialize board with seed, remove 0 to get new puzzle everytime
    Sudoku s{};

    // uncomment to get 40 empty cells
    s.initializeBoard();

    s.print();

    // instanciate your solver
    SudokuSolver solver(s);
    solver.solve();

    /*
    // solution for board with seed=0
    s.setValue(0, 4, 2);
    s.setValue(0, 8, 8);
    s.setValue(1, 2, 3);
    s.setValue(1, 7, 5);
    s.setValue(2, 3, 5);
    s.setValue(2, 8, 4);
    s.setValue(3, 0, 2);
    s.setValue(3, 5, 5);
    s.setValue(4, 1, 7);
    s.setValue(4, 3, 8);
    s.setValue(4, 4, 4);
    s.setValue(4, 8, 6);
    s.setValue(5, 0, 5);
    s.setValue(6, 1, 2);
    s.setValue(6, 6, 9);
    s.setValue(6, 7, 1);
    s.setValue(6, 8, 5);
    s.setValue(7, 7, 4);
    s.setValue(7, 8, 3);
    s.setValue(8, 7, 6);
    */

    std::cout << "solved puzzle:" << std::endl;
    s.print();

    return 0;
}
