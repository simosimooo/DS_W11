#include<iostream>
#include<string>
using namespace std;

class Node {
	friend class BSTMap;
private:
	int key;
	string value;
	Node* parent;
	Node* left;
	Node* right;
public:
	Node(int key,string& value,Node* parent):key(key),value(value),parent(parent),left(nullptr),right(nullptr){}
};

class BSTMap {
private:
	int n;
	Node* root;

	void clear(Node* node) {
		if (node->left)clear(node->left);
		if (node->right)clear(node->right);
		delete node;
		--n;
	}
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
	bool erase(Node* node) {
		if (node == nullptr)return false;
		if (node->left != nullptr && node->right != nullptr) {
			Node* successor = get_successor(node);
			node->key = successor->key;
			node->value = successor->value;
			node = successor;
		}
		Node* child;
		if (node->left != nullptr)child = node->left;
		else child = node->right;
		if (node == root) {
			root = child;
			if (child != nullptr)child->parent = nullptr;
		}
		else {
			Node* parent = node->parent;
			if (child != nullptr)child->parent = parent;
			if (node == parent->left)parent->left = child;
			else parent->right = child;
		}
		delete node;
		--n;
		return true;
	}
public:
	BSTMap():n(0),root(nullptr){}
	~BSTMap() {
		if (!empty())clear(root);
	}
	int size() { return n; }
	bool empty() { return size() == 0; }
	string find(int key) {
		Node* cur = find_entry(key);
		if (cur == nullptr)return "";
		return cur->value;
	}
	bool insert(int key, string value) {
		if (empty()) {
			root = new Node(key, value, nullptr);
			++n;
			return true;
		}
		Node* cur = root;
		Node* parent = nullptr;
		while (cur != nullptr) {
			if (key == cur->key)return false;
			parent = cur;
			if (key < cur->key)cur = cur->left;
			else cur = cur->right;
		}
		Node* newNode = new Node(key, value, parent);
		if (key < parent->key)parent->left = newNode;
		else parent->right = newNode;
		++n;
		return true;
	}
	bool erase(int key) {
		return erase(find_entry(key));
	}
};