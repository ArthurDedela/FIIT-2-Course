#pragma once

template <typename TYPE>
struct Node {
    Node(TYPE d) : data(d), next(nullptr) {};

    TYPE data;
    Node<TYPE>* next;
};


template <typename TYPE>
class QueueTp
{
    Node<TYPE>* head;

    void clear();

public:
    QueueTp() : head(nullptr) {};
    QueueTp(TYPE data);
    
    QueueTp(const QueueTp<TYPE> & obj);

    QueueTp<TYPE> & operator=(const QueueTp<TYPE> & obj);

    void push(TYPE data);
    void pop();

    TYPE front();



    ~QueueTp();
};


template<typename TYPE>
inline void QueueTp<TYPE>::clear()
{
    while (head != nullptr) {
        auto tmp = head;
        head = head->next;
        delete tmp;
    }
}

template<typename TYPE>
inline QueueTp<TYPE>::QueueTp(TYPE data)
{
    head = new Node<TYPE>(data);
}

template<typename TYPE>
inline QueueTp<TYPE>::QueueTp(const QueueTp<TYPE>& obj)
{
    *this = obj;
}

template<typename TYPE>
inline QueueTp<TYPE>& QueueTp<TYPE>::operator=(const QueueTp<TYPE>& obj)
{
    Node<TYPE>* it_1;

    this->clear();

    if (auto it_2 = head = obj.head) {
        head = new Node<TYPE>(it_2->data);
        it_1 = head;

        while (it_2 = it_2->next) {
            it_1->next = new Node<TYPE>(it_2->data);
            it_1 = it_1->next;
        }
    }
    
    return *this;
}


template<typename TYPE>
inline void QueueTp<TYPE>::push(TYPE data)
{
    if (auto it = head) {
        while (it->next != nullptr) it = it->next;

        it->next = new Node<TYPE>(data);
    }
    else {
        head = new Node<TYPE>(data);
    }
}

template<typename TYPE>
inline void QueueTp<TYPE>::pop()
{
    if (head == nullptr) return;

    auto tmp = head;
    head = head->next;
    delete tmp;
}

template<typename TYPE>
inline TYPE QueueTp<TYPE>::front()
{
    if (!head) {
        throw std::exception("Empty que");
        return TYPE{};
    }
    return head->data;
}


template<typename TYPE>
inline QueueTp<TYPE>::~QueueTp()
{
    clear();
}
