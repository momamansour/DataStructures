// Author: Mohammed Almansour

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <assert.h>
#include <ctype.h>

// all the basic data structures and functions are included in this template
// you can add your own auxiliary functions as you like

// data structures representing DLList

// data type for nodes
typedef struct DLListNode {
    int  value;  // value (int) of this list item
    struct DLListNode *prev;
    // pointer previous node in list
    struct DLListNode *next;
    // pointer to next node in list
} DLListNode;

//data type for doubly linked lists
typedef struct DLList{
    int  size;      // count of items in list
    DLListNode *first; // first node in list
    DLListNode *last;  // last node in list
} DLList;

// create a new DLListNode
DLListNode *newDLListNode(int it)
{
    DLListNode *new;
    new = malloc(sizeof(DLListNode));
    assert(new != NULL);
    new->value = it;
    new->prev = new->next = NULL;
    return new;
}

// create a new empty DLList
DLList *newDLList()
{
    DLList *L;

    L = malloc(sizeof (struct DLList));
    assert (L != NULL);
    L->size = 0;
    L->first = NULL;
    L->last = NULL;
    return L;
}

// create a DLList from a text file
// put your time complexity analysis for CreateDLListFromFileDlist() here
// the big-O notation for this function is O(n + p) where n is the number of items in the input given
// including numbers and spaces and p is the number of integers in the input which is also the size of DLList
DLList *CreateDLListFromFileDlist(const char *filename)
{
    // buffer collects single digits for each number then stores them in arr
    // after converting them from char string to int
    int arr[100];
    char buffer[32];
    int i=0;
    int j=0;
    //
    // if stdin is given call input function
    if (filename=="stdin"){

        int k=0;
        int s=0;
        char inputstr[100];
        // ask for input and stop at "END"
        scanf("%[^END]", inputstr);
        fflush(stdin);
        while (1) {

            // check if the current character being read is a digit
            if (isdigit(inputstr[k]) != 0) {
                // reads the current character
                buffer[i] = inputstr[k];

                // increamenting the counter so that the next
                // character is read in the next position in
                // the array of buffer
                i++;
                s=0;

            }

                // If the space " " is encounterd
                // then skip the character
                // and store the last read array of characters in
                // an integer array
            else if (inputstr[k] == ' ') {
                // if the last character was a space as well
                if(s==1) {
                    k++;
                    continue;}

                // Converting the content of the buffer into
                // an array position

                arr[j] = atoi(buffer);

                // Increamenting the array position
                j++;


                // Clearing the buffer, this function takes two
                // arguments, one is a character pointer and
                // the other one is the size of the character array
                bzero(buffer, 32);
                s = 1;

                // clearing the counter which counts the number
                // of character in each number used for reading
                // into the buffer.
                i = 0;
                //incrementing the input counter
                k++;
                // then continue
                continue;
            }

                // when finding anything other than a space or a digit
            else {
                buffer[i] = inputstr[k];
                arr[j] = atoi(buffer);
                bzero(buffer, 32);
                s = 1;
                break;

            }
            k++;
        }
    }


        // in case filename is not "stdin" assume a file name is given
    else {
        char ch;
        FILE *fptr;
        int s = 0;


        // if file is not found
        if ((fptr = fopen(filename, "r")) == NULL) {
            printf("Error! opening file");

            // Program exits if the file pointer returns NULL.
            exit(1);
        }
        while (1) {
            // Reads the character where the seeker is currently
            ch = fgetc(fptr);

            // If EOF is encountered then break out of the while loop
            if (ch == EOF) {
                buffer[i] = ch;
                arr[j] = atoi(buffer);
                bzero(buffer, 32);
                j++;
                break;
            }

                // If the delimiter is encounterd(which can be
                // anything according to your wish) then skip the character
                // and store the last read array of characters in
                // an integer array
            else if (ch == ' ') {
                if (s == 1) {continue;}
                // Converting the content of the buffer into
                // an array position
                arr[j] = atoi(buffer);

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
                s = 1;
                // then continue
                continue;
            } else {

                // reads the current character in the buffer
                buffer[i] = ch;
                s = 0;
                // increamenting the counter so that the next
                // character is read in the next position in
                // the array of buffer
                i++;
            }
        }
        fclose(fptr);
    }










    // create a new DLList
    struct DLList* newlist = newDLList();
    newlist->size=j;
    // populate the list by creating nodes and filling them with values from arr
    for (i=0;i<j; i++) {
        struct DLListNode* newNode = newDLListNode(arr[i]);
        // the first node
        if (newlist->first == NULL) {
            newlist->first = newNode;
            newlist->last = newNode;
            continue;

        }
            // all nodes between first and last
        else if (i<j) {
            struct DLListNode* temp = newlist->first;
            struct DLListNode* newNode = newDLListNode(arr[i]);
            while (temp->next != NULL) temp = temp->next;
            temp->next = newNode;
            newNode->prev = temp;
        }
        // last node
        if (i==j) {
            newlist->last = newNode;
        }

    }


    return newlist;
}

// display items of a DLList
// put your time complexity analysis for printDDList() here
// the big-O notation for this function is O(n) and n is the size of the DLList u.
void printDLList(DLList *u) {
    // create a temp node and iterate through the list and print one by one
    struct DLListNode *temp = u->first;
    while (temp != NULL) {
        printf("%d\n", temp->value);
        temp = temp->next;
    }
    //free(temp);

}



// clone a DLList
// put your time complexity analysis for cloneList() here
// the big-O notation for this function is O(n) and n is the size of the DLList u.
DLList *cloneList(DLList *u)
{

    struct DLListNode* newNode;
    // create a new list and two temp nodes
    struct DLList* clone = newDLList();
    struct DLListNode *temp = u->first;
    struct DLListNode* fNode = newDLListNode(temp->value);
    // populate the first node
    temp = temp->next;
    clone->first = fNode;
    // populate the rest
    int i=0;
    while (temp != NULL) {
        i++;
        struct DLListNode* newNode = newDLListNode(temp->value);
        newNode->prev = fNode;
        newNode->prev->next = newNode;
        temp = temp->next;
        fNode = newNode;
        // assign a value to last in the list
        if (i == (u->size -1)) {clone->last = newNode;}


    }

    clone->size = u->size;

    return clone;
}


// compute the union of two DLLists u and v
// put your time complexity analysis for cloneList() here
// the big-O notation for this function is O(n*p) and n is the size of the DLList u and p is the size of the DLList v.
DLList *setUnion(DLList *u, DLList *v)
{

    int s=0;
    // create a clone of u
    struct DLList* c = cloneList(u);
    // create two temp node pointers to use for iteration
    struct DLListNode* temp = v->first;
    struct DLListNode* temp2 = u->first;
    // iterate through items in u and v
    while (temp != NULL) {
        while (temp2 != NULL) {
            // if item is in both in u and v then do nothing
            if (temp->value == temp2->value) {s=1; break;}

            temp2 = temp2->next;
            s=0;


        }
        // if not then s=0 and we can add the node it to the cloned u list
        if (s==0){
            struct DLListNode* newNode= newDLListNode(temp->value);
            newNode->prev = c->last;
            c->last->next = newNode;
            c->last = newNode;


        }
        temp = temp->next;
        temp2 = u->first;
    }

    return c;
}

// compute the insection of two DLLists u and v
// put your time complexity analysis for intersection() here
// the big-O notation for this function is O(n*p) and n is the size of the DLList u and p is the size of the DLList v.
DLList *setIntersection(DLList *u, DLList *v)
{

    int i=0;
    // similar to the union function create a new list and two temp node pointers
    struct DLList* d = newDLList();
    struct DLListNode* temp = v->first;
    struct DLListNode* temp2 = u->first;
    // iterate through all items in both lists
    while (temp != NULL) {
        while (temp2 != NULL) {
            // if a node is in both lists then add it create a copy and add it to the new list
            if (temp->value == temp2->value) {
                struct DLListNode *newNode = newDLListNode(temp->value);
                i++;
                // if it is the first node
                if (i == 1) {
                    d->first = newNode;
                    d->last = newNode;
                }
                    // after the first
                else {
                    d->last->next = newNode;
                    newNode->prev = d->last;
                    d->last = newNode;
                }

                break;
            }
            temp2 = temp2->next;
        }

        temp = temp->next;
        temp2 = u->first;


    }
    //free(temp);
    //free(temp2);
    return d;
}


// free up all space associated with list
// put your time complexity analysis for freeDLList() here
// the big-O notation for this function is O(n) and n is the size of the DLList u.
void freeDLList(DLList *L) {

    // create two temp node pointers assign one of them to the first
    struct DLListNode* temp;
    struct DLListNode* head = L->first;

    // iterate through all nodes and free them
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }


}



int main()
{
    DLList *list1, *list2, *list3, *list4;

    list1=CreateDLListFromFileDlist("/Users/Mohammed/CLionProjects/untitled2/File1.txt");
    printDLList(list1);

    list2=CreateDLListFromFileDlist("/Users/Mohammed/CLionProjects/untitled2/File2.txt");
    printDLList(list2);

    list3=setUnion(list1, list2);
    printDLList(list3);

    list4=setIntersection(list1, list2);
    printDLList(list4);

    freeDLList(list1);
    freeDLList(list2);
    freeDLList(list3);
    freeDLList(list4);

    printf("please type all the integers of list1\n");
    list1=CreateDLListFromFileDlist("stdin");

    printf("please type all the integers of list2\n");
    list2=CreateDLListFromFileDlist("stdin");

    list3=cloneList(list1);
    printDLList(list3);
    list4=cloneList(list2);
    printDLList(list4);

    freeDLList(list1);
    freeDLList(list2);
    freeDLList(list3);
    freeDLList(list4);

    return 0;
}
