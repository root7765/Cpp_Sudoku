#pragma once

#include <array>
#include <iostream>
#include <random>
#include <stdexcept>

/**
 * 9x9 Sudoku Puzzle
 */
class Sudoku
{
  public:
    // number of rows
    static constexpr uint8_t FIELD_ROWS = 9;
    // number of columns
    static constexpr uint8_t FIELD_COLS = 9;
    // number of block rows
    static constexpr uint8_t BLOCK_ROWS = 3;
    // number of block columns
    static constexpr uint8_t BLOCK_COLS = 3;
    // static value for not-set cell
    static constexpr uint8_t NOTSET = 0;

    using Board = std::array<std::array<uint8_t, FIELD_COLS>, FIELD_ROWS>;

    /*
     * constructor
     * @param seed seed value for random number generator
     * @param output redirect for output for testing
     */
    Sudoku(std::mt19937::result_type seed = std::mt19937::default_seed,
           std::ostream &output = std::cout);

    /**
     * initialize the board with a new puzzle
     * @param spaces number of empty spaces
     */
    void initializeBoard(uint8_t spaces = 20) noexcept;

    /**
     * test if board has a valid content
     * @returns true if board is valid
     */
    bool check() const noexcept;

    /**
     * get access to the game board
     * @return 2D array of the layout [FIELD_ROWS][FIELD_COLS]
     */
    const Board &getBoard() const noexcept;

    /**
     * print the board to the output stream given to the constructor
     */
    void print() const noexcept;

    /**
     * set a cell value in the board
     * checks if new content is valid
     *
     * @param row row of board
     * @param col column of board
     * @param value value to be set
     * @throws range_error if row, col, or value are out of range
     * @throws domain_error if new value violates sudoku rules
     */
    void setValue(const uint8_t &row, const uint8_t &col,
                  const uint8_t value) noexcept(false);

  private:
    class Block
    {
      public:
        Block(Board &board, const uint8_t &block_row, const uint8_t &block_col);

        void initialize(const std::array<uint8_t, 9> &values) noexcept;
        bool check() const noexcept;

      private:
        Board &m_board;
        uint8_t m_block_row;
        uint8_t m_block_col;
    };

    class Row
    {
      public:
        Row(const Board &board, const uint8_t &row);

        bool check() const noexcept;

      private:
        const Board &m_board;
        uint8_t m_row;
    };

    class Column
    {
      public:
        Column(const Board &board, const uint8_t &col);

        bool check() const noexcept;

      private:
        const Board &m_board;
        uint8_t m_col;
    };

    bool findEmptyField(uint8_t &row, uint8_t &col) const noexcept;
    bool solve() noexcept;
    bool solve(const bool &stop, uint32_t &solution_count) noexcept;

    std::ostream &m_out;

    std::random_device m_rd;
    std::mt19937 m_rnd_gen;
    std::array<uint8_t, FIELD_COLS> m_random_idx_cols = {0, 1, 2, 3, 4,
                                                         5, 6, 7, 8};
    std::array<uint8_t, FIELD_ROWS> m_random_idx_rows = {0, 1, 2, 3, 4,
                                                         5, 6, 7, 8};
    std::array<uint8_t, 9> m_random_values = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    Board m_board;
};
