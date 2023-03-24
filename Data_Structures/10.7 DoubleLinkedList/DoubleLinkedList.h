/**
 * @file DoubleLinkedList.cpp
 * @author Nan Ziqian (1727411859@qq.com)
 * @brief 数据结构与算法10.7作业
 * @version 0.1
 * @date 2022-10-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<iostream>
using namespace std;

/**
 * @brief 所有的List功能都在模板类中实现，模板类有助于节点存储不同数据类型的数据
 * 
 */
template <typename T>

class List{
    private:
    /// @brief Node结构为节点，有名为data的数据和名为prev和next的指针，分别指向前一节点和后一节点
    struct Node{
        T data;
        Node *prev;
        Node *next;
        /// @brief 输入变量时调用第一个，输入常量时调用第二个，在未给出前后指针时默认空指针
        /// @param d 
        /// @param p 
        /// @param n 
        Node( const T & d = T{ }, Node * p = nullptr,Node * n = nullptr )
        : data{ d }, prev{ p }, next{ n } { }
        Node( T && d, Node * p = nullptr, Node * n = nullptr )
        : data{ std::move( d ) }, prev{ p }, next{ n } { }
    };

    public:
    class const_iterator{
        public:
        /// @brief 常量迭代器继承了名为current的节点
        const_iterator():current{nullptr}{}
        /// @brief 在数据类型为const_iterator的运算中，我们重载了* ++ == ！=的运算符。
        /// @return 
        const T & operator*()const{
            return retrieve();
        }
        /// @brief ++能够让迭代器指向下一个节点
        /// @return 引用const_iterator的节点
        const_iterator & operator++ ( ){
            current = current->next;
            return *this;
        }
        const_iterator operator++ ( int ){
            const_iterator old = *this;
            ++( *this );
            return old;
        }
        /// @brief ==与！=能够比较两个迭代器指向的节点是否一致
        /// @param rhs 
        /// @return 1 or 0
        bool operator== ( const const_iterator & rhs ) const{
            return current == rhs.current;
        }
        bool operator!= ( const const_iterator & rhs ) const{
            return !( *this == rhs );
        }
        
        protected:
        Node *current;
        /// @brief retrieve是从节点获得数据的函数
        /// @return T data
        T & retrieve( ) const{
            return current->data;
        }
        
        const_iterator( Node *p ) : current{ p }{ }
        /// @brief 友元，类list中的所有函数都可访问const_iterator中的参数
        friend class List<T>;
    };
    /// @brief 非常量迭代器公开继承了常量迭代器，也重载了* ++ == ！=的运算符。
    class iterator : public const_iterator{
        public:
        iterator( ){ }

        T & operator* ( ){
            return const_iterator::retrieve( );
        }
        const T & operator* ( ) const{
            return const_iterator::operator*( );
        }
        iterator & operator++ ( ){
            this->current = this->current->next;
            return *this;
        }
        iterator operator++ ( int ){
            iterator old = *this;
            ++( *this );
            return old;
        }
        iterator & operator-- ( ){
            this->current = this->current->prev;
            return *this;
        }
        iterator operator-- ( int ){
            iterator old = *this;
            --( *this );
            return old;
        }

        protected:
        iterator( Node *p ) : const_iterator{ p }{ }

        friend class List<T>;
    };


    /// @brief 这是List类的有参及无参的初始化函数及析构函数，若已经存在rhs，可进行rhs的复制。
    /// @tparam T 
    public:
    List( ){
        init();
    }
    List( const List & rhs ){
        init( );
        for( auto & x : rhs )
            push_back( x );
    }

    ~List( ){
        clear( );
        delete head;
        delete tail;
    }
    /// @brief 重载了=运算符，能让=之前的list变成rhs的复制
    /// @param rhs 
    /// @return =之前的list
    List & operator= ( const List & rhs ){
        List copy = rhs;
        std::swap( *this, copy );
        return *this; 
    }
    /// @brief 如果=前不是常量list，将把其和rhs交换
    /// @param rhs 
    List( List && rhs ): theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail }
    {
        rhs.theSize = 0;
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }
    List & operator= ( List && rhs ){
        std::swap( theSize, rhs.theSize );
        std::swap( head, rhs.head );
        std::swap( tail, rhs.tail );
        return *this;
    }
    /// @brief 让迭代器显示第一个节点的指针
    /// @return head->next
    iterator begin( ){
        return { head->next }; 
    }
    const_iterator begin( ) const{
        return { head->next }; 
    }
    iterator end( ){
        return { tail }; 
    }
    const_iterator end( ) const{
        return { tail }; 
    }
    /// @brief 输出list节点个数
    /// @return thSize
    int size( ) const{
        return theSize;
    }
    /// @brief 判断list节点个数是否为0
    /// @return 
    bool empty( ) const{
        return size( ) == 0;
    }
    /// @brief 不断删除第一个节点直至清空
    void clear( ){
        while( !empty( ) )
            pop_front( );
    }
    /// @brief 输出第一个节点
    /// @return 
    T & front( ){
        return *begin( );
    }
    const T & front( ) const{
        return *begin( );
    }
    /// @brief 输出最后一个节点
    /// @return 
    T & back( ){
        return *--end( );
    }
    const T & back( ) const{
        return *--end( );
    }
    /// @brief 在开头（head->next）插入数据为x的节点
    /// @param x 
    void push_front( const T & x ){
        insert( begin( ), x );
    }
    void push_front( T && x ){
        insert( begin( ), std::move( x ) );
    }
    /// @brief 在结尾（tail）插入数据为x的节点
    /// @param x 
    void push_back( const T & x ){
        insert( end( ), x );
    }
    void push_back( T && x ){
        insert( end( ), std::move( x ) );
    }
    /// @brief 删除第一个节点
    void pop_front( ){
        erase( begin( ) );
    }
    /// @brief 删除最后一个节点
    void pop_back( ){
        erase( --end( ) );
    }
    /// @brief 在迭代器所指的节点之前插入数据为x的节点，
    /// @param itr 
    /// @param x 
    /// @return 插入的新节点
    iterator insert( iterator itr, const T & x ){
        Node *p = itr.current;
        theSize++;
        return { p->prev = p->prev->next = new Node{ x, p->prev, p } };
    }
    iterator insert( iterator itr, T && x ){
        Node *p = itr.current;
        theSize++;
        return { p->prev = p->prev->next= new Node{ std::move( x ), p->prev, p } };
    }
    /// @brief erase是插入的反操作
    /// @param itr 
    /// @return p之后的节点
    iterator erase( iterator itr ){
        Node *p = itr.current;
        iterator retVal{ p->next };
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        theSize--;
        return retVal;
    }
    /// @brief erase重载使可以实现从一个节点到另一个节点之间（左闭右开）全部抹除
    /// @param from 
    /// @param to 
    /// @return to节点
    iterator erase( iterator from, iterator to ){
        for( iterator itr = from; itr != to; )
        itr = erase( itr );
        return to;
    }
    
    private:
    int theSize;
    Node *head;
    Node *tail;
    /// @brief init函数设置了链表大小，创建了头尾节点
    void init( ){
        theSize = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }

};
