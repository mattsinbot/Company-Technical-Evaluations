#include <iostream>
#include <memory>
#include <queue>
#include <stack>

using namespace std;

// A simple Node class
struct Node{
    int value;
    shared_ptr<Node> left;
    shared_ptr<Node> right;
};

// BiTree class
class BiTree{
    public:
        BiTree();
	void insert_node(int key);
        int find_min_recur();
        int find_max_recur();
        void print_left();
        void print_right();
        void print_manual();
        int element_exist(int element_value);
        int find_tree_height();
        void BFS_Search();
        void DFS_Search();
    private:
	shared_ptr<Node> root;
        void insert_node(int key, shared_ptr<Node>& leaf);
        int find_min_recur(shared_ptr<Node>& cnode);
        int find_max_recur(shared_ptr<Node>& cnode);
        void print_left(shared_ptr<Node>& cnode);
        void print_right(shared_ptr<Node>& cnode);
        int element_exist(int element_value, shared_ptr<Node>& cnode);
        int find_tree_height(shared_ptr<Node>& cnode);
};


/* **************************************** */
/*           Methods of BiTree class        */
/* **************************************** */

// Constructor 
BiTree::BiTree(){
    // no activity :)
}

//===============================================
// method: insert_node type 1
void BiTree::insert_node(int key){
    if(!root){
        this->root = shared_ptr<Node>(new Node);
        this->root->value = key;
    }
    else {
        // std::cout << "root is not empty" << std::endl;
        insert_node(key, this->root);
    }
}

// method: insert_node type 2
void BiTree::insert_node(int key, shared_ptr<Node>& leaf){
    if (key < leaf->value ) {
        if (!leaf->left) {
            leaf->left = shared_ptr<Node>(new Node);
            // leaf->left.reset(new Node);
            leaf->left->value = key;
        }
        else {
            insert_node(key, leaf->left);
        }
    }
    else{
        if (!leaf->right) {
            leaf->right = shared_ptr<Node>(new Node);
            // leaf->right.reset(new Node);
            leaf->right->value = key;
        }
        else {
            insert_node(key, leaf->right);
        }
    }
}

//===============================================
// method: find_min_recur type 1
int BiTree::find_min_recur() {
    if(!this->root) {
        std::cout << "Root does not exist" << std::endl;
        return -1;
    }
    
    if(!this->root->left) {
         std::cout << "Left subtree is empty" << std::endl;
         return root->value;
    }

    int min_element = find_min_recur(root->left);
    cout << min_element << endl;
    return min_element;
}

// method: find_min_recur type 2
int BiTree::find_min_recur(shared_ptr<Node>& cnode) {
    if(!cnode->left) {
         return cnode->value;
    }
    return find_min_recur(cnode->left);
}

//===============================================
// method: find_max_recur type 1
int BiTree::find_max_recur() {
    if(!this->root) {
        std::cout << "Root does not exist" << std::endl;
        return -1;
    }
    
    if(!this->root->right) {
         std::cout << "Right subtree is empty" << std::endl;
         return root->value;
    }

    int max_element = find_max_recur(root->right);
    cout << max_element << endl;
    return max_element;
}

// method: find_max_recur type 2
int BiTree::find_max_recur(shared_ptr<Node>& cnode) {
    if(!cnode->right) {
         return cnode->value;
    }
    return find_max_recur(cnode->right);
}

//===============================================
//        Method to print left most elements
//===============================================
void BiTree::print_left(shared_ptr<Node>& cnode) {
    if(!cnode->left){
        std::cout << cnode->value << std::endl;
    }
    else{
       std::cout << cnode->value << std::endl;
       print_left(cnode->left);
    }    
}

void BiTree::print_left() {
    if(!this->root->left){
        std::cout << this->root->value << std::endl;
    }
    else{
       std::cout << this->root->value << std::endl;
       print_left(this->root->left); 
    }
    
}

//===============================================
//        Method to print right most elements
//===============================================
void BiTree::print_right(shared_ptr<Node>& cnode) {
    if(!cnode->right){
        std::cout << cnode->value << std::endl;
    }
    else{
       std::cout << cnode->value << std::endl;
       print_right(cnode->right);
    }    
}

void BiTree::print_right() {
    if(!this->root->right){
        std::cout << this->root->value << std::endl;
    }
    else{
       std::cout << this->root->value << std::endl;
       print_right(this->root->right); 
    }
    
}


//=================================================
void BiTree::print_manual() {
    std::cout << this->root->left->left->value << std::endl;
}

//================================================================
//        Method to find if a given element exists in the tree
//================================================================
int BiTree::element_exist(int element_value, shared_ptr<Node>& cnode) {
    if(!cnode) {
        return -1;
    }
    else if (cnode->value == element_value) {
        std::cout << cnode->value << " == " << element_value << std::endl;
        return 1;
    }
    else {
        if (cnode->value < element_value) {
            std::cout << cnode->value << " < " << element_value << std::endl;
            element_exist(element_value, cnode->right);
        }
        else {
            std::cout << cnode->value << " > " << element_value << std::endl;
            element_exist(element_value, cnode->left);
        }
    }
}

int BiTree::element_exist(int element_value) {
    if(!this->root) {
        return -1;
    }
    else if (this->root->value == element_value) {
        std::cout << this->root->value << " == " << element_value << std::endl;
        return 1;
    }
    else {
        if (this->root->value < element_value){
            std::cout << this->root->value << " < " << element_value << std::endl;
            element_exist(element_value, root->right);
        }
        else {
            std::cout << this->root->value << " > " << element_value << std::endl;
            element_exist(element_value, root->left);
        }
    }
}

//======================================================
//         Find height of a binary search tree
//======================================================
int BiTree::find_tree_height(shared_ptr<Node>& cnode) {
    if(!cnode) {return -1;}
    return max(find_tree_height(cnode->left), find_tree_height(cnode->right))+1;
}

int BiTree::find_tree_height() {
    if(!this->root) {return -1;}
    return max(find_tree_height(this->root->left), find_tree_height(this->root->right))+1;
}

//=======================================================
//         BFS Tree traversal of a Tree
//=======================================================
void BiTree::BFS_Search() {
    if(!this->root) {
        return;
    }
    queue<shared_ptr<Node>> Q;
    shared_ptr<Node> cnode;
    Q.push(root);
    while(!Q.empty()){
        cnode = Q.front();
        std::cout << cnode->value << std::endl;
        if(cnode->left) Q.push(cnode->left);
        if(cnode->right) Q.push(cnode->right);
        Q.pop();
    }
}

//=======================================================
//         DFS Tree traversal of a Tree
//=======================================================
void BiTree::DFS_Search() {
    if(!this->root) {
        return;
    }
    stack<shared_ptr<Node>> S;
    shared_ptr<Node> cnode;
    S.push(root);
    while(!S.empty()){
        cnode = S.top();
        std::cout << cnode->value << std::endl;
        S.pop();
        if(cnode->right) S.push(cnode->right);
        if(cnode->left) S.push(cnode->left);
    }
}


// Main function call
int main(){

    shared_ptr<BiTree> tree(new BiTree());

    tree->insert_node(10);
    tree->insert_node(6);
    tree->insert_node(14);
    tree->insert_node(8);
    tree->insert_node(11);
    tree->insert_node(18);
    tree->insert_node(5);
    
    tree->print_manual();
    std::cout << "================" << std::endl;

    tree->print_left();    
    std::cout << "================" << std::endl;

    tree->print_right();    
    std::cout << "================" << std::endl;

    tree->find_min_recur();
    tree->find_max_recur();
    std::cout << "================" << std::endl;

    std::cout << tree->element_exist(20) << std::endl;
    std::cout << "================" << std::endl;

    std::cout << tree->find_tree_height() << std::endl;
    std::cout << "================" << std::endl;

    tree->BFS_Search();
    std::cout << "================" << std::endl;

    tree->DFS_Search();
    std::cout << "================" << std::endl;
}

