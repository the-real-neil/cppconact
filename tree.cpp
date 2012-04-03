/* cppconact/tree.cpp */

#include<cstddef>
#include<iostream>
#include<iterator>
#include<vector>

#include"boost/phoenix.hpp"


class iter;

struct Node
{
    char char_;
    Node*left_,*right_;

    /* ctor */
    Node( char c )
        :char_(c),left_(0),right_(0)
    {}

    /* copy ctor */
    Node( Node const&o )
        :char_  ( o.char_  )
        ,left_  ( o.left_  )
        ,right_ ( o.right_ )
    {}

    Node&operator=( Node const&o )
    {
        char_  = o.char_  ;
        left_  = o.left_  ;
        right_ = o.right_ ;
        return*this;
    }

    ~Node( void )
    {
        delete left_;
        std::cout << "\ndeleting " << std::string(&char_,1);
        delete right_;
    }
};


bool empty( Node const*node ){ return NULL == node ; }

bool has_left_successor( Node const*node ){ return ! empty( node->left_ ) ; }

bool has_right_successor( Node const*node ){ return ! empty( node->right_ ) ; }

Node const*left_successor( Node const*node ){ return node->left_ ; }

Node const*right_successor( Node const*node ){ return node->right_ ; }


enum visit{pre,in,post};



int traverse_step( visit&v,
                   std::vector< Node const* >&stack )
{
    /* precondition: stack.back() has predecessor || v != post */
    /* "stack.back() has predecessor" implies stack.size() > 1 */
    Node const*tmp;

    switch( v ){

    case pre:
        if( has_left_successor( stack.back() ) ){
            stack.push_back( left_successor( stack.back() ) );
            return 1;
        }else{
            v = in;
            return 0;
        }

    case in:
        if( has_right_successor( stack.back() ) ){
            v = pre;
            stack.push_back( right_successor( stack.back() ) );
            return 1;
        }else{
            v = post;
            return 0;
        }

    case post:
        /* by precondition, stack.size() > 1 */
        tmp = stack.back();
        stack.pop_back();
        if( left_successor( stack.back() ) == tmp ) v = in;
        return -1;
    }

    return 0;//never get here
}



typedef std::vector< Node const* >Stack;



void advance( visit const&ord,
              visit&vis,
              Stack&stack )
{
    do{
        traverse_step( vis, stack );
        /* std::cout */
        /*     << "visit_ == " << visit_ << std::endl ; */
        /* using namespace boost::phoenix; */
        /* using namespace boost::phoenix::arg_names; */
        /* std::for_each( stack_.begin(), stack_.end(), std::cout << arg1 << "," ); */
        /* std::cout << std::endl ; */
        if( ord == vis ) return;
    }while( ! ( 1 == stack.size() && post == vis ) );
    stack.clear();
}

class iter
{
    visit order_,visit_;
    Stack stack_;

    visit init_visit_( Node const*p )
    {
        return empty( p ) ? post : pre ;
    }

    Stack init_stack_( Node const*p )
    {
        Stack ret;
        if( ! empty( p ) ){
            ret.push_back( p );
            advance( order_, visit_, ret );
        }
        return ret;
    }
public:
    /* dtor */
    virtual ~iter( void ){}

    /* ctor */
    explicit iter( Node const*p = NULL, visit const&order = in )
        :order_( order )
        ,visit_( init_visit_( p ) )
        ,stack_( init_stack_( p ) )
    {}

    /* prefix autoincrement */
    iter&operator++(){ advance( order_, visit_, stack_ ); return*this; }

    /* postfix autoincrement */
    iter operator++(int){ iter ret(*this); operator++(); return ret; }

    /* equality */
    bool operator==( iter const&rhs )const
    {
        if( stack_.size() != rhs.stack_.size() )
            return false;
        if( ! std::equal( stack_.begin(), stack_.end(), rhs.stack_.begin() ) )
            return false;
        if( order_ != rhs.order_ )
            return false;
        if( visit_ != rhs.visit_ )
            return false;
        return true;
    }

    /* inequality */
    bool operator!=( iter const&rhs )const{ return ! operator==(rhs); }

    /* dereference */
    Node const&operator*(void){ return *stack_.back(); }
};


iter begin( Node const*p ){ return iter( p ); }
iter end( Node const* ){ return iter(); }


void foo( Node const&n )
{
    std::cout << n.char_ << std::endl ;
}


int main( int, char** )
{
    Node*tree = new Node('F');
    tree->left_ = new Node('B');
    tree->left_->left_ = new Node('A');
    tree->left_->right_ = new Node('D');
    tree->left_->right_->left_ = new Node('C');
    tree->left_->right_->right_ = new Node('E');

    tree->right_ = new Node('G');
    tree->right_->right_ = new Node('I');
    tree->right_->right_->left_ = new Node('H');

    std::for_each( begin( tree ), end( tree ), foo );

    Node*o = new Node('O');
    std::for_each( begin(o), end(o), foo );

    delete tree;
    delete o;
    std::cout << std::endl ;

    return 0;
}
