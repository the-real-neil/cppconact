/* cppconact/hello_concurrent_world.cpp */

#include<iostream>
#include<thread>

void
hello( void )
{
    std::cout << "Hello, Concurrent World!\n" ;
}

int
main( int, char** )
{
    std::thread t( hello );
    t.join();
    return 0;
}
