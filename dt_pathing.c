#include "dt_include.h"

/******************************************************************************/
/* Function:                                                                  */
/*                                                                            */
/* Purpose:                                                                   */
/*                                                                            */
/* Returns:                                                                   */
/*                                                                            */
/* Parameters:                                                                */
/*                                                                            */
/* Operation:                                                                 */
/******************************************************************************/
int dt_cost_move_unit(DT_UNIT *unit, DT_BACKGROUND_TILE *tile)
{
  /****************************************************************************/
  /* Local Variables.                                                         */
  /****************************************************************************/
  int cost_unit_class_tile_type;
  int final_cost;

  /****************************************************************************/
  /* Determine the cost of a unit of the particular class moving onto a tile  */
  /* of the given type.                                                       */
  /****************************************************************************/
  cost_unit_class_tile_type = dt_cost_unit_class_tile_type(unit->unit_class,
                                                           tile->terrain_type);

  /****************************************************************************/
  /* Calculate the cost of moving the unit onto the given tile (assuming that */
  /* they are adjacent) as follows:                                           */
  /****************************************************************************/
  final_cost = (cost_unit_class_tile_type + tile->movement_modifier)
                                                                  / unit->speed;

  return(final_cost);
}

/******************************************************************************/
/* Function: dt_cost_turn_unit                                                */
/*                                                                            */
/* Purpose: Calculate the cost to turn a unit.                                */
/*                                                                            */
/* Returns: The cost as an integer.                                           */
/*                                                                            */
/* Parameters: IN     unit - Contains the unit which is to be turned.         */
/*             IN     direction - The direction to which the unit is to be    */
/*                                turned.                                     */
/*                                                                            */
/* Operation: Calculate the difference in orientations as an absolute value.  */
/*            Find the minimum distance around the orientations.              */
/******************************************************************************/
int dt_cost_turn_unit(DT_UNIT *unit, DT_ORIENTATION direction)
{
  /****************************************************************************/
  /* Local Variables.                                                         */
  /****************************************************************************/
  int answer;
  int diff_orientation;

  /****************************************************************************/
  /* Calculate the difference in orientation between the unit and where it is */
  /* to be turned.                                                            */
  /****************************************************************************/
  diff_orientation = abs(direction - unit->orientation);

  /****************************************************************************/
  /* The cost to turn a unit is the minimum distance from the current         */
  /* orientation to the new orientation.                                      */
  /****************************************************************************/
  answer = MIN(diff_orientation, NORTH_1 - diff_orientation);

  return(answer);
}

/******************************************************************************/
/* Function:                                                                  */
/*                                                                            */
/* Purpose:                                                                   */
/*                                                                            */
/* Returns:                                                                   */
/*                                                                            */
/* Parameters:                                                                */
/*                                                                            */
/* Operation:                                                                 */
/******************************************************************************/
int dt_cost_unit_class_tile_type(int unit_class,
                                 int terrain_type)
{
  /****************************************************************************/
  /* Local Variables.                                                         */
  /****************************************************************************/
  int answer;

  /****************************************************************************/
  /****************************************************************************/


  return(answer);
}
