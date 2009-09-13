typedef struct dt_unsorted_list_element
{
  struct dt_unsorted_list_element *next;
  void *object;
} DT_UNSORTED_LIST_ELEMENT;

typedef struct dt_unsorted_list
{
  struct dt_unsorted_list_element *head;
  struct dt_unsorted_list_element *tail;
  void (* free_object)(void *);
} DT_UNSORTED_LIST;

#define DT_OBJECT_REMOVED 0
#define DT_OBJECT_NOT_FOUND 1
