



class List {

private:

    
    int list_length;

    struct node {
        int value;
        node* next;

    };

    typedef struct node* nodeptr;

    nodeptr head;
    nodeptr tail;
    nodeptr current;
    nodeptr temp;

public:
    List();

    
    void push(int add_val);
    void insert(int item_pos, int item_val);
    int remove(int item_pos);
    int pop();
    int get(int item_pos);
    void peek();
    void print_list();
    void menu();


};


class Test : public List {

public:
    Test();
    void test1_get();
    void test1_insert();
    void test2_insert();
    void test1_remove();
    void test2_remove();
};


