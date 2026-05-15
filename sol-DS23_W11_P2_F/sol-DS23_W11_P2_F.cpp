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
			node->key=successor->key;
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
			if (parent->left == node)parent->left = child;
			else parent->right = child;
		}
		delete node;
		--n;
	}
	int height(Node* node) {
		if (node == nullptr)return -1;
		int leftH = height(node->left);
		int rightH = height(node->right);
		return 1 + (leftH > rightH ? leftH : rightH);
	}
	int depth(Node* node) {
		int d = 0;
		while (node != root) {
			node = node->parent;
			++d;
		}
		return d;
	}
public:
	BSTMap():n(0),root(nullptr){}
	int size() { return n; }
	bool empty() { return size() == 0; }
	void insert(int x) {
		if (empty()) {
			root = new Node(x, nullptr);
			++n;
			cout << depth(root) << '\n';
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
		cout << depth(newNode) << '\n';
	}
	void Delete(int x) {
		Node* delNode = find_entry(x);
		cout << depth(delNode) << "\n";
		erase(delNode);
	}
	void min(int k) {
		Node* res = root;
		while (res->left)res = res->left;
		for (int i{ 0 }; i < k-1; ++i) {
			res = get_successor(res);
		}
		cout << res->key << '\n';
	}
	void height(int x) {
		cout << height(find_entry(x)) << '\n';
	}
};

int main() {
	int T;
	cin >> T;
	BSTMap tree;
	while (T--) {
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
		else if (cmd == "min") {
			int k;
			cin >> k;
			tree.min(k);
		}
		else if (cmd == "height") {
			int x;
			cin >> x;
			tree.height(x);
		}
	}
}