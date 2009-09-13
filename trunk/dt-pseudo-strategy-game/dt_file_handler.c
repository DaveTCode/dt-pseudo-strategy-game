#include "dt_include.h"

/******************************************************************************/
/* Function: dt_open_file                                                     */
/*                                                                            */
/* Purpose: Open a file given a filename and a open mode.                     */
/*                                                                            */
/* Returns: DT_FILE_OPEN_ERR if there was an error opening the file.          */
/*          DT_FILE_OPEN_OK if the file was opened successfully.              */
/*                                                                            */
/* Parameters: IN     filename - The filename of the file to be opened.       */
/*             IN     file_mode - One of group FILE_MODE_VALUES.              */
/*             OUT    opened_file - Will be returned as a pointer to the file.*/
/*                                                                            */
/* Operation: Open the file and check this was successful.                    */
/*            If the file was opened then add it to the list of opened files. */
/******************************************************************************/
int dt_open_file(char *filename, char *file_mode, FILE **opened_file)
{
  /****************************************************************************/
  /* Local Variables.                                                         */
  /****************************************************************************/
  int ret_code = DT_FILE_OPEN_OK;

  /****************************************************************************/
  /* Attempt to open the file.                                                */
  /****************************************************************************/
  (*opened_file) = (FILE *) fopen(filename, file_mode);
  if (NULL == (*opened_file))
  {
    ret_code = DT_FILE_OPEN_ERR;
    goto EXIT_LABEL;
  }

EXIT_LABEL:

  return(ret_code);
}

/******************************************************************************/
/* Function: dt_close_file                                                    */
/*                                                                            */
/* Purpose: Close a file opened with dt_open_file.                            */
/*                                                                            */
/* Returns: Nothing.                                                          */
/*                                                                            */
/* Parameters: old_file - The file to be closed.                              */
/*                                                                            */
/* Operation:Close the file.                                                  */
/******************************************************************************/
void dt_close_file(FILE *old_file)
{
  fclose(old_file);

  return;
}
