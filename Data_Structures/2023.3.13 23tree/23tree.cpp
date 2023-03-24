#include <iostream>
#include<vector>
#include<queue>
#include<string>
using namespace std;

template <typename T>
class ThreeOrderedTree {
private:
	struct Node
	{
		// remember!!! ele is just a pointer	
		T* ele[4];

		// Child pointers
		Node* child[4];
		Node* parent;
		// Constructor to initialize the node with one value. The other value 
		// pointers will be set to nullptr and all child pointers will be set to nullptr. 
		// The pointer given as the parameter is directly copied to ele1.
		Node(){}

		Node(T* valueForele1)
		{
			ele[0] = valueForele1;
			ele[1] = ele[2] = ele[3] = nullptr;
			child[0] = child[1] = child[2] = child[3] = nullptr;
			parent = nullptr;
		}

		Node(T* valueForele1, T* valueForele2)
		{
			ele[0] = valueForele1;
			ele[1] = valueForele2;
			ele[2] = ele[3] = nullptr;
			child[0] = child[1] = child[2] = child[3] = nullptr;
			parent = nullptr;
		}

		// Constructor to initialize the node with one value and two child pointers.
		Node(T* valueForele1, Node* leftChildOfele1, Node* rightChildOfele1)
		{
			ele[0] = valueForele1;
			child[0] = leftChildOfele1;
			child[1] = rightChildOfele1;

			// Everything else is nullptr
			ele[1] = ele[2] = ele[3] = nullptr;
			child[2] = child[3] = nullptr;
			parent = nullptr;
		}

		Node(T* ele1Val, T* ele2Val, Node* left, Node* m, Node* right)
		{
			ele[0] = ele1Val;
			ele[1] = ele2Val;
			ele[2] = ele[3] = nullptr;
			child[0] = left;
			child[1] = m;
			child[2] = right;
			child[3] = nullptr;
			parent = nullptr;
		}


		bool ContainsKey(T key)
		{
			if (ele[3] && *ele[3] == key) { return true; }
			if (ele[2] && *ele[2] == key) { return true; }
			if (ele[1] && *ele[1] == key) { return true; }
			if (ele[0] && *ele[0] == key) { return true; }
			return false;
		}

		T* FindsKey(T key)
		{
			if (ele[3] && *ele[3] == key) { return ele[3]; }
			if (ele[2] && *ele[2] == key) { return ele[2]; }
			if (ele[1] && *ele[1] == key) { return ele[1]; }
			if (ele[0] && *ele[0] == key) { return ele[0]; }
			return nullptr;
		}

		void DeleteData()
		{
			if (ele[3]) { delete ele[3]; ele[3] = nullptr; }
			if (ele[2]) { delete ele[2]; ele[2] = nullptr; }
			if (ele[1]) { delete ele[1]; ele[1] = nullptr; }
			if (ele[0]) { delete ele[0]; ele[0] = nullptr; }
		}

		// Returns true if all two data-value pointers are non-null, 
		// false otherwise.
		bool IsFull()
		{
			if (!IsLeaf())//not a leaf
				return (ele[0] != nullptr && ele[1] != nullptr);
			else
				return (ele[0] != nullptr && ele[1] != nullptr && ele[2] != nullptr);
		}

		// Returns true if all 3 child pointers are null,
		// implying that the node is a leaf
		bool IsLeaf()
		{
			return (child[0] == nullptr && child[1] == nullptr && child[2] == nullptr && child[3] == nullptr);
		}

		int ValueCount()
		{
			if (ele[3]) { return 4; }
			else if (ele[2]) { return 3; }
			else if (ele[1]) { return 2; }
			else if (ele[0]) { return 1; }
			// Should never come here
			return 0;
		}

		void split() {
			if (IsLeaf()) {

				//case 1:the leaf is a root
				if (parent == nullptr) {
					parent = new Node(new T(*ele[2]), this, new Node(ele[2],ele[3]));
					parent->child[0]->parent = parent;
					parent->child[1]->parent = parent;
					ele[2]=ele[3]=nullptr;
					
					return;
				}
				else if (!parent->IsFull()) {

					//case 2:the parent has 1 key
					if (this == parent->child[0]) {
						parent->ele[1] = parent->ele[0];
						parent->ele[0] = new T(*ele[2]);
						parent->child[2] = parent->child[1];
						parent->child[1] = new Node(new T(*ele[2]), new T(*ele[3]));
						parent->child[1]->parent = parent;
						delete ele[2]; delete ele[3];
						ele[2] = ele[3] = nullptr;
						return;
					}
					else if (this == parent->child[1]) {
						
						parent->ele[1] = new T(*ele[2]);
						parent->child[2] = new Node(new T(*ele[2]), new T(*ele[3]));
						parent->child[2]->parent = parent;
						delete ele[2]; delete ele[3];
						ele[2] = ele[3] = nullptr;
						
						return;
					}
				}
				else if (parent->IsFull()) {
					
					//case 2:the parent has 2 keys
						//case 2a :"*this" is child[0]
					if (this == parent->child[0]) {
						parent->ele[2] = parent->ele[1];
						parent->ele[1] = parent->ele[0];
						parent->ele[0] = new T(*ele[2]);
						parent->child[3] = parent->child[2];
						parent->child[2] = parent->child[1];
						parent->child[1] = new Node(new T(*ele[2]), new T(*ele[3]));
						parent->child[1]->parent = parent;
						delete ele[2]; delete ele[3];
						ele[2] = ele[3] = nullptr;
					}
					else if (this == parent->child[1]) {

						//case 2b :"*this" is child[1]
						parent->ele[2] = parent->ele[1];
						parent->ele[1] = new T(*ele[2]);
						parent->child[3] = parent->child[2];
						parent->child[2] = new Node(new T(*ele[2]), new T(*ele[3]));
						parent->child[2]->parent = parent;
						delete ele[2]; delete ele[3];
						ele[2] = ele[3] = nullptr;
					}
					else if (this == parent->child[2]) {

						//case 2c :"*this" is child[2]
						parent->ele[2] = new T(*ele[2]);
						parent->child[3] = new Node(new T(*ele[2]), new T(*ele[3]));
						parent->child[3]->parent = parent;
						delete ele[2]; delete ele[3];
						ele[2] = ele[3] = nullptr;
						
					}
					//time to iterate
					parent->split();
				}
			}
			else if (!IsLeaf()) {
				if (parent == nullptr) {
					Node* temp = new Node(new T(*ele[2]), child[2], child[3]);
					child[2]->parent = child[3]->parent =temp;
					delete ele[1]; delete ele[2];
					ele[1] = ele[2] = nullptr;
					child[2] = child[3] = nullptr;
					Node* temp2 = FindMin(temp);
					parent = new Node(new T(*(temp2->ele[0])), this, temp);
					this->parent=parent;
					parent->child[1]->parent = parent;
					return;
				}
				else if (!parent->IsFull()) {
					//the parent has 1 key
					if (this == parent->child[0]) {
						Node* temp = new Node(new T(*ele[2]), child[2], child[3]);
						child[2]->parent = child[3]->parent =temp;
						delete ele[1]; delete ele[2];
						ele[1] = ele[2] = nullptr;
						child[2] = child[3] = nullptr;
						parent->ele[1] = parent->ele[0];
						Node* temp2 = FindMin(temp);
						parent->ele[0] = new T(*(temp2->ele[0]));
						parent->child[2] = parent->child[1];
						parent->child[1] = temp;
						parent->child[1]->parent = parent;
						return;
					}
					else if (this == parent->child[1]) {
						Node* temp = new Node(new T(*ele[2]), child[2], child[3]);
						child[2]->parent = child[3]->parent =temp;
						delete ele[1]; delete ele[2];
						ele[1] = ele[2] = nullptr;
						child[2] = child[3] = nullptr;
						parent->child[2] = temp;
						parent->child[2]->parent = parent;
						Node* temp2 = FindMin(temp);
						parent->ele[1] = new T(*(temp2->ele[0]));
						return;
					}
				}
				else if (parent->IsFull()) {
					//case 2:the parent has 2 keys
						//case 2a :"*this" is parent->child[0]
					if (this == parent->child[0]) {
						parent->ele[2] = parent->ele[1];
						parent->ele[1] = parent->ele[0];
						parent->ele[0] = new T(*ele[1]);
						parent->child[3] = parent->child[2];
						parent->child[2] = parent->child[1];
						parent->child[1] = new Node(new T(*ele[2]), child[2], child[3]);
						child[2]->parent = child[3]->parent =parent->child[1];
						parent->child[1]->parent = parent;
						delete ele[1]; delete ele[2];
						ele[1] = ele[2] = nullptr;
						child[2] = child[3] = nullptr;
					}
					else if (this == parent->child[1]) {
						//case 2b :"*this" is parent->child[1]
						parent->ele[2] = parent->ele[1];
						parent->ele[1] = new T(*ele[1]);
						parent->child[3] = parent->child[2];
						parent->child[2] = new Node(new T(*ele[2]), child[2], child[3]);
						child[2]->parent = child[3]->parent =parent->child[2];
						parent->child[2]->parent = parent;
						delete ele[1]; delete ele[2];
						ele[1] = ele[2] = nullptr;
						child[2] = child[3] = nullptr;
					}
					else if (this == parent->child[2]) {
						//case 2b :"*this" is parent->child[2]
						parent->ele[2] = new T(*ele[1]);
						parent->child[3] = new Node(new T(*ele[2]), child[2], child[3]);
						child[2]->parent = child[3]->parent =parent->child[3];
						parent->child[3]->parent = parent;
						delete ele[1]; delete ele[2];
						ele[1] = ele[2] = nullptr;
						child[2] = child[3] = nullptr;
					}
					//time to iterate
					parent->split();
				}


			}
		}

	};

	Node* m_root;

public:
	void Display() {
		Display(m_root);
	}

	void LevelOrderedDisplay(){
		LevelOrderedDisplay(m_root);
	}

	void LevelOrderedDisplay(Node* n){
		vector<string> res;
        queue<Node*> q;
        if (n == NULL) return;
        q.push(n);
        string v;

        while(!q.empty()){
            v.clear();
            
            // 将同一层的节点全部出队
            int size = q.size();
            while (size--){
                Node* temp = q.front();
				v+="[";
				v+=to_string(*temp->ele[0]);
				for(int i=1;i<temp->ValueCount();i++){
					v+=",";
					v+=to_string(*temp->ele[i]);
				}
				v+="]";
				
                if (temp->child[0]) q.push(temp->child[0]);		// 下一层所有节点入队
                if (temp->child[1]) q.push(temp->child[1]);
				if (temp->child[2]) q.push(temp->child[2]);
				if (temp->child[3]) q.push(temp->child[3]);
                q.pop();
            }
            res.push_back(v);	// 存储当前层的节点输出
        }//end while(!q.empty())

		//time to cout
		for (vector<string>::iterator it = res.begin(); it != res.end(); it++) {
			cout << *it << endl;
		}

	}

	void DeleteTree(Node* root)
	{
		if (root)
		{
			root->DeleteData();
			if (root->child[0])
				DeleteTree(root->child[0]);
			if (root->child[1])
				DeleteTree(root->child[1]);
			if (root->child[2])
				DeleteTree(root->child[2]);
			delete root;
		}
		root = nullptr;
	}

	void Display(Node* n)//中序遍历
	{
		if (!n) { return; }//if empty
		if (!n->IsLeaf()) {//not a leaf
			cout << "[" << *(n->ele[0]);
			// There may or may not be a B value
			if (n->ele[1])//if not empty
			{
				cout << "," << *(n->ele[1]) << "]";
			}
			else {
				cout << "]";
			}
			Display(n->child[0]);
			Display(n->child[1]);
			if (n->ele[1])
			{
				Display(n->child[2]);
			}
		}
		else {
			int i = 0;
			if(n->ele[3]) {cout << "fourth occupied!!";}
			cout << "[" << *(n->ele[0]);
			while (n->ele[++i] && i <= 2) {//not empty
				cout << "," << *(n->ele[i]);
			}
			cout << "]";
		}

	}

	static Node* FindMin(Node* root)//find the node containing the smallest element in its subtree
	{
		if (root->IsLeaf())
		{
			return root;
		}

		Node* n = root->child[0];
		while (n->child[0]) { n = n->child[0]; }
		return n;
	}

public:
	ThreeOrderedTree(void)
	{
		m_root = nullptr;
	}

	~ThreeOrderedTree(void)
	{
		DeleteTree(m_root);
		m_root = nullptr;
	}

	T* Find(T key)//find key in node
	{
		Node* n_ptr = m_root;

		T* result = n_ptr->FindsKey(key);

		if (result) { return result; }//if found
		else
		{
			if (n_ptr->ele[1] && *(n_ptr->ele[1]) < key)
			{
				return Find(key, n_ptr->child[2]);
			}
			else if (n_ptr->ele[0] && *(n_ptr->ele[0]) < key)
			{
				return Find(key, n_ptr->child[1]);
			}
			else
			{
				return Find(key, n_ptr->child[0]);
			}
		}

		return nullptr;
	}

	T* Find(T const& key, Node*& n_ptr)
	{
		if (!n_ptr)
			return nullptr;

		T* result = n_ptr->FindsKey(key);
		if (result) { return result; }
		else
		{
			if (n_ptr->ele[1] && *(n_ptr->ele[1]) < key)
			{
				return Find(key, n_ptr->child[2]);
			}
			else if (n_ptr->ele[0] && *(n_ptr->ele[0]) < key)
			{
				return Find(key, n_ptr->child[1]);
			}
			else
			{
				return Find(key, n_ptr->child[0]);
			}
		}
	}

	T* GetMin()//find the min element in the tree
	{
		if (!m_root) { return nullptr; }
		Node* n = FindMin(m_root);
		return n->ele[0];
	}


	bool Add(T& toCopyAndAdd)
	{
		// Create root node if 2-3 tree is empty
		if (m_root == nullptr)
		{
			m_root = new Node(new T(toCopyAndAdd));
			return true;
		}

		T key = toCopyAndAdd;

		Node* n_ptr = m_root;  // traversing pointer

		while (!n_ptr->IsLeaf()) {//when not leaf,get to the leaf where key should be
			if (2 == n_ptr->ValueCount()) {
				if (key < *(n_ptr->ele[0]))
					n_ptr = n_ptr->child[0];
				else if (key == *(n_ptr->ele[0]))
					n_ptr = FindMin(n_ptr->child[1]);
				else if (key < *(n_ptr->ele[1]))
					n_ptr = n_ptr->child[1];
				else if (key == *(n_ptr->ele[1]))
					n_ptr = FindMin(n_ptr->child[2]);
				else
					n_ptr = n_ptr->child[2];
			}
			else if (1 == n_ptr->ValueCount()) {
				if (key < *(n_ptr->ele[0]))
					n_ptr = n_ptr->child[0];
				else if (key == *(n_ptr->ele[0]))
					n_ptr = FindMin(n_ptr->child[1]);
				else if (key > *(n_ptr->ele[0]))
					n_ptr = n_ptr->child[1];
			}
		}

		// Check for duplicates
		if (n_ptr->ContainsKey(key)) {
			cout << "Key " << key << " is duplicated" << endl;
			return false;
		}

		/*** CASE 2: Is it a leaf node ***/
		if (n_ptr->IsLeaf())
		{
			// Case 2a: Has 1 key
			if (1 == n_ptr->ValueCount())
			{
				if (key > *(n_ptr->ele[0]))
				{
					n_ptr->ele[1] = new T(toCopyAndAdd);
					return true;
				}
				else if (key < *(n_ptr->ele[0]))
				{
					T* temp = new T(toCopyAndAdd);
					n_ptr->ele[1] = n_ptr->ele[0];
					n_ptr->ele[0] = temp;
					return true;
				}
			} // end Case 2a


			// Case 2b: Has 2 keys
			else if (2 == n_ptr->ValueCount())
			{
				if (key > *(n_ptr->ele[1]))
				{
					n_ptr->ele[2] = new T(toCopyAndAdd);
					return true;
				}
				else if (key > *(n_ptr->ele[0]))
				{
					T* temp = new T(toCopyAndAdd);
					n_ptr->ele[2] = n_ptr->ele[1];
					n_ptr->ele[1] = temp;
					return true;
				}
				else if (key < *(n_ptr->ele[0]))
				{
					T* temp = new T(toCopyAndAdd);
					n_ptr->ele[2] = n_ptr->ele[1];
					n_ptr->ele[1] = n_ptr->ele[0];
					n_ptr->ele[0] = temp;
					return true;
				}
			} // end Case 2b

			// Case 2b: Has 3 keys
			else if (3 == n_ptr->ValueCount())
			{
				if (key > *(n_ptr->ele[2]))
				{
					n_ptr->ele[3] = new T(toCopyAndAdd);
				}
				else if (key > *(n_ptr->ele[1]))
				{
					T* temp = new T(toCopyAndAdd);
					n_ptr->ele[3] = n_ptr->ele[2];
					n_ptr->ele[2] = temp;
				}
				else if (key > *(n_ptr->ele[0]))
				{
					T* temp = new T(toCopyAndAdd);
					n_ptr->ele[3] = n_ptr->ele[2];
					n_ptr->ele[2] = n_ptr->ele[1];
					n_ptr->ele[1] = temp;
				}
				else {
					T* temp = new T(toCopyAndAdd);
					n_ptr->ele[3] = n_ptr->ele[2];
					n_ptr->ele[2] = n_ptr->ele[1];
					n_ptr->ele[1] = n_ptr->ele[0];
					n_ptr->ele[0] = temp;
				}
				n_ptr->split();
				while(m_root->parent !=nullptr){
					m_root=m_root->parent;
				}
				return true;
			}

		} // end Case 2


	  // Should never get here!
		return false;
	}

};

int main() {
	ThreeOrderedTree<int> tree;
	int n;
	cin >> n;
	int a[10000];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		tree.Add(a[i]);
	}
	tree.LevelOrderedDisplay();
	return 0;
}