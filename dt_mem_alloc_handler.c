/******************************************************************************/
/* File: dt_mem_alloc_handler.c                                               */
/*                                                                            */
/* Purpose: Provides a mechanism to call into malloc and test that the result */
/*          is not null without repeating condition code throughout.          */
/******************************************************************************/
#include "dt_include.h"

/******************************************************************************/
/* Function: dt_malloc                                                        */
/*                                                                            */
/* Purpose: Allocate memory and exit gracefully if not enough memory found.   */
/*                                                                            */
/* Returns: A void pointer to the allocated memory.                           */
/*                                                                            */
/* Parameters: size - The number of bytes to be allocated. e.g. sizeof(int)   */
/*                                                                            */
/* Operation: Attempt to allocate the required memory. If this fails then set */
/*            the error message to be the out of memory error and exit the    */
/*            software.                                                       */
/******************************************************************************/
void *dt_malloc(size_t size)
{
  /****************************************************************************/
  /* Local Variables.                                                         */
  /****************************************************************************/
  void *temp_object;
  char err_log_message[DT_MAX_ERR_LOG_SIZE];

  temp_object =  malloc(size);
  if (temp_object == NULL)
  {
    strncpy(err_log_message, DT_OUT_OF_MEM_ERR, DT_MAX_ERR_LOG_SIZE);
    dt_graceful_exit(err_log_message);
  }

  return(temp_object);
}

void dt_free(void *object)
{
  free(object);

  return;
}
