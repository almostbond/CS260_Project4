Skip to content
Search or jump to…

Pull requests
Issues
Marketplace
Explore

@almostbond
Learn Git and GitHub without any code!
Using the Hello World guide, you’ll start a branch, write comments, and open a pull request.


almostbond
/
CS260_Project4
1
00
Code
Issues
Pull requests
Actions
Projects
Wiki
Security
Insights
Settings
CS260_Project4 / Week 4 Arbitrary list operations.cpp
@almostbond
almostbond Add files via upload
Latest commit 566daf3 29 days ago
History
1 contributor
350 lines(247 sloc)  7.22 KB

// Week 3 project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*uses a linked-list to store values in the queue
has an enqueue method that will appropriately add a value to the back of the queue as an appropriate element
has a dequeue method that will appropriately remove an element from the front of the queue and return its value
Optionally has a peek method that returns the value at the front of the queue without removing it
Bonus if you also create an array based Queue!*/


#include <iostream>
#include "Header.h"

using namespace std;



// constructors.
List::List() {

    list_length = 0;
    head = NULL;
    tail = NULL;
    current = NULL;
    temp = NULL;
}

Test::Test() {}

// Creates a new node and assigns it a value and a spot at the back of the queue.
void List::push(int add_val) {

    node* new_node = new node;

    new_node->next = tail;
    new_node->value = add_val;
    if (head == NULL) {
        new_node->next = NULL;
        head = new_node;
        tail = new_node;
    }
    else {

        tail = new_node;
    }

    ++list_length;
}
// deletes the eldest node and returns its value.
int List::pop() {

    int popped_val = NULL;
    current = tail;
    temp = head;
    popped_val = temp->value;
    // this feels like it would get very slow in the future if a large node was created.
    while (current->next != temp) {

        current = current->next;
    }


    free(head);
    head = current;
    head->next = NULL;


    cout << "Value popped: " << popped_val << endl;
    cout << "Memory Address freed: " << temp << endl;

    return popped_val;
}

// prints the head and tail of the queue.
void List::peek() {

    cout << "Head value: " << head->value << endl;
    cout << "Tail value: " << tail->value << endl;
}


//prints all node values in the stack.
void List::print_list() {

    current = tail;
    while (current != NULL) {
        cout << current->value << ", ";
        current = current->next;

    }
    cout << endl << endl;
}

// O(n) complexity; After a fair amount of effort I have come to the conclusion that 
//insert is unable to have the same functionality as push without being exceedingly complicated.
void List::insert(int item_pos, int item_val) {

    int steps = 0;
    current = tail;

    node* new_node = new node;
    new_node->value = item_val;


    if (item_pos <= 0) {
        head->next = new_node;
        head = new_node;
        head->next = NULL;
    }

    if (item_pos > list_length) {

        new_node->next = tail;
        tail = new_node;
    }

    if (item_pos != 0 and item_pos <= list_length) {
        while (steps != (list_length - item_pos)) {

            steps++;
            current = current->next;

        }

        temp = current->next;
        new_node->next = temp;
        current->next = new_node;


    }

    ++list_length;
    //cout << "list length: " << list_length << endl;
}

// O(n)
int List::remove(int item_pos) {
    current = tail;
    int steps = 0;
    int removed_val = 0;

    //empty list condition
    if (list_length == 0) {
        cout << "there's nothing to remove";
        return 0;
    }

    //removes head node.
    if (item_pos == 0) {
        while (steps != (list_length - 2)) {

            steps++;
            current = current->next;
        }

        removed_val = head->value;
        free(head);
        current->next = NULL;
        head = current;
        return removed_val; //breaks without this return for some reason.
    }

    // removes tail node
    if (item_pos >= list_length) {
        removed_val = tail->value;
        temp = current->next;
        free(tail);
        tail = temp;

    }

    // removes arbitrary node
    else {
        while (steps != (list_length - item_pos - 2)) {

            steps++;
            current = current->next;

        }
        temp = current->next;
        removed_val = temp->value;
        current->next = temp->next;
        free(temp);
    }


    --list_length;
    return removed_val;
}

//
int List::get(int item_pos) {

    int item_value = 0;
    if (list_length == 0) {
        cout << "no ist to get values from." << endl;
        return 0;
    }

    if (item_pos == 0) {
        return head->value;
    }

    current = tail;
    for (int i = 0; i < (list_length - item_pos); i++) {

        current = current->next;

    }
    item_value = current->value;
    //cout << "got value: "<< item_value << endl;
    return item_value;
}

void List::menu() {

    cout << "press 0 to quit" << endl;
    cout << "press 1 to push" << endl;
    cout << "press 2 to pop" << endl;
    cout << "press 3 to peek" << endl;

    int menu = 0;


    bool loop = true;
    while (loop == true) {
        cout << "Enter a number: ";
        cin >> menu;
        if (menu == 1) {
            int node_val;
            cout << "enter an integer value you'd like to store." << endl;
            cin >> node_val;
            push(node_val);

        }
        if (menu == 2) {
            pop();

        }
        if (menu == 3) {
            peek();

        }
        if (menu == 0) {
            loop = false;
        }
    }
}

// ~~~~testing stuff~~~~


void Test::test1_get() {
    for (int i = 0; i < 10; i++) {

        push(i);
    }
    print_list();
    cout << get(0) << endl;
    cout << get(20) << endl;// For some reason that I dont entirely understand when item_pos is any number larger than the length of the list it doesn't have any issues. its a feature not a bug :)
    cout << get(5) << endl;// works as normal 
}
//test1 demonstrates insertion at the head, tail, and an arbitary location.
void Test::test1_insert() {

    // populates the list
    for (int i = 0; i < 10; i++) {

        push(i);
    }

    //prints the stacks values
    print_list();
    //using our get function we can confirm that the values are inserted into the correct position.
    insert(11, 18);
    if (get(11) == 18) {
        cout << "tail insertion pass;" << endl;
    }
    insert(0, 42);
    if (get(0) == 42) {
        cout << "head insertion pass;" << endl;
    }

    insert(3, 99);
    if (get(3) == 99) {
        cout << "arbitrary insertion pass;" << endl;
    }

    print_list();

    peek();




}

//test1 demonstrates removal from the head, tail, and an arbitrary location.
void Test::test1_remove() {


    for (int i = 0;i < 5;i++) {
        push(i);
    }


    print_list();
    remove(3);
    print_list();
    remove(0);
    print_list();
    remove(12);

}
//test2 tries to remove from an empty list.
void Test::test2_remove() {

    remove(0);
}




int main()
{
    List listy;
    Test testy;
    // Uncomment to manually use.
    //listy.menu();

    //Testing

    //get tests
    //testy.test1_get();

    //insert tests
    testy.test1_insert();


    // remove tests
    //testy.test1_remove();
    //testy.test2_remove();

    cout << "Successful Exit." << endl;
}


