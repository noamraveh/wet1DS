//
// Created by Noam Raveh on 08/05/2020.
//

#ifndef WET1DS_FINALAVLTREE_H
#define WET1DS_FINALAVLTREE_H

#include <algorithm>
#include <cstdbool>
#include <iostream>
#include <cmath>
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
class TreeNode{
private:
    T data;
    TreeNode* l_son;
    TreeNode* r_son;
    TreeNode* parent;
    int height;
public:
    //c'tors
    TreeNode() = default;
    explicit TreeNode(const T& data):data(data),l_son(nullptr), r_son(nullptr), parent(
            nullptr),height(1){}
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
        if (grandson_node)
            grandson_node->parent=this;
        son_node->parent=this->parent;
        this->parent=son_node;
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
        if (grandson_node)
            grandson_node->parent=this;
        son_node->parent=this->parent;
        this->parent=son_node;
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
                l_son->parent = this;
                return balanceNode();
            } else {
                l_son = l_son->insertNode(add_data);
                return balanceNode();
            }
        } else {
            if (r_son == nullptr) {
                r_son = new TreeNode(add_data);
                r_son->parent = this;
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
                    TreeNode* parent_ptr = this->parent;
                    *this = *temp;
                    this->parent=parent_ptr;
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
    //reverse inorder remove node
    TreeNode<T>* revInorderRemove(TreeNode* node,int* to_delete){
        if (!node)
            return nullptr;
        if (!node->l_son && !node->r_son && *to_delete >0){
            delete node;
            *to_delete = *to_delete -1;
            return nullptr;
        }
        node->r_son = revInorderRemove(node->r_son,to_delete);
        node->l_son = revInorderRemove(node->l_son,to_delete);

        return node;
    }
    void treeClearNodes(TreeNode* node){
        if (l_son)
            delete l_son;
        if (r_son)
            delete r_son;
    }
    void inorderFillArray(int amount,T* array){
        if (l_son){
            l_son->inorderFillArray(amount, array);
        }
    }

    T* findDataNode(T* search_data){
        if (data == search_data){
            return data;
        }
        if (!r_son && !l_son){
            return nullptr;
        }
        else if (search_data < data){
            return l_son->findDataNode(search_data);
        }
        else {
            return r_son->findDataNode(search_data);
        }
    }
    TreeNode* updateMinInsert(){
        if (l_son){
            return l_son;
        }
        return this;
    }

    TreeNode* updateMinRemove(TreeNode* root) {
        if (!root)
            return nullptr;
        TreeNode* smallest = root->getSuccessor();
        if (smallest == this)
            return this;
        return smallest;
    }

    TreeNode*  buildSubtree(int height){
        if (height == 0)
            return nullptr;
        auto node = new TreeNode();
        node->l_son = buildSubtree(height-1);
        node->r_son = buildSubtree(height-1);
        return node;
    }

    void FillNodeFromArrayInorder(int* index,T* array) {
        if (l_son) {
            l_son->FillNodeFromArrayInorder(index, array);
            l_son->parent = this;
        }
        data = array[*index];
        *index = *index + 1;
        if (r_son) {
            r_son->FillNodeFromArrayInorder(index, array);
            r_son->parent = this;
        }
    }


};

template<class T>
class AVLTree {
private:
    TreeNode<T> *root;
    TreeNode<T> *min;
    int num_of_nodes;
public:
    //c'tor
    AVLTree() : root(nullptr),min(nullptr), num_of_nodes(0) {}

    //c'tor for empty tree
    AVLTree(int size) :  root(nullptr),min(nullptr), num_of_nodes(size) {
        //create full tree
        int height = ceil(log(size))+1;
        TreeNode<T>* temp = new TreeNode<T>();
        root = temp->buildSubtree(height);
        delete temp;
        //remove redundant leaves
        int to_delete = pow(2,height)-1 - size;
        root->revInorderRemove(root,&to_delete);
    }
    //d'tor
    ~AVLTree() {
        delete root;
    }
    //insert
    TreeNode<T>* insert(T data){
        if (root == nullptr){
            root = new TreeNode<T>(data);
            num_of_nodes++;
            min = root;
        }
        else if (!root->nodeExists(data)){
            root = root->insertNode(data);
            num_of_nodes++;
            min = min->updateMinInsert();
        }
        //throw success
        //else throw node exists
        return ;
    }

    //remove
    void remove(T data){

        if (!root || !root->nodeExists(data)){
            return; //throw node does not exist
        }

        root = root->removeNode(data);
        min = min->updateMinRemove(root);
        num_of_nodes--;
        //success
    }
    //findData
    T* findData(T search_data){
        if (root == nullptr){
            return nullptr;
        }
        return root->findDataNode(search_data);
    }
    //inorder traverse
    void inorder(){
        if (root == nullptr)
            return;
        root->inorderTraverse(root);
    }

    void fillTreeFromArray(T* array){
        if (!array){
            return;
        }
        int i = 0;
        root->FillNodeFromArrayInorder(&i,array);
        min = root->updateMinRemove(root);
    }

    void inorderToArray(int amount,T* array){
        if (root == nullptr){
            return;
        }
        int i=0;
        root->inorderFillArray(i, amount, array);
    }







};

#endif //WET1DS_FINALAVLTREE_H
