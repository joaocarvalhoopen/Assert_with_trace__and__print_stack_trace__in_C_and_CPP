// main.cpp

#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <cstring>

#include "assert_with_trace.hpp"

bool FLAG_ASSERTS_WITH_TRACE_ON = true;
// bool FLAG_ASSERTS_WITH_TRACE_ON = false;

void function_d( int val_d, char * my_str ) {

    printf("Inside function_d( ) . ASSERT_WITH_TRACE:\n");
    ASSERT_WITH_TRACE( val_d == 5, " The val_d variable should be 5 !" );

    ASSERT_WITH_TRACE( my_str != NULL, "The pointer my_str is NULL !" );

    ASSERT_WITH_TRACE( ! strcmp( my_str, "Couves com arros!" ) , "The configuration string is incorrect !" );


    printf("----------------------------------------\n");
}

void function_c( int val_c ) {

    printf("Inside function_c( ) . Printing stack trace:\n");
    print_back_trace( );
    printf("----------------------------------------\n");

    printf( "\n\n" );

    function_d( val_c, ( char * ) "Couves com massa!" );

    printf("----------------------------------------\n");
}

void function_b( int val_b ) {

    printf("Inside function_b( ) .\n");
    function_c( val_b );
}

void function_a( int val_a ) {

    printf("Inside function_a( ).\n");
    function_b( val_a );
}

int main( ) {

   // O executavel tem de ser compilado com as flags -g e -lbacktrace 
   char * exec_filename = (char *) "./out.exe";
   init_back_trace( exec_filename );

   function_a( 5 );
}
