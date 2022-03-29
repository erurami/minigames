
#pragma once

#include "4InARow.hpp"
#include "utils/ArrayUtil.hpp"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FourInARow::Game::Game(int width, int height)
{
    m_width = width;
    m_height = height;

    AllocBlankMemberBuffers();

    m_turnPlayer = 1;
    m_turnNumber = 0;

    m_gameStatus = 0;

    m_lastX = -1;
    m_lastY = -1;
}

FourInARow::Game::Game(const Game& game)
{
    this->Reconstruct(game);
}

FourInARow::Game::~Game()
{
    delete [] m_pBoard;
    delete [] m_pGameHistory;
    delete [] m_pWinningLine;
#ifdef MINIGAMES_USEDEBUG
    // TODO
#endif
}

FourInARow::Game& FourInARow::Game::operator = (const Game& game)
{
    if (this == &game)
    {
        return *this;
    }

    this->Reconstruct(game);

    return *this;
}

void FourInARow::Game::Reconstruct(const Game& game)
{
    this->m_width = game.m_width;
    this->m_height = game.m_height;

    this->AllocBlankMemberBuffers();

    this->m_turnPlayer = game.GetWhichTurn();
    this->m_turnNumber = game.GetTurnNumber();

    this->m_gameStatus = game.GetGameStatus();

    game.GetEntireBoard(this->m_pBoard);
    game.GetWinningLine(this->m_pWinningLine);
    game.GetGameHistory(this->m_pGameHistory);

    this->m_lastX = this->m_pGameHistory[(this->m_turnNumber - 1) * 2];
    this->m_lastY = this->m_pGameHistory[(this->m_turnNumber - 1) * 2 + 1];
}


void FourInARow::Game::GetEntireBoard(int* pBoardDest) const
{
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            pBoardDest[y * m_width + x] = m_pBoard[y * m_width + x];
        }
    }
}
void FourInARow::Game::GetWinningLine(int* pWinningLineDest) const
{
    memcpy(pWinningLineDest, m_pWinningLine, sizeof(int) * 8);
}
void FourInARow::Game::GetGameHistory(int* pHistoryDest) const
{
    memcpy(pHistoryDest, m_pGameHistory, sizeof(int) * m_width * m_height * 2);
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

    if (m_gameStatus != 0)
    {
        m_gameStatus = 0;
        UpdateGameStatus();
    }
}




void FourInARow::Game::UpdateGameStatus(void)
{
    if (SearchLine_Passes_Direction(m_lastX, m_lastY,  1, 0)) return; // horizontal
    if (SearchLine_Passes_Direction(m_lastX, m_lastY,  0, 1)) return; // vertical
    if (SearchLine_Passes_Direction(m_lastX, m_lastY,  1, 1)) return; // diagonal : from left-up to right-down
    if (SearchLine_Passes_Direction(m_lastX, m_lastY, -1, 1)) return; // diagonal : from right-up to left-down

    if (m_turnNumber >= (m_width * m_height) && m_gameStatus == 0)
    {
        m_gameStatus = 3;
        return;
    }

    return;
}

bool FourInARow::Game::SearchLine_Passes_Direction(int x, int y, int directionX, int directionY)
{
    int searching_x = x;
    int searching_y = y;

    while (StepOnce(&searching_x, &searching_y, -directionX, -directionY))
    {
    }

    int continuing_number = -1;
    int continuing_length = 0;

    int number_now;

    for (bool step_result = true;
         step_result;
         step_result = StepOnce(&searching_x, &searching_y, directionX, directionY))
    {
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
            continuing_length = 0;
            if (continuing_number != 0)
            {
                m_gameStatus = continuing_number;
                return true;
            }
        }
    }
    return false;
}

bool FourInARow::Game::StepOnce(int* x, int*y, int directionX, int directionY)
{
    (*x) += directionX;
    (*y) += directionY;

    if ((*x) < 0 || (*x) >= m_width ||
        (*y) < 0 || (*y) >= m_height)
    {
        (*x) -= directionX;
        (*y) -= directionY;
        return false;
    }
    return true;
}


#ifdef MINIGAMES_USEDEBUG
void FourInARow::Game::AddHighlightPosition_AtColour(int x, int y, int colour)
{
    // TODO : 
    if (m_highlightPointsCount == -1)
    {
        Alloc2dIntArray(&m_pHighlightInNextPrint, 1, 3, 0);
        m_highlightPointsCount = 1;
    }
    else
    {
        m_highlightPointsCount++;
        Expand2dIntArray_FromTo(&m_pHighlightInNextPrint, m_highlightPointsCount - 1, 3, m_highlightPointsCount, 0);
    }
    m_pHighlightInNextPrint[m_highlightPointsCount - 1][0] = x;
    m_pHighlightInNextPrint[m_highlightPointsCount - 1][1] = y;
    m_pHighlightInNextPrint[m_highlightPointsCount - 1][2] = colour;
}
#endif



void FourInARow::Game::AllocBlankMemberBuffers(void)
{
    m_pBoard = new int[m_width * m_height];
    for (int i = 0; i < (m_width * m_height); i++) m_pBoard[i] = 0;

    m_pGameHistory = new int [m_width * m_height * 2];

    m_pWinningLine = new int [8];
}




int _FourInARow_IntToIntarr(int num, int base, int* numBuf = NULL, int bufsize = 0);

int FourInARow::Game::GetSaveSize(void)
{
    int save_size = 0;
    save_size += _FourInARow_IntToIntarr(m_width, 10);
    save_size += _FourInARow_IntToIntarr(m_height, 10);
    save_size += 2;
    save_size += _FourInARow_IntToIntarr((m_width * m_height), 32) * m_width * m_height;
    return save_size;
}

void FourInARow::Game::Export(char* strSaveData, int bufSize)
{
    snprintf(strSaveData, bufSize, "%d|%d|", m_width, m_height);

    int* main_save;
    main_save = new int[m_width * m_height];
    for (int i = 0; i < (m_width * m_height); i++) main_save[i] = 0;

    for (int i = 0; i < m_turnNumber; i++)
    {
        int x, y;
        x = m_pGameHistory[i * 2];
        y = m_pGameHistory[i * 2 + 1];

        main_save[y * m_width + x] = i + 1;
    }


    int digits_each_cell = _FourInARow_IntToIntarr(m_width * m_height, 64);
    int*  saving_cell_data_int;
    char* saving_cell_data;
    saving_cell_data_int = new int  [digits_each_cell];
    saving_cell_data     = new char [digits_each_cell + 1];

    for (int i = 0; i < (m_width * m_height); i++)
    {
        _FourInARow_IntToIntarr(main_save[i], 64, saving_cell_data_int, digits_each_cell);
        for (int j = 0; j < digits_each_cell; j++)
        {
            saving_cell_data[j] = (char)(saving_cell_data_int[j] + 33);
        }
        saving_cell_data[digits_each_cell] = '\0';
        strcat(strSaveData, saving_cell_data);
    }

    delete [] saving_cell_data;
    delete [] main_save;
}

int _FourInARow_IntToIntarr(int num, int base, int* numBuf, int bufsize)
{
    int digits_count = 1;

    if (numBuf == NULL)
    {
        bufsize = 0;
        numBuf = new int [1];
    }

    numBuf[0] = num;

    while (numBuf[0] >= base)
    {
        if (digits_count >= bufsize &&
            bufsize != 0)
        {
            return 0;
        }

        for (int i = digits_count; i > 1; i--)
        {
            numBuf[i] = numBuf[i - 1];
        }

        numBuf[1] = numBuf[0] % base;
        numBuf[0] = numBuf[0] / base;

        digits_count++;
    }

    return digits_count;
}


int _FourinARow_IntArrToInt(int* IntArr, int ArrLen, int base);

int FourInARow::Game::Import(char* strSaveData)
{
    int save_length = (int)strlen(strSaveData);

    char* pWidth  = NULL;
    char* pHeight = NULL;
    char* pSave   = NULL;

    pWidth = strSaveData;

    int comma_count = 0;
    for (int i = 0; i < save_length; i++)
    {
        if (strSaveData[i] == '|')
        {
            comma_count++;
            switch (comma_count)
            {
                case 1:
                    pHeight = &(strSaveData[i + 1]);
                    strSaveData[i] = '\0';
                    break;
                case 2:
                    pSave = &(strSaveData[i + 1]);
                    strSaveData[i] = '\0';
                    break;
                default:
                    return 0;
            }
        }
    }

    if (comma_count != 2)
    {
        return 0;
    }

    int board_width  = atoi(pWidth);
    int board_height = atoi(pHeight);

    int digits_each_cell = _FourInARow_IntToIntarr(board_width * board_height, 64);

    if ((board_width * board_height * digits_each_cell) != strlen(pSave))
    {
        return 0;
    }

    int* saved_rows_to_put;
    saved_rows_to_put = new int [board_width * board_height];
    int saved_puts_count = 0;

    int* cell_data_arr;
    cell_data_arr = new int [digits_each_cell];
    for (int i = 0; i < (board_width * board_height); i++)
    {
        for (int j = 0; j < digits_each_cell; j++)
        {
            cell_data_arr[j] = pSave[digits_each_cell * i + j] - 33;
        }
        int cell_data;
        cell_data = _FourinARow_IntArrToInt(cell_data_arr, digits_each_cell, 64);
        if (cell_data == 0)
        {
            continue;
        }

        saved_puts_count++;
        saved_rows_to_put[cell_data - 1] = i % board_width;
    }
    delete [] cell_data_arr;

    m_width  = board_width;
    m_height = board_height;

    AllocBlankMemberBuffers();

    m_turnPlayer = 1;
    m_turnNumber = 0;

    m_gameStatus = 0;

    m_lastX = -1;
    m_lastY = -1;

    for (int i = 0; i < saved_puts_count; i++)
    {
#ifdef DEBUG
        printf("%d ", saved_rows_to_put[i]);
#endif
        PutCoin(saved_rows_to_put[i]);
    }
    delete [] saved_rows_to_put;

    return 1;
}

int _FourinARow_IntArrToInt(int* IntArr, int ArrLen, int base)
{
    int num = 0;

    for (int i = 0; i < ArrLen; i++)
    {
        num *= base;
        num += IntArr[i];
    }

    return num;
}



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

#ifdef MINIGAMES_USEDEBUG
    for (int i = 0; i < m_highlightPointsCount; i++)
    {
        print_buffer_backcolor
            [m_pHighlightInNextPrint[i][1]]
            [m_pHighlightInNextPrint[i][0]] = m_pHighlightInNextPrint[i][2];
    }
    Free2dIntArray(&m_pHighlightInNextPrint, m_highlightPointsCount, 3);
    m_highlightPointsCount = -1;
#endif

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

