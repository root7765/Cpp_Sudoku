#include "SudokuSolver.hpp"
#include <algorithm>

SudokuSolver::SudokuSolver(Sudoku &sudoku) : m_sudoku(sudoku) {}

void updateMarker(const Sudoku::Board &board, const uint8_t &row, const uint8_t &col, std::array<bool, 10> &marker)
{
    // init all numbers to be available
    for (uint8_t i = 0; i < marker.size(); ++i)
    {
        marker[i] = true;
    }
    marker[Sudoku::NOTSET] = false;

    // allready solved?
    if (board[row][col] != Sudoku::NOTSET)
    {
        // only one possible number allowed
        for (uint8_t i = 0; i < marker.size(); ++i)
        {
            marker[i] = false;
        }
        marker[board[row][col]] = false;
        return;
    }
    // disable complete row
    for (uint8_t i = 0; i < Sudoku::FIELD_COLS; ++i)
    {
        marker[board[row][i]] = false;
    }
    // disable complete col
    for (uint8_t i = 0; i < Sudoku::FIELD_ROWS; ++i)
    {
        marker[board[i][col]] = false;
    }
    // disable complete block
    uint8_t b_col = col / Sudoku::BLOCK_COLS;
    uint8_t b_row = row / Sudoku::BLOCK_ROWS; //Modulo 3
    for (uint8_t r = b_row * Sudoku::BLOCK_ROWS; r < (b_row + 1) * Sudoku::BLOCK_ROWS; ++r)
    {
        for (uint8_t c = b_col * Sudoku::BLOCK_COLS; c < (b_col + 1) * Sudoku::BLOCK_COLS; ++c)
        {
            marker[board[r][c]] = false;
        }
    }
}

void SudokuSolver::solve()
{
   auto &board = m_sudoku.getBoard();

    bool changed = true; // auf true gesetzt
    
    // while there are changed we should continue
    while (changed)
    {
        changed = false;
        for (uint8_t row = 0; row < Sudoku::FIELD_ROWS; ++row)
        {
            for (uint8_t col = 0; col < Sudoku::FIELD_COLS; ++col)
            {
                // care for unset cells only
                if (board[row][col] == Sudoku::NOTSET) // != zu ==
                {
                    std::array<bool, 10> m; // 9 + Not Set //anstatt 9 10
                    // update the marker with all local changes
                    updateMarker(board, row, col, m);

                    // if there only one possible solution, set the cell
                    if (std::count(m.begin(), m.end(), true) == 1)
                    {
                        for (uint8_t i = 0; i < 10; ++i) // von 1 bis 9 einsetzen
                        {
                            if (m[i])
                            {
                                // set cell
                                m_sudoku.setValue(row, col, i);
                                // set changed to reevaluate the board
                                changed = true;
                            }
                        }
                    }
                }
            }
        }   
    }
}