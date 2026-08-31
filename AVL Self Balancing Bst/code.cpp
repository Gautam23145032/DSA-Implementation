
#include<bits/stdc++.h>
using namespace std;

/*
    The easiest way to understand it is to separate
    it into 5 pieces;
    1. Node structure
    2. height
    3. Balancing factor
    4. Rotation 
    5. Insertion and rebalancing

*/

// 1.Node structure

struct Node{
    int val;
    Node *left, *right;
    int height;
    Node(int x){
        val = x;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

/*

    why height ?
    because after inserting a node, we need to know whether
    the tree became unbalanced

    For example:

        20
        /
       10
      /
    5

    At 20:

    height(left)  = 2
    height(right) = 0

    so the difference is 2 → imbalance.

*/

// 2.Height

int height(Node* root){
    if(root == nullptr) return 0;
    return root->height;
}

//3. Updating Height -> whenever tree changes,
//   we need to update the affected node

void updateHeight(Node* root){
    root->height = 1 + max(height(root->left), height(root->right));
}

// 4. Balance Factor

int balance(Node* root){
    if(root == nullptr) return 0;
    return height(root->left) - height(root->right);
}

// 5. Rotations
/*
    There are only two basic rotation
    Right rotation
    Left Rotation

    # Right rotation
    Consider:

            y
           /
          x
        /  \
       T1  T2

    We want:

         x
        / \
       T1  y
          /
         T2


        

*/

Node* rightRotate(Node* y){
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

/*
    #Left Rotation

        y
        \
          x
        /  \
       T1  T2

    We want:

         x
        / \
       y  T2
        \  
        T1
        



*/
Node* leftRotate(Node* y){
    Node* x = y->right;
    Node* T1 = x->left;

    x->left = y;
    y->right = T1;

    updateHeight(x);
    updateHeight(y);
    return x;
}


/*
    Now comes the most important part
    after insertion, calculate
    int bf = balance(root);

    there are four possibilities

    case 1. LL
    insertion goes
        30
       /
      20
     /
    10

    at 30 -> balance = +2

    and insertion value went into left of left
    so,
    if(bf > 1 && val < root->left->val){
        return rightRotate(root);
    }

    case 2. RR
     10
      \
        20
          \
           30

    balance = -2;
    inserted value went to right of right

    if(bf < -1 && val < root->right->val){
        return leftRotate(root);
    }

    case 3. LR

      30
     /
    10
      \
       20

       balance = +2

    but insertion went left->right
    so first rotate left on 10 then rotate 30

    if(bf > 1 && val > root->left->val){
        root->left = leftRotate(root->left);
        return rightRotate(root->left);
    }

    case 4. RL

    mirror or LR

       10
        \
        30
        /
      20

    first right rotate at 30 then left rotate at 10;

    if(bf < 1 && val < root->right->val){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    
*/


Node* insert(Node* root, int val) {

    // Normal BST insertion
    if(root == NULL)
        return new Node(val);

    if(val < root->val)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);

    // Update height
    updateHeight(root);

    // Check balance
    int bf = balance(root);

    // LL
    if(bf > 1 && val < root->left->val)
        return rightRotate(root);

    // RR
    if(bf < -1 && val > root->right->val)
        return leftRotate(root);

    // LR
    if(bf > 1 && val > root->left->val) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL
    if(bf < -1 && val < root->right->val) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

/*

              INSERT
                 ↓
          Normal BST insert
                 ↓
          Update height
                 ↓
         Calculate balance
                 ↓
       ┌─────────┴─────────┐
       ↓                   ↓
    balanced            unbalanced
       ↓                   ↓
   return root       identify LL/RR/LR/RL
                           ↓
                       rotate
                           ↓
                    return new root


*/