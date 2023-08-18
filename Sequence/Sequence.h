#ifndef NEW_SEQUENCE
#define NEW_SEQUENCE

#include <string>

using ItemType = std::string;

class Sequence
{
public:
    Sequence();
    ~Sequence();
    Sequence(const Sequence& other);
    Sequence& operator=(const Sequence& other);

    bool empty() const;
    int size() const;
    int insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);  
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);

    void dump ()const;
   

private:
    //doubly linked list
    struct Node {
        ItemType m_elem;
        Node* prev;
        Node* next;
    };

    //
    int m_size;
    Node* head;
    Node* tail;
   

};


int subsequence(const Sequence& seq1, const Sequence& seq2);
void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result);


#endif //NEW_SEQUENCE