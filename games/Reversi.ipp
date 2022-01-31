
#pragma once

#include "Reversi.hpp"
#include "utils/ArrayUtil.hpp"

// m_pBoard[height][width]

Reversi::Game::Game()
    :Game(8, 8)
{
}

Reversi::Game::Game(int width, int height)
{
    Alloc2dIntArray(&m_pBoard, height, width, 0);
    Alloc2dIntArray(&m_pPlacablePositions, height * width, 2, 0);

    if ((width  % 2) == 1 ||
        (height % 2) == 1)
    {
        width  = (width  + 1) / 2 * 2;
        height = (height + 1) / 2 * 2;

        printf("The board size should be even number.\n"
               "Width and height are fixed.\n"
               "width  = %d\n"
               "height = %d\n",
               width, height);
    }

    m_width = width;
    m_height = height;

    m_turnPlayer = 1;
    m_turnNumber = 0;

    m_pBoard[(m_height - 1) / 2    ][(m_width - 1) / 2    ] = 2;
    m_pBoard[(m_height - 1) / 2    ][(m_width - 1) / 2 + 1] = 1;
    m_pBoard[(m_height - 1) / 2 + 1][(m_width - 1) / 2    ] = 1;
    m_pBoard[(m_height - 1) / 2 + 1][(m_width - 1) / 2 + 1] = 2;

    UpdatePlacablePos();
}

Reversi::Game::~Game()
{
    Free2dIntArray(&m_pBoard, m_height, m_width);
    Free2dIntArray(&m_pPlacablePositions, m_height * m_width, 2);
}


void Reversi::Game::Print(bool useColor,
                          bool printRuler,
                          int  printPlacable)
{
    int **print_buf_color;

    Alloc2dIntArray(&print_buf_color, m_height, m_width, 2);

    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            switch (m_pBoard[y][x])
            {
                case 0:
                    print_buf_color[y][x] = 2;
                    break;
                case 1:
                    print_buf_color[y][x] = 0;
                    break;
                case 2:
                    print_buf_color[y][x] = 7;
                    break;
            }
        }
    }

    if (printPlacable)
    {
        for (int i = 0; i < m_placablePosCount; i++)
        {
            print_buf_color[m_pPlacablePositions[i][1]]
                           [m_pPlacablePositions[i][0]] = 1;
        }
    }



    if (printRuler)
    {
        printf("   | ");
        for (int i = 0; i < m_width; i++)
        {
            printf("%2d", i);
        }
        printf("\n");
        for (int i = 0; i < (5 + 2 * m_width); i++)
        {
            printf("-");
        }
        printf("\n");
    }

    if (useColor)
    {
        for (int y = 0; y < m_height; y++)
        {
            if (printRuler) printf("%2d | ", y);
            printf("\033[42m");
            for (int x = 0; x < m_width; x++)
            {
                printf("\033[3%1dm", print_buf_color[y][x]);
                printf("##");
            }
            printf("\033[m");
            printf("\n");
        }
        printf("\033[m");
    }
    else
    {
        // for (int y = 0; y < m_height; y++)
        // {
        //     for (int x = 0; x < m_width; x++)
        //     {
        //         printf("##");
        //     }
        //     printf("\n");
        // }
    }

    Free2dIntArray(&print_buf_color, m_height, m_width);

    // for (int i = 0; i < m_height; i++)
    // {
    //     printf("%2d | ", i);

    //     if (useColor)
    //     {
    //         printf("\033[42m");
    //     }
    //     for (int j = 0; j < m_width; j++)
    //     {
    //         if (useColor)
    //         {
    //             switch (m_pBoard[i][j])
    //             {
    //                 case 0:
    //                     printf("\033[32m");
    //                     break;
    //                 case 1:
    //                     printf("\033[30m");
    //                     break;
    //                 case 2:
    //                     printf("\033[37m");
    //                     break;
    //             }
    //             printf("##");
    //             printf("\033[37m");
    //         }
    //         else
    //         {
    //             printf("%d ", m_pBoard[i][j]);
    //         }
    //     }
    //     if (useColor)
    //     {
    //         printf("\033[m");
    //     }
    //     printf("\n");
    // }

    // if (useColor)
    // {
    //     printf("\033[m");
    // }
}



static int search_directions[8][2] = {
    { 0,  1},
    { 0, -1},
    { 1,  0},
    { 1,  1},
    { 1, -1},
    {-1,  0},
    {-1,  1},
    {-1, -1}};

int Reversi::Game::PutDisc(int x, int y)
{
    if (x >= m_width || y >= m_height)
    {
        return 1;
    }
    if (m_pBoard[y][x] != 0)
    {
        return 2;
    }

    bool is_placable = false;
    for (int i = 0; i < m_placablePosCount; i++)
    {
        if (m_pPlacablePositions[i][0] == x &&
            m_pPlacablePositions[i][1] == y)
        {
            is_placable = true;
        }
    }

    if (is_placable == false)
    {
        return 3;
    }


    m_pBoard[y][x] = m_turnPlayer;

    for (int i = 0; i < 8; i++)
    {
        int next_position[2] = {y + search_directions[i][1],
                                x + search_directions[i][0]};

        if (next_position[0] < 0 ||
            next_position[0] >= m_height ||
            next_position[1] < 0 ||
            next_position[1] >= m_width)
        {
            continue;
        }

        if (m_pBoard[next_position[0]][next_position[1]] == 0)
        {
            continue;
        }
        if (m_pBoard[next_position[0]][next_position[1]] == m_turnPlayer)
        {
            continue;
        }
        if (SearchLine(x, y,
                       search_directions[i][0], search_directions[i][1],
                       m_turnPlayer) == false)
        {
            continue;
        }

        int x_i = x;
        int y_i = y;

        x_i += search_directions[i][0];
        y_i += search_directions[i][1];
        while (1)
        {
            if (x_i < 0 ||
                x_i >= m_width ||
                y_i < 0 ||
                y_i >= m_height)
            {
                break;
            }

            if (m_pBoard[y_i][x_i] == m_turnPlayer)
            {
                break;
            }

            m_pBoard[y_i][x_i] = m_turnPlayer;

            x_i += search_directions[i][0];
            y_i += search_directions[i][1];
        }
    }

    m_turnNumber++;
    m_turnPlayer = m_turnPlayer == 2 ? 1 : 2;

    UpdatePlacablePos();

    if (m_placablePosCount == 0)
    {
        m_turnPlayer = m_turnPlayer == 2 ? 1 : 2;
    }

    return 0;
}


void Reversi::Game::UpdatePlacablePos(void)
{
    int **pPlacable_positions;

    Alloc2dIntArray(&pPlacable_positions, m_height, m_width, 0);

    // for y
    for (int y = 0; y < m_height; y++)
    {
        // for x
        for (int x = 0; x < m_width; x++)
        {
            if (m_pBoard[y][x] != 0)
            {
                continue;
            }

            // for direction
            for (int i = 0; i < 8; i++)
            {
                int search_direction[2] = {search_directions[i][0],
                                           search_directions[i][1]};

                int next_position[2] = {y + search_direction[1],
                                        x + search_direction[0]};

                if (next_position[0] <  0 ||
                    next_position[0] >= m_height ||
                    next_position[1] <  0 ||
                    next_position[1] >= m_width)
                {
                    continue;
                }

                int next_position_color = m_pBoard[next_position[0]][next_position[1]];
                if (next_position_color == m_turnPlayer ||
                    next_position_color == 0)
                {
                    continue;
                }

                if (SearchLine(x, y,
                               search_direction[0], search_direction[1],
                               next_position_color == 1 ? 2 : 1))
                {
                    pPlacable_positions[y][x] = 1;
                }
            }
        }
    }

    m_placablePosCount = 0;
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            if (pPlacable_positions[y][x] == 1)
            {
                m_pPlacablePositions[m_placablePosCount][0] = x;
                m_pPlacablePositions[m_placablePosCount][1] = y;
                m_placablePosCount++;
            }
        }
    }

    Free2dIntArray(&pPlacable_positions, m_height, m_width);
}


bool Reversi::Game::SearchLine(int fromX, int fromY,
                               int directionX, int directionY,
                               int searchFor)
{
    int x = fromX;
    int y = fromY;

    x += directionX;
    y += directionY;
    while (not(x < 0 ||
               x >= m_width ||
               y < 0 ||
               y >= m_height))
    {
        if (m_pBoard[y][x] == searchFor)
        {
            return true;
        }
        x += directionX;
        y += directionY;
    }

    return false;
}

