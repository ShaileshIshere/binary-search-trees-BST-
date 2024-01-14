#include<iostream>
#include<queue>

using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node* insert_into_BST(Node* root, int data) {
    if(!root) {
        root = new Node(data);
        return root;
    }
    // right call
    if(data > root->data) {
        root->right = insert_into_BST(root->right, data);
    }
    // left call
    else {
        root->left = insert_into_BST(root->left, data);
    }
    return root;
}

void create_BST(Node* &root) {
    cout << "enter the root node you want to insert in the tree :" << endl;
    int data;
    cin >> data;
    while(data != 0) {
        root = insert_into_BST(root, data);
        cout << "enter the ordinary nodes here :" << endl;
        cin >> data;
    }
}

void level_order_traversal(Node* root) {
    queue<Node*> q;
    q.push(root);
    q.push(nullptr);
    while(!q.empty()) {
        Node* front = q.front(); q.pop();
        if(!front) {
            cout << endl;
            if(!q.empty()) {
                q.push(nullptr);
            }
        }
        else {
            cout << front->data << " ";
            if(front->left) 
                q.push(front->left);
            if(front->right)
                q.push(front->right);
        }
    }
}

void preorder_traversal(Node* root) {
    if(!root)
        return;
    cout << root->data << " ";
    preorder_traversal(root->left);
    preorder_traversal(root->right);
}

void inorder_traversal(Node* root) {
    if(!root)
        return;
    inorder_traversal(root->left);
    cout << root->data << " ";
    inorder_traversal(root->right);
}

void postorder_traversal(Node* root) {
    if(!root) 
        return;
    postorder_traversal(root->left);
    postorder_traversal(root->right);
    cout << root->data << " ";
}

Node* min_element(Node* root) {
    if(!root) {
        return nullptr;
    }
    Node* temp = root;
    while(temp->left) 
        temp = temp->left;
    return temp;
}

Node* max_element(Node* root) {
    if(!root) {
        return nullptr;
    }
    Node* temp = root;
    while(temp->right) 
        temp = temp->right;
    return temp;
}

bool search_in_BST(Node* root, int given_node) {
    if(!root)
        return false;
    if(root->data == given_node)
        return true;
    bool left_part = false;
    bool right_part = false;
    if(given_node > root->data) 
        right_part = search_in_BST(root->right, given_node);
    else    
        left_part = search_in_BST(root->left, given_node);
    return left_part || right_part;
}

Node* delete_from_BST(Node* root, int target) {
    if(!root)
        return nullptr;
    if(root->data == target) {
        // all 4 cases
        // 1. both side null
        if(!root->left && !root->right) {
            delete root;
            return nullptr;
        }
        // 2. left side non null 
        else if(root->left && !root->right) {
            Node* child_subtree = root->left;
            delete root;
            return child_subtree;
        }
        // 3. right side non null
        else if(!root->left && root->right) {
            Node* child_subtree = root->right;
            delete root;
            return child_subtree;
        }
        // 4. both side non null
        else {
            // we're taking left side max node here to replace it with the root node
            Node* maxi = max_element(root->left);
            // replace the node with the root node
            root->data = maxi->data;
            // delete the node which we've replaced with the root node
            root->left = delete_from_BST(root->left, maxi->data);
            return root;
        }
    }
    // root existing in the left part of tree
    else if(target < root->data) 
        root->left = delete_from_BST(root->left, target);
    else 
        root->right = delete_from_BST(root->right, target);
    return root;
}
 
int main() {

    Node* root = nullptr;
    create_BST(root);

    cout << "printing in level order traversal here : " << endl;
    level_order_traversal(root);

    // cout << endl << "printing in pre-order traversal here : " << endl;
    // preorder_traversal(root);

    // cout << endl << "printing in post-order traversal here : " << endl;
    // postorder_traversal(root);

    // cout << endl << "printing in in-order traversal here : " << endl;
    // inorder_traversal(root);
    cout << endl;

    // Node* find_max = max_element(root);
    // if(find_max)
    //     cout << "max value in the given BST is : " << find_max->data << endl;
    // else 
    //     cout << "no max value here :(" << endl;

    // Node* find_min = min_element(root);
    // if(find_min)
    //     cout << "min value in the given BST is : " << find_min->data << endl;
    // else 
    //     cout << "no min value here :(" << endl;
    
    // int given_node;
    // cout << "enter the node you want to find in this tree : ";
    // cin >> given_node;
    // while(given_node != 0) {
    //     // bool ans = search_in_BST(root, given_node);
    //     if(search_in_BST(root, given_node))
    //         cout << "node found" << endl;
    //     else 
    //         cout << "node not found" << endl;
    //     cout << "enter the node you want to find in this tree : ";
    //     cin >> given_node;
    // }

    int target;
    cout << "enter the node you want to delete from this tree : " << endl;
    cin >> target;
    while(target != 0) {
        Node* ans = delete_from_BST(root, target);
        level_order_traversal(root);
        cout << "enter the node you want to delete from this tree : " << endl;
        cin >> target;
    }

    return 0;
}