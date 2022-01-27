
#pragma once

#include "4InARow.hpp"
#include "utils/ArrayUtil.hpp"

#include <stdio.h>

FourInARow::Game::Game(int width, int height)
{
    m_width = width;
    m_height = height;

    m_pBoard = new int[width * height];
    for (int i = 0; i < (width * height); i++) m_pBoard[i] = 0;

    m_pGameHistory = new int [width * height * 2];

    m_pWinningLine = new int [8];

    m_turnPlayer = 1;
    m_turnNumber = 0;

    m_gameStatus = 0;

    m_lastX = -1;
    m_lastY = -1;
}

FourInARow::Game::~Game()
{
    delete [] m_pBoard;
    delete [] m_pGameHistory;
    delete [] m_pWinningLine;
}



int FourInARow::Game::PutCoin(int column, int player)
{
    if (player == 0) player = m_turnPlayer;

    if (player != m_turnPlayer)
    {
        return 1;
    }

    if (column >= m_width)
    {
        return 3;
    }



    int node_x_i = column;
    int node_y_i = 0;
    while (1)
    {
        if (node_y_i == m_height)
        {
            break;
        }
        if (m_pBoard[node_y_i * m_width + node_x_i] != 0)
        {
            break;
        }

        node_y_i++;
    }

    node_y_i--;

    if (node_y_i < 0)
    {
        return 2;
    }

    m_pBoard[node_y_i * m_width + node_x_i] = player;

    m_pGameHistory[m_turnNumber * 2]     = node_x_i;
    m_pGameHistory[m_turnNumber * 2 + 1] = node_y_i;

    m_turnNumber++;
    m_turnPlayer = (m_turnPlayer % 2) + 1;

    m_lastX = node_x_i;
    m_lastY = node_y_i;


    UpdateGameStatus();

    return 0;
}

void FourInARow::Game::Undo(void)
{
    if (m_turnNumber <= 0)
    {
        return;
    }

    m_pBoard[m_lastY * m_width + m_lastX] = 0;
    m_turnNumber--;
    m_turnPlayer = (m_turnNumber % 2) + 1;

    m_lastX = m_pGameHistory[(m_turnNumber - 1) * 2];
    m_lastY = m_pGameHistory[(m_turnNumber - 1) * 2 + 1];
}



// TODO: readable code (use functions...)
void FourInARow::Game::UpdateGameStatus(void)
{
    for (int i = 0; i < 4; i++)
    {
        int searching_x = m_lastX;
        int searching_y = m_lastY;

        while (1)
        {
            switch (i)
            {
                case 0:
                    searching_x--;
                    break;
                case 1:
                    searching_x--;
                    searching_y--;
                    break;
                case 2:
                    searching_y--;
                    break;
                case 3:
                    searching_x++;
                    searching_y--;
                    break;
            };
            if (searching_x <= 0 || searching_x >= (m_width  - 1)||
                searching_y <= 0 || searching_y >= (m_height - 1))
            {
                break;
            }
        }

        int continuing_number = -1;
        int continuing_length = 0;

        int number_now;

        while (1)
        {
            switch (i)
            {
                case 0:
                    searching_x++;
                    break;
                case 1:
                    searching_x++;
                    searching_y++;
                    break;
                case 2:
                    searching_y++;
                    break;
                case 3:
                    searching_x--;
                    searching_y++;
                    break;
            }
            if (searching_x < 0 || searching_x >= m_width ||
                searching_y < 0 || searching_y >= m_height)
            {
                break;
            }

            number_now = m_pBoard[searching_y * m_width + searching_x];
            if (continuing_number == number_now)
            {
                continuing_length++;
            }
            else
            {
                continuing_number = number_now;
                continuing_length = 1;
            }
            m_pWinningLine[(continuing_length - 1) * 2]     = searching_x;
            m_pWinningLine[(continuing_length - 1) * 2 + 1] = searching_y;

            if (continuing_length >= 4)
            {
                continuing_length = 1;
                if (continuing_number != 0)
                {
                    m_gameStatus = continuing_number;
                    return;
                }
            }
        }
    }

    if (m_turnNumber >= (m_width * m_height) && m_gameStatus == 0)
    {
        m_gameStatus = 3;
    }

    return;
}



// TODO : use array to contain number and highlight options and print
void FourInARow::Game::Print(bool useColor,
                             int highlightLastCoin,
                             int highlightWinningLine)
{
    if (m_turnNumber == 0)
    {
        highlightLastCoin = 0;
    }

    if (m_gameStatus == 0 || m_gameStatus == 3)
    {
        highlightWinningLine = 0;
    }

    if (useColor == false)
    {
        if (highlightLastCoin == 2)
        {
            highlightLastCoin = 0;
        }
        if (highlightWinningLine == 2)
        {
            highlightWinningLine = 0;
        }
    }

    int **print_buffer_backcolor;
    int **print_buffer_forecolor;
    int **print_buffer_asterisk;
    int **print_buffer_printnumber;

    Alloc2dIntArray(&print_buffer_backcolor  , m_height, m_width, 0);
    Alloc2dIntArray(&print_buffer_forecolor  , m_height, m_width, 7);
    Alloc2dIntArray(&print_buffer_asterisk   , m_height, m_width, 0);
    Alloc2dIntArray(&print_buffer_printnumber, m_height, m_width, 0);


    int number_now;
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            number_now = m_pBoard[y * m_width + x];

            print_buffer_printnumber[y][x] = number_now;

            if (useColor)
            {
                if (number_now == 0)
                {
                    print_buffer_forecolor[y][x] = 7;
                }
                else
                {
                    print_buffer_forecolor[y][x] = number_now;
                }
            }
        }
    }


    if (highlightLastCoin == 1)
    {
        print_buffer_asterisk[m_lastY][m_lastX] = 1;
    }

    if (highlightLastCoin == 2)
    {
        print_buffer_backcolor[m_lastY][m_lastX] = 4;
    }

    if (highlightWinningLine == 1)
    {
        for (int i = 0; i < 4; i++)
        {
            print_buffer_asterisk
                [m_pWinningLine[i * 2 + 1]]
                [m_pWinningLine[i * 2    ]] = 1;
        }
    }

    if (highlightWinningLine == 2)
    {
        for (int i = 0; i < 4; i++)
        {
            print_buffer_backcolor
                [m_pWinningLine[i * 2 + 1]]
                [m_pWinningLine[i * 2    ]] = 3;
        }
    }

    if (useColor)
    {
        for (int y = 0; y < m_height; y++)
        {
            for (int x = 0; x < m_width; x++)
            {
                printf("\033[3%1dm", print_buffer_forecolor[y][x]);
                printf("\033[4%1dm", print_buffer_backcolor[y][x]);
                printf("%d", print_buffer_printnumber[y][x]);
                printf("\033[m");
                printf("%c", print_buffer_asterisk[y][x] == 1 ? '*' : ' ');
            }
            printf("\033[m");
            printf("\n");
        }
    }
    else
    {
        for (int y = 0; y < m_height; y++)
        {
            for (int x = 0; x < m_width; x++)
            {
                printf("%d", print_buffer_printnumber[y][x]);
                printf("%c", print_buffer_asterisk[y][x] == 1 ? '*' : ' ');
            }
            printf("\n");
        }
    }

    Free2dIntArray(&print_buffer_backcolor  , m_height, m_width);
    Free2dIntArray(&print_buffer_forecolor  , m_height, m_width);
    Free2dIntArray(&print_buffer_asterisk   , m_height, m_width);
    Free2dIntArray(&print_buffer_printnumber, m_height, m_width);
}

