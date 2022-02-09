
#pragma once


// if one or more of the following macro if defined, it only includes the specified games
//    INCLUDE_4INAROW : for 4 in a row.
//    INCLUDE_REVERSI : for Reversi.
//    INCLUDE_2048    : for 2048.

#if defined(INCLUDE_4INAROW) || defined(INCLUDE_REVERSI) || defined(INCLUDE_2048)
  #ifdef INCLUDE_4INAROW
  #include "games/4InARow.hpp"
  #endif

  #ifdef INCLUDE_REVERSI
  #include "games/Reversi.hpp"
  #endif

  #ifdef INCLUDE_2048
  #include "games/2048.hpp"
  #endif

#else
  #if __has_include("games/4InARow.hpp")
  #include "games/4InARow.hpp"
  #endif

  #if __has_include("games/Reversi.hpp")
  #include "games/Reversi.hpp"
  #endif

  #if __has_include("games/2048.hpp")
  #include "games/2048.hpp"
  #endif
#endif



