// assert_with_trace.cpp

// The following code comes from this article.
//
// C/C++: printing stacktrace containing file name, function name, and line numbers using libbacktrace
//
// https://tjysdsg.github.io/libbacktrace/

// With modifications!

#include <cxxabi.h>
#include <cstdio>
#include <cstdlib>
#include <backtrace.h>

#include "assert_with_trace.hpp"

// extern "C" void init_back_trace(const char *filename);
// extern "C" void print_back_trace();

void *__bt_state = nullptr;

int bt_callback(void *, uintptr_t, const char *filename, int lineno, const char *function) {

  /// demangle function name
  const char *func_name = function;
  int status;
  char *demangled = abi::__cxa_demangle(function, nullptr, nullptr, &status);
  if (status == 0) {

    func_name = demangled;
  }

  /// print
  printf("%s:%d in function %s\n", filename, lineno, func_name);
  return 0;
}

void bt_error_callback(void *, const char *msg, int errnum) {

  printf("Error %d occurred when getting the stacktrace: %s", errnum, msg);
}

void bt_error_callback_create(void *, const char *msg, int errnum) {

  printf("Error %d occurred when initializing the stacktrace: %s", errnum, msg);
}

void init_back_trace(const char *filename) {

  __bt_state = backtrace_create_state(filename, 0, bt_error_callback_create, nullptr);
}

void print_back_trace() {

  if (!__bt_state) { /// make sure init_back_trace() is called

    printf("Make sure init_back_trace() is called before calling print_stack_trace()\n");
    abort();
  }
  printf( "\n ---Stack Back Trace---\n" );
  backtrace_full((backtrace_state *) __bt_state, 0, bt_callback, bt_error_callback, nullptr);
}

// --- Assertion Failure Handler ---
void custom_assertion_failed_handler(

    const char* condition_str,
    const char* description_str,
    const char* file,
    int line,
    const char* func_name) {

    fprintf(stderr, "\n!!! Assertion Failed !!!\n");
    fprintf(stderr, "%s\n", description_str);
    fprintf(stderr, "  Condition: %s\n", condition_str);
    fprintf(stderr, "  Location:  %s:%d\n", file, line);
    fprintf(stderr, "  Function:  %s\n", func_name);

    print_back_trace( );
   
    fflush(stderr); // Ensure output before abort
    std::abort();
}


