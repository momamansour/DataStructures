// Author: Mohammed Almansour

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <assert.h>
#include <ctype.h>

// all the basic data structures and functions are included in this template
// you can add your own auxiliary functions as you like

// data type for avl tree nodes
typedef struct AVLTreeNode {
    int key; //key of this item
    int  value;  //value (int) of this item
    int height; //height of the subtree rooted at this node
    struct AVLTreeNode *parent; //pointer to parent
    struct AVLTreeNode *left; //pointer to left child
    struct AVLTreeNode *right; //pointer to right child
} AVLTreeNode;

//data type for AVL trees
typedef struct AVLTree{
    int  size;      // count of items in avl tree
    AVLTreeNode *root; // root
} AVLTree;

// create a new AVLTreeNode
AVLTreeNode *newAVLTreeNode(int k, int v )
{
    AVLTreeNode *new;
    new = malloc(sizeof(AVLTreeNode));
    assert(new != NULL);
    new->key = k;
    new->value = v;
    new->height = 0; // height of this new node is set to 0
    new->left = NULL; // this node has no child
    new->right = NULL;
    new->parent = NULL; // no parent
    return new;
}

// create a new empty avl tree
AVLTree *newAVLTree()
{
    AVLTree *T;
    T = malloc(sizeof (AVLTree));
    assert (T != NULL);
    T->size = 0;
    T->root = NULL;
    return T;
}


// function to get the height of the tree
int height(struct AVLTreeNode *N)
{
    // if node does not exist it gives -1
    if (N == NULL)
        return -1;
    return N->height;
}

// function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}

// function to get balance factor of node N
int getBalance(struct AVLTreeNode *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}


// a function that performs a right rotation
struct AVLTreeNode *rightRotate(struct AVLTreeNode *y)
{
    struct AVLTreeNode *x = y->left;
    struct AVLTreeNode *T2 = x->right;

    // performing rotation
    x->right = y;
    y->left = T2;


    // reassigning parents
    if (T2!=NULL) {T2->parent = y;}
    x->parent = y->parent;
    y->parent = x;


    // updating heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    // new root
    return x;
}

// function that performs a left rotation
struct AVLTreeNode *leftRotate(struct AVLTreeNode *x)
{
    struct AVLTreeNode *y = x->right;
    struct AVLTreeNode *T2 = y->left;

    // performing rotation
    y->left = x;
    x->right = T2;

    // reassigning parents
    y->parent = x->parent;
    x->parent = y;
    if (T2!=NULL) {T2->parent = x;}


    //  updating heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    // new root
    return y;
}

// recursive function that performs a single insertion
struct AVLTreeNode* insert(struct AVLTreeNode* node, int k, int v)
{

    if (node == NULL)
        // return the new node
        return(newAVLTreeNode(k,v));

    // search the tree for the appropriate location
    if (k < node->key) {
        node->left = insert(node->left, k, v);
        node->left->parent = node;
    }
    else if (k > node->key) {
        node->right = insert(node->right, k, v);
        node->right->parent = node;
    }
    else {
        if (v < node->value) {
            node->left = insert(node->left, k, v);
            node->left->parent = node;
        } else if (v > node->value) {
            node->right = insert(node->right, k, v);
            node->right->parent = node;
        }
            // if duplicate do nothing
        else { return node;}
    }

    // updating the height
    node->height = 1 + max(height(node->left),
                           height(node->right));

    // get the balance
    int balance = getBalance(node);

    // If balance outside -1<= balance <= 1 then unbalanced

    // in case ks are not equal
    if (k != node->key) {
        // Left Left
        if (balance > 1 && k < node->left->key)
            return rightRotate(node);

        // Right Right
        if (balance < -1 && k > node->right->key)
            return leftRotate(node);

        // Left Right
        if (balance > 1 && k > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left
        if (balance < -1 && k < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
        // in case keys are equal then we use values to sort
    else {
        // Left Left
        if (balance > 1 && v < node->left->value)
            return rightRotate(node);

        // Right Right
        if (balance < -1 && v > node->right->value)
            return leftRotate(node);

        // Left Right
        if (balance > 1 && v > node->left->value)
        {
            node->left =  leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left
        if (balance < -1 && v < node->right->value)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    // return the same node
    return node;
}



// put your time complexity analysis of CreateAVLTree() here
// it follows O(n*log(n)) since it constructs a tree node by node
// search and insert is O(log(n)) and since this is done for each node then O(n*log(n))
AVLTree *CreateAVLTree(const char *filename)
{
    // put your code here
    // buffer collects single digits for each number then stores them in arr
    // after converting them from char string to int
    int arrk[100];
    int arrv[100];
    bzero(arrk,100);
    bzero(arrv,100);
    char buffer[32];
    int i=0;
    int j=0;
    int ky=0;
    int va=0;
    //
    // if stdin is given call input function
    if (filename=="stdin"){

        int k=-1;
        char inputstr[100];
        // ask for input and stop at "END"
        printf("enter keys and vs\n");
        scanf("%[^end]", inputstr);
        fflush(stdin);
        while (1) {
            k++;


            // check if the current character being read is a digit
            if (isdigit(inputstr[k]) != 0 || inputstr[k]=='-') {
                // reads the current character
                buffer[i] = inputstr[k];


                // increamenting the counter so that the next
                // character is read in the next position in
                // the array of buffer
                i++;
                continue;
                //for != '\0'

            }

                // If the space " " is encounterd
                // then skip the character
                // and store the last read array of characters in
                // an integer array
            else {
                if (inputstr[k] == ' ') {
                    continue;
                }
                else if (inputstr[k] == '(') {
                    ky=1;
                    continue;}
                else if (inputstr[k] == ',') {
                    va=1;
                    if (ky==1) {
                        arrk[j] = atoi(buffer);

                        // Increamenting the array position
                        //j++;


                        // Clearing the buffer, this function takes two
                        // arguments, one is a character pointer and
                        // the other one is the size of the character array
                        bzero(buffer, 32);

                        // clearing the counter which counts the number
                        // of character in each number used for reading
                        // into the buffer.
                        i = 0;

                        ky=0;
                        // then continue
                        continue;
                    }
                }
                else if (inputstr[k] == ')') {
                    if (va==1) {
                        arrv[j] = atoi(buffer);

                        // Increamenting the array position
                        j++;


                        // Clearing the buffer, this function takes two
                        // arguments, one is a character pointer and
                        // the other one is the size of the character array
                        bzero(buffer, 32);

                        // clearing the counter which counts the number
                        // of character in each number used for reading
                        // into the buffer.
                        i = 0;
                        //incrementing the input counter
                        va=0;
                        // then continue
                        continue;
                    }
                }
                else {break;}


            }

        }
    }
        // in case filename is not "stdin" assume a file name is given

    else {
        char ch;
        FILE *fptr;

        // if file is not found
        if ((fptr = fopen(filename, "r")) == NULL) {
            printf("Error! opening file");

            // Program exits if the file pointer returns NULL.
            exit(1);
        }
        int k = -1;
        while (1) {
            // Reads the character where the seeker is currently
            ch = fgetc(fptr);
            k++;
            // If EOF is encountered then break out of the while loop
            if (ch == EOF) {
                break;
            }

            //printf("%c\n", ch);

            // check if the current character being read is a digit
            if (isdigit(ch) != 0 || ch == '-') {
                // reads the current character
                buffer[i] = ch;



                // increamenting the counter so that the next
                // character is read in the next position in
                // the array of buffer
                i++;
                continue;
                //for != '\0'

            }

                // If the space " " is encounterd
                // then skip the character
                // and store the last read array of characters in
                // an integer array
            else {
                if (ch == ' ') {
                    continue;
                } else if (ch == '(') {
                    ky = 1;
                    continue;
                } else if (ch == ',') {
                    va = 1;
                    if (ky == 1) {
                        arrk[j] = atoi(buffer);

                        // Increamenting the array position
                        //j++;


                        // Clearing the buffer, this function takes two
                        // arguments, one is a character pointer and
                        // the other one is the size of the character array
                        bzero(buffer, 32);

                        // clearing the counter which counts the number
                        // of character in each number used for reading
                        // into the buffer.
                        i = 0;

                        ky = 0;
                        // then continue
                        continue;
                    }
                } else if (ch == ')') {
                    if (va == 1) {
                        arrv[j] = atoi(buffer);

                        // Increamenting the array position
                        j++;


                        // Clearing the buffer, this function takes two
                        // arguments, one is a character pointer and
                        // the other one is the size of the character array
                        bzero(buffer, 32);

                        // clearing the counter which counts the number
                        // of character in each number used for reading
                        // into the buffer.
                        i = 0;
                        //incrementing the input counter
                        va = 0;
                        // then continue
                        continue;
                    }
                }


            }




        }
        fclose(fptr);


    }

    struct AVLTree* T = newAVLTree();
    struct AVLTreeNode* N =newAVLTreeNode(arrk[0],arrv[0]);

    struct AVLTreeNode* root;
    root = N;
    for (i=1;i<j;i++) {
        root = insert(root,arrk[i],arrv[i]);
    }
    T->root = root;
    T->size = i;
    return T;

}

// function that returns the node with the smallest key in a tree rooted in N
struct AVLTreeNode* minValNode(struct AVLTreeNode* N) {

    struct AVLTreeNode* current = N;

    while (current->left != NULL) {current = current->left;}

    return current;
}

// a recursive function called by the original deletenode function to delete a node
struct AVLTreeNode* DeleteNode1(AVLTreeNode *N,int k,int v,int* s) {

    if (N == NULL) { return N;}

    // if k is smaller than current key
    if (k < N->key) { N->left = DeleteNode1(N->left,k,v,s); }

        // if k is greater than current key
    else if (k > N->key) { N->right = DeleteNode1(N->right,k,v,s); }

    else if (k == N->key && v != N->value) { N->left = DeleteNode1(N->left,k,v,s); }

        // if key and value found
    else {
        // node with one or no children
        if ( (N->left == NULL) || (N->right == NULL) ) {
            // assign the child to temp if it exists
            struct AVLTreeNode *temp = N->left ? N->left : N->right;

            // if no children
            if (temp == NULL) {
                temp = N;
                N = NULL;
            }
            else {
                N->right = temp->right;
                N->left = temp->left;
                N->key = temp->key;
                N->value = temp->value;
                N->height = temp->height;
            }
            free(temp);
            *s += 1;
        }
            // node with two children
        else {
            // get the node with the smallest key in the right tree to replace it with
            struct AVLTreeNode* temp = minValNode(N->right);

            // copy its key and value
            N->key = temp->key;
            N->value = temp->value;

            // delete the copied node
            N->right = DeleteNode1(N->right,temp->key,temp->value,s);
        }
    }

    // in case it is the last node and it was deleted
    if (N == NULL) { return N;}

    // updating the height of the current node N
    N->height = 1 + max(height(N->left),height(N->right));

    // check if this node bacame unbalanced
    int balance = getBalance(N);

    // if it is unbalanced then check which case

    // Left Left
    if (balance > 1 && getBalance(N->left) >= 0) { return rightRotate(N);}

    // Left Right
    if (balance > 1 && getBalance(N->left) < 0) {
        N->left = leftRotate(N->left);
        return rightRotate(N);
    }

    // Right Right
    if (balance < -1 && getBalance(N->right) <= 0) { return leftRotate(N);}

    // Right Left
    if (balance < -1 && getBalance(N->right) > 0) {
        N->right = rightRotate(N->right);
        return leftRotate(N);
    }

    return N;
}


// recursive function that performs a single insertion and increases the size by one if added
struct AVLTreeNode* insert2(struct AVLTree* T, struct AVLTreeNode* node, int k, int v)
{

    if (node == NULL) {
        // return the new node
        T->size += 1;
        return (newAVLTreeNode(k, v));
    }

    // search the tree for the appropriate location
    if (k < node->key) {
        node->left = insert2(T, node->left, k, v);
        node->left->parent = node;
    }
    else if (k > node->key) {
        node->right = insert2(T, node->right, k, v);
        node->right->parent = node;
    }
    else {
        if (v < node->value) {
            node->left = insert2(T, node->left, k, v);
            node->left->parent = node;
        } else if (v > node->value) {
            node->right = insert2(T, node->right, k, v);
            node->right->parent = node;
        }
            // if duplicate do nothing
        else { return node;}
    }

    // updating the height
    node->height = 1 + max(height(node->left),
                           height(node->right));

    // get the balance
    int balance = getBalance(node);

    // If balance outside -1<= balance <= 1 then unbalanced

    // in case ks are not equal
    if (k != node->key) {
        // Left Left
        if (balance > 1 && k < node->left->key)
            return rightRotate(node);

        // Right Right
        if (balance < -1 && k > node->right->key)
            return leftRotate(node);

        // Left Right
        if (balance > 1 && k > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left
        if (balance < -1 && k < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
        // in case keys are equal then we use values to sort
    else {
        // Left Left
        if (balance > 1 && v < node->left->value)
            return rightRotate(node);

        // Right Right
        if (balance < -1 && v > node->right->value)
            return leftRotate(node);

        // Left Right
        if (balance > 1 && v > node->left->value)
        {
            node->left =  leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left
        if (balance < -1 && v < node->right->value)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    // return the same node
    return node;
}



// put the time complexity analysis for InsertNode() here
// it follows O(log(n)) time since it only goes through a number of nodes equal to the tree height at most using a recursive function
int InsertNode(AVLTree *T, int k, int v)
{
    if (T->root == NULL) {T->root = newAVLTreeNode(k,v);
        T->size +=1;
        return 1;}

    int sizebefore = T->size;
    // call the recusive insert function
    T->root = insert2(T, T->root, k, v);

    if (T->size > sizebefore) { return 1;}
    else { return 0;}
}


// put your time complexity for DeleteNode() here
// it follows O(log(n)) time since it only goes through a number of nodes equal to the tree height at most using a recursive function
int DeleteNode(AVLTree *T, int k, int v)
{
    // put your code here
    // if found return one if not return 0
    //update the size of the tree
    int ss = 0;
    int * s = &ss;
    T->root = DeleteNode1(T->root,k,v,s);
    if (ss == 1) {T->size -= 1;}

    return ss;
}

// recursive function called by the original function to print all nodes
void printnode(AVLTreeNode *N) {
    if (N==NULL){return;}
    printnode(N->left);

    printf("(%d,%d) %d\n", N->key,N->value,N->height);
    //if (N->parent != NULL) {printf("%d\n",N->parent->key);}

    printnode(N->right);
}


// put your time complexity analysis for PrintAVLTree() here
// it follows time O(n) since it uses a recursive function that goes through each node exactly once
void PrintAVLTree(AVLTree *T)
{
    // put your code here
    printnode(T->root);
}

// recursive function that clones a tree when given the root
// O is original and P is parent nodes
AVLTree *CloneAVLTreeNode(AVLTreeNode *O,AVLTreeNode *P)
{
    if (O==NULL) {return NULL;}

    struct AVLTreeNode *n = newAVLTreeNode(O->key,O->value);
    n->parent = P;
    n->height = O->height;

    n->left = CloneAVLTreeNode(O->left, n);
    n->right = CloneAVLTreeNode(O->right, n);

    return n;

}


// put your time complexity analysis for CloneAVLTree() here
// it follows time O(n) since it uses a recursive function that goes through each node exactly once
AVLTree *CloneAVLTree(AVLTree *T)
{
    // put your code here
    struct AVLTree *clone = newAVLTree();
    clone->root = CloneAVLTreeNode(T->root, NULL);
    clone->size = T->size;

    return clone;

}

// function that creates a sorted array from any binary tree
void sortedArr(struct AVLTreeNode* N, int arrk[], int arrv[], int *index) {

    if (N == NULL) { return;}

    // left child
    sortedArr(N->left, arrk, arrv, index);

    // add data to arr
    arrk[*index] = N->key;
    arrv[*index] = N->value;
    (*index)++;

    // right child
    sortedArr(N->right, arrk, arrv, index);
}

// function that computes the union of two sorted arrays
int unionArr(int uarrk[], int uarrv[], int arr1k[], int arr1v[], int arr2k[], int arr2v[], int size1, int size2) {


    int i=0; int j=0; int k=0;

    while (i<size1 && j<size2) {
        if (arr1k[i] < arr2k[j]) {
            uarrk[k] = arr1k[i];
            uarrv[k] = arr1v[i];
            i++; k++;
        }
        else if (arr1k[i] > arr2k[j]) {
            uarrk[k] = arr2k[j];
            uarrv[k] = arr2v[j];
            j++; k++;
        }
        else {
            if (arr1v[i] < arr2v[j]) {
                uarrk[k] = arr1k[i];
                uarrv[k] = arr1v[i];
                i++; k++;
            }
            else if (arr1v[i] > arr2v[j]) {
                uarrk[k] = arr2k[j];
                uarrv[k] = arr2v[j];
                j++; k++;
            }
            else {
                uarrk[k] = arr1k[i];
                uarrv[k] = arr1v[i];
                i++; j++; k++;
            }
        }
    }
    // in case items are still left in one of the arrays
    while (i<size1) {
        uarrk[k] = arr1k[i];
        uarrv[k] = arr1v[i];
        i++; k++;
    }
    while (j<size2) {
        uarrk[k] = arr2k[j];
        uarrv[k] = arr2v[j];
        j++; k++;
    }

    return k;
}

// function that computes the intersection of two sorted arrays
int intersectArr(int uarrk[], int uarrv[], int arr1k[], int arr1v[], int arr2k[], int arr2v[], int size1, int size2) {


    int i=0; int j=0; int k=0;

    while (i<size1 && j<size2) {
        if (arr1k[i] < arr2k[j]) {
            i++;
        }
        else if (arr1k[i] > arr2k[j]) {
            j++;
        }
        else {
            if (arr1v[i] < arr2v[j]) {
                i++;
            }
            else if (arr1v[i] > arr2v[j]) {
                j++;
            }
            else {
                uarrk[k] = arr1k[i];
                uarrv[k] = arr1v[i];
                i++; j++; k++;
            }
        }
    }

    return k;
}

// function that uses sorted arrays to create an AVL tree
struct AVLTreeNode* arrToTree(int arrk[], int arrv[], int start, int end) {

    if (start > end) { return NULL;}

    // make the middle int in arr a new node
    int mid = (start + end)/2;
    struct AVLTreeNode* N = newAVLTreeNode(arrk[mid], arrv[mid]);

    // left subtree
    N->left = arrToTree(arrk, arrv, start, mid-1);
    if (N != NULL && N->left != NULL) {N->left->parent = N;}


    // right subtree
    N->right = arrToTree(arrk, arrv, mid+1, end);
    if (N != NULL && N->right != NULL) {N->right->parent = N;}

    // set the height
    N->height = 1+max(height(N->left),height(N->right));


    return N;
}


// put your time complexity for ALVTreesUNion() here
// this function follows time O(m+n) where n and m are the sizes of the two trees
// creating each couple of sorted arrays for keys and values takes up time O(n) and O(m)
// creating the sorted union array takes O(m+n) at most
// creating the tree from the sorted array is also O(m+n)
// so O(2*(m+n)) is ~= O(m+n)
AVLTree *AVLTreesUnion(AVLTree *T1, AVLTree *T2)
{
    // put the first tree into an array
    int s1 = T1->size;
    int arr1k[s1];
    int arr1v[s1];
    int i = 0;
    sortedArr(T1->root, arr1k, arr1v, &i);

    // put the second tree into arr
    int s2 = T2->size;
    int arr2k[s2];
    int arr2v[s2];
    int j = 0;
    sortedArr(T2->root, arr2k, arr2v, &j);

    // compute the unoin of the two arrays
    int k;
    int uarrk[s1+s2];
    int uarrv[s1+s2];
    k = unionArr(uarrk, uarrv, arr1k, arr1v, arr2k, arr2v, s1, s2);

    // make the union arr into a tree
    struct AVLTree* U = newAVLTree();
    U->size = k;
    U->root = arrToTree(uarrk, uarrv, 0, k-1);

    return U;

}


// put your time complexity for ALVTreesIntersection() here
// this function follows time O(m+n) where n and m are the sizes of the two trees
// creating each couple of sorted arrays for keys and values takes up time O(n) and O(m)
// creating the sorted Intersection array takes O(m+n) at most
// creating the tree from the sorted array is also O(m+n)
// so O(2*(m+n)) is ~= O(m+n)
AVLTree *AVLTreesIntersection(AVLTree *T1, AVLTree *T2)
{
    // put the first tree into an array
    int s1 = T1->size;
    int arr1k[s1];
    int arr1v[s1];
    int i = 0;
    sortedArr(T1->root, arr1k, arr1v, &i);

    // put the second tree into arr
    int s2 = T2->size;
    int arr2k[s2];
    int arr2v[s2];
    int j = 0;
    sortedArr(T2->root, arr2k, arr2v, &j);

    // compute the unoin of the two arrays
    int k;
    int iarrk[s1+s2];
    int iarrv[s1+s2];
    k = intersectArr(iarrk, iarrv, arr1k, arr1v, arr2k, arr2v, s1, s2);

    // make the union arr into a tree
    struct AVLTree* I = newAVLTree();
    I->size = k;
    I->root = arrToTree(iarrk, iarrv, 0, k-1);

    return I;
}


// put your time complexity analysis for Search() here
// it follows O(log(n)) time since it only goes through a number of nodes equal to the tree height at most
AVLTreeNode *Search(AVLTree *T, int k, int v)
{
    // temp pointer
    struct AVLTreeNode *temp = T->root;

    // search the tree for k and v
    while (temp != NULL) {
        if (k > temp->key) { temp = temp->right;}

        else if (k < temp->key) { temp = temp->left;}

        else if (k == temp->key && v != temp->value) { temp = temp->left;}

        else {break;}
    }

    return temp;
}


// recursive function that frees the space of all nodes in a tree when given the root
void FreeAVLTreeNode(AVLTreeNode *N) {

    if (N == NULL) { return;}
    // Left
    FreeAVLTreeNode(N->left);

    // Right
    FreeAVLTreeNode(N->right);

    struct AVLTreeNode* temp = N;
    N = N->parent;
    // Free current node
    free(temp);

}

// put your time complexity analysis for freeAVLTree() here
// it follows time O(n) since it is a recursive function that goes through each node exactly once
void FreeAVLTree(AVLTree *T)
{
    // call the recursive fucntion to free all nodes
    FreeAVLTreeNode(T->root);

    // free the tree structure
    free(T);

}




int main() //sample main for testing
{ int i,j;
    AVLTree *tree1, *tree2, *tree3, *tree4, *tree5, *tree6, *tree7, *tree8;
    AVLTreeNode *node1;

    tree1=CreateAVLTree("stdin");
    PrintAVLTree(tree1);
    FreeAVLTree(tree1);
    //you need to create the text file file1.txt
    // to store a set of items without duplicate items
    tree2=CreateAVLTree("file1.txt");
    PrintAVLTree(tree2);
    tree3=CloneAVLTree(tree2);
    PrintAVLTree(tree3);
    FreeAVLTree(tree2);
    FreeAVLTree(tree3);
    //Create tree4
    tree4=newAVLTree();
    j=InsertNode(tree4, 10, 10);
    for (i=0; i<15; i++)
    {
        j=InsertNode(tree4, i, i);
        if (j==0) printf("(%d, %d) already exists\n", i, i);
    }

    PrintAVLTree(tree4);
    node1=Search(tree4,20,20);
    if (node1!=NULL)
        printf("key= %d value= %d\n",node1->key,node1->value);
    else
        printf("Key 20 does not exist\n");

    for (i=17; i>0; i--)
    {
        j=DeleteNode(tree4, i, i);
        if (j==0)
            printf("Key %d does not exist\n",i);
        PrintAVLTree(tree4);
    }
    FreeAVLTree(tree4);
    //Create tree5
    tree5=newAVLTree();
    j=InsertNode(tree5, 6, 25);
    j=InsertNode(tree5, 6, 10);
    j=InsertNode(tree5, 6, 12);
    j=InsertNode(tree5, 6, 20);
    j=InsertNode(tree5, 9, 25);
    j=InsertNode(tree5, 10, 25);
    PrintAVLTree(tree5);
    //Create tree6
    tree6=newAVLTree();
    j=InsertNode(tree6, 6, 25);
    j=InsertNode(tree6, 5, 10);
    j=InsertNode(tree6, 6, 12);
    j=InsertNode(tree6, 6, 20);
    j=InsertNode(tree6, 8, 35);
    j=InsertNode(tree6, 10, 25);
    PrintAVLTree(tree6);
    tree7=AVLTreesIntersection(tree5, tree6);
    tree8=AVLTreesUnion(tree5,tree6);
    PrintAVLTree(tree7);
    PrintAVLTree(tree8);
    return 0;
}
