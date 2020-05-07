//
// Created by Noam Raveh on 05/05/2020.
//

#ifndef WET1DS_AVLTREE_H
#define WET1DS_AVLTREE_H
#include <algorithm>
#include <cstdbool>
#include <iostream>
//using std::cout;
//using std::endl;
using namespace std;
typedef enum {
    AVL_SUCCESS,
    AVL_NULL_ARG,
    AVL_OUT_OF_MEMORY,
    AVL_ALREADY_EXISTS,
    AVL_NOT_FOUND
}AVLResult;
template<class T>
class AVLTree {
private:
    class TreeNode{
    private:
        T data;
        TreeNode* l_son;
        TreeNode* r_son;
        int height;
    public:
        //c'tor
        explicit TreeNode(const T& data):data(data),l_son(nullptr), r_son(nullptr), height(1){}
        //d'tor
        ~TreeNode() {
            if (l_son)
                delete l_son;
            if (r_son)
                delete r_son;


        }
        //update height
        void updateHeight(){
            if (r_son == nullptr && l_son == nullptr){
                height = 1;
            }
            else if (r_son == nullptr){
                height = 1 + l_son->height;
            }
            else if (l_son == nullptr){
                height = 1 + r_son->height;
            }
            else {
                height = 1 + max(r_son->height,l_son->height);
            }
        }
        //calculate balance factor
        int calcBF(){
            if (r_son == nullptr && l_son == nullptr) return 0;
            else if (r_son == nullptr) return l_son->height;
            else if (l_son == nullptr) return -(r_son->height);
            else return (l_son->height)-(r_son->height);
        }
        //left rotation
        TreeNode* leftRotation(){
            TreeNode* son_node = r_son;
            TreeNode* grandson_node = son_node->l_son;
            son_node->l_son=this;
            r_son=grandson_node;
            updateHeight();
            son_node->updateHeight();
            return son_node;
        }
        //right rotation
        TreeNode* rightRotation(){
            TreeNode* son_node = l_son;
            TreeNode* grandson_node = son_node->r_son;
            son_node->r_son=this;
            l_son=grandson_node;
            updateHeight();
            son_node->updateHeight();
            return son_node;
        }
        //balance
        TreeNode* balanceNode(){
            updateHeight();
            int balance_factor = calcBF();

            //LL rotation
            if (balance_factor>1 && l_son->calcBF()!=-1){
                return rightRotation();
            }
                //RR rotation
            else if (balance_factor<-1 && r_son->calcBF()!=1){
                return leftRotation();
            }
                //LR rotation
            else if (balance_factor>1 && l_son->calcBF()== -1){
                l_son = l_son->leftRotation();
                return rightRotation();
            }
                //RL rotation
            else if (balance_factor<-1 && r_son->calcBF()==1){
                r_son = r_son->rightRotation();
                return leftRotation();
            }
            return this;
        }
        //nodeExists
        bool nodeExists(const T& search_data){
            if (search_data == data){
                return true;
            }
            if (!l_son && !r_son)
                return false;
            else if (search_data < data) {
                if (l_son == nullptr) {
                    return false;
                }
                return l_son->nodeExists(search_data);
            }
            else {
                if (r_son == nullptr) {
                    return false;
                }
                return r_son->nodeExists(search_data);
            }
        }

        //insert
        TreeNode* insertNode(const T &add_data) {
            if (add_data < data) {
                if (l_son == nullptr) {
                    l_son = new TreeNode(add_data);
                    return balanceNode();
                } else {
                    l_son = l_son->insertNode(add_data);
                    return balanceNode();
                }
            } else {
                if (r_son == nullptr) {
                    r_son = new TreeNode(add_data);
                    return balanceNode();
                } else {
                    r_son = r_son->insertNode(add_data);
                    return balanceNode();
                }
            }
        }
        TreeNode* getSuccessor() {
            if (l_son == nullptr) {
                return this;
            }
            return l_son->getSuccessor();
        }

        //remove_node
        TreeNode* removeNode( const T &search_data) {

            if (search_data < data){
                l_son = l_son->removeNode(search_data);
            }
            else if (search_data > data){
                r_son = r_son->removeNode(search_data);
            }
                //wanted node was found
            else {
                if (!l_son || !r_son) { //1 or 0 children
                    TreeNode *temp = l_son ? l_son : r_son;
                    if (!temp) { // no children
                        delete this;
                        return nullptr;
                    } else { // has one child
                        *this = *temp;
                    }
                    delete temp;
                } else { //2 children
                    TreeNode *temp = r_son->getSuccessor();
                    data = temp->data;
                    r_son = r_son->removeNode(temp->data);
                }
            }
          //  if (this == nullptr) return this;
            return balanceNode();
        }
        //inorder node
        void inorderTraverse(TreeNode* node){
            if (!node)
                return;
            inorderTraverse(node->l_son);
            cout << node->data<< endl;
            inorderTraverse(node->r_son);
        }
        void treeClearNodes(TreeNode* node){
            if (l_son)
                delete l_son;
            if (r_son)
                delete r_son;
        }
    };
    TreeNode *root;
    int num_of_nodes;
public:
    //c'tor
    AVLTree() : root(nullptr), num_of_nodes(0) {}
    //d'tor
    ~AVLTree() {
        delete root;
    }
    //insert
    void insert(T data){

        if (root == nullptr){
            root = new TreeNode(data);
            num_of_nodes++;
            return;
        }
        if (!root->nodeExists(data)){
            root = root->insertNode(data);
            num_of_nodes++;
            return;;
        }
        //throw success
        //else throw node exists
    }

    //remove
    void remove(T data){

        if (!root || !root->nodeExists(data)){
            return; //throw node does not exist
        }
        root = root->removeNode(data);
        num_of_nodes--;
        //success
    }
    //inorder traverse
    void inorder(){
        if (root == nullptr)
            return;
        root->inorderTraverse(root);
    }

};

#endif //WET1DS_AVLTREE_H
