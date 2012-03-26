/* cppconact/background_task.hpp */


void do_something( void )
{
    std::cout << __PRETTY_FUNCTION__ << std::endl ;
}
void do_something_else( void )
{
    std::cout << __PRETTY_FUNCTION__ << std::endl ;
}


struct background_task
{
    void operator()( void )const
    {
        do_something();
        do_something_else();
    }
};

