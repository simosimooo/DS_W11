#include<iostream>
#include<string>
using namespace std;

class Node {
	friend class BSTMap;
private:
	int key;
	int value;
	Node* parent;
	Node* left;
	Node* right;
public:
	Node(int key,int value,Node* parent):key(key),value(value),parent(parent),left(nullptr),right(nullptr){}
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
			node->value = successor->value;
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
			if (child != nullptr)child->parent = parent;
			if (node == parent->left)parent->left = child;
			else parent->right = child;
		}
		delete node;
		--n;
	}
	int Height(Node* node) {
		if (node == nullptr)return -1;
		int leftH = Height(node->left);
		int rightH = Height(node->right);
		return 1 + (leftH > rightH ? leftH : rightH);
	}
public:
	BSTMap():n(0),root(nullptr){}
	int size() { return n; }
	bool empty() { return size() == 0; }
	void Find(int K) {
		Node* node = find_entry(K);
		if (node == nullptr) { cout << 0 << '\n';return; }
		cout << node->value << '\n';
	}
	void Insert(int K, int V) {
		if (empty()) {
			root = new Node(K, V, nullptr);
			++n;
			return;
		}
		Node* cur = root;
		Node* parent = nullptr;
		while (cur != nullptr) {
			if (K == cur->key)return;
			parent = cur;
			if (K < cur->key)cur = cur->left;
			else cur = cur->right;
		}
		Node* newNode = new Node(K, V, parent);
		if (K < parent->key)parent->left = newNode;
		else parent->right = newNode;
		++n;
	}
	void Erase(int K) {
		erase(find_entry(K));
	}
	void Height(int K) {
		Node* cur = find_entry(K);
		if (cur == nullptr) { cout << -1 << '\n';return; }
		cout << Height(cur) << "\n";
	}
	void Next(int K, int S) {
		Node* cur = find_entry(K);
		for (int i{ 0 };i < S;++i) {
			cur = get_successor(cur);
			if (cur == nullptr) {
				cout << -2 << '\n';
				return;
			}
		}
		cout << cur->key << '\n';
	}
};

int main() {
	int Q;
	cin >> Q;
	BSTMap tree;
	while (Q--) {
		string cmd;
		cin >> cmd;
		if (cmd == "Insert") {
			int K, V;
			cin >> K >> V;
			tree.Insert(K, V);
		}
		else if (cmd == "Find") {
			int K;
			cin >> K;
			tree.Find(K);
		}
		else if (cmd == "Erase") {
			int K;
			cin >> K;
			tree.Erase(K);
		}
		else if (cmd == "Height") {
			int K;
			cin >> K;
			tree.Height(K);
		}
		else if (cmd == "Next") {
			int K, S;
			cin >> K >> S;
			tree.Next(K, S);
		}
	}
}