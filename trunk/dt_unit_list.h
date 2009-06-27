/******************************************************************************/
/* These are the different return values that can be taken by functions that  */
/* either search for or remove elements from a list.                          */
/******************************************************************************/
#define DT_UNIT_REMOVED 0
#define DT_UNIT_NOT_FOUND 1
#define DT_UNIT_FOUND 2

/******************************************************************************/
/* The unit list element is not specific to either sorted or unsorted lists.  */
/*                                                                            */
/* unit - A unit structure that remains intact after this object is destroyed.*/
/* next - The next element in the unit list.                                  */
/******************************************************************************/
typedef struct dt_unit_list_element
{
	struct dt_unit *unit;
	struct dt_unit_list_element *next;
} DT_UNIT_LIST_ELEMENT;

/******************************************************************************/
/* An unsorted unit list. Specifically this is a very basic linked list where */
/* elements are added to the end. It is used to keep a complete master list   */
/* of all the units in the game at any time so that they can be freed easily  */
/* on exit.                                                                   */
/*                                                                            */
/* first - The first element in the list. This will be NULL if the list is    */
/* empty.                                                                     */
/* last - The last element in the list. Undefined if the list is empty.       */
/******************************************************************************/
typedef struct dt_unit_list_ns
{
  struct dt_unit_list_element *first;
  struct dt_unit_list_element *last;
} DT_UNIT_LIST_NS;
