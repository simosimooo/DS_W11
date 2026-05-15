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
	explicit Node(int key,Node* parent):key(key),parent(parent),left(nullptr),right(nullptr){}
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
	int subtreeSize(Node* node) {
		if (node == nullptr)return 0;
		int leftS = subtreeSize(node->left);
		int rightS = subtreeSize(node->right);
		return 1 + leftS + rightS;
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
	void rightSubtreeSize(int x, int y) {
		Node* nodeX = find_entry(x);
		Node* nodeY = find_entry(y);
		int xRSize = subtreeSize(nodeX->right);
		int yRSize = subtreeSize(nodeY->right);
		int diff = xRSize - yRSize;
		cout << (diff > 0 ? diff : -diff) << '\n';
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
		tree.rightSubtreeSize(x, y);
	}
}