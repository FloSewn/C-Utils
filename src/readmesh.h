#ifndef READMESH_H
#define READMESH_H

#include "testunit.h"
#include "bstrlib_wrapper.h"

/***********************************************************************
* Mesh file reader structure
***********************************************************************/
struct MeshReader;
typedef struct MeshReader {
  String           file_path;      /* Path of file                 */
  StringList       file_content;   /* file, splitted for newlines  */
  int              n_lines;        /* Number of lines in total file*/

} MeshReader;


/***********************************************************************
* Library interface
***********************************************************************/
static inline MeshReader* readmesh_meshreader_create(String meshfile_path);
static inline int readmesh_meshreader_destroy(MeshReader* mesh_reader);


/***********************************************************************
* Create a new mesh reader entity
***********************************************************************/
static inline 
MeshReader* readmesh_meshreader_create(String meshfile_path)
{
  StringList meshfile_content 
    = bstrlib_stringlist_read_textfile(meshfile_path, '\n');

  // Allocate memory
  MeshReader* mesh_reader = (MeshReader*) safe_calloc(1, sizeof(MeshReader));
  mesh_reader->file_path    = meshfile_path;
  mesh_reader->file_content = meshfile_content;
  mesh_reader->n_lines      = meshfile_content->qty;

  return mesh_reader;

} // readmesh_meshreader_create()

/***********************************************************************
* Destroy a given mesh reader entity
***********************************************************************/
static inline 
int readmesh_meshreader_destroy(MeshReader* mesh_reader)
{
  bstrlib_stringlist_destroy(mesh_reader->file_content);
  safe_free(mesh_reader);

  return 0;

} // readmesh_meshreader_destroy()


#endif /* READMESH_H */
