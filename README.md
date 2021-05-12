# DataStructures
## Doubly Linked Lists and Sets

The functions implemented are shown as follows:

1. DLList *CreateDLListFromFileDlist(const char *filename). This function creates a doubly linked list of integers by reading all integers from a text file named filename, and returns a pointer to the doubly linked list where each node stores one integer. Assume that adjacent integers in the file filename and the standard input are separated by one or more white space characters or a new line character.
If filename is “stdin”, CreateDLListFromFileDlist (“stdin”) creates a doubly linked list by reading all integers from the standard input and the word end denotes the end of input.
This function must check for invalid input. In case of invalid input, it prints an error message “Invalid input!” and returns NULL.

2. void printDLList(DLList *u ). This function prints all the elements (integers) of a doubly linked list pointed by u in the order from the first node to the last node in the list on the standard output, one element per line. 

3. DLList *cloneList(DLList *u). This function creates an identical copy of a doubly linked list u and returns a pointer to the list cloned. (1.6 marks)

4. DLList *setUnion(DLList *u, DLList *v). This function computes the union of the two sets of integers that are stored in the doubly linked lists pointed by u and v, respectively, and returns a pointer to the doubly linked list that stores the union. Each element (int) of a set is stored in a node of the corresponding doubly linked list.
Given two sets A and B, the union of A and B is a set that contains all the distinct elementofAandB.Forexample,assumingthatA={2,8,5,7}andB={5,9,6,7}, A ꓴ B = {2, 8, 5, 7, 9, 6}. Note that in a set, all the integers are not necessarily sorted. (2 marks)

5. DLList *setIntersection(DLList *u, DLList *v). This function computes the intersection of the two sets of integers that are stored in the doubly linked lists pointed by u and v, respectively, and returns a pointer to the doubly linked list that stores the intersection. Each element (int) of a set is stored in a node of the corresponding doubly linked list.
For simplicity, you may assume that all the elements of each input set are distinct for both set union and set intersection. Therefore, you do not need to check if a set contains duplicates.
Given two sets A and B, the intersection of A and B is a set that contains all the elements of A that are also in B. For example, assuming that A = {2, 8, 5, 7} and B = {5, 9,6,7}, AꓵB={5,7}.

6. void freeDLList(DLList *u). This function frees the space occupied by all the nodes of the doubly linked list pointed by u.

Time complexity analysis: For each function, you need to analyze its time complexity in terms of big-O notation and put your analysis as comments immediately before the code of the function. You may assume that a single execution of each built-in I/O function such as printf(), malloc() and free(), takes O(1) time.

