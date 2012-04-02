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



class iter
{
    typedef std::vector< Node const* >Stack;
    Stack stack_;
    visit order_,visit_;
    
    void past_last( void )
    {
        stack_.clear();
        order_ = in;
        visit_ = pre;
    }

    void advance( void )
    {
        do{
            traverse_step( visit_, stack_ );
            /* std::cout */
            /*     << "visit_ == " << visit_ << std::endl ; */
            /* using namespace boost::phoenix; */
            /* using namespace boost::phoenix::arg_names; */
            /* std::for_each( stack_.begin(), stack_.end(), std::cout << arg1 << "," ); */
            /* std::cout << std::endl ; */
            if( order_ == visit_ ) return;
        }while( ! ( 1 == stack_.size() && post == visit_ ) );
        stack_.clear();
    }

public:
    /* dtor */
    virtual ~iter( void ){}

    /* ctor */
    explicit iter( Node const*p = NULL, visit const&order = in )
        :stack_ ( p ? Stack( 1, p ) : Stack( 0 ) )
        ,order_ ( order           )
        ,visit_ ( p ? pre : post  )
    {
        /* do this to get past the root on the first dereference */
        if( 0 < stack_.size() ) advance();
    }

    /* copy ctor */
    iter( iter const&nit )
        :stack_( nit.stack_ )
        ,order_( nit.order_ )
        ,visit_( nit.visit_ )
    {}
    /* assignment op */
    iter&operator=( iter const&nit )
    {
        stack_ = nit.stack_ ;
        order_ = nit.order_ ;
        visit_ = nit.visit_ ;
        return*this;
    }

    /* prefix autoincrement */
    iter&operator++(){ advance(); return*this; }
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

    delete tree;
    std::cout << std::endl ;
    return 0;
}
