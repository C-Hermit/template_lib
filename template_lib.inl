#ifndef _STL_LIB_INL_
#define _STL_LIB_INL_

#include<math.h>
#include<iostream>
#include<iterator>
#include<algorithm>
#include"template_lib.h"
/* -------------------------------------------------------------------------- */
/*                                 linearlist                                 */
/* -------------------------------------------------------------------------- */
/* ---------------------------- array_linearlist ---------------------------- */
//instruct
template<class T>
array_linearlist<T>::array_linearlist(int initial_capacity)
{
    //check initial capacity is valid
    if(initial_capacity<1)
    {
        throw std::runtime_error("initial_capacity is invalid");
    }    

    element=new T[initial_capacity];
    array_length=0;
    array_size=initial_capacity;
};
template<class T>
array_linearlist<T>::array_linearlist(const array_linearlist<T>&the_list)
{
    element=new T[the_list.array_length];
    array_length=the_list.array_length;
    array_size=the_list.array_size;
    std::copy(the_list.element,the_list.element+the_list.array_length,element);

};
template<class T>
array_linearlist<T>::~array_linearlist(){delete[] element;};
//ADT function
template<class T>
bool array_linearlist<T>::empty()const{return array_length==0;};
template<class T>
int array_linearlist<T>::length()const{return array_length;};
template<class T>
int array_linearlist<T>::index_of(const T &the_element)const
{
    int the_index=(int)(std::find(element,element+array_length,the_element)-element);
    if(the_index==array_length)
    {
        return -1;
    }
    else return the_index;
}
template<class T>
T &array_linearlist<T>::get(const int the_index)const
{
    //chack the_index is valid
    chack_the_index(the_index);
    return element[the_index];
}
template<class T>
void array_linearlist<T>::erase(const int the_index)
{
    chack_the_index(the_index);
    std::copy(element+the_index+1,element+array_length,element+the_index);
    array_length--;

}
template<class T>
void array_linearlist<T>::insert(const T &the_element,const int the_index)
{

    if(the_index<0||the_index>array_size)
    {
        throw std::runtime_error("the_index is invaild");
    }
    if (the_index==array_size)//no space
    {
        T *tamp=new T[array_size*2];
        std::copy(element,element+array_size,tamp);
        delete[] element;
        element=tamp;
    }

    std::copy(element+the_index,element+array_length,element+the_index+1);
    element[the_index]=the_element;
    array_length++;
}
template<class T>
void array_linearlist<T>::output(std::ostream &out)const
{
    std::copy(element,element+array_length,std::ostream_iterator<T>(std::cout,""));
}
template <class T>
std::ostream& operator<<(std::ostream &out, const array_linearlist<T>& x){x.output(out); return out;}
template<class T>
void array_linearlist<T>::chack_the_index(const int the_index)const
{
    if(the_index<0||the_index>=array_length)
    {
        throw std::runtime_error("the_index is invaild");
    }
}
/* ---------------------------- chain_linearlist --------------------------- */
template<class T>
chain_linearlist<T>::chain_linearlist(int initial_capacity)
{
    if(initial_capacity<1)
    {
        throw std::runtime_error("initail_capcity is invalid");
    }
    head_node=NULL;
    chain_length=0;
};
template<class T>
chain_linearlist<T>::chain_linearlist(const chain_linearlist<T>& the_list)
{
    chain_length=the_list.chain_length;
    if (chain_length==0)
    {
        head_node=NULL;
        return;
    }
    chain_node<T> *source_node=the_list.head_node;

    head_node=new chain_node<T>;
    head_node->element=source_node->element;
    source_node=source_node->next;

    chain_node<T> *temp_node=head_node;
    while (source_node!=NULL)
    {
        temp_node->next=new chain_node<T>;
        temp_node->next->element=source_node->element;

        temp_node=temp_node->next;
        source_node=source_node.next;
    }
    temp_node->next=NULL;
};
template<class T>
chain_linearlist<T>::~chain_linearlist()
{
    while (head_node!=NULL)
    {
        chain_node<T> *temp_node=head_node->next;
        delete head_node;
        head_node=temp_node;
    }
};
template<class T>
bool chain_linearlist<T>::empty()const{return chain_length==0;};
template<class T>
int chain_linearlist<T>::length()const{return chain_length;};
template<class T>
int chain_linearlist<T>::index_of(const T &the_element)const
{
    int the_index=0;
    chain_node<T> *temp_node=head_node;
    while (temp_node!=NULL)
    {
        if(temp_node->element=the_element)
        {
            return the_index;
        }
        the_index++;
        temp_node=temp_node->next;
    }
    return -1;
};
template<class T>
T &chain_linearlist<T>::get(const int the_index)const
{
    chack_the_index(the_index);
    chain_node<T> *temp_node=head_node;
    for(int i=0;i<the_index;i++,temp_node=temp_node->next);
    return temp_node->element;
};
template<class T>
void chain_linearlist<T>::erase(const int the_index)
{
    //chack the_index
    if(the_index<0||the_index>chain_length)
    {
        throw std::runtime_error("the_index is invalid");
    }
    chain_node<T> *delete_node;
    chain_node<T> *previous_node;
    if (the_index==0)
    {
        delete_node=head_node;
        head_node=head_node->next;
    }
    else
    {
        delete_node=head_node;
        for (int i = 0; i < the_index; i++)
        {
            if (i==the_index-1)
            {
                previous_node=delete_node;
            }
            delete_node=delete_node->next;   
        }
        previous_node->next=delete_node->next;
    }
    delete delete_node;
    chain_length--;
    
};
template<class T>
void chain_linearlist<T>::insert(const T &the_element)
{
    chain_node<T> *insert_node=new chain_node<T>;
    insert_node(the_element,head_node);
    head_node=insert_node;
    chain_length++;
};
template<class T>
void chain_linearlist<T>::insert(const T &the_element,const int the_index)
{
    if(the_index<0||the_index>chain_length)
    {
        throw std::runtime_error("the_index is invalid");
    }
    chain_node<T> *previous_node=head_node;
    chain_node<T> *insert_node=new chain_node<T>;
    insert_node(the_element);
    if (the_index==0)
    {
        insert_node->next=head_node;
        head_node=insert_node;
    }
    else 
    {
        for (int i = 0; i < the_index-1; i++)
            previous_node=previous_node->next;
        insert_node->next=previous_node->next;
        previous_node->next=insert_node;
    }
    chain_length++;
};
template<class T>
void chain_linearlist<T>::chack_the_index(const int the_index)const
{
    if(the_index<0||the_index>=chain_length)
    {
        throw std::runtime_error("the_index is invlid");
    }
};
template<class T>
void chain_linearlist<T>::output(std::ostream &out)const
{
    for(chain_node<T> *temp_node=head_node;
        temp_node!=NULL;
        temp_node=temp_node->next)
    {
        out<<temp_node->element<<"";
    }
};
template<class T>
std::ostream &operator<<(std::ostream &out,const chain_linearlist<T> &x){x.output(out);return out;};
/* ------------------------ circularchain_linearlist ------------------------ */
template<class T>
circularchain_linearlist<T>::circularchain_linearlist(const int initial_capacity)
{
    if(initial_capacity<1)
    {
        throw std::runtime_error("initial_capacity is invalid");
    }
    head_node=new chain_node<T>;
    head_node->next=head_node;
    circularchain_length=0;
};
template<class T>
circularchain_linearlist<T>::circularchain_linearlist(const circularchain_linearlist<T> &the_list)
{
    circularchain_length=the_list.circularchain_length;
    if (circularchain_length=0)
    {
        head_node=new circularchain_linearlist<T>;
        head_node->next=head_node;
    }
    head_node=new circularchain_linearlist<T>;
    chain_node<T> *source_node=the_list.head_node;
    chain_node<T> *temp_node=head_node;
    for(int i=0;i<circularchain_length;i++)
    {
        temp_node->next=new circularchain_linearlist<T>;
        temp_node->next->element=source_node->next->element;
        temp_node=temp_node->next;
        source_node=source_node->next;
    }
};
template<class T>
circularchain_linearlist<T>::~circularchain_linearlist()
{
    
    for(int i=0;i<circularchain_length+1;i++)
    {
        chain_node<T> *temp_node=head_node->next;
        delete head_node;
        head_node=temp_node;
    }
    
}
template<class T>
bool circularchain_linearlist<T>::empty()const{return circularchain_length==0;};
template<class T>
int circularchain_linearlist<T>::length()const{return circularchain_length;};
template<class T>
int circularchain_linearlist<T>::index_of(const T &the_element)const
{
    chain_node<T> *temp_node=head_node->next;
    head_node->element=the_element;
    int i=0;
    while (temp_node->element!=temp_node)
    {
        temp_node=temp_node->next;
        i++;
    }
    if (temp_node!=head_node)
        return i;
    else
        return -1;
    /*chain_node<T> *temp_node=head_node->next;
    for (int i = 0; i < circularchain_length; i++)
    {
        if (temp_node->element==the_element)
        {
            return i;
        }
        temp_node=temp_node->next;
    }
    return -1;*/
};
template<class T>
T &circularchain_linearlist<T>::get(const int the_index)const
{
    chack_the_index(the_index);
    chain_node<T> *temp_node=head_node->next;
    for (int i = 0; i < the_index; i++)
    {
        temp_node=temp_node->next;
    }
    return temp_node->element;
    
};
template<class T>
void circularchain_linearlist<T>::erase(const int the_index)
{
    chack_the_index(the_index);
    chain_node<T> *previous_node=head_node;
    chain_node<T> *delete_node;
    for(int i=0;i<the_index;i++)
    {
        previous_node=previous_node->next;
    }
    delete_node=previous_node->next;
    previous_node->next=previous_node->next->next;
    delete delete_node;
    circularchain_length--;
};
template<class T>
void circularchain_linearlist<T>::insert(const T &the_element)
{
    chain_node<T> *temp_node=head_node->next;
    head_node->next=new chain_node<T>;
    head_node->next(the_element,temp_node);
    circularchain_length++;
};
template<class T>
void circularchain_linearlist<T>::insert(const T &the_element,const int the_index)
{
    if(the_index<0||the_index>circularchain_length)
    {
        throw std::runtime_error("the_index is invalid");
    }
    chain_node<T> *previous_node=head_node;
    chain_node<T> *temp_node;
    for(int i=0;i<the_index;i++)
    {
        previous_node=previous_node->next;
    }
    temp_node=previous_node->next;
    previous_node->next=new chain_node<T>;
    previous_node->next(the_element,temp_node);
    circularchain_length++;
};
template<class T>
void circularchain_linearlist<T>::chack_the_index(const int the_index)const
{
    if(the_index<1||the_index>=circularchain_length)
    {
        throw std::runtime_error("the_index is invalid");
    }
};
template<class T>
void circularchain_linearlist<T>::output(std::ostream &out)const
{
    chain_node<T> *temp_node=head_node->next;
    for (int i = 0; i < circularchain_length; i++)
    {
        out<<temp_node->element<<"";
        temp_node=temp_node->next;
    }
};
template<class T>
std::ostream &operator<<(std::ostream &out,const circularchain_linearlist<T> &x){x.output(out);return out;};
/* ---------------------- bidirectionalchain_linearlist --------------------- */
template<class T>
bidirectionalchain_linearlist<T>::bidirectionalchain_linearlist(const int initial_capacity)
{
    //chack initial_capacity
    if(initial_capacity<1)
    {
        throw std::runtime_error("initial_capacity is invalid");
    }
    head_node=NULL;
    tail_node=head_node;
    bidrectionalchain_length=0;
};
template<class T>
bidirectionalchain_linearlist<T>::bidirectionalchain_linearlist(const bidirectionalchain_linearlist<T> &the_list)
{
    bidrectionalchain_length=the_list.bidrectionalchain_length;
    if(bidrectionalchain_length=0)
    {
        head_node=NULL;
        tail_node=head_node;
        return;
    }
    head_node=new bidirectionalchain_node<T>;
    head_node->previous=NULL;
    head_node->element=the_list.head_node->element;
    bidirectionalchain_node<T> *temp_node=head_node;
    bidirectionalchain_node<T> *sourse_node=the_list.head_node->next;
    while (sourse_node!=NULL)
    {
        temp_node->next=new bidirectionalchain_node<T>;
        temp_node->next->previous=temp_node;
        temp_node->next->element=sourse_node->element;
        sourse_node=sourse_node->next;
        temp_node=temp_node->next;
    }
    tail_node=temp_node;
};
template<class T>
bidirectionalchain_linearlist<T>::~bidirectionalchain_linearlist()
{
    while (head_node!=NULL)
    {
        bidirectionalchain_node<T> *temp_node=head_node->next;
        delete head_node;
        head_node=temp_node;
    }
};
template<class T>
bool bidirectionalchain_linearlist<T>::empty()const{return bidrectionalchain_length==0;};
template<class T>
int bidirectionalchain_linearlist<T>::length()const{return bidrectionalchain_length;};
template<class T>
int bidirectionalchain_linearlist<T>::index_of(const T &the_element)const
{
    bidirectionalchain_node<T> *temp_node=head_node;
    for(int i=0;i<bidrectionalchain_length;i++)
    {
        if(temp_node->element=the_element)
            return i;
        temp_node=temp_node->next;
    }
    return -1;
};
template<class T>
T &bidirectionalchain_linearlist<T>::get(const int the_index)const
{
    bidirectionalchain_node<T> *temp_node;
    if((the_index+1)<=bidrectionalchain_length/2)
    {    temp_node=head_node;
        for (int i = 0; i < the_index; i++)
            temp_node=temp_node->next;
    }
    else
    {    temp_node=tail_node;
        for (int i = 0; i < bidrectionalchain_length-(the_index+1); i++)
            temp_node=temp_node->previous;
    }
    return temp_node->element;
};
template<class T>
void bidirectionalchain_linearlist<T>::erase(const int the_index)
{
    if (the_index<0||the_index>bidrectionalchain_length)
    {
        throw std::runtime_error("the_index is invalid");
    }
    bidirectionalchain_node<T> *delete_node;
    if(the_index==0)
    {
        delete_node=head_node;
        head_node=delete_node->next;
        head_node->previous=NULL;
        
    }
    else if(the_index==bidrectionalchain_length-1)
    {
        delete_node=tail_node;
        tail_node=delete_node->previous;
        tail_node->next=NULL;
    }
    else if ((the_index+1)<=bidrectionalchain_length/2)
    {
        delete_node=head_node;
        for (int i = 0; i < the_index; i++)
            delete_node=delete_node->next;
        delete_node->previous->next=delete_node->next;
        delete_node->next->previous=delete_node->previous;
    }
    else
    {
        delete_node=tail_node;
        for (int i = 0; i < bidrectionalchain_length-(the_index+1); i++)
            delete_node=delete_node->previous;
        delete_node->previous->next=delete_node->next;
        delete_node->next->previous=delete_node->previous;
    }
    delete delete_node;
    bidrectionalchain_length--;
    
};
template<class T>
void bidirectionalchain_linearlist<T>::insert(const T &the_element)
{
    bidirectionalchain_node<T> *insert_node=new bidirectionalchain_node<T>;
    insert_node(the_element,head_node);
    insert_node->previous=NULL;
    head_node=insert_node;
    if (bidrectionalchain_length==0)
    {
         tail_node=insert_node;
    }
    else
    {
        insert_node->next->previous=insert_node;
    }
    bidrectionalchain_length++;
};
template<class T>
void bidirectionalchain_linearlist<T>::insert(const T &the_element,const int the_index)
{
    bidirectionalchain_node<T> *temp_node;
    bidirectionalchain_node<T> *insert_node=new bidirectionalchain_node<T>;
    insert_node(the_element);
    if (the_index==0)
    {
        insert_node->next=head_node;
        insert_node->previous=NULL;
        head_node->previous=insert_node;
        head_node=insert_node;
        bidrectionalchain_length++;
    }
    else if (the_index==bidrectionalchain_length)
    {
        insert_node->next=NULL;
        insert_node->previous=tail_node;
        tail_node->next=insert_node;
        tail_node=insert_node;
        bidrectionalchain_length++;
    }
    else if((the_index+1)<=bidrectionalchain_length/2)
    {
        temp_node=head_node;
        for (int i = 0; i < the_index; i++)
            temp_node=temp_node->next;
        temp_node->previous->next=insert_node;
        insert_node->previous=temp_node->previous;
        temp_node->previous=insert_node;
        insert_node->next=temp_node;
        bidrectionalchain_length++;
    }
    else
    {
        temp_node=tail_node;
        for (int i = 0; i < bidrectionalchain_length-(the_index+1); i++)
            temp_node=temp_node->previous;
        temp_node->previous->next=insert_node;
        insert_node->previous=temp_node->previous;
        temp_node->previous=insert_node;
        insert_node->next=temp_node;
        bidrectionalchain_length++;
    }
};
template<class T>
void bidirectionalchain_linearlist<T>::chack_the_index(const int the_index)const
{
    if (the_index<0||the_index>=bidrectionalchain_length)
    {
        throw std::runtime_error("the_index is invalid");
    }
};
template<class T>
void bidirectionalchain_linearlist<T>::output(std::ostream &out)const
{
    for(bidirectionalchain_node<T> *temp_node=head_node;
        temp_node!=NULL;
        temp_node=temp_node->next)
    {
        out<<temp_node->element<<"";
    }
};
template<class T>
std::ostream &operator<<(std::ostream &out,const bidirectionalchain_linearlist<T> &x){x.output(out);return out;};
/* -------------------------------------------------------------------------- */
/*                                    stack                                   */
/* -------------------------------------------------------------------------- */
/* ------------------------------- array_stack ------------------------------ */
template<class T>
array_stack<T>::array_stack(const int initial_capacity)
{
    //chack initial_capacity
    if (initial_capacity<1)
    {
        throw std::runtime_error("initial_capacity is invalid");
    }
    
    stack_length=0;
    stack_size=initial_capacity;
    stack=new T[initial_capacity];
};
template<class T>
array_stack<T>::~array_stack()
{
    delete[] stack; 
}
template<class T>
bool array_stack<T>::empty()const{return stack_length==0;};
template<class T>
int array_stack<T>::length()const{return stack_length;};
template<class T>
T &array_stack<T>::top()
{
    //chack stack_length
    if (stack_length==0)
        throw std::runtime_error("the stack is empty");
    return stack[stack_length];
};
template<class T>
void array_stack<T>::pop()
{
    //chack stack_length
    if (stack_length==0)
        throw std::runtime_error("the stack is empty");
    stack_length--;
};
template<class T>
void array_stack<T>::push(const T &the_element)
{
    //chack stack_length
    if (stack_length==stack_size)
    {
        T *temp=new T[stack_size*2];
        std::copy(stack,stack+stack_size,temp);
        delete[] stack;
        stack=temp;
        stack_size=stack_size*2;
    }
    stack[++stack_length]=the_element;
};
/* ------------------------------- chain_stack ------------------------------ */
template<class T>
chain_stack<T>::chain_stack(const int initial_capacity)
{
    if(initial_capacity<1)
        throw std::runtime_error("initial_capacity is invalid");
    stack_length=0;
    stack=NULL;
};
template<class T>
chain_stack<T>::~chain_stack()
{
    while (stack!=NULL)
    {
        chain_node<T> *temp_node=stack->next;
        delete stack;
        stack=temp_node;
    }
};
template<class T>
bool chain_stack<T>::empty()const{return stack_length==0;};
template<class T>
int chain_stack<T>::length()const{return stack_length;};
template<class T>
T &chain_stack<T>::top()
{
    if (stack_length=0)
    {
        throw std::runtime_error("the stack is empty");
    }
    return stack->element;
};
template<class T>
void chain_stack<T>::pop()
{
    if (stack_length==0)
    {
        throw std::runtime_error("the stack is empty");
    }
    chain_node<T> *temp_node=stack->next;
    delete stack;
    stack=temp_node;
    stack_length--;
};
template<class T>
void chain_stack<T>::push(const T &the_element)
{
    chain_node<T> *temp_node=new chain_node<T>;
    temp_node(the_element,stack);
    stack=temp_node;
    stack_length++;
};
/* ------------------------------- array_queue ------------------------------ */
template<class T>
array_queue<T>::array_queue(const int initial_capacity)
{
    if(initial_capacity<1)
    {
        throw std::runtime_error("initial_capacity is invalid");
    }
    queue_front=0;
    queue_back=0;
    queue_size=initial_capacity;
    queue=new T[initial_capacity];
};
template<class T>
array_queue<T>::~array_queue(){delete[] queue;};
template<class T>
bool array_queue<T>::empty()const{return queue_front==queue_back;};
template<class T>
int array_queue<T>::length()const{return (queue_back-queue_front+queue_size)%queue_size;};
template<class T>
T &array_queue<T>::front()
{
    if(queue_front==queue_back)
        throw std::runtime_error("the queue is empty");
    return queue[(queue_front+1)%queue_size];
}
template<class T>
T &array_queue<T>::back()
{
    if(queue_front==queue_back)
        throw std::runtime_error("the queue is empty");
    return queue[queue_back];
}
template<class T>
void array_queue<T>::pop()
{
    if (queue_front==queue_back)
    {
        throw std::runtime_error("the queue is empty");
    }
    queue_front=(queue_front+1)%queue_size;
}
template<class T>
void array_queue<T>::push(const T &the_element)
{
    if ((queue_back+1)%queue_size==queue_front)
    {
        T *temp=new T[queue_size*2];
        std::copy(queue,queue+queue_size,temp);
        std::copy(temp+queue_back,temp+queue_size,temp+queue_size-queue_back);
        delete queue;
        queue=temp;
        queue_size*=2;
    }
    queue_back=(queue_back+1)%queue_size;
    queue[queue_back]=the_element;
}
/* ------------------------------- chain_queue ------------------------------ */
template<class T>
chain_queue<T>::chain_queue(const int initial_capacity)
{
    if (initial_capacity<1)
        throw std::runtime_error("initial_capacity is invalid");
    
    queue_front=NULL;
    queue_back=queue_front;
    queue_length=0;
};
template<class T>
chain_queue<T>::~chain_queue()
{
    while (queue_front != NULL)
    {
        chain_node<T> *temp_node=queue_front->next;
        delete queue_front;
        queue_front=temp_node;
    }
};
template<class T>
bool chain_queue<T>::empty()const{return queue_length==0;};
template<class T>
int chain_queue<T>::length()const{return queue_length;};
template<class T>
T &chain_queue<T>::front(){return queue_front->element;};
template<class T>
T &chain_queue<T>::back(){return queue_back->element;};
template<class T>
void chain_queue<T>::pop()
{
    if (queue_front==queue_back)
        throw std::runtime_error("the queue is empry");
    chain_node<T> *temp_node=queue_front->next;
    delete queue_front;
    queue_front=temp_node;
    queue_length--;
};
template<class T>
void chain_queue<T>::push(const T &the_element)
{
    chain_node<T> *push_node=new chain_node<T>;
    push_node(the_element,NULL);
    if (queue_length==0)
    {
        queue_front=push_node;
    }
    else
    {
        queue_back->next=push_node;
    }
    queue_back=push_node;
    queue_length++;
};
/* -------------------------------------------------------------------------- */
/*                                 dictionary                                 */
/* -------------------------------------------------------------------------- */
/* ---------------------------- array_dictionary ---------------------------- */
template<class K,class E>
array_dictionary<K,E>::array_dictionary(const int initial_capacity)
{
    if (initial_capacity<1)
        throw std::runtime_error("initial_capacity is invalid");
    dictionary=new std::pair< K,E>[initial_capacity];
    dictionary_size=initial_capacity;
    dictionary_length=0;
};
template<class K,class E>
array_dictionary<K,E>::~array_dictionary(){delete[] dictionary;};
template<class K,class E>
bool array_dictionary<K,E>::empty()const{return dictionary_length==0;};
template<class K,class E>
int array_dictionary<K,E>::length()const{return dictionary_length;};
template<class K,class E>
std::pair<const K,E> *array_dictionary<K,E>::find(const K &the_key)const
{
    for (int i = 0; i < dictionary_length; i++)
    {
        if (dictionary[i].first==the_key)
            return (std::pair<const K,E> *)dictionary+i;
    }
    return 0;
};
template<class K,class E>
void array_dictionary<K,E>::insert(const  std::pair<const K,E> &the_keypair)
{
    int i=0;
    while ( i < dictionary_length&&the_keypair.first>dictionary[i].first)
        i++;
    if (i < dictionary_length&&the_keypair.first==dictionary[i].first)
    {
        dictionary[i].second=the_keypair.second;
        return;
    }
    if (dictionary_length==dictionary_size)
    {
        dictionary_size*=2;
        std::pair<K,E> *temp=new std::pair<K,E>[dictionary_size];
        std::copy(dictionary,dictionary+dictionary_size,temp);
        delete dictionary;
        dictionary=temp;
    }
    if (i!=dictionary_length)
        std::copy(dictionary+i,dictionary+dictionary_size,dictionary+i+1);
    *(dictionary+i)=the_keypair;
    dictionary_length++;
};
template<class K,class E>
void array_dictionary<K,E>::erase(const K &the_key)
{
    for (int i = 0; i < dictionary_length; i++)
    {
        if (dictionary[i].first==the_key)
        {
            std::copy(dictionary+i+1,dictionary+dictionary_length,dictionary+1);
            dictionary_length--;
            return;
        }
    }
};
template<class K,class E>
void array_dictionary<K,E>::output(std::ostream &out)const
{
    for (int i = 0; i < dictionary_length; i++)
        out<<dictionary[i].first<<""<<dictionary[i].second<<"";
};
template<class K,class E>
std::ostream &operator<<(std::ostream &out,const array_dictionary<K,E> &x){x.output(out);return out;};
/* ---------------------------- chain_dictionary ---------------------------- */
template<class K,class E>
chain_dictionary<K,E>::chain_dictionary(const int initial_capacity)
{
    if (initial_capacity<1)
    {
        throw std::runtime_error("initial_capacity is invalid");
    }
    head_node=NULL;
    dirtionary_length=0;
};
template<class K,class E>
chain_dictionary<K,E>::~chain_dictionary()
{
    while (head_node!=NULL)
    {
        chain_node<std::pair<const K,E>> *temp_node=head_node->next;
        delete head_node;
        head_node=temp_node;
    }
}
template<class K,class E>
bool chain_dictionary<K,E>::empty()const{return dirtionary_length==0;};
template<class K,class E>
int chain_dictionary<K,E>::length()const{return dirtionary_length;};
template<class K,class E>
std::pair<const K,E> *chain_dictionary<K,E>::find(const K&the_key)const
{
    chain_node<std::pair<const K,E>> *temp_node=head_node;
    while (temp_node!=NULL)
    {
        if (temp_node->element.first==the_key)
            return &temp_node->element;
        temp_node=temp_node->next;
    }
    return NULL;
};
template<class K,class E>
void chain_dictionary<K,E>::insert(const std::pair<const K,E> &the_keypair)
{
    chain_node<std::pair<const K,E>> *temp_node=head_node,
                                     *previous_node=NULL;
    while (temp_node!=NULL&&temp_node->element.first<the_keypair.first)
    {
        previous_node=temp_node;
        temp_node=temp_node->next;
    }
    if (temp_node!=NULL&&temp_node->element.first==the_keypair.first)
    {
        temp_node->element.second=the_keypair.second;
        return;
    }
    chain_node<std::pair<const K,E>> *insert_node=new chain_node<std::pair<const K,E>>(the_keypair,temp_node);
    if (previous_node==NULL)
    {
        head_node=insert_node;
    }
    else previous_node->next=insert_node;
    dirtionary_length++;
};
template<class K,class E>
void chain_dictionary<K,E>::erase(const K &the_key)
{
    chain_node<std::pair<const K,E>> *temp_node=head_node,
                                     *previous_node=NULL;
    while (temp_node!=NULL&&temp_node->element.first<the_key)
    { 
        previous_node=temp_node;
        temp_node=temp_node->next;
    }
    if (temp_node!=NULL&&temp_node->element.first==the_key)
    {
        if (previous_node==NULL)
                head_node=temp_node->next;
        else previous_node->next=temp_node->next;
        delete temp_node;
        dirtionary_length--;
    }
};
template<class K,class E>
void chain_dictionary<K,E>::output(std::ostream &out)const
{
    chain_node<std::pair<const K,E>> *temp_node=head_node;
    while (temp_node!=NULL)
    {
        out<<temp_node->element.first<<""<<temp_node->element.second<<"";
        temp_node=temp_node->next;
    }
}
template<class K,class E>
std::ostream &operator<<(std::ostream &out,const chain_dictionary<K,E> &x){x.output(out);return out;};
/* -------------------------------- skiplist_dictionary ------------------------------- */
template<class K,class E>
skiplist_dictionary<K,E>::skiplist_dictionary(K the_maxkey,int max_keypairs,float probability)
{
    cutoff=probability*RAND_MAX;
    max_level=(int)ceil(logf((float)max_keypairs)/logf(1/probability))-1;
    levels=0;
    dirctionary_length=0;
    max_key=the_maxkey;

    std::pair<K,E> tail_pair;
    tail_pair.first=max_key;
    head_node=new skip_node<K,E>(tail_pair,max_level+1);
    tail_node=new skip_node<K,E>(tail_pair,0);
    last=new skip_node<K,E> *[max_level+1];

    for (int i = 0; i <=max_level; i++)
        head_node->next[i]=tail_node;
};
template<class K,class E>
skiplist_dictionary<K,E>::~skiplist_dictionary()
{
    while (head_node!=tail_node)
    {
        skip_node<K,E> *temp_node=head_node->next[0];
        delete head_node;
        head_node=temp_node;
    }

    delete tail_node;

    delete[] last;
};
template<class K,class E>
bool skiplist_dictionary<K,E>::empty()const{return dirctionary_length==0;};
template<class K,class E>
int skiplist_dictionary<K,E>::length()const{return dirctionary_length;};
template<class K,class E>
std::pair<const K,E> *skiplist_dictionary<K,E>::find(const K &the_key)const
{
    if (the_key>max_key)
        return NULL;
    skip_node<K,E> *temp_node=head_node;
    for (int i = levels; i >0 ; i--)
    {
        while (temp_node->next[i]->element.first<the_key)
        {
            temp_node=temp_node->next[i];
        }
    }
    if (temp_node->next[0]->element.first==the_key)
    {
        return &temp_node->next[0]->element;
    }
    return NULL;  
};
template<class K,class E>
void skiplist_dictionary<K,E>::insert(const std::pair<const K,E> &the_keypair)
{
    if (the_keypair.first>max_key)
        throw std::runtime_error("the key is invailed");
    skip_node<K,E> *temp_node=search(the_keypair.first);
    if (temp_node->element.first==the_keypair.first)
    {
        temp_node->element.second=the_keypair.second;
        return;
    }
    int the_level=level();
    if (the_level>levels)
    {
        the_level=++levels;
        last[the_level]=head_node;
    }
    skip_node<K,E> *insert_node=new skip_node<K,E>(the_keypair,the_level+1);
    for (int i = 0; i <= the_level; i++)
    {
        insert_node->next[i]=last[i]->next[i];
        last[i]->next[i]=insert_node;
    }
    dirctionary_length++;
    return;
};
template<class K,class E>
void skiplist_dictionary<K,E>::erase(const K &the_key)
{
    if (the_key>=max_key)
        throw std::runtime_error("the key is invailed");
    skip_node<K,E> *temp_node=search(the_key);
    if (temp_node->element.first!=the_key)
        return;
    for (int i = 0; i <= levels &&last[i]->next[i]==temp_node; i++)
        last[i]->next[i]=temp_node->next[i];

    while (levels > 0 &&head_node->next[levels]==tail_node)
        levels--;

    delete temp_node;
    dirctionary_length--;
};
template<class K,class E>
skip_node<K,E> *skiplist_dictionary<K,E>::search(const K &the_key)const
{
    skip_node<K,E> *temp_node=head_node;
    for (int i = levels; i >=0; i--)
    {
        while (temp_node->next[i]->element.first<the_key)
            temp_node=temp_node->next[i];
        last[i]=temp_node;
    }
    return temp_node->next[0];
};
template<class K,class E>
int skiplist_dictionary<K,E>::level()const
{
    int lev=0;
    while (rand()<=cutoff)
        lev++;
    return (lev<=max_level)?lev:max_level;
    
};
template<class K,class E>
void skiplist_dictionary<K,E>::output(std::ostream &out)const
{
    for ( skip_node<K,E> *temp_node = head_node->next[0];temp_node!=tail_node; temp_node=temp_node->next[0])
    {
        out<<temp_node->element.first<<""<<temp_node->element.second<<"";
    }
};
template<class K,class E>
std::ostream &operator<<(std::ostream &out,const skiplist_dictionary<K,E> &x){x.output(out);return out;};
template<class K,class E>
hashtable_dictionary<K,E>::hashtable_dictionary(int the_divisor)
{
    divisor=the_divisor;
    dictionary_length=0;
    table=new std::pair<const K,E> *[divisor];
    for (int  i = 0; i < divisor; i++)
        table[i]=NULL;
};
template<class K,class E>
hashtable_dictionary<K,E>::~hashtable_dictionary(){delete[] table;};
template<class K,class E>
bool hashtable_dictionary<K,E>::empty()const{return dictionary_length==0;};
template<class K,class E>
int hashtable_dictionary<K,E>::length()const{return dictionary_length;};
template<class K,class E>
int hashtable_dictionary<K,E>::search(const K &the_key)const
{
    int i=(int)hash(the_key)%divisor;
    int j=i;
    do
    {
        if (table[j]==NULL||table[j]->first==the_key)
            return j;
        j=(j+1)%divisor;
    }while(j!=i);
    return j;
};
template<class K,class E>
std::pair<const K,E> *hashtable_dictionary<K,E>::find(const K &the_key)const
{
    int b=search(the_key);
    if (table[b]==NULL||table[b]->first!=the_key)
        return NULL;
    return table[b];   
};
template<class K,class E>
void hashtable_dictionary<K,E>::insert(const std::pair<const K,E> &the_keypair)
{
    int b=search(the_keypair.first);
    if (table[b]==NULL)
    {
        table[b]=new std::pair<const K,E>(the_keypair);
        dictionary_length++;
    }
    else
    {
        if (table[b]->first==the_keypair.first)
        {
            table[b]->second=the_keypair.second;
        }
        else
        {
            throw std::runtime_error("hashtable is full");
        }
    }
};
template<class K,class E>
void hashtable_dictionary<K,E>::erase(const K &the_key)
{
    int b=search(the_key);
    if (table[b]==NULL)
    {
        return;
    }
    else
    {
        if (table[b]->first==the_key)
        {
            int i=(b+1)%divisor;
            if (dictionary_length==1)
            {
                table[b]=NULL;
            }
            else
            {
                do
                {
                    if (table[i]!=NULL)
                    {
                        int j=(int)hash(table[i]->first)%divisor;
                        if (j==b)
                        {
                            table[b]=table[i];  
                            table[i]=NULL;
                        }
                    }
                    i=(i+1)%divisor;
                } while (i!=b);
            }
        }
        else
        {
            return;
        }
        
    }
    dictionary_length--;
};
template<class K,class E>
void hashtable_dictionary<K,E>::output(std::ostream &out)const
{
    for (int i = 0; i < divisor; i++)
    {
        if (table[i]==NULL)
        {
            out<<"NULL"<<std::endl;
        }
        else
        {
            out<<table[i]->first<<""<<table[i]->second<<std::endl;
        }
    }
};
template<class K,class E>
std::ostream &operator<<(std::ostream &out,const hashtable_dictionary<K,E> &x){x.output(out);return out;}; 
template<class K,class E>
hashchains_dictionary<K,E>::hashchains_dictionary(int the_divisor)
{
    divisor=the_divisor;
    dictionary_length=0;
    table=new chain_dictionary<K,E>[divisor];
}
template<class K,class E>
hashchains_dictionary<K,E>::~hashchains_dictionary(){delete[] table;};
template<class K,class E>
bool hashchains_dictionary<K,E>::empty()const{return dictionary_length==0;};
template<class K,class E>
int hashchains_dictionary<K,E>::length()const{return dictionary_length;};
template<class K,class E>
std::pair<const K,E> *hashchains_dictionary<K,E>::find(const K &the_key)const{return table[hash(the_key)%divisor].find(the_key);};
template<class K,class E>
void hashchains_dictionary<K,E>::insert(const std::pair<const K,E> &the_keypair)
{
    int tin_length=table[hash(the_keypair.first)%divisor].length();
    table[hash(the_keypair.first)%divisor].insert(the_keypair);
    if (table[hash(the_keypair.first)%divisor].length()>tin_length)
        dictionary_length++;
}
template<class K,class E>
void hashchains_dictionary<K,E>::erase(const K &the_key)
{
    int tin_length=table[hash(the_key)%divisor].length();
    table[hash(the_key)%divisor].erase(the_key);
    if (table[hash(the_key)%divisor].length()<tin_length)
        dictionary_length--;    
};
template<class K,class E>
void hashchains_dictionary<K,E>::output(std::ostream &out)const
{
    for (int  i = 0; i < divisor; i++)
    {
        if (table[i].length()==0)
            out<<"NULL"<<std::endl;
        else
            out<<table[i]<<std::endl;
    }
};
template<class K,class E>
std::ostream &operator<<(std::ostream &out,const hashchains_dictionary<K,E> &x){x.output(out);return out;};
/* ---------------------------- array_binarytree ---------------------------- */
#if 0
template<class T>
array_binarytree<T>::array_binarytree(int initial_capacity)
{
    if (initial_capacity<1)
        throw std::runtime_error("the initial_capacity is invalid");
    
    binarytree_length=0;
    binarytree_size=initial_capacity;
    element=new T[initial_capacity];
};
template<class T>
array_binarytree<T>::~array_binarytree(){delete[] element;};
template<class T>
bool array_binarytree<T>::empty()const{return binarytree_length==0;};
template<class T>
int array_binarytree<T>::length()const{return binarytree_length;};
template<class T>
void array_binarytree<T>::pre_order(void (*the_visit)(T *))
{
    visit=the_visit;
    pre_order(element,1);
};
template<class T>
void array_binarytree<T>::in_order(void (*the_visit)(T *))
{
    visit=the_visit;
    in_order(element,1);
};
template<class T>
void array_binarytree<T>::post_order(void (*the_visit)(T *))
{
    visit=the_visit;
    post_order(element,1);
};
template<class T>
void array_binarytree<T>::pre_order(T *the_element,int i)
{
    if (i<binarytree_size)
    {
        array_binarytree<T>::visit(the_element+i);
        if (2*i<binarytree_size)
        {
            pre_order(the_element,2*i);
        }
        if (2*i+1<binarytree_size)
        {
            pre_order(the_element,2*i+1);
        }
    }
};
template<class T>
void array_binarytree<T>::in_order(T *the_element,int i)
{
    if (i<binarytree_size)
    {
        if (2*i<binarytree_size)
        {
            in_order(the_element,2*i);
        }
        if (2*i+1<binarytree_size)
        {
            in_order(the_element,2*i+1);
        }
    }
}
template<class T>
void array_binarytree<T>::post_order(T *the_element,int i)
{
    if (i<binarytree_size)
    {
        if (2*i<binarytree_size)
        {
            post_order(the_element,2*i);
        }
        if (2*i+1<binarytree_size)
        {
            post_order(the_element,2*i+1);
        }
    }
};
template<class T>
void array_binarytree<T>::level_order(void (*the_visit)(T *))
{
    array_queue<T*> q;
    T *t=element;
    for (int i = 1; i < binarytree_size; i++)
    {
        the_visit(t+i);
        if (2*i<binarytree_size)
            q.push(t+2*i);
        if (2*i+1<binarytree_size)
            q.push(t+2*i+1);
        if (t==q.front())
        {
            throw std::runtime_error("the_queue is empty");
        }
        q.pop();
    }    
}
template<class T>
void array_binarytree<T>::pre_order_output(){pre_order(output);std::cout<<std::endl;};
template<class T>
void array_binarytree<T>::in_order_output(){in_order(output);std::cout<<std::endl;};
template<class T>
void array_binarytree<T>::post_order_output(){post_order(output);std::cout<<std::endl;};
template<class T>
void array_binarytree<T>::level_order_output(){level_order(output);std::cout<<std::endl;};
template<class T>
void array_binarytree<T>::output(T *t){std::cout<<*t<<' ';};
#endif
template<class T>
chain_binarytree<T>::chain_binarytree()
{
    root=NULL;
    binarytree_length=0;
};
template<class T>
chain_binarytree<T>::~chain_binarytree()
{
    post_order(dispose);
    root=NULL;
    binarytree_length=0;
};
template<class T>
bool chain_binarytree<T>::empty()const{return binarytree_length==0;};
template<class T>
int chain_binarytree<T>::length()const{return binarytree_length;};
template<class T>
T *chain_binarytree<T>::root_element()const
{
    if (binarytree_length==0)
        return NULL;
    else
        return &root->element;
}
template<class T>
void chain_binarytree<T>::make_tree(const T &element,chain_binarytree<T> &left_child,chain_binarytree<T> &right_child)
{
    root=new binarytree_node<T>(element,left_child.root,right_child.root);
    binarytree_length=left_child.length+right_child.length+1;

    left_child.root=right_child.root=NULL;
    left_child.length=right_child.length=0;
}

#endif