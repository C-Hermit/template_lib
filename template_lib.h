#ifndef _STL_LIB_H_
#define _STL_LIB_H_

#include<iostream>
#include<iterator>
#include<algorithm>
/* ------------------------------- linearlist ------------------------------- */
template<class T>
class linearlist
{
    public:
        virtual ~linearlist(){};
        virtual bool empty()const=0;
        //check to see if it is empty
        virtual int length()const=0;
        //get the number 0f elements in linearlist
        virtual int index_of(const T &the_element)const=0;
        //get the index of the element
        virtual T &get(const int the_index)const=0;
        //get the element of the index
        virtual void erase(const int the_index)=0;
        //erase the element of the index
        virtual void insert(const T &the_element,const int the_index)=0;
        //insert the element to the index
        virtual void output(std::ostream& out)const=0;
        //output a linearlist
};
template<class T>
class array_linearlist:public linearlist<T>
{
    public:
        //instrct
        array_linearlist(int initial_capacity=10);
        array_linearlist(const array_linearlist<T> &the_list);
        ~array_linearlist();
        //ADT function
        bool empty()const;
        int length()const;
        int index_of(const T &the_element)const;
        T &get(const int the_index)const;
        void erase(const int the_index);
        void insert(const T &the_element,const int the_index);
        void output(std::ostream& out)const;
    protected:
        void chack_the_index(const int the_index)const;

        T *element;//->array
        int array_length;//the number of elements 
        int array_size;//the size of elements
};
template<class T>
class chain_node
{
    public:
        T element;
        chain_node<T> *next;
        chain_node(const T &the_element)
                :element(the_element){};
        chain_node(const T &the_element,chain_node<T> *the_next)
                :element(the_element){next=the_next;};
};
template<class T>
class chain_linearlist:public linearlist<T>
{
    public:
        //instuct
        chain_linearlist(const int initial_capacity=10);
        chain_linearlist(const chain_linearlist<T> &the_list);
        ~chain_linearlist();
        //ADT function
        bool empty()const;
        int length()const;
        int index_of(const T &the_element)const;
        T& get(const int the_index)const;
        void erase(const int the_index);
        void insert(const T &the_element);//insert from head
        void insert(const T &the_element,const int the_index);//insert from the_index
        void output(std::ostream &out)const;
    protected:
        void chack_the_index(const int the_index)const;

        chain_node<T> *head_node;
        int chain_length;
};
template<class T>
class circularchain_linearlist:public linearlist<T>
{
    public:
        //instruct
        circularchain_linearlist(const int initial_capacity=10);
        circularchain_linearlist(const circularchain_linearlist<T> &the_list);
        ~circularchain_linearlist();
        //ADT function
        bool empty()const;
        int  length()const;
        int index_of(const T &element)const;
        T &get(const int the_index)const;
        void erase(const int the_index);
        void insert(const T &the_element);
        void insert(const T &the_element,const int the_index);
        void output(std::ostream &out)const;
    protected:
        void chack_the_index(const int the_index)const;

        chain_node<T> *head_node;
        int circularchain_length;
};
template<class T>
class bidirectionalchain_node
{
    public:
        T element;
        bidirectionalchain_node<T> *previous;
        bidirectionalchain_node<T> *next;
};
template<class T>
class bidirectionalchain_linearlist:public linearlist<T>
{
    public:
        //instrect
        bidirectionalchain_linearlist(const int initial_capacity=10);
        bidirectionalchain_linearlist(const bidirectionalchain_linearlist<T> &the_list);
        ~bidirectionalchain_linearlist();
        //ADT function
        bool empty()const;
        int length()const;
        int index_of(const T &the_element)const;
        T &get(const int the_index)const;
        void erase(const int the_index);
        void insert(const T &the_element);
        void insert(const T &the_element,const int the_index);
        void output(std::ostream &out)const;
    protected:
        void chack_the_index(const int the_index)const;

        bidirectionalchain_node<T> *head_node;
        bidirectionalchain_node<T> *tail_node;
        int bidrectionalchain_length;
};
/* ---------------------------------- stack --------------------------------- */
template<class T>
class stack
{
    public:
        virtual ~stack(){};
        virtual bool empty()const=0;
        //chack to see if it is empty
        virtual int length()const=0;
        //get the number of elements in stack
        virtual T &top()=0;
        //get reference to the top element
        virtual void pop()=0;
        //delete the top element
        virtual void push(const T &the_element)=0;
        //push the_element to the top of the stack
};
template<class T>
class array_stack:public stack<T>
{
    public:
        array_stack(const int initial_capacity=10);
        ~array_stack();
        bool empty()const;
        int length()const;
        T &top();
        void pop();
        void push(const T &the_element);
    protected:
        int stack_length;//the top of stack
        int stack_size;//stack capacity
        T *stack;//element array
};
template<class T>
class chain_stack:public stack<T>
{
    public:
        chain_stack(const int initial_capacity=10);
        ~chain_stack();
        bool empty()const;
        int length()const;
        T &top();
        void pop();
        void push(const T &the_element);
    protected:
        int stack_length;//the number of element in chain_stack
        chain_node<T> *stack;//->the top element
};
/* ---------------------------------- queue --------------------------------- */
template<class T>
class queue
{
    public:
        virtual ~queue(){};
        virtual bool empty()const=0;
        virtual int length()const=0;
        virtual T &front()=0;
        virtual T &back()=0;
        virtual void pop()=0;
        virtual void push(const T &the_element)=0;
};
template<class T>
class array_queue: public queue<T>
{
    public:
        array_queue(const int initial_capacity=10);
        ~array_queue();
        bool empty()const;
        int length()const;
        T &front();
        T &back();
        void pop();
        void push(const T &the_element);
    protected:
        int queue_front;
        int queue_back;
        int queue_size;
        T *queue;
};
template<class T>
class chain_queue:public queue<T>
{
    public:
        chain_queue(const int initial_capacity=10);
        ~chain_queue();
        bool empty()const;
        int length()const;
        T &front();
        T &back();
        void pop();
        void push(const T &the_element);
    protected:
        chain_node<T> *queue_front;
        chain_node<T> *queue_back;
        int queue_length;
};
/* ------------------------------- dictionary ------------------------------- */
template<class K,class E>
class dictionary
{
    public:
        virtual ~dictionary(){};
        virtual bool empty()const=0;
        virtual int length()const=0;
        virtual std::pair<const K,E> *find(const K &the_key)const=0;
        virtual void insert(const std::pair<const K,E>&the_keypair)=0;
        virtual void erase(const K &the_key)=0;
};
template<class K,class E>
class array_dictionary:public dictionary<K,E>
{
    public:
        array_dictionary(const int initial_capacity=10);
        ~array_dictionary();
        bool empty()const;
        int length()const;
        std::pair<const K,E> *find(const K& the_key)const;
        void insert(const std::pair<const K,E> &the_keypair);
        void erase(const K &the_key);
        void output(std::ostream &out)const;
    protected:
        std::pair<K, E> *dictionary;
        int dictionary_length;
        int dictionary_size;
};
template<class K,class E>
class chain_dictionary:public dictionary<K,E>
{
    public:
        chain_dictionary(const int initial_capacity=10);
        ~chain_dictionary();
        bool empty()const;
        int length()const;
        std::pair<const K,E> *find(const K &the_key)const;
        void insert(const std::pair<const K,E> &the_keypair);
        void erase(const K &the_key);
        void output(std::ostream &out)const;
    protected:
        chain_node<std::pair<const K,E>> *head_node;
        int dirtionary_length;
};
template<class K,class E>
class skip_node
{
    public:
        std::pair<const K,E> element;
        skip_node<K,E> **next;
        skip_node(const std::pair<const K,E> &the_element,int size)
                :element(the_element){next=new skip_node<K,E> *[size];}
};
template<class K,class E>
class skiplist_dictionary:public dictionary<K,E>
{
    public:
        skiplist_dictionary(K the_maxkey,int max_pairs,float probability);
        ~skiplist_dictionary();
        bool empty()const;
        int length()const;
        std::pair<const K,E> *find(const K &the_key)const;
        void insert(const std::pair<const K,E> &the_keypair);
        void erase(const K &the_key);
        void output(std::ostream &out)const;
    protected:
        float cutoff;//the probability of grading
        int level()const;
        int levels;//maximun non-empty chainlist
        int max_level;
        int dirctionary_length;//the number of elements in dictionary
        K max_key;//the element in tail_node
        skip_node<K,E> *search(const K &the_key)const;

        skip_node<K,E> *head_node;
        skip_node<K,E> *tail_node;
        skip_node<K,E> **last;//an array of final nodes for each level

};
template<class K>class hash;
template<> 
class hash<std::string>
{
    public:
        size_t operator()(const std::string the_key)const
        {
            unsigned long hashvalue=0;
            int length =(int)the_key.length();
            for (int  i = 0; i < length; i++)
            {
                hashvalue=5*hashvalue+the_key.at(i);
            }
            return size_t(hashvalue);
        }
};
template<> 
class hash<int>
{
    public:
        size_t operator()(const int the_key)const{return size_t(the_key);};
};
template<> 
class hash<float>
{
    public:
        size_t operator()(const long the_key)const{return size_t(the_key);};
};
template<class K,class E>
class hashtable_dictionary:public dictionary<K,E>
{
    public:
        hashtable_dictionary(int the_divisor=11);
        ~hashtable_dictionary();
        
        bool empty()const;
        int length()const;
        std::pair<const K,E> *find(const K&the_key)const;
        void insert(const std::pair<const K,E> &the_keypair);
        void erase(const K &the_key);
        void output(std::ostream &out)const;
    protected:
        int search(const K &the_key)const;
        hash<K> hash;
        std::pair<const K,E> **table;
        int dictionary_length;
        int divisor;
};
template<class K,class E>
class hashchains_dictionary:public dictionary<K,E>
{
    public:
        hashchains_dictionary(int the_divisor);
        ~hashchains_dictionary();

        bool empty()const;
        int length()const;
        std::pair<const K,E> *find(const K &the_key)const;
        void insert(const std::pair<const K,E> &the_keypair);
        void erase(const K  &the_key);
        void output(std::ostream &out)const;
    protected:
        chain_dictionary<K,E> *table;
        hash<K> hash;
        int dictionary_length;
        int divisor;
};
/* ------------------------------- binarytree ------------------------------- */
template<class T>
class binarytree
{
    public:
        virtual ~binarytree(){};
        virtual bool empty()const=0;
        virtual int length()const=0;
        virtual void pre_order(void(*)(T *))=0;
        virtual void in_order(void (*)(T *))=0;
        virtual void post_order(void (*)(T *))=0;
        virtual void level_order(void (*)(T *))=0;
};
template<class T>
class array_binarytree:public binarytree<T>
{
    public:
        array_binarytree(int initial_capacity=10);
        ~array_binarytree();
        bool empty()const;
        int length()const;
        T *root_element()const;
        void insert(T the_element);
        void pre_order(void (*the_visit)(T *));
        void in_order(void (*the_visit)(T *));
        void post_order(void (*the_visit)(T *));
        void level_order(void (*the_visit)(T *));
        void pre_order_output();
        void in_order_output();
        void post_order_output();
        void level_order_output();
    protected:
        T *element;
        int binarytree_length;
        int binarytree_size;
        void (*visit)(T *);
        void pre_order(int i);
        void in_order(int i);
        void post_order(int i);
        static void output(T *t);
};
template<class T>
class binarytree_node
{
    public:
        T element;
        binarytree_node *left_child;
        binarytree_node *right_child;
        binarytree_node(){left_child=right_child=NULL;}
        binarytree_node(const T &the_element):element(the_element)
        {
            left_child=right_child=NULL;
        }
        binarytree_node(const T &the_element,binarytree_node<T> *the_leftchild,binarytree_node<T> *the_rightchild)
        :element(the_element)
        {
            left_child=the_leftchild;
            right_child=the_rightchild;
        }
};
template<class T>
class chain_binarytree:public binarytree<binarytree_node<T>>
{
    public:
        chain_binarytree();
        ~chain_binarytree();
        bool empty()const;
        int length()const;
        T *root_element()const;
        void make_tree(const T &element,chain_binarytree<T>&,chain_binarytree<T>&);
        void pre_order(void(*the_visit)(binarytree_node<T> *));
        void in_order(void (*the_visit)(binarytree_node<T> *));
        void post_order(void (*the_visit)(binarytree_node<T> *));
        void level_order(void (*the_visit)(binarytree_node<T> *));
        void pre_order_output();
        void in_order_output();
        void post_order_output();
        void level_order_output();
        void erase();
        int height()const;
    protected:
        binarytree_node<T> *root;
        int binarytree_length;//the numbers of elements in binarytree
        void (*visit)(binarytree_node<T> *);
        int count;//used to count nodes in subtree
        void pre_order(binarytree_node<T> *t);
        void in_order(binarytree_node<T> *t);
        void post_order(binarytree_node<T> *t);
        void count_nodes(binarytree_node<T> *t);
        static void dispose(binarytree_node<T> *t);
        static void output(binarytree_node<T> *t);
        void add_to_nodes(binarytree_node<T> *t);
        static int height(binarytree_node<T> *t);
};
/* ---------------------------- maxpriority_queue --------------------------- */
template<class T>
class maxpriority_queue
{
    public:
        virtual ~maxpriority_queue(){}
        virtual bool empty()const=0;
        virtual int length()const=0;
        virtual const T &top()const=0;
        virtual void pop()=0;
        virtual void push(const T &the_element)=0;
};
template<class T>
class array_maxpriority_queue:public maxpriority_queue<T>//maxheep
{
    public:
        array_maxpriority_queue(int initial_capacity=10);
        ~array_maxpriority_queue();
        bool empty()const;
        int length()const;
        const T &top()const;
        void pop();
        void push(const T &the_element);
        void initialize(T *the_queue,int length);
        void deactivate_array();
        void output(std::ostream &out)const;
    protected:
        T *queue;
        int queue_length;
        int queue_size;
};
template<class T>
class chain_maxpriority_queue:public maxpriority_queue<T>,
                              public chain_binarytree<std::pair<int,T>>
{
    public:
        bool empty()const;
        int length()const;
        const T &top()const;
        void pop();
        void push(const T &the_element);
        void initialize(T *the_element,int the_length);
        void meld(chain_maxpriority_queue<T> &the_element);
        void output();
    private:
        void meld(binarytree_node<std::pair<int,T>> *&x,binarytree_node<std::pair<int,T>> *&y);
        static void nodeoutput(binarytree_node<std::pair<int,T>> *t);
};
/* ----------------------------- competitivetree ---------------------------- */
template<class T>
class competitivetree
{
    public:
        virtual ~competitivetree(){};
        virtual void initialise(T *the_player,int the_number_of_player)=0;
        virtual int competitor()const=0;
        virtual void replay(int the_player)=0;
};
template<class T>
class  winner_competitivetree:public competitivetree<T>
{
    public:
        winner_competitivetree(T *the_player,int player_number);
        ~winner_competitivetree();
        void initialise(T *the_player,int player_number);
        int competitor()const;
        int competitor(int i)const;
        void replay(int the_player);
        void output()const;
    private:
        int lowExt;           // lowest-level external nodes
        int offset;           // 2^log(n-1) - 1
        int *tree;            // array for winner tree
        int players_number;
        T *player;            // array of players
        void play(int, int, int);
};
#include"template_lib.inl"
#endif