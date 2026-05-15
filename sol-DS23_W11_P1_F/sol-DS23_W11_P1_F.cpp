#include<iostream>
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
	int subtreeSize(Node* node) {
		if(node==nullptr)return 0;
		int leftS = subtreeSize(node->left);
		int rightS = subtreeSize(node->right);
		return 1+leftS + rightS;
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
public:
	BSTMap():n(0),root(nullptr){}
	int size() { return n; }
	bool empty() { return size() == 0; }
	void insert(int key) {
		if (empty()) {
			root = new Node(key, nullptr);
			++n;
			return;
		}
		Node* cur = root;
		Node* parent = nullptr;
		while (cur != nullptr) {
			parent = cur;
			if (key < cur->key)cur = cur->left;
			else cur = cur->right;
		}
		Node* newNode = new Node(key, parent);
		if (key < parent->key)parent->left = newNode;
		else parent->right = newNode;
		++n;
	}
	void leftSubtreeSize(int x, int y) {
		cout << subtreeSize(find_entry(x)->left) + subtreeSize(find_entry(y)->left) << '\n';
	}
};

int main() {
	int N, M;
	cin >> N >> M;
	BSTMap tree;
	while (N--) {
		int x;
		cin >> x;
		tree.insert(x);
	}
	while (M--) {
		int x, y;
		cin >> x >> y;
		tree.leftSubtreeSize(x, y);
	}
}