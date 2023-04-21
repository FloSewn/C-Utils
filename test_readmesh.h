#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "src/bstrlib_wrapper.h"
#include "src/testunit.h"
#include "src/readmesh.h"


/***********************************************************************
* 
***********************************************************************/
static inline void test_meshreader(String gridfile)
{
  MeshReader *mesh_reader = readmesh_meshreader_create(gridfile);

  readmesh_meshreader_destroy(mesh_reader);

} // test_meshreader()


/***********************************************************************
* The main function
***********************************************************************/
static inline int test_readmesh(int argc, char* argv[])
{
  if (argc < 2)
  {
    printf("\n  > %s Gridfile\n\n", argv[0]);
    return EXIT_FAILURE;
  }

  String gridfile = bstrlib_string_copy_cstring(argv[1]);

  test_meshreader(gridfile);


  bstrlib_string_destroy(gridfile);

  printf("\n  [readmesh] works like a charm!\n\n");

  return EXIT_SUCCESS;
}
