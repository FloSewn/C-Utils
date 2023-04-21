#ifndef BSTRLIB_WRAPPER_H
#define BSTRLIB_WRAPPER_H

#include "extern/bstrlib.h"
#include "testunit.h"

typedef bstring          String;
typedef struct bstrList* StringList;

/***********************************************************************
* Library interface
***********************************************************************/
static inline int bstrlib_string_destroy(String string);

static inline String bstrlib_string_copy_string(const String string);
static inline String bstrlib_string_copy_cstring(const char* cstring);
static inline String bstrlib_string_copy_bulk(const void* bulk, int length);
static inline String bstrlib_string_copy_substring(const String string, int start_pos, int length);

static inline int bstrlib_string_assign_string(String target, String string_to_assign);
static inline int bstrlib_string_assign_cstring(String target, const char* cstring);
static inline int bstrlib_string_assign_bulk(String target, const void* bulk, int length);

static inline int bstrlib_string_concat_string(String target, String append);
static inline int bstrlib_string_concat_cstring(String target, const char* append);
static inline int bstrlib_string_concat_char(String target, char append);
static inline int bstrlib_string_concat_bulk(String target, const void* append, int bulk_length);

static inline int bstrlib_string_insert_string(String target, int target_pos, String string, unsigned char fill_char);
static inline int bstrlib_string_insert_cstring(String target, int target_pos, const char *cstring, unsigned char fill_char);
static inline int bstrlib_string_insert_bulk(String target, int target_pos,const void* bulk, int bulk_length, unsigned char fill_char);
static inline int bstrlib_string_insert_char(String target, int target_pos, unsigned char fill_char);
static inline int bstrlib_string_insert_chars(String target, int target_pos, unsigned char fill_char, int n_chars);

static inline int bstrlib_string_replace_string(String target, int target_pos, const String replacement, int chars_to_replace, unsigned char fill_char);
static inline int bstrlib_string_delete_chars(String target, int target_pos, int n_chars_to_delete);
static inline int bstrlib_string_overwrite_string(String target, int target_pos, const String overwrite, unsigned char fill_char);
static inline int bstrlib_string_truncate(String target, int target_length);

static inline int bstrlib_string_compare(const String s1, const String s2);
static inline int bstrlib_string_compare_caseless(const String s1, const String s2);

static inline int bstrlib_string_compare_part(const String s1, const String s2, int part_length);
static inline int bstrlib_string_compare_part_caseless(const String s1, const String s2, int part_length);

static inline int bstrlib_string_contains(const String target, int target_pos, const String query);
static inline int bstrlib_string_contains_caseless(const String target, int target_pos, const String query);
static inline int bstrlib_string_contains_reverse(const String target, int target_pos, const String query);
static inline int bstrlib_string_contains_reverse_caseless(const String target, int target_pos, const String query);

static inline String bstrlib_string_read_textfile(String textfile_path);
static inline StringList bstrlib_stringlist_read_textfile(String textfile_path, unsigned char delimiter);


static inline StringList bstrlib_string_split(const String string_to_split, unsigned char split_char);

static inline StringList bstrlib_stringlist_create(void);
static inline int bstrlib_stringlist_alloc(StringList list, int n_strings);
static inline int bstrlib_stringlist_destroy(StringList list);

static inline StringList bstrlib_stringlist_pop_with_string(StringList stringlist, const String identifier);
static inline StringList bstrlib_stringlist_pop_with_cstring(StringList stringlist, const char *identifier);

static inline StringList bstrlib_stringlist_get_with_string(StringList stringlist, const String identifier);
static inline StringList bstrlib_stringlist_get_with_cstring(StringList stringlist, const char *identifier);

static inline String bstrlib_stringlist_extract_with_string(StringList stringlist, const String identifier);
static inline String bstrlib_stringlist_extract_with_cstring(StringList stringlist, const char *identifier);


/***********************************************************************
* Destructor functions
***********************************************************************/
static inline 
int bstrlib_string_destroy(String string)
{ return bdestroy(string); }

/***********************************************************************
* Copy functions
***********************************************************************/
static inline 
String bstrlib_string_copy_string(const String string)
{ return bstrcpy(string); }

static inline 
String bstrlib_string_copy_cstring(const char* cstring)
{ return bfromcstr(cstring); }

static inline 
String bstrlib_string_copy_bulk(const void* bulk, int length)
{ return blk2bstr(bulk, length); }

static inline 
String bstrlib_string_copy_substring(const String string, int start_pos, int length)
{ return bmidstr(string, start_pos, length); }

/***********************************************************************
* Assign functions
***********************************************************************/
static inline 
int bstrlib_string_assign_string(String target, 
                                 String string_to_assign)
{ return bassign(target, string_to_assign); }

static inline 
int bstrlib_string_assign_cstring(String target, 
                                  const char* cstring)
{ return bassigncstr(target, cstring); }

static inline 
int bstrlib_string_assign_bulk(String target, 
                               const void* bulk, int length)
{ return bassignblk(target, bulk, length); }

/***********************************************************************
* String concatenation functions
***********************************************************************/
static inline 
int bstrlib_string_concat_string(String target, String append)
{ return bconcat(target, append); }

static inline 
int bstrlib_string_concat_cstring(String target, const char* append)
{ return bcatcstr(target, append); }

static inline 
int bstrlib_string_concat_char(String target, char append)
{ return bconchar(target, append); }

static inline 
int bstrlib_string_concat_bulk(String target, 
                               const void* append, int bulk_length)
{ return bcatblk(target, append, bulk_length); }


/***********************************************************************
* String insertion functions
*
* Inserts a given string-object into <target> at position <pos>.  
* If the position <pos> is past the end of <target>, then the 
* character <fill> is appended as necessary to make up the gap between 
* the end of <target> and <pos>. 
*
***********************************************************************/
static inline 
int bstrlib_string_insert_string(String target, int target_pos, 
                                 String string, 
                                 unsigned char fill_char)
{ return binsert(target, target_pos, string, fill_char); }

static inline 
int bstrlib_string_insert_cstring(String target, int target_pos, 
                                  const char *cstring, 
                                  unsigned char fill_char)
{ 
  String tmp = bstrlib_string_copy_cstring(cstring);
  int ret = bstrlib_string_insert_string(target, target_pos, tmp, fill_char);
  bstrlib_string_destroy(tmp);
  return ret; 
}

static inline 
int bstrlib_string_insert_bulk(String target, int target_pos,
                               const void* bulk, int bulk_length,
                               unsigned char fill_char)
{ return binsertblk(target, target_pos, bulk, bulk_length, fill_char); }

static inline 
int bstrlib_string_insert_char(String target, int target_pos,
                               unsigned char fill_char)
{ return binsertch(target, target_pos, 1, fill_char); }

static inline 
int bstrlib_string_insert_chars(String target, int target_pos,
                                unsigned char fill_char, 
                                int n_chars)
{ return binsertch(target, target_pos, n_chars, fill_char); }


/***********************************************************************
* String replace / deletion / overwrite / truncate functions
***********************************************************************/
static inline 
int bstrlib_string_replace_string(String target, int target_pos,
                                  const String replacement,
                                  int chars_to_replace,
                                  unsigned char fill_char)
{ return breplace(target, target_pos, chars_to_replace, 
                  replacement, fill_char); }

static inline 
int bstrlib_string_delete_chars(String target, int target_pos,
                                int n_chars_to_delete)
{ return bdelete(target, target_pos, n_chars_to_delete); }

static inline 
int bstrlib_string_overwrite_string(String target, int target_pos,
                                    const String overwrite,
                                    unsigned char fill_char)
{ return bsetstr(target, target_pos, overwrite, fill_char); }

static inline 
int bstrlib_string_truncate(String target, int target_length)
{ return btrunc(target, target_length); }



/***********************************************************************
* Scan / search functions
***********************************************************************/
static inline 
int bstrlib_string_compare(const String s1, const String s2)
{ return bstrcmp(s1, s2); }

static inline 
int bstrlib_string_compare_caseless(const String s1, const String s2)
{ return bstricmp(s1, s2); }

static inline 
int bstrlib_string_compare_part(const String s1, const String s2, int part_length)
{ return bstrncmp(s1, s2, part_length); }

static inline 
int bstrlib_string_compare_part_caseless(const String s1, const String s2, int part_length)
{ return bstrnicmp(s1, s2, part_length); }

static inline 
int bstrlib_string_contains(const String target, int target_pos,
                            const String query)
{ return binstr(target, target_pos, query); }

static inline 
int bstrlib_string_contains_caseless(const String target, int target_pos,
                                     const String query)
{ return binstrcaseless(target, target_pos, query); }

static inline 
int bstrlib_string_contains_reverse(const String target, int target_pos,
                                    const String query)
{ return binstrr(target, target_pos, query); }

static inline 
int bstrlib_string_contains_reverse_caseless(const String target, 
                                             int target_pos,
                                             const String query)
{ return binstrrcaseless(target, target_pos, query); }


/***********************************************************************
* Open a text file and copy its content into a string
***********************************************************************/
static inline 
String bstrlib_string_read_textfile(String textfile_path)
{
  // Copy data from file
  FILE *textfile = NULL;
  const char* textfile_path_c = (const char*) textfile_path->data; 

  textfile = fopen(textfile_path_c, "rb");

  if (!textfile)
  {
    fprintf(TESTUNIT_ERRORSTREAM, 
            "Failed to read mesh file: %s\n", textfile_path_c);
    ASSERT(0," ");
    return NULL;
  }

  // Estimate length of chars in whole file 
  fseek(textfile, 0, SEEK_END);
  long length = ftell(textfile);
  fseek(textfile, 0, SEEK_SET);

  // Read total file into buffer
  char *buffer = (char *) safe_malloc(length + 1);
  buffer[length] = '\0';
  fread(buffer, 1, length, textfile);

  // Copy data to a new string
  String output = bfromcstr( buffer );

  fclose(textfile);
  safe_free(buffer);

  return output;

} // bstrlib_string_read_textfile()



/***********************************************************************
* String split and join functions
***********************************************************************/
static inline 
StringList bstrlib_string_split(const String string_to_split, 
                                unsigned char split_char)
{ return bsplit(string_to_split, split_char); }


/***********************************************************************
* Scan / search functions
***********************************************************************/
static inline
StringList bstrlib_stringlist_create(void)
{ return bstrListCreate(); }

static inline 
int bstrlib_stringlist_alloc(StringList list, int n_strings)
{ return bstrListAlloc(list, n_strings); }

static inline 
int bstrlib_stringlist_destroy(StringList list)
{ return bstrListDestroy(list); }


/***********************************************************************
* Pop a node in a given StringList, if it contains a given identifier
***********************************************************************/
static inline
StringList bstrlib_stringlist_pop_with_string(StringList stringlist,
                                              const String identifier)
{
  String* list_pos = stringlist->entry;
  int n_strings = stringlist->qty;
  int *marker = (int*) safe_calloc(n_strings, sizeof(int));

  // Fill array of markers with line numbers, that do not contain 
  // the identifier string
  int n_hits = 0;
    
  for (int i = 0; i < n_strings; i++) 
  {
    int found = bstrlib_string_contains(list_pos[i], 0, identifier);

    if ( found == BSTR_ERR )
    {
      n_hits += 1;
      marker[i] = i;
    }
    else
    {
      marker[i] = -1;
    }
  }

  // Create new bstrList that will contained all filtered lines
  StringList new_stringlist = bstrlib_stringlist_create();
  bstrlib_stringlist_alloc(new_stringlist, n_hits);

  // Copy marked lines into new string list
  String* string_ptr = new_stringlist->entry;
  int count = 0;

  for (int i = 0; i < n_strings; i++) 
  {
    if (marker[i] >= 0)
    {
      const int curline = marker[i];
      string_ptr[count] = bstrlib_string_copy_string(list_pos[curline]);
      new_stringlist->qty += 1;
      count += 1;
    }
  }

  // Cleanup
  safe_free(marker);

  return new_stringlist;

} // bstrlib_stringlist_pop_with_string() 


static inline
StringList bstrlib_stringlist_pop_with_cstring(StringList stringlist,
                                               const char *identifier)
{
  String  identifier_tmp = bstrlib_string_copy_cstring(identifier);

  StringList tmp 
    = bstrlib_stringlist_pop_with_string(stringlist, identifier_tmp);

  bstrlib_string_destroy(identifier_tmp);

  return tmp;

} // bstrlib_stringlist_pop_with_cstring()


/***********************************************************************
* Get all nodes in a given StringList, if it contains a given identifier
***********************************************************************/
static inline
StringList bstrlib_stringlist_get_with_string(StringList stringlist,
                                              const String identifier)
{
  String *list_pos = stringlist->entry;
  int n_strings = stringlist->qty;
  int *marker = (int*) safe_calloc(n_strings, sizeof(int));

  // Fill array of markers with line numbers, that  
  // contain the filter string
  int n_hits = 0;

  for (int i = 0; i < n_strings; i++) 
  {
    int found = bstrlib_string_contains(list_pos[i], 0, identifier);

    if ( found != BSTR_ERR )
    {
      n_hits += 1;
      marker[i] = i;
    }
    else
    {
      marker[i] = -1;
    }
  }

  // Create new bstrList that will contained all filtered lines
  StringList new_stringlist = bstrlib_stringlist_create();
  bstrlib_stringlist_alloc(new_stringlist, n_hits);

  // Copy marked lines into new bstrList
  String* string_ptr = new_stringlist->entry;
  int count = 0;

  for (int i = 0; i < n_strings; i++) 
  {
    if (marker[i] >= 0)
    {
      const int curline = marker[i];
      string_ptr[count] = bstrlib_string_copy_string(list_pos[curline]);
      new_stringlist->qty += 1;
      count += 1;
    }
  }

  // Cleanup
  safe_free(marker);

  return new_stringlist;

} // bstrlib_stringlist_get_with_string()

 
static inline
StringList bstrlib_stringlist_get_with_cstring(StringList stringlist,
                                               const char *identifier)
{
  String identifier_tmp = bstrlib_string_copy_cstring(identifier);

  StringList tmp 
    = bstrlib_stringlist_get_with_string(stringlist, identifier_tmp);

  bstrlib_string_destroy(identifier_tmp);

  return tmp;

} // bstrlib_stringlist_get_with_cstring()



/***********************************************************************
* Function searches for an identifier in a StringList.
* The parameter behind the identifier is then returned.
*
* Returns 0 if specifier was not found in the file.
* Otherwise, it returns the number of times, the 
* specifier was found.
* Returns -1 on errors.
***********************************************************************/
static inline 
String bstrlib_stringlist_extract_with_string(StringList stringlist,
                                              const String identifier)
{
  // Get all lines, containing the specifier
  StringList found_lines 
    = bstrlib_stringlist_get_with_string(stringlist, identifier);
  int n_found = found_lines->qty;

  if (n_found < 1)
  {
    bstrlib_stringlist_destroy(found_lines);
    return NULL;
  }

  // Take last string, in which specifier was found
  String line = found_lines->entry[n_found - 1];

  int off = bstrlib_string_contains(line, 0, identifier); 
  int len = identifier->slen;

  String extraction 
    = bstrlib_string_copy_substring(line, off+len, line->slen );

  bstrlib_stringlist_destroy(found_lines);

  return extraction;

} // bstrlib_stringlist_extract_with_string() 

 
static inline 
String bstrlib_stringlist_extract_with_cstring(StringList stringlist,
                                               const char *identifier)
{
  String identifier_tmp = bstrlib_string_copy_cstring(identifier);

  String extraction 
    = bstrlib_stringlist_extract_with_string(stringlist, identifier_tmp);

  bstrlib_string_destroy(identifier_tmp);

  return extraction;

} // bstrlib_stringlist_extract_with_cstring()


/***********************************************************************
* Open a text file and copy its content into a stringlist, where a
* given delimiter is used to separate the file content into several
* strings.
***********************************************************************/
static inline 
StringList bstrlib_stringlist_read_textfile(String textfile_path, 
                                            unsigned char delimiter)
{
  // Read textfile content into single string
  String buffer = bstrlib_string_read_textfile(textfile_path);

  StringList output = bstrlib_string_split(buffer, delimiter);

  bstrlib_string_destroy(buffer);

  return output;

} // bstrlib_stringlist_read_textfile()

#endif /* BSTRLIB_WRAPPER_H */
