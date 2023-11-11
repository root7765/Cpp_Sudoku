#pragma once

#include "Sudoku.hpp"

/**
 * solver for sudoku puzzles with no recursion needed
 */
class SudokuSolver
{
  public:
    /**
     * constructor
     * @param sudoku reference to sudoku object
     */
    SudokuSolver(Sudoku &sudoku);

    /**
     * this functions solves the puzzle
     */
    void solve();

  private:
    Sudoku &m_sudoku; ///< reference to sudoku object
};