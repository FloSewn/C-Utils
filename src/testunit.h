#ifndef TESTUNIT_H
#define TESTUNIT_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


/***********************************************************************
* Settings
***********************************************************************/
#define TESTUNIT_ERRORSTREAM (stderr)


/***********************************************************************
* A custom assert() function that prints out an error message, 
* as well as the filename and the line number 
***********************************************************************/
static inline 
void testunit__assert(int state, const char *message, 
                      const char* file, unsigned int line)
{
  if (!state)
  {
    fprintf(TESTUNIT_ERRORSTREAM, 
      "[Error in %s: Line %d] %s\n", file, line, message);
    exit(EXIT_FAILURE);
  }

  return;
}

/***********************************************************************
* Macro implementations
***********************************************************************/
#ifdef NDEBUG
#define ASSERT(state, message) \
  (testunit__assert(state, message, __FILE__, __LINE__))
#else
#define ASSERT(state, message) ((void)0);
#endif


/***********************************************************************
* Allocation
***********************************************************************/
static inline
void* safe_calloc(size_t n_chunks, size_t n_bytes)
{
  ASSERT((n_bytes > 0) && (n_chunks > 0), 
   "Invalid allocation of zero-sized array."); 

  void* tmp = calloc(n_chunks, n_bytes);

  ASSERT(tmp != NULL, 
   "NULL return of calloc() - Run out of memory?"); 

  return tmp;
}

static inline
void* safe_malloc(size_t n_bytes)
{
  ASSERT((n_bytes > 0), 
   "Invalid allocation of zero-sized array."); 

  void* tmp = malloc(n_bytes);

  ASSERT(tmp != NULL, 
   "NULL return of calloc() - Run out of memory?"); 

  return tmp;
}


static inline
void* safe_free(void* ptr)
{
  free(ptr);
  ptr = NULL;
  return ptr;
}

#endif /* TESTUNIT_H */
