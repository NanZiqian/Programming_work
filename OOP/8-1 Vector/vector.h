#include<iostream>
#include <type_traits>

using namespace std;

class OutOfRange{
public:
    OutOfRange(): m_flag(1){ };
    OutOfRange(int len, int index): m_len(len), m_index(index), m_flag(2){ }
    void what() const{
        if(m_flag == 1){
            cout<<"Error: empty vector, no elements to pop."<<endl;
        }else if(m_flag == 2){
            cout<<"Error: out of range( vector size "<<m_len<<", access index "<<m_index<<" )"<<endl;
        }else{
            cout<<"Unknown exception."<<endl;
        }
    }
private:
    int m_flag;  //不同的flag表示不同的错误
    int m_len;  //当前数组的长度
    int m_index;  //当前使用的数组下标
};

template<typename T>
class Vector{
public:
    Vector(int size=0){
        m_nSize=0;
        m_nCapacity=size;
        if(size < 0){
            cout << "input error!" << endl;
            system("pause");
            exit(0);
        }else if(size == 0){
            m_nCapacity=5;
        }
        m_pElements = initialize(m_nCapacity);
    }

    Vector(Vector<T> & rhs){
        m_nSize = rhs.size();
        m_nCapacity = 2*m_nSize;
        m_pElements = Vector_copy(rhs,m_nSize);
    }

    ~Vector(){
        delete m_pElements;
    }

    /// @brief use this after clear()
    void resize(int capacity=5){
        clear();
        if(capacity<=0){
            capacity = 5;
        }
        m_pElements = initialize(capacity);
    }

    /// @brief if x <= size, OK!
    //if x > size <= capacity, no need to inflate; but get [size,x] to default.
    //if x > capcity inflate!
    /// @param x 
    /// @return 
    T& operator[](int x){
        inflate(x+1);
        return m_pElements[x];
    }

    T& at(int index){
        if (index<0 || index>=m_nSize){
            throw OutOfRange(m_nSize,index);
        }
        return m_pElements[index];
    }

    int size() const{
        return m_nSize;
    }

    int capacity() const{
        return m_nCapacity;
    }

    void push_back(const T& x){
        m_pElements[m_nSize++] = x;
        inflate();
    }

    void clear(){
        if(m_pElements!=nullptr)
            delete m_pElements;
        m_nSize = m_nCapacity = 0;
    }

    int empty(){
        if(m_nSize == 0){
            return 1;
        }
        return 0;
    }

    void print(){
        if(m_nSize > 0){
            cout <<"printing : ";
            for(int i=0;i<m_nSize;i++){
                cout << m_pElements[i] << " " ;
            }
            cout << endl;
        }
        cout << "Size: " << m_nSize << ". Capacity: " << m_nCapacity << endl;
    }

private:

    T *m_pElements;                // pointer to the dynamically allocated storage
    int m_nSize;                   // the number of elements in the container
    int m_nCapacity;               // the total number of elements that can be held in the allocated storage

    /// @brief run this function if there is potential risk of out_of_range
    //normally index = m_nSize - 1; unless operator[].
    void inflate(){
        inflate(m_nSize);
    }
    void inflate(int size){
        if(size < 0){
            cout << "index < 0! Exiting." << endl;
            system("pause");
            exit(0);
        }else if(size == 0){
            cout << "why need to inflate(0)?" << endl;
            system("pause");
            exit(0);
        }
        
        if(size <= m_nSize && m_nSize < m_nCapacity){
            //case 1a: operator[< m-nSize - 1]
            //case 1b: after push_back, size < capacity
                //don't need anything
            return;
        }else if (size > m_nSize && size < m_nCapacity){
            //case 2: operator[< m-nCapcity - 1]
                //initialize [m_nSize,index], set m_nSize as size.
            m_nSize = size;
        }else if(size >= m_nCapacity){
            //case 3a: operator[ >= m_ncapacity - 1] , =m_nCapacity means size = capacity.
            //case 3b: after push_back, m_nSize == m_nCapacity
                //set m_nSize as size, set m_nCapacity double of index.
            T * m_temp = Vector_copy(*this,size);
            clear();
            m_pElements = m_temp;
            m_nSize = size;
            m_nCapacity = 2*m_nSize;
        } 
    }

    /// @brief used in ctor and Vector_copy. need m_nCapacity preset.
    //including initializing for int float, and char.
    T * initialize(int capacity){
        T * elements;
        if(capacity == 0){
            elements = nullptr;
            return elements;
        }
        //new space of m_nCapacity
        elements = new T[capacity];
        //if T is customized then all have been initialized
        if(std::is_same<int, T>::value || std::is_same<float, T>::value)
            for(int i=0;i<capacity;i++)
                elements[i] = 0;
        else if(std::is_same<char, T>::value)
            for(int i=0;i<capacity;i++)
                elements[i] = '\0';
        return elements;
    }

    /// @brief copy [0,size) to a new T[], initialize [size, capacity) , return its pointer.
    /// @return 
    T * Vector_copy(Vector<T> & rhs, int size){
        T * temp;
        if(size < 0){
            cout << "size < 0! Exiting." << endl;
            system("pause");
            exit(0);
        }else if(size == 0){
            return nullptr;
        }else{
            temp = initialize(2*size);
            for(int i=0;i<size;i++){
                temp[i]=rhs.at(i);
            }
            return temp;
        }
        cout << "should never get here." << endl;
        return nullptr;
    }
};
