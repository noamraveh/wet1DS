
#include <iostream>
using namespace std;
#include "FinalAVLTree.h"

int main() {
    AVLTree<int> tree1(6);
    int arr[6] = {1,2,3,4,5,6};
    tree1.fillTreeFromArray(arr);
    return 0;

}

