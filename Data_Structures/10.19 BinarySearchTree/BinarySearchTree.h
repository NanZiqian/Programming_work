#include<iostream>
using namespace std;
#include<vector>


vector<int> v_global;
template <typename T>
class BinarySearchTree{
public:
    BinarySearchTree( ): root(nullptr){}
    BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }{
        root = clone( rhs.root );
    }
    BinarySearchTree( BinarySearchTree && rhs ): root{ nullptr }{
        root = clone( rhs.root );
    }
    ~BinarySearchTree(){
        makeEmpty();
    }


    /// @brief 所有的以下形式的函数都是为了传递私有引用，实现共有函数操作私有属性
    /// @return 
    const T & findMin( ) const{
        findMin(root);
    }
    const T & findMax( ) const{
        findMin(root);
    }
    
    /// @brief 如果x在树中则Return 1
    /// @param x 
    /// @return 1
    bool contains( const T & x ) const{
        return contains(x, root);
    }
    /// @brief 如果是空的则return 1
    /// @return 1/0
    bool isEmpty( ) const{
        return isEmpty(root);
    }
    /// @brief 从小到大打印所有数据
    /// @param out 
    void printTree( ostream & out = cout ) const{
        printTree(root,out);
    }

    /// @brief 将删除root的数据及子树的数据
    void makeEmpty( ){
        makeEmpty(root);
    }


    /// @brief 插入元素为x的结点; 不考虑重复的情况
    /// @param x 
    void insert( const T & x ){
        insert( x, root );
    }
    void insert( T && x ){
        insert( x, root );
    }

    /// @brief x存在时移除x，x不存在时不操作
    /// @param x 
    void remove( const T & x ){
        remove( x, root );
    }

    /// @brief 我自己加的函数，用于把二叉搜索树转换为vector并进行输出
    /// @return 
    vector<int> CreateVector(){
        MidOrderTraverse(root);
        return v_global;
    }

    /// @brief 未使用，所以未定义
    /// @param rhs 
    /// @return 
    BinarySearchTree & operator=( const BinarySearchTree & rhs );
    BinarySearchTree & operator=( BinarySearchTree && rhs );
    






private:
    /// @brief 二叉树的每一个结点都有数据、左子树指针和右子树指针，将结点的左右子结点指针命名为m_l和m_r方便写函数时确认
    struct BinaryNode{
        T element;
        BinaryNode *m_lchild;
        BinaryNode *m_rchild;

        /// @brief 二叉树结点的构造函数，方便在函数中进行复制。
        /// @param theElement 
        /// @param lt 
        /// @param rt 
        BinaryNode( const T & theElement, BinaryNode *lt, BinaryNode *rt )
        : element{ theElement }, m_lchild{ lt }, m_rchild{ rt } { }
        
        BinaryNode( T && theElement, BinaryNode *lt, BinaryNode *rt )
        : element{ std::move( theElement ) }, m_lchild{ lt }, m_rchild{ rt } { }
    };
    
    BinaryNode *root;



    /// @brief 左子结点为空时，该结点即为最小数，不然递归
    /// @param t 
    /// @return 最小数t
    BinaryNode * findMin( BinaryNode *t ) const{
        if( t == nullptr )
            return nullptr;
        if( t->m_lchild == nullptr )
            return t;
        return findMin( t->m_lchild );
    }


    /// @brief 递归通常很耗资源，用while循环能缓解这一点
    /// @param t 
    /// @return 
    BinaryNode * findMax( BinaryNode *t ) const{
        if( t != nullptr )
            while( t->m_rchild != nullptr )
                t = t->m_rchild;
        return t;
    }


    /// @brief 将结点t及所有的子结点全部释放
    /// @param t 
    void makeEmpty( BinaryNode * & t ){
        if( t != nullptr ){
            makeEmpty( t->m_lchild );
            makeEmpty( t->m_rchild );
            delete t;
        }
        t = nullptr;
    }



    bool isEmpty(BinaryNode *t) {
        if(t == nullptr)
            return 1;
        else
            return 0;
    }



    void printTree( BinaryNode *t, ostream & out ) const{
        if(t == nullptr)
            return;
        else{
            printTree(t->lchild);
            out << t->element << endl;
            printTree(t->rchild);
        }
    }



    /// @brief 递归复制结点及所有的子结点
    /// @param t 
    /// @return new 包含所有数据的BinaryNode
    BinaryNode * clone( BinaryNode *t ) const{
        if( t == nullptr )
            return nullptr;
        else
            return new BinaryNode{ t->element, clone( t->m_lchild ), clone( t->m_rchild ) };
    }


    /// @brief x是在根结点为t的树中搜索的数据
    /// @param x 
    /// @param t 
    /// @return "<"递归至左结点、">"右节点，叶结点搜索不到就return false，出现等于就return true；
    bool contains( const T & x, BinaryNode *t ) const{
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->m_lchild );
        else if( t->element < x )
            return contains( x, t->m_rchild );
        else
            return true; // Match
    }



    /// @brief 不考虑有相同元素，插入x，比结点小去左，大则去右
    /// @param x 
    /// @param t 
    void insert( const T & x, BinaryNode *&t){
        if( t == nullptr )
        {
            t = new BinaryNode{ x, nullptr, nullptr };
            return;
        }
        if( x < t->element )
            insert( x, t->m_lchild );
        else if( t->element < x )
            insert( x, t->m_rchild );
        else ; // Duplicate; do nothing
    }



    /// @brief 常量x的重载
    /// @param x 
    /// @param t 
    void insert( T && x, BinaryNode *&t){
        if( t == nullptr )
            t = new BinaryNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->m_lchild );
        else if( t->element < x )
            insert( std::move( x ), t->m_rchild );
        else ; // Duplicate; do nothing
    }



    /// @brief remove有三种情况，无子结点，有一个和有多个
    /// @param x
    /// @param t 
    void remove( const T & x, BinaryNode *&t){
        if( t == nullptr )
            return; // Item not found; do nothing
        if( x < t->element )
            remove( x, t->m_lchild );
        else if( t->element < x )
            remove( x, t->m_rchild );
        else if( t->m_lchild != nullptr && t->m_rchild != nullptr ){// found and got Two children
            t->element = findMin( t->m_rchild )->element;
            remove( t->element, t->m_rchild );
        }
        else{
        BinaryNode *oldNode = t;//将t移走后将原来的t释放
            t = ( t->m_lchild != nullptr ) ? t->m_lchild : t->m_rchild;
            delete oldNode;
        }
    }

    /// @brief 通过遍历将数据从小到大传入vector v;
    /// @param t 
    /// @param v 
    /// @return 
    void MidOrderTraverse(BinaryNode *t){
        if(t == nullptr)
        return;
	else{
        MidOrderTraverse(t->m_lchild);
		v_global.push_back(t->element);
		MidOrderTraverse(t->m_rchild);
	}
}

};


