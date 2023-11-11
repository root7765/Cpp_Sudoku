#include "Sudoku.hpp"
#include <algorithm>
#include <cassert>

Sudoku::Sudoku(std::mt19937::result_type seed, std::ostream &output)
    : m_out(output), m_rnd_gen(m_rd())
{
    if (seed != std::mt19937::default_seed)
        m_rnd_gen.seed(seed);

    // search randomly
    std::shuffle(m_random_idx_cols.begin(), m_random_idx_cols.end(), m_rnd_gen);
    std::shuffle(m_random_idx_rows.begin(), m_random_idx_rows.end(), m_rnd_gen);

    // test randomly
    std::shuffle(m_random_values.begin(), m_random_values.end(), m_rnd_gen);

    initializeBoard();
}

void Sudoku::initializeBoard(uint8_t spaces) noexcept
{
    // clear board
    for (auto &r : m_board)
        for (auto &cell : r)
            cell = NOTSET;

    assert(BLOCK_COLS == BLOCK_ROWS);
    for (uint8_t i = 0; i < BLOCK_COLS; i++)
    {
        Block(m_board, i, i).initialize(m_random_values);
    }

    assert(solve() == true);

    uint32_t solution_count = 0;
    std::uniform_int_distribution<> distrib_cols(0, FIELD_COLS - 1);
    std::uniform_int_distribution<> distrib_rows(0, FIELD_ROWS - 1);

    while (spaces > 0)
    {
        auto &cell = m_board[distrib_rows(m_rnd_gen)][distrib_cols(m_rnd_gen)];
        if (cell != NOTSET)
        {
            auto backup = cell;
            cell = NOTSET;

            // try to solve it and test if there is only one solution
            solution_count = 0;
            solve(false, solution_count);
            if (solution_count == 1)
            {
                --spaces;
            }
            else
            {
                // revert if not
                cell = backup;
            }
        }
    }
}

bool Sudoku::check() const noexcept
{
    for (uint8_t c = 0; c < FIELD_COLS; ++c)
    {
        if (!Column(m_board, c).check())
            return false;
    }
    for (uint8_t r = 0; r < FIELD_ROWS; ++r)
    {
        if (!Row(m_board, r).check())
            return false;
    }
    for (uint8_t r = 0; r < BLOCK_ROWS; r++)
    {
        for (uint8_t c = 0; c < BLOCK_COLS; c++)
        {
            // ugly cast but check is const only, therefore no problem
            if (!Block(*const_cast<Board *>(&m_board), r, c).check())
                return false;
        }
    }
    return true;
}

const Sudoku::Board &Sudoku::getBoard() const noexcept { return m_board; }

void Sudoku::print() const noexcept
{
    for (const auto &r : m_board)
    {
        for (const auto &c : r)
        {

            if (c == NOTSET)
                m_out << " "
                      << " ";
            else
                m_out << int(c) << " ";
        }
        m_out << std::endl;
    }
}

void Sudoku::setValue(const uint8_t &row, const uint8_t &col,
                      const uint8_t value) noexcept(false)
{
    if (row >= FIELD_ROWS || col >= FIELD_COLS)
    {
        throw std::range_error("coordinates are out of field");
    }
    if (value > 9)
    {
        throw std::range_error("value is out of range");
    }

    if (m_board[row][col] != NOTSET && value != NOTSET)
    {
        throw std::range_error("cell already set");
    }

    auto backup = m_board[row][col];
    m_board[row][col] = value;
    if (!check())
    {
        m_board[row][col] = backup;
        throw std::domain_error("sudoku not valid with this input");
    }
}

bool Sudoku::findEmptyField(uint8_t &row, uint8_t &col) const noexcept
{

    for (const auto &r : m_random_idx_rows)
    {
        for (const auto &c : m_random_idx_cols)
        {
            if (m_board[r][c] == NOTSET)
            {
                row = r;
                col = c;
                return true;
            }
        }
    }
    return false;
}

bool Sudoku::solve() noexcept
{
    uint32_t count = 0;
    return solve(true, count);
}

bool Sudoku::solve(const bool &stop, uint32_t &solution_count) noexcept
{
    uint8_t row, col;
    if (!findEmptyField(row, col)) // all filled
    {
        ++solution_count;
        return true;
    }

    for (const auto &v : m_random_values)
    {
        m_board[row][col] = v;

        if (check() && solve(stop, solution_count))
        {
            if (stop)
                return true;
        }

        m_board[row][col] = NOTSET;
    }

    // not successfull
    return false;
}

Sudoku::Column::Column(const Board &board, const uint8_t &col)
    : m_board(board), m_col(col)
{
}

bool Sudoku::Column::check() const noexcept
{
    std::array<bool, 10> used = {false}; // include not set
    for (uint8_t r = 0; r < FIELD_ROWS; ++r)
    {
        const auto &value = m_board[r][m_col];
        if (value != NOTSET && used[value])
        {
            return false;
        }
        used[value] = true;
    }
    return true;
}

Sudoku::Row::Row(const Board &board, const uint8_t &row)
    : m_board(board), m_row(row)
{
}

bool Sudoku::Row::check() const noexcept
{
    std::array<bool, 10> used = {false}; // include not set
    for (uint8_t c = 0; c < FIELD_COLS; ++c)
    {
        const auto &value = m_board[m_row][c];
        if (value != NOTSET && used[value])
        {
            return false;
        }
        used[value] = true;
    }
    return true;
}

Sudoku::Block::Block(Board &board, const uint8_t &block_row,
                     const uint8_t &block_col)
    : m_board(board), m_block_row(block_row), m_block_col(block_col)
{
}

void Sudoku::Block::initialize(const std::array<uint8_t, 9> &values) noexcept
{
    auto value = values.begin();
    for (uint8_t r = m_block_row * BLOCK_ROWS;
         r < (m_block_row + 1) * BLOCK_ROWS; ++r)
    {
        for (uint8_t c = m_block_col * BLOCK_COLS;
             c < (m_block_col + 1) * BLOCK_COLS; ++c)
        {
            m_board[r][c] = *value;
            value++;
        }
    }
}

bool Sudoku::Block::check() const noexcept
{
    std::array<bool, 10> used = {false}; // include not set
    for (uint8_t r = m_block_row * BLOCK_ROWS;
         r < (m_block_row + 1) * BLOCK_ROWS; ++r)
    {
        for (uint8_t c = m_block_col * BLOCK_COLS;
             c < (m_block_col + 1) * BLOCK_COLS; ++c)
        {
            const auto &value = m_board[r][c];
            if (value != NOTSET && used[value])
            {
                return false;
            }
            used[value] = true;
        }
    }
    return true;
}