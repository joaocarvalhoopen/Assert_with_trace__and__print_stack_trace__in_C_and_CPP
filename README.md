# Assert_with_trace and print_stack_trace in C and CPP
A simple solution for defensive and assert trip wire programming.

## Description
This is a very simple solution for a better programming pratice of assert trip wire programming with ASSERT_WITH_TRACE( ) and print_stack_trace( ). It should work on CPP11 and above and with C. I tryed on Linux x86_64 and ARM64 and it works correctly. This prints the stack trace, the function name, the type of it's parameters, the filename, and the the line number. You can enable or disable the asserts with the change of a global variable. This uses libbacktrace and the example code from the following article from MarK Tang, that was adapted and modified and build uppon to include also the ASSERT_WITH_TRACE part. <br>
It can also be used to print the stack trace in case a signal occurs like a segmentation fault core dump, by doing a NULL pointer dereferencing, exemple: <br>

``` cpp
int *p = nullptr;
*p = 42;          // Dereference NULL -> SIGSEGV
                  // Segmentatio fault core dump :-)
                  // We dumped the core memory made with nucleo core ferrites!
```

## References
- GitHub ianlancetaylor - libbacktrace <br>
  [https://github.com/ianlancetaylor/libbacktrace](https://github.com/ianlancetaylor/libbacktrace) <br>
- Article <br>
  C - CPP: printing stacktrace containing file name, function name, and line numbers using libbacktrace<br>
  [https://tjysdsg.github.io/libbacktrace/](https://tjysdsg.github.io/libbacktrace/)

## Description of use

``` cpp
ASSERT_WITH_TRACE( expression, descricption );

and

print_stack_trace( )
```


``` cpp
int local_var = val - 5;
// Note: #expr in the macro will stringify the entire expression.
ASSERT_WITH_TRACE( local_var > 0, "Value must be positive after adjustment" );

or

ASSERT_WITH_TRACE( ptr_my_str != NULL && ptr_my_val != NULL, "The function input pointers can't be NULL !" );

```

## Example of output of a print stack and a assert_with_trace

``` bash
(base) joaocarvalho@soundofsilence:~/libbacktrace/assert_with_trace> ./out.exe 
Inside function_a( ).
Inside function_b( ) .
Inside function_c( ) . Printing stack trace:

 ---Stack Back Trace---
/home/joaocarvalho/libbacktrace/assert_with_trace/assert_with_trace.cpp:55 in function print_back_trace
/home/joaocarvalho/libbacktrace/assert_with_trace/main.cpp:29 in function function_c(int)
/home/joaocarvalho/libbacktrace/assert_with_trace/main.cpp:42 in function function_b(int)
/home/joaocarvalho/libbacktrace/assert_with_trace/main.cpp:48 in function function_a(int)
/home/joaocarvalho/libbacktrace/assert_with_trace/main.cpp:57 in function main
(null):0 in function (null)
(null):0 in function (null)
../sysdeps/x86_64/start.S:115 in function _start
(null):0 in function (null)
----------------------------------------


Inside function_d( ) . ASSERT_WITH_TRACE:

!!! Assertion Failed !!!
The configuration string is incorrect !
  Condition: ! strcmp( my_str, "Couves com arros!" )
  Location:  main.cpp:20
  Function:  function_d

 ---Stack Back Trace---
/home/joaocarvalho/libbacktrace/assert_with_trace/assert_with_trace.cpp:55 in function print_back_trace
/home/joaocarvalho/libbacktrace/assert_with_trace/assert_with_trace.cpp:73 in function custom_assertion_failed_handler
/home/joaocarvalho/libbacktrace/assert_with_trace/main.cpp:20 in function function_d(int, char*)
/home/joaocarvalho/libbacktrace/assert_with_trace/main.cpp:34 in function function_c(int)
/home/joaocarvalho/libbacktrace/assert_with_trace/main.cpp:42 in function function_b(int)
/home/joaocarvalho/libbacktrace/assert_with_trace/main.cpp:48 in function function_a(int)
/home/joaocarvalho/libbacktrace/assert_with_trace/main.cpp:57 in function main
(null):0 in function (null)
(null):0 in function (null)
../sysdeps/x86_64/start.S:115 in function _start
(null):0 in function (null)
Abortado (núcleo despejado)

```

## Example NULL pointer dereferencing generating a signal segmentation fault core dump

To show the print_stack_trace( ) after a signal like a segmentation fault core dump, so you can see imediatlly where in your code you have a introduced a bug or a memory access was invalid. put the following code in the main.

``` cpp

#include <cstring>

int main( ) {

    // Install our SIGSEGV handler ( using sigaction ):
    struct sigaction sa;
    memset( &sa, 0, sizeof( sa ) );
    sa.sa_sigaction = signal_handler;
    sa.sa_flags = SA_SIGINFO | SA_RESTART; 
    if ( sigaction( SIGSEGV, &sa, nullptr ) != 0 ) {
        perror( "sigaction" );
        return EXIT_FAILURE;
    }

    // The rest of your main code...
}
```


Example of output

``` bash
(base) joaocarvalho@soundofsilence:~/libbacktrace/assert_with_trace> ./out.exe
Inside function_a( ).
Inside function_b( ) .
Inside function_c( ) . Cause Null Pointer dereferencing -> Segmentation fault core dump!

[-] Caught signal 11 (SIGSEGV) at address (nil)
Segmentation fault

 ---Stack Back Trace---
/home/joaocarvalho/libbacktrace/assert_with_trace/assert_with_trace.cpp:65 in function print_back_trace
/home/joaocarvalho/libbacktrace/assert_with_trace/assert_with_trace.cpp:105 in function signal_handler(int, siginfo_t*, void*)
(null):0 in function (null)
/home/joaocarvalho/libbacktrace/assert_with_trace/main.cpp:30 in function function_c(int)
/home/joaocarvalho/libbacktrace/assert_with_trace/main.cpp:47 in function function_b(int)
/home/joaocarvalho/libbacktrace/assert_with_trace/main.cpp:53 in function function_a(int)
/home/joaocarvalho/libbacktrace/assert_with_trace/main.cpp:75 in function main
(null):0 in function (null)
(null):0 in function (null)
../sysdeps/x86_64/start.S:115 in function _start
(null):0 in function (null)

```

## How to install libbacktrace on a Linux computer from source code

``` bash
git clone https://github.com/ianlancetaylor/libbacktrace.git
cd libbacktrace
mkdir build
cd build
../configure
sudo make
sudo make install
```

## Steps to include this lib in a project

- You will need to install libbacktrace on the computer.

- Then it's is only necessary to include the file assert_with_trace.hpp e assert_with_trace.cpp in the project.

- Include the assert_with_trace.hpp in the C and CPP files where you are using the ASSERT_WITH_TRACE( condition, description ) and print_stack_trace( ).

- In main.cpp define a variable <br>
  ```bool flag_assert_with_trace_on = true;``` <br>
  if it is <br>
  ```bool flag_assert_with_trace_on = false;``` <br>
  it will disables all the ASSERT_WITH_TRACE( ).

- Then is necessary to initialize the path to the program name to read the program symbols table of the program executable ( it self ) so it can fill the information about the file names and the code lines of each function and the parameters types, for the stack trace, in the main.cpp for the executable, In this case "./out.exe" .

- Then it's only the use of the print_stack_trace(  ) for example in a signal handler for core dump analysis and to put the ASSERT_WITH_TRACE( condition, descprition ) spreaded in the code.

- In the compilation lines on the Makefile it's necessary to compile with the following flags "-g", "-O0" and "-lbacktrace".

## License
MIT Open Source license

## Have fun
Best regards, <br>
Joao Carvalho

