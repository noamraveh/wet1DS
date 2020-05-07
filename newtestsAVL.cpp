//
// Created by Noam Raveh on 07/05/2020.
//

#include "AVLtree.h"
#include <vector>
#include <ostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <cstdbool>
#include <iostream>

int main() {
    AVLTree<int> tree;

    std::vector<int> vector;
    for (int i=1; i<=100; i++) vector.push_back(i);
    //Randomly insert and removes nodes
    for (int k = 0; k < 20; ++k) {
        AVLTree<int> tree;
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle (vector.begin(), vector.end(), std::default_random_engine(seed));
        for (std::vector<int>::iterator it = vector.begin() ; it != vector.end(); ++it){
            tree.insert(*it);

        }
        tree.inorder();
        shuffle (vector.begin(), vector.end(), std::default_random_engine(seed));
        for (std::vector<int>::iterator it = vector.begin() ; it != vector.end(); ++it){
            tree.remove(*it);
            tree.inorder();
            cout << endl;

        }
        tree.inorder();
        std::cout << '\n';
    }

    return 0;
}