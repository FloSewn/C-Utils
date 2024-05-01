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
* 
***********************************************************************/
static inline void test_meshgrid(String gridfile)
{
  MeshReader *mesh_reader = readmesh_meshreader_create(gridfile);

  MeshGrid *mesh = readmesh_meshgrid_create(mesh_reader);

  for (int i = 0; i < mesh->number_of_vertices; ++i)
  {
    printf("%d: (%lf, %lf)\n", i, 
        mesh->vertex_coordinates[i][0],
        mesh->vertex_coordinates[i][1]
    );
  }

  printf("\n\n");

  for (int i = 0; i < mesh->number_of_quads; ++i)
  {
    printf("%d: (%d, %d, %d, %d)\n", i, 
        mesh->quads[i][0],
        mesh->quads[i][1],
        mesh->quads[i][2],
        mesh->quads[i][3]
    );
  }

  readmesh_meshgrid_destroy(mesh);

  readmesh_meshreader_destroy(mesh_reader);

} // test_meshgrid()


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
  test_meshgrid(gridfile);


  bstrlib_string_destroy(gridfile);

  printf("\n  [readmesh] works like a charm!\n\n");

  return EXIT_SUCCESS;
}
