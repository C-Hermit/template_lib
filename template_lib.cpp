#ifndef _TEMPLATE_LIB_CPP_
#define _TEMPLATE_LIB_CPP_

#include"template_lib.h"

template<class K,class E>
std::ostream &operator<<(std::ostream &stream,std::pair<const K,E> &other)
{
    stream<<other.first<<' '<<other.second;
    return stream;
}
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
        int start=(queue_front+1)%queue_size;
        if(start<2)
        {
            std::copy(queue+start,queue+start+queue_size-1,temp);
        }
        else
        {
            std::copy(queue+start,queue+queue_size,temp);
            std::copy(queue,queue+queue_back+1,temp+queue_size-start);
        }
        queue_front=2*queue_size-1;
        queue_back=queue_size-2;
        queue_size*=2;
        queue=temp;
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
/* -------------------------- hashtable_dictionary -------------------------- */
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
/* -------------------------------------------------------------------------- */
/*                                 binarytree                                 */
/* -------------------------------------------------------------------------- */
/* ---------------------------- array_binarytree ---------------------------- */
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
T *array_binarytree<T>::root_element()const
{
    if (binarytree_length==0)
    {
        return NULL;
    }
    else
    {
        return element;
    }
};
template<class T>
void array_binarytree<T>::insert(T the_element)
{
    if (binarytree_length==binarytree_size-1)
    {
        int* temp=new T[binarytree_size*2];
        std::copy(element,element+binarytree_size,temp);
        delete[] element;
        element=temp;
    }
    element[binarytree_length+1]=the_element;
    binarytree_length++;
};
template<class T>
void array_binarytree<T>::pre_order(void (*the_visit)(T *))
{
    visit=the_visit;
    pre_order(1);
};
template<class T>
void array_binarytree<T>::in_order(void (*the_visit)(T *))
{
    visit=the_visit;
    in_order(1);
};
template<class T>
void array_binarytree<T>::post_order(void (*the_visit)(T *))
{
    visit=the_visit;
    post_order(1);
};
template<class T>
void array_binarytree<T>::pre_order(int i)
{
    if (i<binarytree_size)
    {
        array_binarytree<T>::visit(element+i);
        if (2*i<binarytree_size)
        {
            pre_order(2*i);
        }
        if (2*i+1<binarytree_size)
        {
            pre_order(2*i+1);
        }
    }
};
template<class T>
void array_binarytree<T>::in_order(int i)
{
    if (i<binarytree_size)
    {
        array_binarytree::visit(element+i);
        if (2*i<binarytree_size)
        {
            in_order(2*i);
        }
        if (2*i+1<binarytree_size)
        {
            in_order(2*i+1);
        }
    }
}
template<class T>
void array_binarytree<T>::post_order(int i)
{
    if (i<binarytree_size)
    {
        array_binarytree<T>::visit(element+i);
        if (2*i<binarytree_size)
        {
            post_order(2*i);
        }
        if (2*i+1<binarytree_size)
        {
            post_order(2*i+1);
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
/* ---------------------------- chain_binarytree ---------------------------- */
template<class T>
chain_binarytree<T>::chain_binarytree()
{
    root=NULL;
    binarytree_length=0;
};
template<class T>
chain_binarytree<T>::~chain_binarytree(){erase();};
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
};
template<class T>
void chain_binarytree<T>::make_tree(const T &element,chain_binarytree<T> &left_child,chain_binarytree<T> &right_child)
{
    root=new binarytree_node<T>(element,left_child.root,right_child.root);
    binarytree_length=left_child.binarytree_length+right_child.binarytree_length+1;

    left_child.root=right_child.root=NULL;
    left_child.binarytree_length=right_child.binarytree_length=0;
};
template<class T>
void chain_binarytree<T>::pre_order(void (*the_visit) (binarytree_node<T> *))
{
    visit=the_visit;
    pre_order(root);
};
template<class T>
void chain_binarytree<T>::in_order(void (*the_visit) (binarytree_node<T> *))
{
    visit=the_visit;
    in_order(root);
};
template<class T>
void chain_binarytree<T>::post_order(void (*the_visit) (binarytree_node<T> *))
{
    visit=the_visit;
    post_order(root);
};
template<class T>
void chain_binarytree<T>::level_order(void (*the_visit)(binarytree_node<T> *))
{
    array_queue<binarytree_node<T> *>q;
    binarytree_node<T> *t=root;
    while (t!=NULL)
    {
        the_visit(t);
        if (t->left_child!=NULL);
        {
            q.push(t->left_child);
        }
        if (t->right_child!=NULL)
        {
            q.push(t->right_child);
        }
        try{t=q.front();}
        catch(const std::runtime_error& e)
        {
            std::cerr<<"the binarytree is empty"<<std::endl;
        }
        q.pop();
    }
};
template<class T>
void chain_binarytree<T>::pre_order_output()
{
    pre_order(output);
    std::cout<<std::endl;
};
template<class T>
void chain_binarytree<T>::in_order_output()
{
    in_order(output);
    std::cout<<std::endl;
};
template<class T>
void chain_binarytree<T>::post_order_output()
{
    post_order(output);
    std::cout<<std::endl;
};
template<class T>
void chain_binarytree<T>::level_order_output()
{
    level_order(output);
    std::cout<<std::endl;
};
template<class T>
void chain_binarytree<T>::erase()
{
    post_order(dispose);
    root=NULL;
    binarytree_length=0;
};
template<class T>
int chain_binarytree<T>::height()const{return height(root);};
template<class T>
void chain_binarytree<T>::pre_order(binarytree_node<T> *t)
{
    if(t!=NULL)
    {
        chain_binarytree<T>::visit(t);
        pre_order(t->left_child);
        pre_order(t->right_child);
    }
};
template<class T>
void chain_binarytree<T>::in_order(binarytree_node<T> *t)
{
    if (t!=NULL)
    {
        in_order(t->left_child);
        chain_binarytree<T>::visit(t);
        in_order(t->right_child);
    }
};
template<class T>
void chain_binarytree<T>::post_order(binarytree_node<T> *t)
{
    if (t!=NULL)
    {
        post_order(t->left_child);
        post_order(t->right_child);
        chain_binarytree<T>::visit(t);
    }
};
template<class T>
void chain_binarytree<T>::count_nodes(binarytree_node<T> *t)
{
    visit=add_to_nodes;
    count=0;
    pre_order(t);
};
template<class T>
void chain_binarytree<T>::add_to_nodes(binarytree_node<T> *t){count++;};
template<class T>
void chain_binarytree<T>::dispose(binarytree_node<T> *t){delete t;};
template<class T>
void chain_binarytree<T>::output(binarytree_node<T> *t){std::cout<< t->element<<' ';};
template<class T>
int chain_binarytree<T>::height(binarytree_node<T> *t) 
{
    if (t==NULL)
        return 0;
    int left_h=height(t->left_child);
    int right_h=height(t->right_child);
    if(left_h>right_h)
        return ++left_h;
    else
        return ++right_h;
};
/* ------------------------- array_maxpriority_queue ------------------------ */
template<class T>
array_maxpriority_queue<T>::array_maxpriority_queue(int initial_capacity)
{
    if (initial_capacity<1)
        throw std::runtime_error("the initial_capacity is invaild");
    queue=new T[initial_capacity];
    queue_length=0;
    queue_size=initial_capacity;
};
template<class T>
array_maxpriority_queue<T>::~array_maxpriority_queue(){delete[] queue;};
template<class T>
bool array_maxpriority_queue<T>::empty()const{return queue_length==0;};
template <class T>
int array_maxpriority_queue<T>::length()const{return queue_length;};
template<class T>
const T &array_maxpriority_queue<T>::top()const
{
    if (queue_length==0)
        throw std::runtime_error("the queue is empty");
    return queue[1];
};
template<class T>
void array_maxpriority_queue<T>::pop()
{
    if (queue_length==0)
        throw std::runtime_error("the queue is empty");
    T last_element=queue[queue_length];
    int current_node=1;
    int child=2;
    while (child<=queue_length)
    {
        if(child<queue_length&&queue[child]<queue[child+1])
            child++;
        if (last_element>queue[child])
            break;
        queue[current_node]=queue[child];
        current_node=child;
        child*=2;
    }
    queue[current_node]=last_element;    
};
template<class T>
void array_maxpriority_queue<T>::push(const T &the_element)
{
    if (queue_size==queue_length-1)
    {
        T *temp=new T[queue_size*2];
        std::copy(queue,queue+queue_size,temp);
        delete[] queue;
        queue=temp;
        queue_size*=2;
    }
    int current_node=++queue_length;//new the new of tree_node
    while (current_node!=1||queue[current_node/2]<the_element)
    {
        queue[current_node]=queue[current_node/2];
        current_node/=2;
    }
    queue[current_node]=the_element;
};
template<class T>
void array_maxpriority_queue<T>::initialize(T *the_queue,int the_length)
{
    if (the_length>queue_size-1)
        throw std::runtime_error("the_length is invaild");
    delete[] queue;
    queue=the_queue;
    queue_length=the_length;
    //heapify
    for(int root=queue_length/2;root>=1;root--)
    {
        T root_element=queue[root];
        int child=2*root;
        while(child<=queue_length)
        {
            if (child<queue_length&&queue[child]<queue[child+1])
                child++;
            if (root_element>=queue[child])
                break;
            queue[child/2]=queue[child];
            child*=2;
        }
        queue[child/2]=root_element;
    }
};
template<class T>
void array_maxpriority_queue<T>::deactivate_array(){queue=NULL;queue_length=queue_size=0;};
template<class T>
void array_maxpriority_queue<T>::output(std::ostream &out)const
{
    for (int i = 0; i < queue_length; i++)
    {
        out<<queue[i]<<std::endl;
    }
    
    //std::copy(queue,queue+queue_length+1,std::ostream_iterator<T>(std::cout,' '));
};
template<class T>
std::ostream &operator<<(std::ostream &out,const array_maxpriority_queue<T> &x){x.output(out);return out;};
/* ------------------------- chain_maxpriority_queue ------------------------ */
template<class T>
bool chain_maxpriority_queue<T>::empty()const{return this->binarytree_length==0;};
template<class T>
int chain_maxpriority_queue<T>::length()const{return this->binarytree_length;};
template<class T>
const T &chain_maxpriority_queue<T>::top()const
{
    if (this->binarytree_length==0)
        throw std::runtime_error("the queue is empty");
    return this->root->element.second;
};
template<class T>
void chain_maxpriority_queue<T>::pop()
{
    if (this->root==NULL)
        throw std::runtime_error("the queue is empty");
    binarytree_node<std::pair<int,T>> *left=this->root->left_child,
                                      *right=this->root->right_child;
    delete this->root;
    this->root=left;
    meld(this->root,this->root->right_child);
    this->binarytree_length--;
};
template<class T>
void chain_maxpriority_queue<T>::push(const T &the_element)
{
    binarytree_node<std::pair<int,T>> *p=new binarytree_node<std::pair<int,T>>(std::pair<int,T>(1,the_element));
    meld(this->root,p);
    this->binarytree_length++;
};
template<class T>
void chain_maxpriority_queue<T>::initialize(T *the_elements,int the_length)
{
        array_queue<binarytree_node<std::pair<int,T>>*> p(the_length);
        this->erase();
        for(int i=1;i<=the_length;i++)
            p.push(new binarytree_node<std::pair<int,T>>(std::pair<int,T>(1,the_elements[i])));
        for (int i = 1; i <= the_length-1; i++)
        {
            binarytree_node<std::pair<int,T>> *b=p.front();
            p.pop();
            binarytree_node<std::pair<int,T>> *c=p.front();
            p.pop();
            meld(b,c);
            p.push(b);
        }
        if (the_length>0)
            this->root=p.front();
        this->binarytree_length=the_length;
};
template<class T>
void chain_maxpriority_queue<T>::meld(chain_maxpriority_queue<T> &the_queue)
{
    meld(this->root,the_queue.root);
    this->binarytree_length+=the_queue.binarytree_length;
    the_queue.root=NULL;
    the_queue.binarytree_length=0;
}
template<class T>
void chain_maxpriority_queue<T>::meld(binarytree_node<std::pair<int,T>>* &x,binarytree_node<std::pair<int,T>>* &y)
{
    if (y==NULL)
        return;
    if (x==NULL)
    {
        x=y;
        return;
    }
    if (x->element.second<y->element.second)
        swap(x,y);
    meld(x->right_child,y);
    if (x->left_child==NULL)
    {
        x->left_child=x->right_child;
        x->right_child=NULL;
        x->element.first=1;
    }
    else
    {
        if (x->left_child->element.first<x->right_child->element.first)
            swap(x->left_child,x->right_child);
        x->element.first=x->right_child->element.first+1;
    }
};
template<class T>
void chain_maxpriority_queue<T>::output(){this->pre_order(nodeoutput);std::cout<<std::endl;};
template<class T>
void chain_maxpriority_queue<T>::nodeoutput(binarytree_node<std::pair<int,T>> *t){std::cout<<t->element.second<<' ';};
/* -------------------------------------------------------------------------- */
/*                               competitivetree                              */
/* -------------------------------------------------------------------------- */
/* ------------------------- maxwinner_competitivetree ------------------------- */
template<class T>
maxwinner_competitivetree<T>::maxwinner_competitivetree(T *the_play,int the_players_number)
{
    tree=NULL;
    initialise(the_play,the_players_number);
};
template<class T>
maxwinner_competitivetree<T>::~maxwinner_competitivetree(){delete[] tree;};
template<class T>
void maxwinner_competitivetree<T>::initialise(T *the_player,int the_player_number)
{
    if (the_player_number<2)
        throw std::runtime_error("player_number is invaild");

    players_number=the_player_number;
    player=the_player;
    delete[] tree;
    tree=new int[players_number];

    //compute s(lowest-level leftmost internal node)
    int i,s;
    for (s=1; 2*s < players_number; s*=2);

    lowExt=2*(players_number-s);
    offset=2*s-1;

    //play matchs for lowext-level external nodes
    for (i = 2; i <= lowExt; i+=2)
        play((offset+i)/2,i-1,i);
    
    if (players_number%2==1)
    {
        play(players_number/2,tree[players_number-1],lowExt+1);
        i=lowExt+3;
    }
    else i=lowExt+2;

    for (; i <= players_number; i+=2)
        play((i-lowExt+players_number-1)/2,i-1,i);
};
template<class T>
int maxwinner_competitivetree<T>::competitor()const{return tree[1];}
template<class T>
int maxwinner_competitivetree<T>::competitor(int i)const{return (i<players_number)?tree[i]:0;};
template<class T>
void maxwinner_competitivetree<T>::play(int match_node,int left_node,int right_node)
{
    tree[match_node]=(player[left_node]>=player[right_node])?left_node:right_node;
    while (match_node%2==1&&match_node>1)
    {
        tree[match_node/2]=(player[tree[match_node-1]]>=player[tree[match_node]])?tree[match_node-1]:tree[match_node];
        match_node/=2;
    }
    
};
template<class T>
void maxwinner_competitivetree<T>::replay(int the_player,T the_player_element)
{
    int n = players_number;
    if (the_player<=0||the_player>n)
        throw std::runtime_error("the_plary is invaild");

    player[the_player]=the_player_element;
    int match_node, 
        left_child, 
        right_child;
    //find match_node and its child_node
    if (the_player<=lowExt)
    {
        match_node=(offset+the_player)/2;
        left_child=2*match_node-offset;
        right_child=left_child+1;
    }
    else
    {
        match_node=(the_player-lowExt+n-1)/2;
        if (2*match_node==n-1)
        {
            left_child=tree[2*match_node];
            right_child=the_player;
        }
        else
        {
            left_child=2*match_node+lowExt-n+1;
            right_child=left_child+1;
        }
    }
    T winner=(player[left_child]>=player[right_child])?left_child:right_child;
    if (tree[match_node]!=winner)
    {
        tree[match_node]=winner;
    }
    else return; 
    if (match_node==n-1&&match_node%2==1)
    {
        match_node/=2;
        left_child=tree[n-1];
        right_child=lowExt+1;
        winner=(player[left_child]>=player[right_child])?left_child:right_child;
        if (tree[match_node]!=winner)
        {
            tree[match_node]=winner;
        }
        else return;
    }
    match_node/=2;
    for(;match_node>=1;match_node/=2)
    {
        left_child=tree[2*match_node];
        right_child=tree[2*match_node+1];
        winner=(player[left_child]>=player[right_child])?left_child:right_child;
        if (tree[match_node]!=winner)
        {
            tree[match_node]=winner;
        }
        else return;
    }
};
template<class T>
void maxwinner_competitivetree<T>::output()const
{
    std::cout<<"number of players ="<<players_number
             <<"lowExt ="<<lowExt
             <<"offset ="<<offset<<std::endl;
    std::cout<<"maxnum winner completitive tree are"<<std::endl;
    for (int i = 1; i < players_number; i++)
        std::cout<<tree[i]<<' ';
    std::cout<<std::endl;
}
/* ------------------------ maxloser_competitivetree ------------------------ */
template<class T>
maxloser_competitivetree<T>::maxloser_competitivetree(T *the_player,int the_player_number)
{
    advance=NULL;
    tree=NULL;
    initialise(the_player,the_player_number);
};
template<class T>
maxloser_competitivetree<T>::~maxloser_competitivetree(){delete[] tree;delete[] advance;};
template<class T>
void maxloser_competitivetree<T>::initialise(T *the_player,int the_player_number)
{
    if (the_player_number<1)
    {
        throw std::runtime_error("the_player_number in invaild");
    }
    player_number=the_player_number;
    player=the_player;
    delete[] advance;
    delete[] tree;
    advance=new int[player_number];
    tree=new int[player_number];

    //compute s(lowest-level leftmost internal node)
    int i,s;
    for(s=1;2*s<player_number;s*=2);
    lowExt=2*(player_number-s);
    offset=2*s-1;

    for (i = 2; i <=lowExt; i+=2)
        play((offset+i)/2,i-1,i);
    //special case
    if (player_number%2==1)
    {
        i=lowExt+3;
    }
    else i=lowExt+2;
    for (; i <=player_number; i+=2)
        play((i-lowExt+player_number-1)/2,i-1,i);
    tree[0]=advance[1];
};
template<class T>
int maxloser_competitivetree<T>::competitor()const{return tree[0];};
template<class T>
int maxloser_competitivetree<T>::competitor(int i)const{return (i<player_number&&i>=0)?tree[i]:0;};
template<class T>
void maxloser_competitivetree<T>::play(int match_node,int left_child,int right_child)
{
    if (player[left_child]<=player[right_child])
    {
        tree[match_node]=left_child;
        advance[match_node]=right_child;
    }
    else
    {
        tree[match_node]=right_child;
        advance[match_node]=left_child;
    }
    while (match_node%2==1&&match_node>1)
    {
        if (player[advance[match_node]]<=player[advance[match_node-1]])
        {
            tree[match_node/2]=advance[match_node];
            advance[match_node/2]=advance[match_node-1];
        }
        else
        {
            tree[match_node/2]=advance[match_node-1];
            advance[match_node/2]=advance[match_node];
        }
        match_node/=2;
    }
};
template<class T>
void maxloser_competitivetree<T>::replay(int the_player,T the_player_element)
{
    if (the_player>player_number&&the_player<0)
        throw std::runtime_error("the_player is invaild");
    
    player[the_player]=the_player_element;
    
    int match_node,
        left_child,
        right_child;

    //find match_node and its child
    if(the_player<=lowExt)
    {
        match_node=(offset+the_player)/2;
        left_child=2*match_node-offset;
        right_child=left_child+1;
    }
    else
    {
        match_node=(the_player-lowExt+player_number-1)/2;
        if (2*match_node==player_number-1&&player_number%2==1)
        {
            left_child=advance[player_number-1];
            right_child=the_player;
        }
        else
        {
            left_child=2*match_node+lowExt-player_number+1;
            right_child=left_child+1;            
        }
    }

    //replay
    if (player[the_player]<=player[advance[match_node]])
    {
        advance[match_node]=tree[match_node];
        tree[match_node]=the_player;
        return;
    }
    else 
    {
        tree[match_node]=advance[match_node];
        advance[match_node]=the_player;
    };
    if (match_node==player_number-1&&player_number%2==1)
    {
        match_node/=2;
        if (player[the_player]<=player[advance[match_node]])
        {
            advance[match_node]=tree[match_node];
            tree[match_node]=the_player;
            return;
        }
        else 
        {
            tree[match_node]=advance[match_node];
            advance[match_node]=the_player;
        };
    }
    match_node/=2;
    for(;match_node>=1;match_node/=2)
    {
        if (player[the_player]<=player[advance[match_node]])
        {
            advance[match_node]=tree[match_node];
            tree[match_node]=the_player;
            return;
        }
        else 
        {
            tree[match_node]=advance[match_node];
            advance[match_node]=the_player;
        };
    }
    tree[0]=advance[1];
}
template<class T>
void maxloser_competitivetree<T>::output()const
{
    std::cout<<"number of players ="<<player_number<<" "
             <<"lowExt ="<<lowExt<<" "
             <<"offset ="<<offset<<std::endl;
    std::cout<<"maxnum loser competitive tree are"<<std::endl;
    for (int i = 0; i < player_number; i++)
        std::cout<<tree[i]<<" ";
    std::cout<<std::endl;
};
/* -------------------------------------------------------------------------- */
/*                             binary_search_tree                             */
/* -------------------------------------------------------------------------- */
template<class K,class E>
bool binary_search_tree<K,E>::empty()const{return chain_binarytree<std::pair<const K,E>>::binarytree_length==0;};
template<class K,class E>
int binary_search_tree<K,E>::length()const{return chain_binarytree<std::pair<const K,E>>::binarytree_length;};
template<class K,class E>
std::pair<const K,E> *binary_search_tree<K,E>::find(const K &the_key)const
{
    binarytree_node<std::pair<const K,E>> *p=chain_binarytree<std::pair<const K,E>>::root;
    while (p!=NULL)
    {
        if (the_key<p->element.first)
        {
            p=p->left_child;
        }
        else if (the_key>p->element.first)
        {
            p=p->right_child;
        }
        else return &p->element;
    }
    return NULL;
    
};
template<class K,class E>
void binary_search_tree<K,E>::insert(const std::pair<const K,E> &the_pair)
{
    binarytree_node<std::pair<const K,E>> *p=chain_binarytree<std::pair<const K,E>>::root,
                                          *previous_p=NULL;
    //check p->element
    while (p!=NULL)
    {
        previous_p=p;
        if (p->element.first<the_pair.first)
        {
            p=p->left_child;
        }
        else if (p->element.first>the_pair.first)
        {
            p=p->right_child;
        }
        else
        {
            p->element.second=the_pair.second;
            return;
        }
    }
    //create a new node for the_pair
    binarytree_node<std::pair<const K,E>> *new_node
        =new binarytree_node<std::pair<const K,E>>(the_pair);
    //new_node link to previous_p
    if (chain_binarytree<std::pair<const K,E>>::root!=NULL)
    {
        if(previous_p->element.first<the_pair.first)
        {
            previous_p->right_child=new_node;
        }   
        else if (previous_p->element.first>the_pair.first)
        {
            previous_p->left_child=new_node;
        }
    }
    else chain_binarytree<std::pair<const K,E>>::root=new_node;

    chain_binarytree<std::pair<const K,E>>::binarytree_length++;
};
template<class K,class E>
void binary_search_tree<K,E>::erase(const K &the_key)
{
    binarytree_node<std::pair<const K,E>> *p=chain_binarytree<std::pair<const K,E>>::root,
                                          *previous_p=NULL;
    //find the node to erase
    while (p!=NULL&&p->element.first!=the_key)
    {
        previous_p=p;
        if (the_key<p->element.first)
        {
            p=p->left_child;
        }
        else p=p->right_child;
    }
    if (p==NULL)return;
    //reorganize the tree sturcture
    //if p have two no-zero subtrees
    if (p->left_child!=NULL&&p->right_child!=NULL)
    {
        //convert to empty or only one child case
        //find max element_node at the left child of p
        binarytree_node<std::pair<const K,E>> *s=p->left_child,
                                              *previous_s=p;
        //s move to max element_node
        while (s->right_child!=NULL)
        {
            previous_s=s;
            s=s->right_child;
        }
        //q->element = s->element
        binarytree_node<std::pair<const K,E>> *q=new binarytree_node<std::pair<const K,E>>(s->element,p->left_child,p->right_child);
        if (previous_p==NULL)
            chain_binarytree<std::pair<const K,E>>::root=q;   
        else 
        {
            if (p==previous_p->left_child)
                previous_p->left_child=q;
            else 
                previous_p->right_child=q;
        }
        //p move to the max element_node s
        if (previous_s==p)previous_p=q;
        else previous_p=previous_s;
        delete p;
        p=s;
    }
    //if p have at most one no-zero subtree
    binarytree_node<std::pair<const K,E>> *c;
    if (p->left_child!=NULL)
    {
        c=p->left_child;
    }
    else 
        c=p->right_child;
    if (p==chain_binarytree<std::pair<const K,E>>::root)
    {
        chain_binarytree<std::pair<const K,E>>::root=c;
    }
    else
    {
        if (p==previous_p->left_child)
        {
            previous_p->right_child=c;
        }
        else previous_p->right_child=c;
    }
    delete p;
    chain_binarytree<std::pair<const K,E>>::binarytree_length--;
};
template<class K,class E>
void binary_search_tree<K,E>::ascend()
{
    chain_binarytree<std::pair<const K,E>>::in_order_output();
};
/* -------------------------------------------------------------------------- */
/*                         indexed_binary_search_tree                         */
/* -------------------------------------------------------------------------- */
template<class K,class E>
indexed_binary_search_tree<K,E>::indexed_binary_search_tree()
{
    root=NULL;
    binarytree_length=0;
};
template<class K,class E>
indexed_binary_search_tree<K,E>::~indexed_binary_search_tree()
{
    delete root;
};
template<class K,class E>
bool indexed_binary_search_tree<K,E>::empty()const{return binarytree_length==0;};
template<class K,class E>
int indexed_binary_search_tree<K,E>::length()const{return binarytree_length;};
template<class K,class E>
std::pair<const K,E> *indexed_binary_search_tree<K,E>::find(const K &the_key)const
{
    indexed_bstree_node<std::pair<const K,E>> *p=root;
    while(p!=NULL)
    {
        if (the_key>p->element.first)
        {
            p=p->right_child;
        }
        else if (the_key<p->element.first)
        {
            p=p->left_child;
        }
        else return &p->element;
    }
    return NULL;
};
template<class K,class E>
std::pair<const K,E> *indexed_binary_search_tree<K,E>::get(const int the_index)const
{
    //get the element of the_index
    indexed_bstree_node<std::pair<const K,E>> *p=root;
    int i=the_index;
    while (p!=NULL)
    {
        if (i<p->left_sise+1)
        {
            p=p->left_child;
            i--;
        }
        else if (i>p->left_sise+1)
        {
            p=p->right_child;
            i-=p->left_sise+1;
        }
        else return &p->element;
    }
    return NULL;
};
template<class K,class E>
void indexed_binary_search_tree<K,E>::insert(const std::pair<const K,E> &the_pair)
{
    indexed_bstree_node<std::pair<const K,E>> *p=root,
                                              *previous_p=NULL;
    //chack p->element
    while (p!=NULL)
    {
        previous_p=p;
        if (p->element.first>the_pair.first)
        {
            p->left_sise++;
            p=p->left_child;
        }
        else if(p->element.first<the_pair.first)
        {
            p=p->right_child;
        }
        else
        {
          p->element.second=the_pair.second;
          return;  
        }
    }
    //
    indexed_bstree_node<std::pair<const K,E>> *new_node
        =new indexed_bstree_node<std::pair<const K,E>>(the_pair);
    if (root!=NULL)
    {
        if (the_pair.first>previous_p->element.first)
        {
            previous_p->right_child=new_node;
        }
        else if(the_pair.first<previous_p->element.first)
        {
            previous_p->left_child=new_node;
        }
    }
    else
    {
        root=new_node;
        root->left_sise=0;
    } 
    binarytree_length++;
};
template<class K,class E>
void indexed_binary_search_tree<K,E>::erase(const K &the_key)
{
    indexed_bstree_node<std::pair<const K,E>> *p=root,
                                              *previous_p=NULL;
    //find the node to erase
    while (p!=NULL&&p->element.first!=the_key)
    {
        previous_p=p;
        if (the_key>p->element.first)
        {
            p=p->right_child;
        }
        else p=p->left_child;
    }
    if (p==NULL)return;
    //reorganize the tree structure
    //if p have two no-zero subtree
    if (p->left_child!=NULL&&p->right_child!=NULL)
    {
        indexed_bstree_node<std::pair<const K,E>> *s=p->left_child,
                                                  *previous_s=p;
        //find the maxnum node in left_child of p;
        while (s->right_child!=NULL)
        {
            previous_s=s;
            s=s->right_child;
        }
        //p and s swap place
        indexed_bstree_node<std::pair<const K,E>> *q
            =new indexed_bstree_node(s->element,p->left_child,p->right_child);
        //if erase root node
        if (previous_p==NULL)
        {
            root=q;
        }
        else
        {
            if (previous_p->left_child==p)
            {
                previous_p->left_child=q;
            }
            else
            {
                previous_p->right_child=q;
            }
        }
        //p move to maxnum node s
        if (previous_s=p)previous_s=q;
        else previous_p=previous_s;
        delete p;
        p=s;
    }
    //if p have at most one no-zero subtree
    indexed_bstree_node<std::pair<const K,E>> *nozero_child;
    if (p->left_child!=NULL)
    {
        nozero_child=p->left_child;
    }
    else
    {
        nozero_child=p->right_child;
    }
    if (p==root)
    {
        root=nozero_child;
    }
    else
    {
        if (previous_p->left_child=p)
        {
            previous_p->left_child=nozero_child;
        }
        else
        {
            previous_p->right_child=nozero_child;
        }
    }
    delete p;
    binarytree_length--;
};
template<class K,class E>
void indexed_binary_search_tree<K,E>::erase(const int the_index)
{
    int i=the_index;
    indexed_bstree_node<std::pair<const K,E>> *p=root,
                                              *previous_p=NULL;
    while (p!=NULL)
    {
        previous_p=p;
        if (i>p->left_sise+1)
        {
            i-=p->left_sise+1;
            p=p->right_child;
        }
        else if (i<p->left_sise+1)
        {
            i--;
            p=p->left_child;
        }
        else break;
    }
    if (p==NULL)return;
    if (p->left_child!=NULL&&p->right_child!=NULL)
    {
        indexed_bstree_node<std::pair<const K,E>> *s=p->left_child,
                                                  *previous_s=p;
        while (s->right_child!=NULL)
        {
            previous_s=s;
            s=s->right_child;
        }
        indexed_bstree_node<std::pair<const K,E>> *q=
            new indexed_bstree_node<std::pair<const K,E>>(s->element,p->left_child,p->right_child);
        if (previous_p->left_child==p)
        {
            previous_p->left_child=q;
        }
        else
        {
            previous_p->right_child=q;
        }
        if (previous_s=p)previous_p=q;
        else previous_p=previous_s;
        delete p;
        p=s;
    }
    indexed_bstree_node<std::pair<const K,E>> *nozero_child;
    if (p->left_child!=NULL)
    {
        nozero_child=p->left_child;
    }
    else if (p->right_child!=NULL)
    {
        nozero_child=p->right_child;
    }
    if (p==root)
    {
        root=nozero_child;
    }
    else
    {
        if (previous_p->left_child==p)
        {
            previous_p->left_child=nozero_child;
        }
        else if (previous_p->right_child==p)
        {
            previous_p->right_child=nozero_child;
        }
    }
    delete p;
    binarytree_length--;
};
template<class K,class E>
void indexed_binary_search_tree<K,E>::ascend()
{
    in_order(root);
};
template<class K,class E>
void indexed_binary_search_tree<K,E>::in_order(indexed_bstree_node<std::pair<const K,E>> *t)
{
    if (t!=NULL)
    {
        in_order(t->left_child);
        std::cout<<t<<std::endl;
        in_order(t->right_child);
    }
    
};
#endif