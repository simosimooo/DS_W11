#include<iostream>
#include<string>
using namespace std;

class Node {
	friend class BSTMap;
private:
	int key;
	Node* parent;
	Node* left;
	Node* right;
public:
	Node(int key,Node* parent):key(key),parent(parent),left(nullptr),right(nullptr){}
};

class BSTMap {
private:
	int n;
	Node* root;

	Node* find_entry(int key) {
		Node* cur = root;
		while (cur != nullptr) {
			if (key == cur->key)return cur;
			if (key < cur->key)cur = cur->left;
			else cur = cur->right;
		}
		return nullptr;
	}
	Node* get_successor(Node* node) {
		if (node->right) {
			Node* cur = node->right;
			while (cur->left)cur = cur->left;
			return cur;
		}
		Node* cur = node;
		Node* parent = node->parent;
		while (parent && cur == parent->right) {
			cur = parent;
			parent = parent->parent;
		}
		return parent;
	}
	void erase(Node* node) {
		if (node == nullptr)return;
		if (node->left != nullptr && node->right != nullptr) {
			Node* successor = get_successor(node);
			node->key = successor->key;
			node = successor;
		}
		Node* child;
		if (node->left)child = node->left;
		else child = node->right;
		if (node == root) {
			root = child;
			if (child != nullptr)child->parent = nullptr;
		}
		else {
			Node* parent = node->parent;
			if(child!=nullptr)child->parent = parent;
			if (node == parent->left)parent->left = child;
			else parent->right = child;
		}
		delete node;
		--n;
	}
public:
	BSTMap():n(0),root(nullptr){}
	int size() { return n; }
	bool empty() { return size() == 0; }
	void insert(int x) {
		if (empty()) {
			root = new Node(x, nullptr);
			++n;
			return;
		}
		Node* cur = root;
		Node* parent = nullptr;
		while (cur != nullptr) {
			parent = cur;
			if (x < cur->key)cur = cur->left;
			else cur = cur->right;
		}
		Node* newNode = new Node(x, parent);
		if (x < parent->key)parent->left = newNode;
		else parent->right = newNode;
		++n;
	}
	void Delete(int x) {
		erase(find_entry(x));
	}
	void max(int k) {
		Node* cur = root;
		if (cur->left) {
			while (cur->left)cur = cur->left;
		}
		for (int i{ 0 }; i < size() - k; ++i) {
			cur = get_successor(cur);
		}
		cout << cur->key << '\n';
	}
};

int main() {
	int T;
	cin >> T;
	while (T--) {
		int N;
		cin >> N;
		BSTMap tree;
		while (N--) {
			string cmd;
			cin >> cmd;
			if (cmd == "insert") {
				int x;
				cin >> x;
				tree.insert(x);
			}
			else if (cmd == "delete") {
				int x;
				cin >> x;
				tree.Delete(x);
			}
			else if (cmd == "max") {
				int k;
				cin >> k;
				tree.max(k);
			}
		}
	}
}