#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "test_bstrlib_wrapper.h"
#include "test_readmesh.h"


/***********************************************************************
* The main function
***********************************************************************/
int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    printf("\n  > %s TestID\n\n", argv[0]);
    printf("  Available tests:\n");
    printf("    bstrlib_wrapper\n");
    printf("    readmesh\n");
    printf("\n\n");
    return EXIT_FAILURE;
  }

  const char* test_id = argv[1];

  if (!strcmp(test_id, "bstrlib_wrapper"))
    test_bstrlib_wrapper(argc-1, &argv[1]);

  if (!strcmp(test_id, "readmesh"))
    test_readmesh(argc-1, &argv[1]);
   
  return EXIT_SUCCESS;
}
  
