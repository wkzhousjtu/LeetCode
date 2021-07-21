#include <iostream>
#include <stack>
#include <vector>
#include <queue>
template<class T>
struct BinNode {
	//二叉树节点模板类
	T val;
	BinNode* left;
	BinNode* right;

	BinNode():val(0),left(nullptr),right(nullptr){}
	BinNode(T val):val(val),left(nullptr),right(nullptr){}
	BinNode(T val, BinNode* left, BinNode* right):val(val), left(left), right(right){}
};

template<class T>
void preOrder(BinNode<T>* root ,vector<BinNode<T>>& v) {
	//二叉树的前序遍历，递归版
	if (!root) return;
	visit(root->val); //v.push_back(root);
	preOrder(root->left, v);
	preOrder(root->right, v);
}

template <class T>
vector<T> preOrder(BinNode<T>* root) {
	//二叉树的前序遍历，迭代版1，
	std::stack<BinNode<T>*> s;
	std::vector<T> v;
	if (root == nullptr) return v;	
	if(root) s.push(root);
	while (!s.empty()) {
		BinNode<T>* x = s.top();
		v.push_back(x->val);
		std::cout <<'前序遍历'<< ' ';
		s.pop();
		if (x->right)s.push(x->right);
		if (x->left)s.push(x->left);
	}
	return v;
}
template <class T>
vector<T> preorderTraversal(BinNode<T>* root) {
	////二叉树的前序遍历，迭代版1,微调
	vector<int> res;
	stack<BinNode<T>*> s;
	BinNode<T>* x = root;
	if (x) s.push(x);
	while (!s.empty()) {
		x = s.top();
		s.pop();
		while (x) {
			res.push_back(x->val);
			if (x->right) s.push(x->right);
			x = x->left;
		}
	}
	return res;
}

template<class T>
vector<T> preOrder2(BinNode<T>* root) {
	//二叉树的前序遍历，迭代版2
	std::stack<BinNode<T>*> s;
	std::vector<T> v;
	BinNode* x = root;
	while(true){  //
		while (x) {  // 小循环沿左链向下，访问中间点，向栈中压入右子树节点
			v.push_back(x->val);
			std::cout << "前序遍历2" << ' ';
			if (x->right)s.push(x->right);
			x = x->left;
		}
		if (s.empty()) break;
		x = s.top();//大循环将栈中的节点取出，再次进入小循环，
		s.pop();
	}
	return v;
}

template<class T>
vector<T> midOrder(BinNode<T>* root) {
	//二叉树的中序遍历，迭代版
	std::stack<BinNode*> s;
	std::vector<T> v;
	BinNode<T>* x = root;
	while (true) { //true可改为 x!=nullptr || !s.empty() 上一节点存在右子树或栈不为空
		while (x) {  //小循环沿左链向下，沿途将左孩子压入栈，直至叶节点，不访问中间节点
			s.push(x);
			x = x->left;
		}
		if (s.empty()) break;
		x = s.top(); //大循环pop出中间节点，访问中间节点，进入右子树，如果没有右子树，继续pop上一级中间节点
		s.pop();
		v.push_back(x->val);
		std::cout << "中序遍历" << ' ';
		x = x->right;
	}
	return v;
}

template<class T>
vector<T> postOrder(BinNode<T>* root) {
	//二叉树的后序遍历，迭代版
	std::stack<BinNode<T>*> s;
	std::vector<T> v;
	BinNode<T>* x = root;
	BinNode<T>* prev = nullptr;
	while (true) {
		while (x) { //小循环沿左链向下直至叶节点，将左孩子依次压入栈
			s.push(x);
			x = x->left;
		}
		if (s.empty()) break;
		x = s.top();//大循环pop出中间节点，若有右子树，遍历右子树；若无右子树或右子树已被访问，访问中间节点，pop出上一中间节点
		s.pop();
		if (x->right && x != prev) { //存在右子树且右子树不是刚弹出栈的节点，先把中间节点压进栈
			s.push(x);
			x = x->right;
		}
		else {  //不存在右子树或者右子树刚弹出栈，需要访问中间节点，向上pop
			v.push_back(x->val);
			std::cout << "后序遍历" << ' ';
			prev = x;
			x = nullptr;
		}
	}
	return v;
}

template<class T>
vector<T> levelOrder(BinNode<T>* root) {
	//层次遍历，用队列实现，广度优先搜索。
	std::queue<BinNode<T>*> q;
	std::vector<T> v;
	BinNode<T>* x = root;
	q.push(x);
	while (!q.empty()) {
		x = q.front();
		q.pop();
		v.push_back(x->val);
		if (x->left)q.push(x->left);
		if (x->right)q.push(x->right);
	}
	return v;
}

int main() {

	return 0;
}