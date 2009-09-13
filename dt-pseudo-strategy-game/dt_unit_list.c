#include "dt_include.h"

/******************************************************************************/
/* Function: dt_create_unit_list_ns                                           */
/*                                                                            */
/* Purpose: Create an unsorted list of units.                                 */
/*                                                                            */
/* Returns: A pointer to the new list.                                        */
/*                                                                            */
/* Parameters: None.                                                          */
/*                                                                            */
/* Operation: Allocate memory and fail if there is an error.                  */
/******************************************************************************/
DT_UNIT_LIST_NS *dt_create_unit_list_ns()
{
  /****************************************************************************/
  /* Local Variables.                                                         */
  /****************************************************************************/
  DT_UNIT_LIST_NS *temp_list;

  /****************************************************************************/
  /* Allocate the memory necessary using the dt_malloc function.              */
  /****************************************************************************/
  temp_list = (DT_UNIT_LIST_NS *) dt_malloc(sizeof(DT_UNIT_LIST_NS));

  /****************************************************************************/
  /* Set the first and last pointers to null so that they can be tested.      */
  /****************************************************************************/
  temp_list->first = NULL;
  temp_list->last = NULL;

  return(temp_list);
}

/******************************************************************************/
/* Function: dt_destroy_unit_list                                             */
/*                                                                            */
/* Purpose: Free the memory used in a unit list object.                       */
/*                                                                            */
/* Returns: Nothing.                                                          */
/*                                                                            */
/* Parameters: IN     unit_list - The list to be destroyed.                   */
/*             IN     free_units - A boolean set to true if the underlying    */
/*                                 units are to be freed.                     */
/*                                                                            */
/* Operation: Free the memory for all of the unit list elements and then the  */
/*            list itself. Free the units iff the free_units boolean is       */
/*            passed to this function as true.                                */
/******************************************************************************/
void dt_destroy_unit_list(DT_UNIT_LIST_NS *unit_list, bool free_units)
{
  /****************************************************************************/
  /* Local Variables.                                                         */
  /****************************************************************************/
  DT_UNIT_LIST_ELEMENT *curr_element;
  DT_UNIT_LIST_ELEMENT *next_element;

  /****************************************************************************/
  /* Set the loop variable to the first element in the list.                  */
  /****************************************************************************/
  curr_element = unit_list->first;

  /****************************************************************************/
  /* Loop through the unit list freeing elements.                             */
  /****************************************************************************/
  while (NULL != curr_element)
  {
    next_element = curr_element->next;

    /**************************************************************************/
    /* If we are freeing units and there is a unit attached to this element   */
    /* then destroy it.                                                       */
    /**************************************************************************/
    if (free_units && NULL != curr_element->unit)
    {
      dt_destroy_unit(curr_element->unit);
    }

    dt_destroy_list_element(curr_element);
    curr_element = next_element;
  }

  /****************************************************************************/
  /* Once the list has been cleared of elements free the list object itself.  */
  /****************************************************************************/
  free(unit_list);

  return;
}

/******************************************************************************/
/* Function: dt_create_list_element                                           */
/*                                                                            */
/* Purpose: Allocate memory for a new list element.                           */
/*                                                                            */
/* Returns: A pointer to the new memory.                                      */
/*                                                                            */
/* Parameters: None.                                                          */
/*                                                                            */
/* Operation: Allocate the memory and set the next element in the list to     */
/*            point to NULL so that this can be tested when needed.           */
/******************************************************************************/
DT_UNIT_LIST_ELEMENT *dt_create_list_element()
{
  /****************************************************************************/
  /* Local Variables.                                                         */
  /****************************************************************************/
  DT_UNIT_LIST_ELEMENT *temp_element;

  /****************************************************************************/
  /* Allocate the required memory using the dt_malloc function.               */
  /****************************************************************************/
  temp_element = (DT_UNIT_LIST_ELEMENT *)
                                        dt_malloc(sizeof(DT_UNIT_LIST_ELEMENT));
  temp_element->next = NULL;

  return(temp_element);
}

/******************************************************************************/
/* Function: dt_destroy_list_element                                          */
/*                                                                            */
/* Purpose: Free the memory from a list element.                              */
/*                                                                            */
/* Returns: Nothing.                                                          */
/*                                                                            */
/* Parameters: IN     element - The list element to be freed.                 */
/*                                                                            */
/* Operation: Free the element but NOT the underlying unit.                   */
/******************************************************************************/
void dt_destroy_list_element(DT_UNIT_LIST_ELEMENT *element)
{
  dt_free(element);
}

/******************************************************************************/
/* Function: dt_add_to_list_ns                                                */
/*                                                                            */
/* Purpose: Add a unit to an unsorted unit list.                              */
/*                                                                            */
/* Returns: Nothing.                                                          */
/*                                                                            */
/* Parameters: IN     list - The list which is to be added to.                */
/*             IN     unit - The unit object to be added to the list.         */
/*                                                                            */
/* Operation: Adding to an unsorted list is as simple as putting the new      */
/*            element either at the end of the list (if the list is nonempty) */
/*            or setting the first element of the list to the unit if it is   */
/*            empty.                                                          */
/******************************************************************************/
void dt_add_to_list_ns(DT_UNIT_LIST_NS *list, DT_UNIT *unit)
{
  /****************************************************************************/
  /* Local Variables.                                                         */
  /****************************************************************************/
  DT_UNIT_LIST_ELEMENT *new_list_element;

  new_list_element = dt_create_list_element();
  new_list_element->unit = unit;

  /****************************************************************************/
  /* If the first element in the list is NULL then the list is empty so add   */
  /* the element to the top otherwise add it to the bottom.                   */
  /****************************************************************************/
  if (NULL != list->first)
  {
    list->last->next = new_list_element;
    list->last = new_list_element;
  }
  else
  {
    list->first = new_list_element;
  }

  return;
}

/******************************************************************************/
/* Function: dt_remove_from_list_ns                                           */
/*                                                                            */
/* Purpose: Remove a unit from an unsorted list.                              */
/*                                                                            */
/* Returns: DT_UNIT_REMOVED - If the unit was found and removed.              */
/*          DT_UNIT_NOT_FOUND - If the unit was not found in the list.        */
/*                                                                            */
/* Parameters: IN     list - The list from which the unit is to be removed.   */
/*             IN     unit_id - The unique id for the unit to be removed.     */
/*                                                                            */
/* Operation: Scan through the list from the first element. If the unit is    */
/*            found then remove it as detailed in comments below.             */
/******************************************************************************/
int dt_remove_from_list_ns(DT_UNIT_LIST_NS *list, long unit_id)
{
  /****************************************************************************/
  /* Local Variables                                                          */
  /****************************************************************************/
  DT_UNIT_LIST_ELEMENT *curr_element;
  DT_UNIT_LIST_ELEMENT *prev_element;
  int result = DT_UNIT_NOT_FOUND;

  curr_element = list->first;
  prev_element = NULL;

  /****************************************************************************/
  /* Scan through the list until the end is reached.                          */
  /****************************************************************************/
  while(NULL != curr_element)
  {
    /**************************************************************************/
    /* If the current element in the list has the same id as the unit we wish */
    /* to remove then if it is the first element in the list set the new      */
    /* first element to be the next. Otherwise point the previous element to  */
    /* the next one. Once this has been achieved destroy the list element     */
    /* which has been removed.                                                */
    /**************************************************************************/
    if (curr_element->unit->unit_id == unit_id)
    {
      if (NULL != prev_element)
      {
        prev_element->next = curr_element->next;
      }
      else
      {
        list->first = curr_element->next;
      }
      dt_destroy_list_element(curr_element);
      result = DT_UNIT_REMOVED;
      goto EXIT_LABEL;
    }

    prev_element = curr_element;
    curr_element = curr_element->next;
  }

EXIT_LABEL:

  return(result);
}

//find_in_list
