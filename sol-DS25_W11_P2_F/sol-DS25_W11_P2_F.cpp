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

public:
	BSTMap():n(0),root(nullptr){}
	int size() { return n; }
	bool empty() { return size() == 0; }
	Node* find_entry(int key) {
		Node* cur = root;
		while (cur != nullptr) {
			if (key == cur->key)return cur;
			if (key < cur->key)cur = cur->left;
			else cur = cur->right;
		}
		return nullptr;
	}
	void Insert(int key) {
		if (empty()) {
			root = new Node(key, 0,nullptr);
			++n;
			return;
		}
		Node* cur = root;
		Node* parent = nullptr;
		while (cur != nullptr) {
			if (key == cur->key)return;
			parent = cur;
			if (key < cur->key)cur = cur->left;
			else cur = cur->right;
		}
		Node* newNode = new Node(key, 0, parent);
		if (key < parent->key)parent->left = newNode;
		else parent->right = newNode;
		++n;
	}
	void Attend(int sid) {
		Node* node = find_entry(sid);
		++(node->value);
	}
	void Find(int sid) {
		Node* node = find_entry(sid);
		if (node == nullptr) { cout << -1 << ' ' << -1 << '\n';return; }
		int value = node->value;
		int d = 0;
		while (node != root) {
			++d;
			node = node->parent;
		}
		cout << value << ' ' << d << '\n';
	}
};

int main() {
	int N;
	cin >> N;
	BSTMap class5;
	BSTMap class6;
	while (N--) {
		string cmd;
		cin >> cmd;
		if (cmd == "Insert") {
			int cid, sid;
			cin >> cid >> sid;
			cid == 5 ? class5.Insert(sid) : class6.Insert(sid);
		}
		else if (cmd == "Attend") {
			int sid;
			cin >> sid;
			if (class5.find_entry(sid) != nullptr) {
				cout << 5 << '\n';
				class5.Attend(sid);
			}
			else if (class6.find_entry(sid) != nullptr) {
				cout << 6 << '\n';
				class6.Attend(sid);
			}
			else {
				cout << -1 << '\n';
			}
		}
		else if (cmd == "Find") {
			int cid, sid;
			cin >> cid >> sid;
			cid == 5 ? class5.Find(sid) : class6.Find(sid);
		}
	}
}