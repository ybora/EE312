#include <iostream>
#include <stdlib.h>

using namespace std;
template <typename T>
class BinarySearchTree {
	private:
		int max(int a, int b) {
			return a > b ? a : b;
		}

	class Node {
		public:
			T data;
			Node* left;
			Node* right;

		Node(T data) {
			this->data = data;
			left = nullptr;
			right = nullptr;
		}
	};

	public:
		Node* root;

	BinarySearchTree() {
		root = nullptr;
	}

	~BinarySearchTree() {

	}

	void deleteHelper(Node* current) {
		delete current;
	}

	void insert(T data, Node*& current) {
		if (current == nullptr) {
			current = new Node(data);
		} else if (data > current->data) {
			insert(data, current->right);
		} else {
			insert(data, current->left);
		}
	}

	Node* search(T data, Node*& current) {
		if (current == nullptr)
			return nullptr;
		if (current->data == data) {
			return current;
		} else if (data > current->data) {
			return search(data, current->right);
		} else {
			return search(data, current->left);
		}
	}
	void inOrder(Node*& current) {
		if (current == nullptr) return;
		inOrder(current->left);
		cout << current->data << endl;
		inOrder(current->right);
	}

	int height(Node* current) {
		if (current == nullptr) return 0;
		if (current->left == nullptr && current->right == nullptr) return 0;
		return max(height(current->left) + 1, height(current->right) + 1);
	}	

};

// int main() {
// 	BinarySearchTree<int> bst = BinarySearchTree<int>();
// 	bst.insert(4, bst.root);
// 	bst.insert(2, bst.root);
// 	bst.insert(6, bst.root);
// 	bst.insert(1, bst.root);
// 	bst.insert(3, bst.root);
// 	bst.insert(-1, bst.root);
// 	if (bst.search(2, bst.root) != NULL)
// 		cout << bst.search(2, bst.root)->data << endl;
// 	cout << bst.height(bst.root) << endl;
// }







