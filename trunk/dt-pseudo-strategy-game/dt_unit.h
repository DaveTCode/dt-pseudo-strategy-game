/******************************************************************************/
/* File: dt_unit.h                                                            */
/*                                                                            */
/* Purpose: This file is the header file for the unit object. It contains the */
/*          object definition and DAT - complete                              */
/******************************************************************************/

/******************************************************************************/
/* This is the maximum length of the string which contains a units name. If a */
/* name exceeds this length it is truncated.                                  */
/******************************************************************************/
#define DT_UNIT_MAX_NAME_LEN 255

/******************************************************************************/
/* These are the return codes for the unit comparator function. They are then */
/* used to place units in a linked list.                                      */
/******************************************************************************/
#define DT_UNIT_LESSER -1
#define DT_UNIT_GREATER 1
#define DT_UNITS_SAME 0

/******************************************************************************/
/* Group: DT_UNIT_CLASSES                                                     */
/*                                                                            */
/* All units belong to a particular class. This class determines various      */
/* things such as how fast they travel on particular terrain types.           */
/* For the algorithms used the unit class MUST be of the form 0xa1bc.         */
/******************************************************************************/
#define DT_UNIT_CLASS_NORMAL = 0x0100

/******************************************************************************/
/* Group: DT_VIEW_ORIENTATIONS                                                */
/*                                                                            */
/* The possible values for the orientation of a unit. These are absolute      */
/* values.                                                                    */
/* NORTH_1 is a value which is used to calculate the distance around the      */
/* orientations.                                                              */
/******************************************************************************/
typedef enum dt_orientation
{
  NORTH,
  NORTHEAST,
  EAST,
  SOUTHEAST,
  SOUTH,
  SOUTHWEST,
  WEST,
  NORTHWEST,
  NORTH_1
} DT_ORIENTATION;

/******************************************************************************/
/* DT_UNIT_GRAPHIC:                                                           */
/*                                                                            */
/* entity_graphic - A pointer to a graphic object. This can be shared among   */
/*                  multiple units and should only be destroyed when its ref  */
/*                  count hits 0.                                             */
/* alpha - The inherent alpha blending value of the unit graphic. It ranges   */
/*         0 (transparent) to 255 (opaque).                                   */
/******************************************************************************/
typedef struct dt_unit_graphic
{
  struct dt_entity_graphic *entity_graphic;
  int alpha;
} DT_UNIT_GRAPHIC;

/******************************************************************************/
/* DT_UNIT:                                                                   */
/*                                                                            */
/* unit_id - This is a unique id given per unit. It is used to identify the   */
/*           unit in data structures.                                         */
/* master_list_element - A pointer back to the element in the master unit     */
/*                       list which refers to this unit.                      */
/* graphics - A pointer to some graphic object e.g. a sprite.                 */
/* name - A fixed length string that will contain the unit name.              */
/* unit_class - The class of unit. One of DT_UNIT_CLASSES.                    */
/* curr_pos_x - The current x coordinate in world coordinates.                */
/* curr_pos_y - The current y coordinate in world coordinates.                */
/* new_pos_x - Once the unit has been moved this is set to the new position   */
/*             it is then used to update the curr_pos_x after the turn is     */
/*             complete.                                                      */
/* new_pos_y - Once the unit has been moved this is set to the new position   */
/*             it is then used to update the curr_pos_y after the turn is     */
/*             complete.                                                      */
/* changed_position - A boolean that is set to true if the unit has moved.    */
/* movement_distance - The total distance that the unit can move in a given   */
/*                     turn.                                                  */
/* speed - The speed that a unit moves over tiles. The higher this is the     */
/*         less effect a tile with high movement modifier has.                */
/* orientation - An integer from the group DT_VIEW_ORIENTATIONS.              */
/* field_of_view - An integer from the group DT_FOV_VALUES which determines   */
/*                 how far from the orientation the unit can see.             */
/* sight_distance - The distance away from the unit (along the orientation)   */
/*                  that the unit can see.                                    */
/******************************************************************************/
typedef struct dt_unit
{
  long unit_id;
  struct dt_unit_list_element *master_list_element;
  struct dt_unit_graphic *graphic;
  char name[DT_UNIT_MAX_NAME_LEN];
  int unit_class;
  int curr_pos_x;
  int curr_pos_y;
  int new_pos_x;
  int new_pos_y;
  bool changed_position;
  int max_movement_distance;
  int speed;
  int orientation;
  int field_of_view;
  int sight_distance;
} DT_UNIT;
