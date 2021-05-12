# DataStructures
## Doubly Linked Lists and Sets

The functions implemented are shown as follows:

1. DLList *CreateDLListFromFileDlist(const char *filename). This function creates a doubly linked list of integers by reading all integers from a text file named filename, and returns a pointer to the doubly linked list where each node stores one integer. Assume that adjacent integers in the file filename and the standard input are separated by one or more white space characters or a new line character.
If filename is “stdin”, CreateDLListFromFileDlist (“stdin”) creates a doubly linked list by reading all integers from the standard input and the word end denotes the end of input.
This function must check for invalid input. In case of invalid input, it prints an error message “Invalid input!” and returns NULL.

2. void printDLList(DLList *u ). This function prints all the elements (integers) of a doubly linked list pointed by u in the order from the first node to the last node in the list on the standard output, one element per line. 

3. DLList *cloneList(DLList *u). This function creates an identical copy of a doubly linked list u and returns a pointer to the list cloned. (1.6 marks)

4. DLList *setUnion(DLList *u, DLList *v). This function computes the union of the two sets of integers that are stored in the doubly linked lists pointed by u and v, respectively, and returns a pointer to the doubly linked list that stores the union. Each element (int) of a set is stored in a node of the corresponding doubly linked list.
Given two sets A and B, the union of A and B is a set that contains all the distinct elementofAandB.Forexample,assumingthatA={2,8,5,7}andB={5,9,6,7}, A ꓴ B = {2, 8, 5, 7, 9, 6}. Note that in a set, all the integers are not necessarily sorted. 

5. DLList *setIntersection(DLList *u, DLList *v). This function computes the intersection of the two sets of integers that are stored in the doubly linked lists pointed by u and v, respectively, and returns a pointer to the doubly linked list that stores the intersection. Each element (int) of a set is stored in a node of the corresponding doubly linked list.
For simplicity, you may assume that all the elements of each input set are distinct for both set union and set intersection. Therefore, you do not need to check if a set contains duplicates.
Given two sets A and B, the intersection of A and B is a set that contains all the elements of A that are also in B. For example, assuming that A = {2, 8, 5, 7} and B = {5, 9,6,7}, AꓵB={5,7}.

6. void freeDLList(DLList *u). This function frees the space occupied by all the nodes of the doubly linked list pointed by u.

Time complexity analysis is estimated and written under each function.

## AVL Tree

You need to implement the following functions:
1. AVLTree *CreateAVLTree(const char *filename). This function creates an AVL tree by reading all the items from a text file or from the standard input (keyboard) depending on the argument filename. If filename is “stdin”, this function will read all the items from the standard input. Otherwise, it will read all the items from a text file with filename as its full path name. 
An input text file contains zero or more items where each item is of the form (key, value). Any characters such as white space between two adjacent items are ignored. For example, the following sample file contains 10 items:
(2, 50) (4, 30) (9, 30) (10, 400) (-5, -40)
(7, 20) (19, 200) (20, 50) (-18, -200) (-2, 29)
Similarly, when reading from the standard input, each input line may have zero or more items where each item is of the form (key, value). Any characters such as white space between two adjacent items are ignored. The word end indicates the end of input. A sample input is shown as follows:
(2, 50) (4, 30) (9, 30) (10, 400) (-5, -40)
(7, 20) (19, 200) (20, 50) (-18, -200) (-2, 29) end
In case of an error in the input, this function will print the error and your program terminates.
Assume that the input does not contain duplicate items and thus this function does not need to check for duplicate items.
The time complexity of this function cannot be higher than O(n logn), where n is the size of the resulting AVL tree. 

2. AVLTree *CloneAVLTree(AVLTree *T). This function creates an identical copy (clone) of the input AVL tree T, and returns a pointer to the clone tree. 
The time complexity of this function cannot be higher than O(n), where n is the size of T.

3. AVLTree *AVLTreesUnion(AVLTree *T1, AVLTree *T2). This function computes the union tree of two AVL trees T1 and T2 and returns a pointer to the union tree. The union tree of two AVL trees T1 and T2 is an AVL tree that contains all the items of both T1 and T2 without duplicate items. Assume that neither T1 nor T2 contains duplicate items. Note that this function does not make any change to T1 and T2. 
The time complexity of this function cannot be higher than O(m+n), where m and n are the sizes of T1 and T2, respectively. 
An example: consider the following two AVL trees T1 and T2:

![image](https://user-images.githubusercontent.com/84064508/117939364-5088e500-b34b-11eb-8209-cadc0f9dd79e.png)
![image](https://user-images.githubusercontent.com/84064508/117939455-6ac2c300-b34b-11eb-8a7e-ae6840e47b72.png)

The union tree of T1 and T2 is shown as follows:

![image](https://user-images.githubusercontent.com/84064508/117939491-72826780-b34b-11eb-807f-8be6b8fdc6f7.png)

Note that in general the union tree may not be unique with respect to shape (structure) depending on how it is constructed.

4. AVLTree *AVLTreesIntersection(AVLTree *T1, AVLTree *T2). This function computes the intersection tree of two AVL trees T1 and T2 and returns a pointer to the intersection tree. The intersection tree of two AVL trees T1 and T2 is an AVL tree that contains all the items that appear in both T1 and T2. Assume that neither T1 nor T2 contains duplicate items. Note that this function does not make any change to T1 and T2.
The time complexity of this function cannot be higher than O(m+n), where m and n are the sizes of T1 and T2, respectively, and k the size of the intersection tree. If your time complexity is higher, you will get 0 mark for this function.
An example: consider the previous two AVL trees T1 and T2. The intersection tree is shown as follows:

![image](https://user-images.githubusercontent.com/84064508/117939991-f6d4ea80-b34b-11eb-8841-2a8c2baad97f.png)

Note that in general the intersection tree may not be unique with respect to shape (structure) depending on how it is constructed.

5. int InsertNode(AVLTree *T, int k, int v). If the item (k, v) exists in the tree, this function simply returns 0 without adding the new item (k, v) to the tree. Otherwise, it inserts the new item (k, v) into the AVL tree T, increases the tree size by one and returns 1. 
The time complexity of this function cannot be higher than O(log n), where n is the size of T. 

6. int DeleteNode(AVLTree *T, int k, int v). If the item (k, v) exists in the AVL tree T, this function deletes the node containing this item, decreases the tree size by one and returns 1. Otherwise, it returns 0 only. 
The time complexity of this function cannot be higher than O(log n), where n is the size of T. 

7. AVLTreeNode *Search(AVLTree *T, int k, int v). This function search for the item (k, v) in the AVL tree T. If the item is found, it returns a pointer to the node containing the item. Otherwise, it returns NULL. 
The time complexity of this function cannot be higher than O(log n), where n is the size of T. 

8. void FreeAVLTree(AVLTree *T). This function frees up the heap space occupied by the AVL tree T. 

9. void PrintAVLTree(AVLTree *T). This function prints all the items and their heights stored in the AVL tree T sorted in non-decreasing order of keys on the standard output (screen). Each item is denoted by (key, value) with one item per line. For example, consider the following AVL tree:

![image](https://user-images.githubusercontent.com/84064508/117940247-3996c280-b34c-11eb-825b-720cb461fe33.png)

The output of PrintAVLTree is:
(6, 12), 1
(6, 20), 0
(6, 25), 2
(10, 25), 0
