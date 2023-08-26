#include <stdio.h>
#include <stdlib.h>
// Structure of a single user
struct User{
    char name[50];
    int age;
    int followers;
};
// Structure of a single node in the AVL tree(social media platform)
struct Node{
    struct User user;
    struct Node* left;
    struct Node* right;
    int height;
};
// Defining functions used
int getHeight(struct Node* node);
int max(int a,int b);
struct Node* createNode(struct User newuser);
struct Node* rotateRight(struct Node* y);
struct Node* rotateLeft(struct Node* x);
int getBalance(struct Node* node);
struct Node* insert(struct Node* root,struct User user);
void reverseInOrderTraversal(struct Node* root);
struct Node* minValueNode(struct Node* node);
struct Node* deleteNode(struct Node* root,struct User user);

int main(void){
    struct Node* root=NULL;
// Inputs
    struct User users[]={
        {"Alice", 25, 1000},
        {"Bob", 30, 500},
        {"Charlie", 22, 750},
        {"David", 28, 800},
        {"Eve", 29, 1200}
    };

    int numUsers=sizeof(users)/sizeof(users[0]);

    for(int i=0;i<numUsers;i++){
        root=insert(root,users[i]);
    }
// Before deleting
    printf("Users of the social media platform:\n");
    reverseInOrderTraversal(root);
// Deleting
    struct User userToDelete={"Charlie", 22, 750};
    root=deleteNode(root, userToDelete);
// After deleting
    printf("\nUsers of the social media platform after deletion:\n");
    reverseInOrderTraversal(root);

    return 0;
}

int getHeight(struct Node* node){
    if(node==NULL){
        return 0;
    }else{
        return node->height;
    }
}

int max(int a,int b){
    if(a>b){
        return a;
    }else{
        return b;
    }
}

struct Node* createNode(struct User newuser){
    struct Node* newnode=(struct Node*)malloc(sizeof(struct Node));
    newnode->user=newuser;
    newnode->left=NULL;
    newnode->right=NULL;
    newnode->height=1;
    return newnode;
}

struct Node* rotateRight(struct Node* y){
    struct Node* x=y->left;
// z to store x->right temporarily
    struct Node* z=x->right;
    x->right=y;
    y->left=z;

    y->height=1+max(getHeight(y->left),getHeight(y->right));
    x->height=1+max(getHeight(x->left),getHeight(x->right));

    return x;
}

struct Node * rotateLeft(struct Node* x){
    struct Node* y=x->right;
    struct Node* z=y->left;
    y->left=x;
    x->right=z;

    x->height=1+max(getHeight(x->left),getHeight(x->right));
    y->height=1+max(getHeight(y->left),getHeight(y->right));

    return y;
}

int getBalance(struct Node* node){
    int balance;
    if(node==NULL){
        return 0;
    }else{
        balance=getHeight(node->left)-getHeight(node->right);
        return balance;
    }
}

struct Node* insert(struct Node* root,struct User user){
    if(root==NULL){
        return createNode(user);
    }
//prioritizing the number of followers for each user
    if(user.followers < root->user.followers){
        root->left=insert(root->left,user);
    }else if(user.followers > root->user.followers){
        root->right=insert(root->right,user);
    }else{
// No duplicates
        return root;
    }

    root->height=1+max(getHeight(root->left),getHeight(root->right));

    int balance=getBalance(root);
// Left not balanced(going to left)
    if(balance > 1 && user.followers < root->left->user.followers){
         return rotateRight(root);
    }
// right not balanced(going to right)
    if(balance < -1 && user.followers > root->right->user.followers){
         return rotateLeft(root);
    }
// Left not balanced(going to right)
    if(balance > 1 && user.followers > root->left->user.followers){
        root->left=rotateLeft(root->left);
        return rotateRight(root);
    }
// right not balanced(going to left)
    if(balance < -1 && user.followers < root->right->user.followers){
        root->right=rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

void reverseInOrderTraversal(struct Node* root){
    if(root!=NULL){
        inOrderTraversal(root->right);
        printf("Name: %s, Age: %d, Followers: %d\n",root->user.name,root->user.age,root->user.followers);
        inOrderTraversal(root->left);
    }
}


// Q2
struct Node* minValueNode(struct Node* node){
    struct Node* current=node;
    while(current->left!=NULL){
        current=current->left;
    }
    return current;
}

struct Node* deleteNode(struct Node* root,struct User user){
    if(root==NULL){
        return root;
    }
    if(user.followers < root->user.followers){
        root->left=deleteNode(root->left,user);
    }else if(user.followers > root->user.followers){
        root->right=deleteNode(root->right,user);
    }else{
        if(root->left==NULL || root->right==NULL){
            struct Node* temp; 
            if(root->left!=NULL){
                temp=root->left;
            }else{
                temp=root->right;
            }
            free(root);
            return temp;
        }else{
            struct Node* temp=minValueNode(root->right);
            root->user=temp->user;
            root->right=deleteNode(root->right,temp->user);
        }
    }

    if(root==NULL){
        return root;
    }
// Updating height of the current root node
    root->height= 1 + max(getHeight(root->left),getHeight(root->right));
    int balance=getBalance(root);
// Checking for imbalances after deletion and performing nessessary rotations
    if(balance > 1 && getBalance(root->left) >= 0){
        return rotateRight(root);
    }
    if(balance > 1 && getBalance(root->left) < 0){
        root->left=rotateLeft(root->left);
        return rotateRight(root);
    }

    if(balance < -1 && getBalance(root->right) <= 0){
        return rotateLeft(root);
    }
    if(balance < -1 && getBalance(root->right) > 0){
        root->right=rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}


