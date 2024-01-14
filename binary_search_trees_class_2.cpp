#include<iostream>
#include<queue>

using namespace std;

class Node {
public:
    int data;
    Node *left, *right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node* insert_into_BST(Node* root, int data) {
    if(!root) {
        root = new Node(data);
        return root;
    }
    if(data > root->data) 
        root->right = insert_into_BST(root->right, data);
    else 
        root->left = insert_into_BST(root->left, data);
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

void inorder_traversal(Node* root, vector<int> &inorder) {
    if(!root)
        return;
    inorder_traversal(root->left, inorder);
    inorder.push_back(root->data);
    inorder_traversal(root->right, inorder);
}

Node* find_max(Node* root) {
    if(!root)
        return nullptr;
    Node* temp = root;
    while(temp->right) 
        temp = temp->right;
    return temp;
}

Node* find_min(Node* root) {
    if(!root)
        return nullptr;
    Node* temp = root;
    while(temp->left) 
        temp = temp->left;
    return temp;
}

// create a BST from inorder traversal
Node* BST_from_inorder(vector<int> &inorder, int start, int end) {
    if(start > end)
        return nullptr;
    int mid = start + ((end - start) >> 1);
    int element = inorder[mid];
    Node* root = new Node(element);
    root->left = BST_from_inorder(inorder, start, mid-1);
    root->right = BST_from_inorder(inorder, mid+1, end);
    return root;
}

// validate binary search tree
bool solve(Node* root, long long int lower_bound, long long int upper_bound) {
    if(!root)
        return true;
    bool condition_1 = (root->data > lower_bound);
    bool condition_2 = (root->data < upper_bound);
    bool left_ans = solve(root->left, lower_bound, upper_bound);
    bool right_ans = solve(root->right, lower_bound, upper_bound);
    if(condition_1 && condition_2 && left_ans && right_ans)
        return true;
    else 
        return false;
}
bool is_valid(Node* root) {
    long long int lower_bound = INT_MIN;
    long long int upper_bound = INT_MAX;
    bool ans = solve(root, lower_bound, upper_bound);
    return ans;
}

// lowest common ancestor of binary search tree
Node* LCA(Node* root, Node* p, Node* q) {
    if(!root)
        return nullptr;
    if(p->data < root->data && q->data < root->data) {
        Node* left_ans = LCA(root->left, p, q);
        return left_ans;
    }
    if(p->data > root->data && q->data > root->data) {
        Node* right_ans = LCA(root->right, p, q);
        return right_ans;
    }
    return root;
}

// kth smallest element in a binary search tree
int kth_smallest(Node* root, int &k) {
    if(!root)
        return -1;
    int left = kth_smallest(root->left, k);
    if(left != -1)
        return left;
    k--;
    if(k == 0)
        return root->data;
    int right = kth_smallest(root->right, k);
    return right;
}

// two sum IV input is a BST
void solve(vector<int> &inorder, Node* root) {
    if(!root)
        return;
    solve(inorder, root->left);
    inorder.push_back(root->data);
    solve(inorder, root->right);
}
bool find_target(Node* root, int k) {
    vector<int> inorder;
    solve(inorder, root);
    int start = 0, end = inorder.size()-1;
    while(start < end) {
        int sum = inorder[start] + inorder[end];
        if(sum == k)
            return true;
        else if(sum > k)
            end--;
        else 
            start++;
    }
    return false;
}

int main() {
    
    Node* root = nullptr;
    create_BST(root);
    cout << "printing level order traversal" << endl;
    level_order_traversal(root);

    // Node* left = find_min(root);
    // cout << "min element in this tree : " << left->data << endl;
    // Node* right = find_max(root);
    // cout << "max element in this tree : " << right->data << endl;

    // vector<int> inorder;
    // inorder_traversal(root, inorder);
    // cout << "printing inorder traversal" << endl;
    // for(int x:inorder) 
    //     cout << x << " ";
    // cout << endl;
    // Node* ans = BST_from_inorder(inorder, 0, inorder.size()-1);
    // level_order_traversal(root);

    // if(is_valid(root))
    //     cout << "the given tree is a perfect binary tree" << endl;
    // else 
    //     cout << "the given tree isn't a perfect binary tree" << endl;

    // Node *p;
    // Node *q;
    // cout << "mention (p) or (q) here : " << endl;
    // cin >> p->data >> q->data;
    // Node* ans = LCA(root, p, q);
    // cout << "lowest common ancestor of this binary search tree is : " << ans->data << endl;

    // int k;
    // cout << "enter the value of k here : ";
    // cin >> k;
    // cout << "kth smallest element in this tree is : " << kth_smallest(root, k) << endl;

    // int k;
    // cout << "enter the sum value of 2 nodes : ";
    // cin >> k;
    // if(find_target(root, k))
    //     cout << "sum node has been found :)" << endl;
    // else 
    //     cout << "sum node hasn't been found :(" << endl;

    return 0;
}