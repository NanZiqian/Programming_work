#ifndef BINOMIAL_QUEUE_H
#define BINOMIAL_QUEUE_H

#include <iostream>
#include <vector>
//#include "dsexceptions.h"
using namespace std;

// Binomial queue class
//
// CONSTRUCTION: with no parameters
//
// ******************PUBLIC OPERATIONS*********************
// void Insert( x )       --> Insert x
// void DeleteMin( )      --> Return and remove smallest item
// Comparable GetMin( )   --> Return smallest item
// bool Empty( )          --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void Merge( rhs )      --> Absorb rhs into this heap
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinomialQueue;

template <typename Comparable>
class BinomialNode
{
private:
    Comparable    element;
    BinomialNode* leftChild;
    BinomialNode* nextSibling;
    BinomialNode* parent;

    friend class BinomialQueue<Comparable>;

public:
    BinomialNode(const Comparable& e, BinomialNode* lt, BinomialNode* rt)
        : element{ e }, leftChild{ lt }, nextSibling{ rt }, parent{ nullptr } { }

    BinomialNode(Comparable&& e, BinomialNode* lt, BinomialNode* rt)
        : element{ std::move(e) }, leftChild{ lt }, nextSibling{ rt }, parent{ nullptr } { }

    Comparable GetElement()const
    {
        return element;
    }
};

template <typename Comparable>
class BinomialQueue
{
public:
    BinomialQueue() : theTrees(DEFAULT_TREES)
    {
        for (auto& root : theTrees)
            root = nullptr;
        currentSize = 0;
    }

    BinomialQueue(const Comparable& item) : theTrees(1), currentSize{ 1 }
    {
        theTrees[0] = new BinomialNode<Comparable>{ item, nullptr, nullptr };
    }

    BinomialQueue(const BinomialQueue& rhs)
        : theTrees(rhs.theTrees.size()), currentSize{ rhs.currentSize }
    {
        for (int i = 0; i < rhs.theTrees.size(); ++i)
            theTrees[i] = clone(rhs.theTrees[i]);
    }

    BinomialQueue(BinomialQueue&& rhs)
        : theTrees{ std::move(rhs.theTrees) }, currentSize{ rhs.currentSize }
    {
    }

    ~BinomialQueue()
    {
        makeEmpty();
    }


    /**
     * Deep copy.
     */
    BinomialQueue& operator=(const BinomialQueue& rhs)
    {
        BinomialQueue copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    /**
     * Move.
     */
    BinomialQueue& operator=(BinomialQueue&& rhs)
    {
        std::swap(currentSize, rhs.currentSize);
        std::swap(theTrees, rhs.theTrees);

        return *this;
    }

    /**
     * Return true if empty; false otherwise.
     */
    bool Empty() const
    {
        return currentSize == 0;
    }

    int getnum(){
      return currentSize;
    }

    /**
     * Returns minimum item.
     * Throws UnderflowException if empty.
     */
    const BinomialNode<Comparable>* GetMin() const
    {
        //if( isEmpty( ) )
            //throw UnderflowException{ };

        return theTrees[findMinIndex()];
    }

    /**
     * Insert item x into the priority queue; allows duplicates.
     */
    BinomialNode<Comparable>* Insert(const Comparable& x)
    {
        BinomialQueue oneItem{ x }; return Merge(oneItem);
    }

    /**
     * Insert item x into the priority queue; allows duplicates.
     */
    BinomialNode<Comparable>* Insert(Comparable&& x)
    {
        BinomialQueue oneItem{ std::move(x) }; return Merge(oneItem);
    }

    /**
     * Remove the smallest item from the priority queue.
     * Throws UnderflowException if empty.
     */
    void DeleteMin()
    {
        Comparable x;
        DeleteMin(x);
    }

    /**
     * Remove the minimum item and place it in minItem.
     * Throws UnderflowException if empty.
     */
    void DeleteMin(Comparable& minItem)
    {
        //if( isEmpty( ) )
            //throw UnderflowException{ };

        int minIndex = findMinIndex();
        minItem = theTrees[minIndex]->element;
        //cout<<"Deleted: ( " << minItem.second << " , " << minItem.first <<")"<<endl;

        BinomialNode<Comparable>* oldRoot = theTrees[minIndex];
        BinomialNode<Comparable>* deletedTree = oldRoot->leftChild;
        //deletedTree是pldRoot的第一个左孩子
        delete oldRoot;

        // Construct H''
        BinomialQueue deletedQueue;
        deletedQueue.theTrees.resize(minIndex);
        deletedQueue.currentSize = (1 << minIndex) - 1;
        for (int j = minIndex - 1; j >= 0; --j)
        {
            deletedQueue.theTrees[j] = deletedTree;
            deletedTree = deletedTree->nextSibling;
            deletedQueue.theTrees[j]->parent = nullptr;
            deletedQueue.theTrees[j]->nextSibling = nullptr;
        }

        // Construct H'
        theTrees[minIndex] = nullptr;
        currentSize -= deletedQueue.currentSize + 1;

        Merge(deletedQueue);
    }

    /**
     * Make the priority queue logically empty.
     */
    void makeEmpty()
    {
        currentSize = 0;
        for (auto& root : theTrees)
            makeEmpty(root);
    }

    void printqueue(){
      for (auto& root : theTrees)
        printnode(root);
    }

    void printnode(BinomialNode<Comparable>*& t){
      if (t != nullptr)
        {
            printnode(t->leftChild);
            printnode(t->nextSibling);
            cout <<"( " << t->element.second << " , "<<t->element.first<< ")" << endl;
        }
    }

    /**
     * Merge rhs into the priority queue.
     * rhs becomes empty. rhs must be different from this.
     * Exercise 6.35 needed to make this operation more efficient.
     */
    BinomialNode<Comparable>* Merge(BinomialQueue& rhs)
    {
        if (this == &rhs)    // Avoid aliasing problems
            return nullptr;

        currentSize += rhs.currentSize;

        if (currentSize > capacity())
        {
            int oldNumTrees = theTrees.size();
            int newNumTrees = max(theTrees.size(), rhs.theTrees.size()) + 1;
            theTrees.resize(newNumTrees);
            for (int i = oldNumTrees; i < newNumTrees; ++i)
                theTrees[i] = nullptr;
        }

        BinomialNode<Comparable>* oneitem_p=rhs.theTrees[0];

        BinomialNode<Comparable>* carry = nullptr;
        for (int i = 0, j = 1; j <= currentSize; ++i, j *= 2)
        {
            BinomialNode<Comparable>* t1 = theTrees[i];
            BinomialNode<Comparable>* t2 = i < rhs.theTrees.size() ? rhs.theTrees[i] : nullptr;

            int whichCase = t1 == nullptr ? 0 : 1;
            whichCase += t2 == nullptr ? 0 : 2;
            whichCase += carry == nullptr ? 0 : 4;

            switch (whichCase)
            {
            case 0: /* No trees */
            case 1: /* Only this */
                break;
            case 2: /* Only rhs */
                theTrees[i] = t2;
                rhs.theTrees[i] = nullptr;
                break;
            case 4: /* Only carry */
                theTrees[i] = carry;
                carry = nullptr;
                break;
            case 3: /* this and rhs */
                carry = combineTrees(t1, t2);
                theTrees[i] = rhs.theTrees[i] = nullptr;
                break;
            case 5: /* this and carry */
                carry = combineTrees(t1, carry);
                theTrees[i] = nullptr;
                break;
            case 6: /* rhs and carry */
                carry = combineTrees(t2, carry);
                rhs.theTrees[i] = nullptr;
                break;
            case 7: /* All three */
                theTrees[i] = carry;
                carry = combineTrees(t1, t2);
                rhs.theTrees[i] = nullptr;
                break;
            }
        }

        for (auto& root : rhs.theTrees)
            root = nullptr;

        if (rhs.currentSize==1){
          rhs.currentSize = 0;
          return oneitem_p;
        }

        rhs.currentSize = 0;
        return nullptr;
    }

    void DecreaseKey(BinomialNode<Comparable>* x,Comparable d){
      x->element=d;
      while (x->parent != nullptr && x->element < x->parent->element) {
            SwapNodeValues(x, x->parent);
            x = x->parent;
        }
    }


private:


    const static int DEFAULT_TREES = 1;

    vector<BinomialNode<Comparable>*> theTrees;  // An array of tree roots
    int currentSize;                  // Number of items in the priority queue

    /**
     * Find index of tree containing the smallest item in the priority queue.
     * The priority queue must not be empty.
     * Return the index of tree containing the smallest item.
     */
    int findMinIndex() const
    {
        int i;
        int minIndex;

        for (i = 0; theTrees[i] == nullptr; ++i)
            ;

        for (minIndex = i; i < theTrees.size(); ++i)
            if (theTrees[i] != nullptr &&
                theTrees[i]->element < theTrees[minIndex]->element)
                minIndex = i;

        return minIndex;
    }

    /**
     * Return the capacity.
     */
    int capacity() const
    {
        return (1 << theTrees.size()) - 1;
    }

    /**
     * Return the result of merging equal-sized t1 and t2.
     */
    BinomialNode<Comparable>* combineTrees(BinomialNode<Comparable>* t1, BinomialNode<Comparable>* t2)
    {
        if (t2->element < t1->element)
            return combineTrees(t2, t1);
        t2->nextSibling = t1->leftChild;
        t2->parent=t1;
        t1->leftChild = t2;
        return t1;
    }

    /**
     * Make a binomial tree logically empty, and free memory.
     */
    void makeEmpty(BinomialNode<Comparable>*& t)
    {
        if (t != nullptr)
        {
            makeEmpty(t->leftChild);
            makeEmpty(t->nextSibling);
            delete t;
            t = nullptr;
        }
    }

    /**
     * Internal method to clone subtree.
     */
    BinomialNode<Comparable>* clone(BinomialNode<Comparable>* t) const
    {
        if (t == nullptr)
            return nullptr;
        else
            return new BinomialNode<Comparable>{ t->element, clone(t->leftChild), clone(t->nextSibling) };
    }

    void SwapNodeValues(BinomialNode<Comparable>* node1, BinomialNode<Comparable>* node2) {
        Comparable temp_value = node1->element;
        node1->element = node2->element;
        node2->element = temp_value;
    }
};

#endif
