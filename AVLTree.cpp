#include <cstddef>
using namespace std;

struct Node {
	int info; //значение
	Node* left; //левое поддерево
	Node* right; //правое поддерево
	int balance; //поле баланса (высота правого поддерева - высота левого поддерева)
};

int height(Node* root) {
	if (root == NULL) return 0; //если дерево пусто - возвращаем 0
	int hLeft = height(root->left); //считаем высоту левого поддерева
	int hRight = height(root->right); //считаем высоту правого поддерева
	if (hLeft > hRight)
		return hLeft + 1;
	else
		return hRight + 1;
}

void balance(Node* (&root)) {
	if (root != NULL)
		root->balance = height(root->right) - height(root->left);
}

void turnRight(Node* (&root)) { //правый поворот АВЛ-дерева
	Node* leftSubtree, * leftSubtreeRightSubtree;
	leftSubtree = root->left;
	leftSubtreeRightSubtree = leftSubtree->right;

	leftSubtree->right = root;
	root->left = leftSubtreeRightSubtree;
	root = leftSubtree;
	balance(root->right); //перебалансировка
	balance(root);
}

void turnLeft(Node* (&root)) { //левый поворот АВЛ-дерева
	Node* rightSubtree, * rightSubtreeLeftSubtree;
	rightSubtree = root->right;
	rightSubtreeLeftSubtree = rightSubtree->left;

	rightSubtree->left = root;
	root->right = rightSubtreeLeftSubtree;
	root = rightSubtree;
	balance(root->left);
	balance(root);
}

void insert(Node* (&root), int d) { //добавление узла 
	if (root == NULL) {
		root = new Node;
		root->info = d;
		root->balance = 0;
		root->left = NULL;
		root->right = NULL;

	}
	else {
		if (d > root->info) {
			insert(root->right, d);
			if (height(root->right) - height(root->left) > 1) {
				if (height(root->right->right) < height(root->right->left))
					turnRight(root->right);
				turnLeft(root);
			}
		}
		else
			if (d < root->info) {
				insert(root->left, d);
				if (height(root->left) - height(root->right) > 1) {
					if (height(root->left->left) < height(root->left->right)) {
						turnLeft(root->left);
						turnRight(root);
					}
				}
				balance(root);
			}
	}
}

	bool search(Node * root, int key) { //поиск
		if (root == NULL) {
			return false;
		}
		if (key == root->info) {
			return true;
		}
		if (key < root->info) {
			return search(root->left, key);
		}return search(root->right, key);
	}


	Node* deleteNode(Node* (&root), int key) { //удаление узла
		if (root == NULL) {
			return NULL;
		}

		if (key < root->info) {
			root->left = deleteNode(root->left, key);
		}
		else if (key > root->info) {
			root->right = deleteNode(root->right, key);
		}
		else {
			if (root->left == NULL && root->right == NULL) {
				delete root;
				root = NULL;
			}
			else if (root->left = NULL) {
				Node* temp = root->right;
				delete root;
				root = temp;
			}
			else if (root->right == NULL) {
				Node* temp = root->left;
				delete root;
				root = temp;
			}
			else {
				Node* temp = root->right;
				while (temp->left != NULL) {
					temp = temp->left;
				}
				root->info = temp->info;
				root->right = deleteNode(root->right, temp->info);
			}
		}
		if (root == NULL) {
			return NULL; 
		}

		root->balance = height(root->right) - height(root->left);

		if (root->balance > 1) {
			if (height(root->right->right) < height(root->right->left)) {
				turnRight(root->right);
			}
			turnLeft(root);
		}
		else if (root->balance < -1) {
			if (height(root->left->left) < height(root->left->right)) {
				turnLeft(root->left);
			}
			turnRight(root);
		}

		return root;

	}
		