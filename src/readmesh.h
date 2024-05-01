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
* Meshgrid structure
***********************************************************************/
struct MeshGrid;
typedef struct MeshGrid {

  int number_of_vertices;
  int number_of_triangles;
  int number_of_quads;
  int number_of_interior_edges;
  int number_of_boundary_edges;

  double (*vertex_coordinates)[2];

  int (*quads)[4];
  int (*triangles)[3];

  int (*quad_neighbors)[4];
  int (*triangle_neighbors)[3];

  int (*interior_edges)[2];
  int (*boundary_edges)[2];

  int (*interior_edge_neighbors)[2];
  int  *boundary_edge_neighbors;

  int *boundary_edge_markers;

} MeshGrid;


/***********************************************************************
* Library interface
***********************************************************************/
static inline MeshReader* readmesh_meshreader_create(String meshfile_path);
static inline void readmesh_meshreader_destroy(MeshReader* mesh_reader);

static inline MeshGrid* readmesh_meshgrid_create(MeshReader* mesh_reader);
static inline void readmesh_meshgrid_destroy(MeshGrid *mesh);



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
void readmesh_meshreader_destroy(MeshReader* mesh_reader)
{
  bstrlib_stringlist_destroy(mesh_reader->file_content);
  safe_free(mesh_reader);
  return;

} // readmesh_meshreader_destroy()


/***********************************************************************
* 
***********************************************************************/
static inline
int readmesh_meshreader_get_number_of_entity(MeshReader *mesh_reader,
                                             const char *entity)
{
  String tmp_str = 
    bstrlib_stringlist_extract_with_cstring(mesh_reader->file_content, 
                                            entity);
  int n_entity = (int) atoi((const char*) tmp_str->data);

  bstrlib_string_destroy(tmp_str);

  return n_entity;

} // readmesh_meshreader_get_number_of_entity()



/***********************************************************************
* 
***********************************************************************/
static inline
int readmesh_meshreader_get_entity_startline(MeshReader *mesh_reader,
                                             const char *entity)
{
  // Get line index where we start to gather nodes
  String *file_ptr = mesh_reader->file_content->entry;
  String  identifier = bstrlib_string_copy_cstring(entity);

  int line;
  for (line = 0; line < mesh_reader->n_lines; line++)
    if ( bstrlib_string_contains(file_ptr[line], 0, identifier) != BSTR_ERR )
      break;

  bstrlib_string_destroy(identifier);
  return line;

} // readmesh_meshreader_get_entity_startline()


/***********************************************************************
* 
***********************************************************************/
static inline
void readmesh_meshreader_copy_entity_data_d(MeshReader *mesh_reader,
                                            void *entity_array,
                                            const char *identifier,
                                            int number_of_entities,
                                            int number_of_values)
{
  int line 
    = readmesh_meshreader_get_entity_startline(mesh_reader, identifier);

  int i_entity = 0;
  int max_line = line + number_of_entities + 1;
  String *file_ptr = mesh_reader->file_content->entry;

  double* entity_data = (double*) entity_array;

  for (int i = line + 1; i < max_line; ++i)
  {
    StringList line_values = bstrlib_string_split(file_ptr[i], ',');
    String *value_ptr = line_values->entry;

    for (int j = 0; j < number_of_values; ++j)
      entity_data[i_entity*number_of_values + j]
        = atof((const char*) value_ptr[j]->data);

    ++i_entity;

    bstrlib_stringlist_destroy(line_values);
  }

  return;

} // readmesh_meshreader_copy_entity_data_d()


/***********************************************************************
* 
***********************************************************************/
static inline
void readmesh_meshreader_copy_entity_data_i(MeshReader *mesh_reader,
                                            void *entity_array,
                                            const char *identifier,
                                            int number_of_entities,
                                            int number_of_values)
{
  int line 
    = readmesh_meshreader_get_entity_startline(mesh_reader, identifier);

  int i_entity = 0;
  int max_line = line + number_of_entities + 1;
  String *file_ptr = mesh_reader->file_content->entry;

  int* entity_data = (int*) entity_array;

  for (int i = line + 1; i < max_line; ++i)
  {
    StringList line_values = bstrlib_string_split(file_ptr[i], ',');
    String *value_ptr = line_values->entry;

    for (int j = 0; j < number_of_values; ++j)
      entity_data[i_entity*number_of_values + j]
        = atoi((const char*) value_ptr[j]->data);

    ++i_entity;

    bstrlib_stringlist_destroy(line_values);
  }

  return;

} // readmesh_meshreader_copy_entity_data_i()



/***********************************************************************
* Read the mesh vertex coordinates 
***********************************************************************/
static inline 
void readmesh_meshreader_read_vertices(MeshReader *mesh_reader,
                                       MeshGrid *mesh)
{
  // Get total number of nodes 
  int n_vertices = readmesh_meshreader_get_number_of_entity(mesh_reader,
                                                            "VERTICES");
  ASSERT(n_vertices > 0, "No nodes defined in mesh file.");

  // Copy vertex coordinates 
  mesh->number_of_vertices = n_vertices;
  mesh->vertex_coordinates = safe_calloc(n_vertices, 2*sizeof(double));

  readmesh_meshreader_copy_entity_data_d(mesh_reader,
                                         mesh->vertex_coordinates,
                                         "VERTICES", n_vertices, 2);

  return;

} // readmesh_meshreader_read_vertices()


/***********************************************************************
* Read the mesh quads 
***********************************************************************/
static inline 
void readmesh_meshreader_read_quads(MeshReader *mesh_reader,
                                    MeshGrid *mesh)
{
  // Get total number of quads 
  int n_quads 
    = readmesh_meshreader_get_number_of_entity(mesh_reader, "QUADS");

  if (n_quads < 1)
  {
    mesh->number_of_quads = 0;
    return;
  }

  // Copy quad indices 
  mesh->number_of_quads = n_quads;
  mesh->quads = safe_calloc(n_quads, 4*sizeof(int));

  readmesh_meshreader_copy_entity_data_i(mesh_reader, mesh->quads,
                                         "QUADS", n_quads, 4);
  return;

} // readmesh_meshreader_read_quads()


/***********************************************************************
* Read the mesh triangles 
***********************************************************************/
static inline 
void readmesh_meshreader_read_triangles(MeshReader *mesh_reader,
                                        MeshGrid *mesh)
{
  // Get total number of quads 
  int n_triangles 
    = readmesh_meshreader_get_number_of_entity(mesh_reader, "TRIANGLES");

  if (n_triangles < 1)
  {
    mesh->number_of_triangles = 0;
    return;
  }

  // Copy quad indices 
  mesh->number_of_triangles = n_triangles;
  mesh->triangles = safe_calloc(n_triangles, 3*sizeof(int));

  readmesh_meshreader_copy_entity_data_i(mesh_reader, mesh->triangles,
                                         "TRIANGLES", n_triangles, 3);
  return;

} // readmesh_meshreader_read_triangles()



/***********************************************************************
* Read the mesh quad neighbor connectivity
***********************************************************************/
static inline 
void readmesh_meshreader_read_quad_neighbors(MeshReader *mesh_reader,
                                             MeshGrid *mesh)
{
  // Get total number of quads 
  int n_quads = mesh->number_of_quads; 

  if (n_quads < 1)
    return;

  // Copy quad indices 
  mesh->quad_neighbors = safe_calloc(n_quads, 4*sizeof(int));

  readmesh_meshreader_copy_entity_data_i(mesh_reader, 
                                         mesh->quad_neighbors,
                                         "QUADNEIGHBORS", n_quads, 4);
  return;

} // readmesh_meshreader_read_quad_neighbors()


/***********************************************************************
* Read the mesh triangle neighbor connectivity
***********************************************************************/
static inline 
void readmesh_meshreader_read_triangle_neighbors(MeshReader *mesh_reader,
                                                 MeshGrid *mesh)
{
  // Get total number of triangles 
  int n_triangles = mesh->number_of_triangles; 

  if (n_triangles < 1)
    return;

  // Copy triangle indices 
  mesh->triangle_neighbors = safe_calloc(n_triangles, 3*sizeof(int));

  readmesh_meshreader_copy_entity_data_i(mesh_reader, 
                                         mesh->triangle_neighbors,
                                         "TRIANGLENEIGHBORS", 
                                         n_triangles, 3);
  return;

} // readmesh_meshreader_read_triangle_neighbors()


/***********************************************************************
* Read the mesh interior edges
***********************************************************************/
static inline 
void readmesh_meshreader_read_interior_edges(MeshReader *mesh_reader,
                                             MeshGrid *mesh)
{
  int i; 
  
  // Get total number of edges 
  int n_edges = readmesh_meshreader_get_number_of_entity(mesh_reader, 
                                                         "INTERIOREDGES");
  if (n_edges < 1)
    return;

  // Copy triangle indices 
  mesh->number_of_interior_edges = n_edges;
  mesh->interior_edges           = safe_calloc(n_edges, 2*sizeof(int));
  mesh->interior_edge_neighbors  = safe_calloc(n_edges, 2*sizeof(int));

  int (*container)[4] = safe_calloc(n_edges, 4*sizeof(int));

  readmesh_meshreader_copy_entity_data_i(mesh_reader, 
                                         container,
                                         "INTERIOREDGES", 
                                         n_edges, 4);

  for (i = 0; i < n_edges; ++i)
  {
    mesh->interior_edges[i][0]          = container[i][0];
    mesh->interior_edges[i][1]          = container[i][1];
    mesh->interior_edge_neighbors[i][0] = container[i][2];
    mesh->interior_edge_neighbors[i][1] = container[i][3];
  }

  safe_free(container);

  return;

} // readmesh_meshreader_read_interior_edges()

/***********************************************************************
* Read the mesh boundary edges
***********************************************************************/
static inline 
void readmesh_meshreader_read_boundary_edges(MeshReader *mesh_reader,
                                             MeshGrid *mesh)
{
  int i;

  // Get total number of edges 
  int n_edges = readmesh_meshreader_get_number_of_entity(mesh_reader, 
                                                         "BOUNDARYEDGES");
  if (n_edges < 1)
    return;

  // Copy triangle indices 
  mesh->number_of_boundary_edges = n_edges;
  mesh->boundary_edges           = safe_calloc(n_edges, 2*sizeof(int));
  mesh->boundary_edge_neighbors  = safe_calloc(n_edges,   sizeof(int));
  mesh->boundary_edge_markers    = safe_calloc(n_edges,   sizeof(int));

  int (*container)[4] = safe_calloc(n_edges, 4*sizeof(int));

  readmesh_meshreader_copy_entity_data_i(mesh_reader, 
                                         container,
                                         "BOUNDARYEDGES", 
                                         n_edges, 4);

  for (i = 0; i < n_edges; ++i)
  {
    mesh->boundary_edges[i][0]       = container[i][0];
    mesh->boundary_edges[i][1]       = container[i][1];
    mesh->boundary_edge_neighbors[i] = container[i][2];
    mesh->boundary_edge_markers[i]   = container[i][3];
  }

  safe_free(container);

  return;

} // readmesh_meshreader_read_boundary_edges()


/***********************************************************************
* Destroy a given meshgrid entity
***********************************************************************/
static inline 
void readmesh_meshgrid_destroy(MeshGrid *mesh)
{
  safe_free(mesh->vertex_coordinates);
  safe_free(mesh->quads);
  safe_free(mesh->triangles);
  safe_free(mesh->quad_neighbors);
  safe_free(mesh->triangle_neighbors);
  safe_free(mesh->interior_edges);
  safe_free(mesh->interior_edge_neighbors);
  safe_free(mesh->boundary_edges);
  safe_free(mesh->boundary_edge_neighbors);
  safe_free(mesh->boundary_edge_markers);
  safe_free(mesh);

  return;

} // readmesh_meshgrid_destroy() 

/***********************************************************************
* Create a new meshgrid entity
***********************************************************************/
static inline 
MeshGrid* readmesh_meshgrid_create(MeshReader* mesh_reader)
{
  MeshGrid *mesh = safe_calloc(1, sizeof(MeshGrid));

  readmesh_meshreader_read_vertices(mesh_reader, mesh);
  readmesh_meshreader_read_quads(mesh_reader, mesh);
  readmesh_meshreader_read_triangles(mesh_reader, mesh);
  readmesh_meshreader_read_quad_neighbors(mesh_reader, mesh);
  readmesh_meshreader_read_triangle_neighbors(mesh_reader, mesh);
  readmesh_meshreader_read_interior_edges(mesh_reader, mesh);
  readmesh_meshreader_read_boundary_edges(mesh_reader, mesh);

  return mesh;

} // readmesh_meshreader_read() 


#endif /* READMESH_H */
