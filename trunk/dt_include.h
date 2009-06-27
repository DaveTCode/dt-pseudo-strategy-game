/******************************************************************************/
/* File: dt_include.h                                                         */
/*                                                                            */
/* Purpose: A header file that contains all the includes that are needed in   */
/*          the project source files. That way only this file need be         */
/*          updated when a new header is added.                               */
/******************************************************************************/

/******************************************************************************/
/* System headers.                                                            */
/******************************************************************************/
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include <sdl/SDL.h>
#include <sdl/SDL_image.h>
//#include <sdl/sdl_opengl.h>

/******************************************************************************/
/* User headers.                                                              */
/******************************************************************************/
#include "dt_globals.h"
#include "dt_unit.h"
#include "dt_errors.h"
#include "dt_unit_list.h"
#include "dt_window_handler.h"
#include "dt_grid.h"
#include "dt_entity_graphic.h"
#include "dt_background_tile.h"
#include "dt_prototypes.h"
#include "dt_pathing.h"
#include "dt_macros.h"
