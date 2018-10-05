/*
 Francesca Rizzo
 Competitive Programming and Contests
 */

/*
Code description
*/


/*Please note that it's Function problem i.e.
 you need to write your solution in the form of Function(s) only.
 Driver Code to call/invoke your function is mentioned above.*/

/* A binary tree node has data, pointer to left child
 and a pointer to right child
 struct Node {
 int data;
 Node* left, * right;
 }; */
/* Should return true if tree represented by root is BST.
 For example, return  value should be 1 for following tree.
 20
 /      \
 10       30
 and return value should be 0 for following tree.
 10
 /      \
 20       30 */
int max_int = 1000;

//lato=1 if root->data < root->left ->data altrimenti lato = 0
bool checkBST(Node* root, int min, int max, int lato){
    if ((root->data < min)||(root->data > max)) return false;
    bool dx = true, sx = true;
    if (lato == 1){
        if (root->right) dx = checkBST(root->right, min, root->data, lato);
        if (root->left) sx = checkBST(root->left, root->data, max, lato);
    } else if (lato == 0){
        if (root->right) dx = checkBST(root->right, root->data, max, lato);
        if (root->left) sx = checkBST(root->left, min, root->data, lato);
    }
    
    return (dx&&sx);
}

bool isBST(Node* root) {
    if (!root) return true;
    int lato = 1;
    if ((root->left)&&(root->data > root->left->data)) lato = 0;
    else if ((root->right)&&(root->data < root->right->data)) lato = 0;
    return checkBST(root,0, max_int, lato);
}

