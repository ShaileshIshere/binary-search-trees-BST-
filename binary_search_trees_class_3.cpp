#include<iostream>
#include<queue>

using namespace std;

class Node {
public:
    int data;
    Node *left, *right, *next, *prev;
    Node(int val) : data(val), left(nullptr), right(nullptr), next(nullptr), prev(nullptr) {}
};

void insert_at_head(Node* &head, int data) {
    Node* new_node = new Node(data);
    if(!head)
        head = new_node;
    else {
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
}

int get_doubly_LL(Node* head) {
    Node* temp = head;
    int count=0;
    while(temp) {
        count++;
        temp = temp->next;
    }
    return count;
}

void print_doubly_LL(Node* head) {
    Node* temp = head;
    while(temp) {
        cout << temp->data << " <-> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

Node* insert_into_BST(Node* root, int data) {
    if(!root) {
        root = new Node(data);
        return root;
    }
    if(data > root->data) {
        root->right = insert_into_BST(root->right, data);
        return root;
    }
    else {
        root->left = insert_into_BST(root->left, data);
        return root;
    }
    return root;
}

void create_BST(Node* &root) {
    int data;
    cout << "enter data : " << endl;
    cin >> data;
    while(data != 0) {
        root = insert_into_BST(root, data);
        cout << "enter data : " << endl;
        cin >> data;
    }
}

void level_order_traversal(Node* root) {
    queue<Node*> q;
    q.push(root);
    q.push(nullptr);
    while(!q.empty()) {
        Node* temp = q.front(); q.pop();
        if(!temp) {
            cout << endl;
            if(!q.empty())
                q.push(nullptr);
        }
        else {
            cout << temp->data << " ";
            if(temp->left)
                q.push(temp->left);
            if(temp->right)
                q.push(temp->right);
        }
    }
}

void convert_BST_to_doublyLL(Node* root, Node* &head) {
    if(!root)
        return;
    // we're performing RNL here
    convert_BST_to_doublyLL(root->right, head);
    // N
    root->right = head;
    if(!head)
        root->left = head;
    head = root;
    convert_BST_to_doublyLL(root->left, head);
}
void print_LL(Node* head) {
    Node* temp = head;
    while(temp) {
        cout << temp->data << " -> ";
        temp = temp->right;
    }
}

Node* convert_doublyLL_to_BST(Node* &head, int n) {
    if(!head || n<=0)
        return nullptr;
    // L
    
    Node* left_subtree = convert_doublyLL_to_BST(head, n/2);
    // N
    Node* root = head;
    root->left = left_subtree;
    head = head->next;
    // R
    Node* right_subtree = convert_doublyLL_to_BST(head, n-n/2-1);
    root->right = right_subtree;

    return root;
}

int main() {

    // Node* root = nullptr;
    // create_BST(root);
    // cout << "printing level order traversal : " << endl;
    // level_order_traversal(root);

    // Node* head = nullptr;
    // convert_BST_to_doublyLL(root, head);
    // cout << head->data << endl;
    // cout << "printing sorted doubly linked list : " << endl;
    // print_LL(head);

    Node* head = nullptr;
    // insert_at_head (head, 70);
    insert_at_head (head, 80);
    insert_at_head (head, 70);
    insert_at_head (head, 50);
    insert_at_head (head, 40);
    insert_at_head (head, 30);
    insert_at_head (head, 20);
    print_doubly_LL(head);
    int n = get_doubly_LL(head);
    Node* ans = convert_doublyLL_to_BST(head, n);
    cout << "printing the tree by level order traversal :" << endl;
    level_order_traversal(ans);

    return 0;
}