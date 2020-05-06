
#include <iostream>
using namespace std;
#include "AVLtree.h"

int main() {
	AVLTree<int> tree1;
	tree1.insert(7);
	tree1.insert(3);
	tree1.insert(5);
	tree1.inorder();
	cout << endl;
	tree1.insert(10);
	tree1.inorder();
	cout << endl;
	tree1.insert(4);
	tree1.inorder();
	cout << endl;
	tree1.insert(1);
	tree1.inorder();
	cout << endl;
	tree1.insert(23);
	tree1.inorder();
	cout << endl;

	// RL and RR checks mostly
	AVLTree<double> tree3;
	tree3.insert(2);
	tree3.insert(3);
	tree3.insert(1);
	tree3.insert(8);
	tree3.insert(7);
	tree3.insert(6);
	tree3.insert(5);
	tree3.insert(12);
	tree3.insert(10);
	tree3.insert(9);
	tree3.insert(9.5);
	tree3.insert(11);
	tree3.insert(13);
	tree3.inorder();
	cout << endl;

	// LR and LL checks mostly
	AVLTree<double> tree4;
	tree4.insert(8);
	tree4.insert(5);
	tree4.insert(3);
	tree4.insert(4);
	tree4.insert(4.5);
	tree4.insert(7);
	tree4.insert(6);
	tree4.insert(2);
	tree4.insert(2.5);
	tree4.insert(3.5);
	tree4.inorder();
	cout << endl;

	AVLTree<double> tree2;
	tree2.insert(4);
	tree2.insert(2);
	tree2.insert(3);
	tree2.insert(1);
	tree2.insert(8);
	tree2.insert(7);
	tree2.insert(6);
	tree2.insert(5);
	tree2.insert(12);
	tree2.insert(10);
	tree2.insert(9);
	tree2.insert(9.5);
	tree2.insert(11);
	tree2.insert(13);
	tree2.inorder();
	cout << endl;

	// remove node with no children - no rotation
	tree2.remove(8);
	tree2.inorder();
	cout << endl;
	// remove node with one child - no rotation
	tree2.remove(9);
	tree2.inorder();
	cout << endl;
	// remove node with one child - no rotation
	tree2.remove(2);
	tree2.inorder();
	cout << endl;
	// remove node with two children - no rotation
	tree2.remove(3);
	tree2.inorder();
	cout << endl;
	// remove node with no children - with 1 rotation
	tree2.remove(9.5);
	tree2.inorder();
	cout << endl;
	// remove node with no children - with 1 rotation
	tree2.remove(13);
	tree2.inorder();
	cout << endl;
	// remove node with no children - no rotation
	tree2.remove(10);
	tree2.inorder();
	cout << endl;
	// remove node with two children - no rotation
	tree2.remove(4);
	tree2.inorder();
	cout << endl;
	// remove node with two children - no rotation
	tree2.remove(5);
	tree2.inorder();
	cout << endl;
	// remove node with no children - no rotation
	tree2.remove(12);
	tree2.inorder();
	cout << endl;
	// remove node with one child - no rotation
	tree2.remove(6);
	tree2.inorder();
	cout << endl;
	// remove root with two children - no rotation
	tree2.remove(7);
	tree2.inorder();
	cout << endl;
	// remove root with one child - no rotation
	tree2.remove(11);
	tree2.inorder();
	cout << endl;
	// remove root with no children - no rotation
	tree2.remove(1);
	tree2.insert(12);
	tree2.inorder();
	cout << endl;
	tree2.remove(12);

	// after removal - 2 rotations
	AVLTree<int> tree5;
	tree5.insert(9);
	tree5.insert(3);
	tree5.insert(15);
	tree5.insert(1);
	tree5.insert(7);
	tree5.insert(13);
	tree5.insert(19);
	tree5.insert(5);
	tree5.insert(11);
	tree5.insert(17);
	tree5.insert(21);
	tree5.insert(23);
	tree5.inorder();
	cout << endl;

	tree5.remove(1);
	tree5.inorder();
	cout << endl;

	cout << "YASSSSSS" << endl;
	return 0;
}

