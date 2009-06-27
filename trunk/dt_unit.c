/******************************************************************************/
/* File: dt_unit.c                                                            */
/*                                                                            */
/* Purpose: This files contains functions to retrieve data on the unit object */
/*          and DAT - complete                                                */
/******************************************************************************/
#include "dt_include.h"

/******************************************************************************/
/* Function: dt_create_unit                                                   */
/*                                                                            */
/* Purpose: Allocate required memory for a new unit object.                   */
/*                                                                            */
/* Returns: A pointer to the new unit object.                                 */
/*                                                                            */
/* Parameters: master_unit_list - The master list containing all units.       */
/*                                                                            */
/* Operation: Allocate memory and set up the unit id. Then add the unit to    */
/*            master unit list so that it can be cleaned up when necessary.   */
/******************************************************************************/
DT_UNIT *dt_create_unit(long *next_unit_id)
{
  /****************************************************************************/
  /* Local Variables.                                                         */
  /****************************************************************************/
  DT_UNIT *temp_unit;

  /****************************************************************************/
  /* If the master unit list has not been set up at this point then create it.*/
  /****************************************************************************/
  if (NULL == master_unit_list)
  {
    master_unit_list = dt_create_unit_list_ns();
  }

  /****************************************************************************/
  /* Allocate the required amount of memory.                                  */
  /****************************************************************************/
  temp_unit = (DT_UNIT *) dt_malloc(sizeof(DT_UNIT));

  /****************************************************************************/
  /* Allocate the new unit the next id.                                       */
  /****************************************************************************/
  temp_unit->unit_id = *next_unit_id;
  (*next_unit_id)++;

  /****************************************************************************/
  /* Add the new unit to the master unit list.                                */
  /****************************************************************************/
  dt_add_to_list_ns(master_unit_list, temp_unit);

  /****************************************************************************/
  /* Create a new unit graphic object.                                        */
  /****************************************************************************/
  temp_unit->graphic = (DT_UNIT_GRAPHIC *) dt_create_unit_graphic();

  return(temp_unit);
}

/******************************************************************************/
/* Function: dt_destroy_unit                                                  */
/*                                                                            */
/* Purpose: Free the memory used for a given unit object.                     */
/*                                                                            */
/* Returns: Nothing                                                           */
/*                                                                            */
/* Parameters: IN     unit - The unit to be freed.                            */
/*                                                                            */
/* Operation: Free the object. Do not free the master list element.           */
/******************************************************************************/
void dt_destroy_unit(DT_UNIT *unit)
{
  /****************************************************************************/
  /* Free the unit graphic oject.                                             */
  /****************************************************************************/
  dt_destroy_unit_graphic(unit->graphic);

  free(unit);

  return;
}

/******************************************************************************/
/* Function: dt_update_unit_position                                          */
/*                                                                            */
/* Purpose: Update the x and y coordinates of a given unit object.            */
/*                                                                            */
/* Returns: Nothing.                                                          */
/*                                                                            */
/* Parameters: IN     unit - The unit to be updated.                          */
/*                                                                            */
/* Operation: Check that it needs to be updated and then perform the update.  */
/******************************************************************************/
void dt_update_unit_position(DT_UNIT *unit)
{
  /****************************************************************************/
  /* If the unit needs updating then change its position.                     */
  /****************************************************************************/
  if (unit->changed_position)
  {
    unit->curr_pos_x = unit->new_pos_x;
    unit->curr_pos_y = unit->new_pos_y;
  }

  return;
}

/******************************************************************************/
/* Function: dt_unit_comparator                                               */
/*                                                                            */
/* Purpose: Compare two units so that they can be ordered in a linked list.   */
/*                                                                            */
/* Returns: DT_UNIT_LESSER if unit_1 has a lower id.                          */
/*          DT_UNITS_SAME if the units have the same id.                      */
/*          DT_UNIT_GREATER if unit_1 has a greater id.                       */
/*                                                                            */
/* Parameters: IN     unit_1                                                  */
/*             IN     unit_2                                                  */
/*                                                                            */
/* Operation: Compare the id's and return the result.                         */
/******************************************************************************/
int dt_unit_comparator(DT_UNIT *unit_1, DT_UNIT *unit_2)
{
  /****************************************************************************/
  /* Local Variables.                                                         */
  /****************************************************************************/
  int result;

  /****************************************************************************/
  /* Compare the two units and return the result.                             */
  /****************************************************************************/
  if (unit_1->unit_id < unit_2->unit_id)
  {
    result = DT_UNIT_LESSER;
  }
  else if (unit_1->unit_id > unit_2->unit_id)
  {
    result = DT_UNIT_GREATER;
  }
  else
  {
    result = DT_UNITS_SAME;
  }

  return(result);
}

/******************************************************************************/
/* Function: dt_create_unit_graphic                                           */
/*                                                                            */
/* Purpose: Set up a unit graphic placeholder for a sprite.                   */
/*                                                                            */
/* Returns: A pointer to the new object.                                      */
/*                                                                            */
/* Parameters: None.                                                          */
/*                                                                            */
/* Operation: Allocate memory and set the initial alpha value to make the     */
/*            unit opaque.                                                    */
/******************************************************************************/
DT_UNIT_GRAPHIC *dt_create_unit_graphic()
{
  /****************************************************************************/
  /* Local Variables.                                                         */
  /****************************************************************************/
  DT_UNIT_GRAPHIC *temp_graphic;

  /****************************************************************************/
  /* Allocate memory for the new graphic object.                              */
  /****************************************************************************/
  temp_graphic = (DT_UNIT_GRAPHIC *) dt_malloc(sizeof(DT_UNIT_GRAPHIC));

  /****************************************************************************/
  /* Set the initial alpha value for the graphic to make the unit completely  */
  /* opaque.                                                                  */
  /****************************************************************************/
  temp_graphic->alpha = SDL_ALPHA_OPAQUE;

  return(temp_graphic);
}

/******************************************************************************/
/* Function: dt_destroy_unit_graphic                                          */
/*                                                                            */
/* Purpose: Release memory allocated for a unit graphic object.               */
/*                                                                            */
/* Returns: Nothing.                                                          */
/*                                                                            */
/* Parameters: IN     unit_graphic - The graphic to be freed.                 */
/*                                                                            */
/* Operation: Check the underlying entity graphic. If it has reference count  */
/*            1 then this is the last object which points to that graphic so  */
/*            we free it.                                                     */
/*            Otherwise, decrease the reference count to indicate that this   */
/*            unit no longer points to the graphic.                           */
/*            Finally free the unit graphic itself.                           */
/******************************************************************************/
void dt_destroy_unit_graphic(DT_UNIT_GRAPHIC *unit_graphic)
{
  /****************************************************************************/
  /* If this is the last object which refers to the entity graphic then free  */
  /* the memory associated with the graphic. If not then decrease the         */
  /* reference count on the entity graphic.                                   */
  /****************************************************************************/
  if (NULL != unit_graphic->entity_graphic)
  {
    if (1 == unit_graphic->entity_graphic->ref_count)
    {
      dt_destroy_entity_graphic(unit_graphic->entity_graphic);
    }
    else
    {
      unit_graphic->entity_graphic->ref_count--;
    }
  }

  free(unit_graphic);

  return;
}

/******************************************************************************/
/* Function: dt_assign_entity_graphic_to_unit                                 */
/*                                                                            */
/* Purpose: Safely assign a sprite to a unit.                                 */
/*                                                                            */
/* Returns: Nothing.                                                          */
/*                                                                            */
/* Parameters: IN     unit - The unit for which the sprite is to be assigned. */
/*             IN     entity_graphic - The graphical placeholder that is to   */
/*                                     assigned to the unit.                  */
/*                                                                            */
/* Operation: Assign the placeholder to the unit and then increment its ref   */
/*            counter.                                                        */
/******************************************************************************/
void dt_assign_entity_graphic_to_unit(DT_UNIT *unit,
                                      DT_ENTITY_GRAPHIC *entity_graphic)
{
  /****************************************************************************/
  /* Assign the entity graphic placeholder to the unit.                       */
  /****************************************************************************/
  unit->graphic->entity_graphic = entity_graphic;

  /****************************************************************************/
  /* Increment the reference counter on the entity graphic object.            */
  /****************************************************************************/
  (entity_graphic->ref_count)++;

  return;
}
