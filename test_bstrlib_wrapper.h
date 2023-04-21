#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "src/bstrlib_wrapper.h"
#include "src/testunit.h"


/***********************************************************************
* 
***********************************************************************/
static inline void test_bstrlib_copy_functions()
{
  // Initialization from c-strings
  String string_c = bstrlib_string_copy_cstring("Hello there.");

  ASSERT( 
    strcmp( (const char*) string_c->data, "Hello there.") == 0,
    "bstrlib_string_copy_cstring() failed."
  );


  // Initialization from bulk data
  const char bulk_init[10] = "1 2 3 4 5";
  String string_bulk = bstrlib_string_copy_bulk(bulk_init, 10);

  ASSERT( 
    strcmp( (const char*) string_bulk->data, "1 2 3 4 5") == 0,
    "bstrlib_string_copy_bulk() failed."
  );

  // Initialization from bstrlib-strings
  String string_copy = bstrlib_string_copy_string(string_c);

  ASSERT( 
    strcmp( (const char*) string_copy->data, "Hello there.") == 0,
    "bstrlib_string_copy_string() failed."
  );


  // Free all strings
  bstrlib_string_destroy( string_c );
  bstrlib_string_destroy( string_bulk );
  bstrlib_string_destroy( string_copy );

} // test_bstrlib_copy_function() 


/***********************************************************************
* 
***********************************************************************/
static inline void test_bstrlib_assign_functions()
{
  // Assign c-string 
  String string_c = bstrlib_string_copy_cstring("This is a");
  bstrlib_string_assign_cstring(string_c, "string");

  ASSERT( 
    strcmp( (const char*) string_c->data, "string") == 0,
    "bstrlib_string_assign_cstring() failed."
  );
  ASSERT(string_c->slen == 6, "bstrlib_string_assign_cstring() failed.");


  // Assign bulk data
  const char large_bulk[30] = "These are actually 28 chars.";
  String string_bulk = bstrlib_string_copy_cstring("A smaller string");
  bstrlib_string_assign_bulk(string_bulk, large_bulk, 30);

  ASSERT( 
    strcmp( (const char*) string_bulk->data, "These are actually 28 chars.") == 0,
    "bstrlib_string_assign_bulk() failed."
  );
  ASSERT(string_bulk->slen == 30, "bstrlib_string_assign_bulk() failed.");


  // Assign bstrlib string
  String string_a = bstrlib_string_copy_cstring("Test-string");
  String string_b = bstrlib_string_copy_cstring("Yet another string");
  bstrlib_string_assign_string(string_a, string_b);

  ASSERT( 
    strcmp( (const char*) string_a->data, "Yet another string") == 0,
    "bstrlib_string_assign_string() failed."
  );
  ASSERT(string_a->slen == 18, "bstrlib_string_assign_string() failed.");


  // Free all strings
  bstrlib_string_destroy( string_c );
  bstrlib_string_destroy( string_bulk );
  bstrlib_string_destroy( string_a );
  bstrlib_string_destroy( string_b );

} // test_bstrlib_assign_function() 


/***********************************************************************
* 
***********************************************************************/
static inline void test_bstrlib_concat_functions()
{
  // Concat char to a string
  String string_a = bstrlib_string_copy_cstring("A string ");

  bstrlib_string_concat_char(string_a, 'K');

  ASSERT( 
    strcmp( (const char*) string_a->data, "A string K") == 0,
    "bstrlib_string_concat_char() failed."
  );
  ASSERT(string_a->slen == 10, "bstrlib_string_concat_char() failed.");


  // Concat string to string
  String string_b1 = bstrlib_string_copy_cstring("String A");
  String string_b2 = bstrlib_string_copy_cstring(" - String B");
    
  bstrlib_string_concat_string(string_b1, string_b2);

  ASSERT( 
    strcmp( (const char*) string_b1->data, "String A - String B") == 0,
    "bstrlib_string_concat_string() failed."
  );
  ASSERT(string_b1->slen == 19, "bstrlib_string_concat_string() failed.");


  // Concat bulk of data 
  // -> Attention: String length increases by bulk length
  String string_c1 = bstrlib_string_copy_cstring("Here are");
  const char bulk_data[30] = " some more chars.";
  
  bstrlib_string_concat_bulk(string_c1, bulk_data, 30);

  ASSERT( 
    strcmp( (const char*) string_c1->data, "Here are some more chars.") == 0,
    "bstrlib_string_concat_string() failed."
  );
  ASSERT(string_c1->slen == 38, "bstrlib_string_concat_bulk() failed.");


  // Free all strings
  bstrlib_string_destroy( string_a );
  bstrlib_string_destroy( string_b1 );
  bstrlib_string_destroy( string_b2 );
  bstrlib_string_destroy( string_c1 );

} // test_bstrlib_concat_functions()

/***********************************************************************
* 
***********************************************************************/
static inline void test_bstrlib_insert_functions()
{
  // Insert string / cstring 
  String test_1 = bstrlib_string_copy_cstring("Test string 1");
  bstrlib_string_insert_cstring(test_1, 11, " 2", ' ');

  ASSERT( 
    strcmp( (const char*) test_1->data, "Test string 2 1") == 0,
    "bstrlib_string_insert_string() failed."
  );
  ASSERT(test_1->slen == 15, "bstrlib_string_insert_string() failed.");


  // Insert some chars
  bstrlib_string_insert_chars(test_1, 5, 'X', 4);

  ASSERT( 
    strcmp( (const char*) test_1->data, "Test XXXXstring 2 1") == 0,
    "bstrlib_string_insert_chars() failed."
  );
  ASSERT(test_1->slen == 19, "bstrlib_string_insert_chars) failed.");


  // Free all strings
  bstrlib_string_destroy( test_1 );

} // test_bstrlib_insert_functions()




/***********************************************************************
* 
***********************************************************************/
static inline void test_bstrlib_stringlist_functions()
{
  const char* sample_text = 
    "This is a sample text\n"
    "Here is a new line\n"
    "This is another new line\n"
    "END";

  String message = bstrlib_string_copy_cstring( sample_text );

  StringList stringlist = bstrlib_string_split(message, '\n');

  StringList poppedlist = bstrlib_stringlist_pop_with_cstring(stringlist, "line");

  ASSERT(
    poppedlist->qty == 2,
    "bstrlib_stringlist_pop_with() failed."
  );

  StringList getlist = bstrlib_stringlist_get_with_cstring(stringlist, "line");

  ASSERT(
    getlist->qty == 2,
    "bstrlib_stringlist_get_with() failed."
  );

  String value = bstrlib_stringlist_extract_with_cstring(stringlist, "This is a ");

  ASSERT( 
    strcmp( (const char*) value->data, "sample text") == 0,
    "bstrlib_stringlist_extract_with_cstring() failed."
  );

  bstrlib_string_destroy(message);
  bstrlib_string_destroy(value);
  bstrlib_stringlist_destroy(stringlist);
  bstrlib_stringlist_destroy(poppedlist);
  bstrlib_stringlist_destroy(getlist);






} // test_bstrlib_stringlist_functions()



/***********************************************************************
* The main function
***********************************************************************/
static inline int test_bstrlib_wrapper(int argc, char* argv[])
{
  (void) argc;
  (void) argv;
  
  test_bstrlib_copy_functions();
  test_bstrlib_assign_functions();
  test_bstrlib_concat_functions();
  test_bstrlib_insert_functions();
  test_bstrlib_stringlist_functions();

  printf("\n  [bstrlib_wrapper] works like a charm!\n\n");

  return EXIT_SUCCESS;
}
