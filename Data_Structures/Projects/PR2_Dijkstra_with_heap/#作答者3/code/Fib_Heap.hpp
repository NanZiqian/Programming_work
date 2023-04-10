#ifndef _FIB_HEAP
#define _FIB_HEAP
#include <cmath>
using namespace std;
template <class T> //data field we need
class FibNode //the structure of nodes in FibHeap
{
public:
    FibNode() // initialize a new and empty FibHeap
        : p(nullptr), child(nullptr), left(this), right(this), degree(0), mark(false){};
    FibNode(T value) // initialize a new and empty FibHeap with the data we store
        : p(nullptr), child(nullptr), left(this), right(this), degree(0), mark(false), data(value){};
    ~FibNode() // free the FibHeap
    {
        if(child != nullptr)//delete the non-empty child node
        {
            delete child;
        }
        FibNode *temp = nullptr;
        FibNode *that = this;
        while(that != nullptr)//delete this node
        {
            temp = that;
            that = right;//while pointer move to its right sibling
            delete temp;
        }
    }
    T data; //data field we store
    int degree; //the number of children the node have
    bool mark; //if the node has losen its child after it became someone's child last time
    FibNode *p; //the parent of the node
    FibNode *child; //one of the children of the node
    FibNode *left; //the left siblings of the node
    FibNode *right; //the right siblings of the node
};
template <class T>
class FibHeap  //the structure of FibHeap
{
public:
    typedef FibNode<T> *FibNodePtr;
    FibNodePtr minNode; //point to the minimum root of the whole heap
    FibNodePtr head; //the head of root linked list
    int size; //the number of root nodes in the root linked list
    FibHeap() // initialize a new and empty FibHeap
    {
        minNode = nullptr;
        head = nullptr;
        size = 0;
    }
    ~FibHeap() // free the FibHeap
    {
        FibNodePtr temp = nullptr;
        while(head->right != head) //remove all root nodes from head to the end
        {
            temp = head->right;
            RemoveNode(head);
            delete head;
            head = temp;
        }
        delete head;
        delete minNode; //delete the minimum root of the heap
    }
    void Insert(T value) //insert a node to Fibheap whose datas are "value"
    {
        FibNodePtr temp = new FibNode<T>(value); //allocate memory for newNode
        if (minNode == nullptr)//if minNode is empty, fill it with the new node
        {
            minNode = new FibNode<T>();
            head = new FibNode<T>();
            minNode = temp;
            LeftInsert(head, minNode);//insert minNode to the left of head
        }
        else
        {
            LeftInsert(minNode, temp);//insert temp to the left of minNode
            if (value < minNode->data) //if new value is smaller, adjust the location of minNode
            {
                minNode = temp;//to make sure minNode is the minimum data
            }
        }
        size++;//update the the size of heap
    }
    T DeleteMin()// to delete the minNode and return the value of it 
    {
        T result = minNode->data; //fetch the minimum value
        FibNodePtr tempMin = minNode;
        if (tempMin != nullptr)//ensure the minNode does exist
        {
            FibNodePtr temp = minNode->child;//record the child of minNode
            FibNodePtr next;
            for (int i = 0; i < minNode->degree; i++) //for each child of minNode
            {
                next = temp->right;//record the location of next child
                LeftInsert(head, temp);///insert temp to the left of head in root list
                temp = next;//continue to do it
            }
            RemoveNode(tempMin); //remove the minNode from root list
            if (tempMin == tempMin->right)//if only minNode exists in root list
            {
                minNode = nullptr;//set it as nullptr because it is empty
            }
            else //if still other nodes in root list
            {
                minNode = head->right; //let the node on right of head be minNode temporarily
                Consolidate();//consolidate the root nodes which have the same degree, and find the location of minNode
            }
            size--;//update the size of heap
        }
        return result;//return data of minNode
    }
    bool isEmpty()//recognize the heap is empty or not
    {
        return (size == 0);//size = 0 means it is empty
    }
    void clear()//clear the heap
    {
        size = 0; //size to be zero
        minNode = nullptr;
        head = nullptr; //pointer to be nullptr
    }

private://private functions play in inner space
    void LeftInsert(FibNodePtr old, FibNodePtr cur) //set cur to the left of old
    {
        cur->left = old->left;
        cur->right = old;
        old->left->right = cur;
        old->left = cur;
    }
    void RemoveNode(FibNodePtr node) //to remove node from the current list
    {
        node->left->right = node->right;
        node->right->left = node->left;//just let its siblings pointer to each other
    }
    void Link(FibNodePtr y, FibNodePtr x)//to make y child of x
    {
        RemoveNode(y);//remove y from its current child of root list
        y->p = x; //set y.parent as x

        if (x->child == nullptr)//if x has no child
        {
            x->child = y;//just let x.child pointer to y
            y->left = y->right = y;
        }
        else //if children exist in x'child list
        {
            LeftInsert(x->child, y);//add y into the child list
        }

        x->degree++;//update the degree of x (the number of children x has)
        y->mark = false; //y to be child again, not in the root list
    }
    void Consolidate()//consolidate the root nodes which have the same degree, and find the location of minNode
    {
        int D = (int)log2(size) + 1; //the upper bound of the number of roots
        FibNodePtr *Array = new FibNodePtr[D];//allocate memory for a node array Array
        for (int i = 0; i < D; i++)
        {
            Array[i] = nullptr;//initialize the array Array
        }
        FibNodePtr temp = head->right; //locate one of the root
        FibNodePtr next; //locate the right node of current node 
        do
        {
            if (temp == head)//while iterate all nodes and come back the beginning of root
            {
                break;//exit the loop
            }
            int deg;
            FibNodePtr x, y;
            x = temp;
            deg = x->degree; //record the degree of the current node
            next = temp->right;//store the next location 
            while (Array[deg] != nullptr)//if there has existed a node with same degree in the array
            {
                y = Array[deg];//fetch the existed node as y
                if ((y->data) < (x->data))//compare x and y, if y is smaller
                {
                    swap(x, y);//swap x and y, to ensure x is smaller than y, and x will become the parent of y
                }

                Link(y, x);//set y as the child of x, which means consolidate them
                Array[deg] = nullptr;//clear Array[degree]
                deg++;//after consolidation, the degree of new node will increase, so enter the loop again
            }
            Array[deg] = x;//node x with degree "deg" to store in Array[deg]
            x->degree = deg;
            temp = next;//come to next root node
        } while (temp != head);//until all root node has been traveled
        minNode = nullptr;//clear minNode for the following relinking
        head->left = head->right = head;//clear root list and remain only the empty head
        for (int i = 0; i < D; i++)//iterate the node Array to rebuild the root list
        {
            if (Array[i] != nullptr)//if exist node with degree of i, include it in the list
            {
                if (minNode == nullptr)//if root list is empty
                {
                    minNode = Array[i];
                    LeftInsert(head, minNode);//add it as minNode
                }
                else//if exist nodes in root list
                {
                    LeftInsert(head, Array[i]);//first include it in list
                    if (Array[i]->data < minNode->data)//then update the minNode if new node is smaller than the former one
                    {
                        minNode = Array[i];
                    }
                }
            }
        }
        delete[] Array;//delete the auxiliary array
    }
};
#endif