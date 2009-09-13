#include "dt_include.h"

/******************************************************************************/
/* Function: dt_create_unsorted_list_element                                  */
/*                                                                            */
/* Purpose: Allocate memory for a new list element.                           */
/*                                                                            */
/* Returns: A pointer to the new memory                                       */
/*                                                                            */
/* Parameters: None.                                                          */
/*                                                                            */
/* Operation: Allocate memory and set the pointers in the structure to NULL.  */
/******************************************************************************/
DT_UNSORTED_LIST_ELEMENT *dt_create_unsorted_list_element()
{
  /****************************************************************************/
  /* Local Variables.                                                         */
  /****************************************************************************/
  DT_UNSORTED_LIST_ELEMENT *temp_element;

  /****************************************************************************/
  /* Allocate memory.                                                         */
  /****************************************************************************/
  temp_element = (DT_UNSORTED_LIST_ELEMENT *)
                                    dt_malloc(sizeof(DT_UNSORTED_LIST_ELEMENT));

  /****************************************************************************/
  /* Set the pointer to the object and the next element to null for testing   */
  /* against.                                                                 */
  /****************************************************************************/
  temp_element->object = NULL;
  temp_element->next = NULL;

  return(temp_element);
}

/******************************************************************************/
/* Function: dt_destroy_unsorted_list_element                                 */
/*                                                                            */
/* Purpose: Free memory used for a list element.                              */
/*                                                                            */
/* Returns: Nothing.                                                          */
/*                                                                            */
/* Parameters: IN     element - The element to be freed.                      */
/*                                                                            */
/* Operation: Free the element but not the object or the next pointer.        */
/******************************************************************************/
void dt_destroy_unsorted_list_element(DT_UNSORTED_LIST_ELEMENT *element)
{
  dt_free(element);

  return;
}

/******************************************************************************/
/* Function: dt_create_unsorted_list                                          */
/*                                                                            */
/* Purpose: Allocate memory for a new unsorted list.                          */
/*                                                                            */
/* Returns: A pointer to the new memory.                                      */
/*                                                                            */
/* Parameters: None.                                                          */
/*                                                                            */
/* Operation: Allocate memory and set the head and tail of the list to null.  */
/******************************************************************************/
DT_UNSORTED_LIST *dt_create_unsorted_list(void (*destroy_func))
{
  /****************************************************************************/
  /* Local Variables.                                                         */
  /****************************************************************************/
  DT_UNSORTED_LIST *temp_list;

  /****************************************************************************/
  /* Allocate memory for the new list.                                        */
  /****************************************************************************/
  temp_list = (DT_UNSORTED_LIST *) dt_malloc(sizeof(DT_UNSORTED_LIST));

  /****************************************************************************/
  /* Set the head and tail to null for testing against.                       */
  /****************************************************************************/
  temp_list->head = NULL;
  temp_list->tail = NULL;

  /****************************************************************************/
  /* Set the destroy function for the underlying objects.                     */
  /****************************************************************************/
  temp_list->free_object = destroy_func;

  return(temp_list);
}

/******************************************************************************/
/* Function: dt_destroy_unsorted_list                                         */
/*                                                                            */
/* Purpose: Free memory allocated for a list.                                 */
/*                                                                            */
/* Returns: Nothing.                                                          */
/*                                                                            */
/* Parameters: IN     list - The list to be freed.                            */
/*             IN     destroying_objects - Set to true if underlying objects  */
/*                                         are to be destroyed.               */
/*                                                                            */
/* Operation:                                                                 */
/******************************************************************************/
void dt_destroy_unsorted_list(DT_UNSORTED_LIST *list, bool destroying_objects)
{
  /****************************************************************************/
  /* Local Variables.                                                         */
  /****************************************************************************/
  DT_UNSORTED_LIST_ELEMENT *curr_element;
  DT_UNSORTED_LIST_ELEMENT *next_element;

  /****************************************************************************/
  /* Begin pointing at the head of the list.                                  */
  /****************************************************************************/
  curr_element = list->head;

  /****************************************************************************/
  /* Iterate through the list until we run out of elements.                   */
  /****************************************************************************/
  while(NULL != curr_element)
  {
    next_element = curr_element->next;

    /**************************************************************************/
    /* Free the underlying object if requested and its not null.              */
    /**************************************************************************/
    if (destroying_objects && NULL != curr_element->object)
    {
      list->free_object(curr_element->object);
    }

    dt_destroy_unsorted_list_element(curr_element);

    curr_element = next_element;
  }

  dt_free(list);

  return;
}

/******************************************************************************/
/* Function: dt_add_object_to_unsorted_list                                   */
/*                                                                            */
/* Purpose: Add an object to a given list.                                    */
/*                                                                            */
/* Returns: Nothing.                                                          */
/*                                                                            */
/* Parameters: IN     list                                                    */
/*             IN     object                                                  */
/*                                                                            */
/* Operation: If the list is empty add to the top otherwise add to the bottom */
/*            and adjust tail/head pointers accordingly.                      */
/******************************************************************************/
void dt_add_object_to_unsorted_list(DT_UNSORTED_LIST *list, void *object)
{
  /****************************************************************************/
  /* Local Variables.                                                         */
  /****************************************************************************/
  DT_UNSORTED_LIST_ELEMENT *new_element;

  /****************************************************************************/
  /* Create a new list element to hold the object.                            */
  /****************************************************************************/
  new_element = dt_create_unsorted_list_element();
  new_element->object = object;

  /****************************************************************************/
  /* If the top of the list is NULL then the list is empty so set both the    */
  /* tail and the head to point to the new object. Otherwise put on the tail  */
  /* of the list.                                                             */
  /****************************************************************************/
  if (NULL == list->head)
  {
    list->head = new_element;
    list->tail = new_element;
  }
  else
  {
    list->tail->next = new_element;
    list->tail = new_element;
  }

  return;
}

/******************************************************************************/
/* Function: dt_remove_object_from_unsorted_list                              */
/*                                                                            */
/* Purpose: Remove an object from a list without freeing its memory.          */
/*                                                                            */
/* Returns: DT_OBJECT_REMOVED if the object was found and removed.            */
/*          DT_OBJECT_NOT_FOUND if the object wasn't found.                   */
/*                                                                            */
/* Parameters: IN     list                                                    */
/*             IN     object                                                  */
/*                                                                            */
/* Operation: Scan through the list until the end is reached of the object is */
/*            found. If the object is found then remove it.                   */
/******************************************************************************/
int dt_remove_object_from_unsorted_list(DT_UNSORTED_LIST *list, void *object)
{
  /****************************************************************************/
  /* Local Variables.                                                         */
  /****************************************************************************/
  DT_UNSORTED_LIST_ELEMENT *curr_element;
  DT_UNSORTED_LIST_ELEMENT *prev_element = NULL;
  DT_UNSORTED_LIST_ELEMENT *next_element;
  int ret_code = DT_OBJECT_NOT_FOUND;

  /****************************************************************************/
  /* Point the current unit at the top of the list.                           */
  /****************************************************************************/
  curr_element = list->head;

  /****************************************************************************/
  /* Scan through the list until there are no more elements left.             */
  /****************************************************************************/
  while(NULL != curr_element)
  {
    next_element = curr_element->next;

    /**************************************************************************/
    /* If the object is found then remove from the list as follows:           */
    /* 1) If the object was at the top of the list then free the element and  */
    /*    set the list head to the next element.                              */
    /* 2) If the object was not at the top then set the previous element to   */
    /*    the one after the current unit and then free it.                    */
    /**************************************************************************/
    if (curr_element->object == object)
    {
      if (NULL == prev_element)
      {
        list->head = curr_element->next;
      }
      else
      {
        prev_element->next = curr_element->next;
      }
      dt_destroy_unsorted_list_element(curr_element);

      ret_code = DT_OBJECT_REMOVED;

      goto EXIT_LABEL;
    }

    curr_element = next_element;
  }

EXIT_LABEL:

  return(ret_code);
}
