// assert_with_trace.hpp

#ifndef ASSERT_WITH_TRACE_HPP
#define ASSERT_WITH_TRACE_HPP

#include <csignal>          // sigaction, siginfo_t, SA_SIGINFO


// To initialize the back trace and pass the execution file compile with -g and -lbacktrace  
extern "C" void init_back_trace( const char *filename );

// To print the back trace .
extern "C" void print_back_trace( );

extern "C" void custom_assertion_failed_handler(
                	const char* condition_str,
    				const char* description_str,
    				const char* file,
    				int line,
    				const char* func_name );


// --- The Assert Macro with Stack Back Trace ---
#define ASSERT_WITH_TRACE( cond, desc )                                                     \
    do {                                                                                    \
        if ( FLAG_ASSERTS_WITH_TRACE_ON == true ) {                                         \
           if ( !( cond ) ) {                                                               \
              custom_assertion_failed_handler( #cond, desc, __FILE__, __LINE__, __func__ ); \
           }                                                                                \
        }                                                                                   \
    } while ( 0 )


/*

Example of usage:

	Enable or disable the global variable in the main.c :

	bool FLAG_ASSERTS_WITH_TRACE_ON = true;
    // bool FLAG_ASSERTS_WITH_TRACE_ON = false;



	int local_var = val - 5;
    // Note: #expr in the macro will stringify the entire expression.
    ASSERT_WITH_TRACE( local_var > 0, "Value must be positive after adjustment" );

or

    ASSERT_WITH_TRACE( ptr_my_str != NULL && ptr_my_val != NULL, "The function input pointer can't be NULL !" );

*/


// Handle a signal, example: segmentation fault core dump, and prints the stack trace.
void signal_handler( int signum, siginfo_t *info, void *context );

// Generates a Null pointer exception, that is a segmentation fault core dump.
void cause_segfault( );


#endif /* ASSERT_WITH_TRACE_HPP */

