#include <iostream>
#include <stack>
#include <vector>
#include <queue>
template<class T>
struct BinNode {
	//�������ڵ�ģ����
	T val;
	BinNode* left;
	BinNode* right;

	BinNode():val(0),left(nullptr),right(nullptr){}
	BinNode(T val):val(val),left(nullptr),right(nullptr){}
	BinNode(T val, BinNode* left, BinNode* right):val(val), left(left), right(right){}
};

template<class T>
void preOrder(BinNode<T>* root ,vector<BinNode<T>>& v) {
	//��������ǰ��������ݹ��
	if (!root) return;
	visit(root->val); //v.push_back(root);
	preOrder(root->left, v);
	preOrder(root->right, v);
}

template <class T>
vector<T> preOrder(BinNode<T>* root) {
	//��������ǰ�������������1��
	std::stack<BinNode<T>*> s;
	std::vector<T> v;
	if (root == nullptr) return v;	
	if(root) s.push(root);
	while (!s.empty()) {
		BinNode<T>* x = s.top();
		v.push_back(x->val);
		std::cout <<'ǰ�����'<< ' ';
		s.pop();
		if (x->right)s.push(x->right);
		if (x->left)s.push(x->left);
	}
	return v;
}
template <class T>
vector<T> preorderTraversal(BinNode<T>* root) {
	////��������ǰ�������������1,΢��
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
	//��������ǰ�������������2
	std::stack<BinNode<T>*> s;
	std::vector<T> v;
	BinNode* x = root;
	while(true){  //
		while (x) {  // Сѭ�����������£������м�㣬��ջ��ѹ���������ڵ�
			v.push_back(x->val);
			std::cout << "ǰ�����2" << ' ';
			if (x->right)s.push(x->right);
			x = x->left;
		}
		if (s.empty()) break;
		x = s.top();//��ѭ����ջ�еĽڵ�ȡ�����ٴν���Сѭ����
		s.pop();
	}
	return v;
}

template<class T>
vector<T> midOrder(BinNode<T>* root) {
	//�����������������������
	std::stack<BinNode*> s;
	std::vector<T> v;
	BinNode<T>* x = root;
	while (true) { //true�ɸ�Ϊ x!=nullptr || !s.empty() ��һ�ڵ������������ջ��Ϊ��
		while (x) {  //Сѭ�����������£���;������ѹ��ջ��ֱ��Ҷ�ڵ㣬�������м�ڵ�
			s.push(x);
			x = x->left;
		}
		if (s.empty()) break;
		x = s.top(); //��ѭ��pop���м�ڵ㣬�����м�ڵ㣬���������������û��������������pop��һ���м�ڵ�
		s.pop();
		v.push_back(x->val);
		std::cout << "�������" << ' ';
		x = x->right;
	}
	return v;
}

template<class T>
vector<T> postOrder(BinNode<T>* root) {
	//�������ĺ��������������
	std::stack<BinNode<T>*> s;
	std::vector<T> v;
	BinNode<T>* x = root;
	BinNode<T>* prev = nullptr;
	while (true) {
		while (x) { //Сѭ������������ֱ��Ҷ�ڵ㣬����������ѹ��ջ
			s.push(x);
			x = x->left;
		}
		if (s.empty()) break;
		x = s.top();//��ѭ��pop���м�ڵ㣬�������������������������������������������ѱ����ʣ������м�ڵ㣬pop����һ�м�ڵ�
		s.pop();
		if (x->right && x != prev) { //���������������������Ǹյ���ջ�Ľڵ㣬�Ȱ��м�ڵ�ѹ��ջ
			s.push(x);
			x = x->right;
		}
		else {  //�����������������������յ���ջ����Ҫ�����м�ڵ㣬����pop
			v.push_back(x->val);
			std::cout << "�������" << ' ';
			prev = x;
			x = nullptr;
		}
	}
	return v;
}

template<class T>
vector<T> levelOrder(BinNode<T>* root) {
	//��α������ö���ʵ�֣��������������
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