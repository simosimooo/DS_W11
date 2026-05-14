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
public:
	BSTMap():n(0),root(nullptr){}
	int size() { return n; }
	bool empty() { return size() == 0; }
	void insert(int x) {
		if (empty()) {
			root = new Node(x, nullptr);
			++n;
			cout << 0 << '\n';
			return;
		}
		int cnt = 0;
		Node* cur = root;
		Node* parent = nullptr;
		while (cur != nullptr) {
			parent = cur;
			if (x < cur->key)cur = cur->left;
			else cur = cur->right;
			++cnt;
		}
		Node* newNode = new Node(x, parent);
		if (x < parent->key)parent->left = newNode;
		else parent->right = newNode;
		++n;
		cout << cnt << '\n';
	}
	void search(int x) {
		if (empty()) { cout << "empty\n"; return; }
		int cnt = 0;
		Node* cur = root;
		while (cur != nullptr) {
			++cnt;
			if (x == cur->key)break;
			if (x < cur->key)cur = cur->left;
			else cur = cur->right;
		}
		cout << cnt << '\n';
	}
	void parent(int x) {
		Node* node = find_entry(x);
		if (node == nullptr) { cout << -1 << '\n'; return; }
		Node* parent = node->parent;
		if (parent == nullptr) {cout << -2 << '\n'; return;}
		cout << parent->key << '\n';
	}
	void child(int x) {
		Node* node = find_entry(x);
		if (node == nullptr) { cout << -1 << '\n'; return; }
		Node* left = node->left;
		if(left==nullptr){cout<<-2<<'\n';return; }
		cout << left->key << '\n';
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
			else if (cmd == "search") {
				int x;
				cin >> x;
				tree.search(x);
			}
			else if (cmd == "parent") {
				int x;
				cin >> x;
				tree.parent(x);
			}
			else if (cmd == "child") {
				int x;
				cin >> x;
				tree.child(x);
			}
		}
	}
}