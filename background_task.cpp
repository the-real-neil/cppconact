/* cppconact/background_task.cpp */


#include<iostream>
#include<thread>

#include"background_task.hpp"


int
main( int, char** )
{
    std::thread thread_a( ( background_task() ) );

    std::thread thread_b{ background_task() };

    std::thread thread_c( []{
            do_something();
            do_something_else();
        } );

    thread_a.join();
    thread_b.join();
    thread_c.join();
    return 0;
}

