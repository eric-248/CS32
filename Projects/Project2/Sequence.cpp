#include "Sequence.h"
#include <iostream>

using namespace std;

Sequence::Sequence() {

	//intialize all member variables
	m_size = 0;
	head = nullptr;
	tail = nullptr;
}

Sequence::~Sequence() {
	
	if (head == nullptr) {
		return;
	}

	Node* current = head;
	Node* next;

	while (current != nullptr) {
		next = current->next;
		delete current;
		current = next;
	}
}

Sequence::Sequence(const Sequence& other) {

	for (int i = 0; i < other.size(); i++)
	{
		ItemType a;
		other.get(i, a);
		insert(i, a);
	}
}

Sequence& Sequence::operator=(const Sequence& other) {
	if (this != &other) {
		Sequence temp = other;
		swap(temp);
	}

	return *this;
	
}

bool Sequence::empty() const{
	return m_size == 0;
}

int Sequence::size() const {
	return m_size;
}

int Sequence::insert(int pos, const ItemType& value) {
	
	//check pos
	if (pos < 0 || pos > m_size) {
		return -1;
	}

	//create node
	Node* n = new Node{ value,nullptr,nullptr };

	//beginning
	//if size is 0
	if (m_size == 0 && pos == 0) {

		//head and tail both point to n
		head = n;
		tail = n;

		m_size++;
		return 0;
	}if (m_size > 0 && pos == 0) {

		//insert at first spot
		n->next = head;
		head->prev = n;
		head = n;
		m_size++;
		return 0;
	}
	//end
	else if (pos == m_size) {
		tail->next = n;
		n->prev = tail;
		tail = n;
		tail->next = nullptr;

		m_size++;
		return (m_size - 1);
	}//middle
	else {
		Node* temp = head;
		int index = 0;

		for (int i = 0; i < pos - 1; i++) {
			temp = temp->next;
			index++;
		}
		
		n->prev = temp;
		n->next = temp->next;
		n->prev->next = n;
		n->next->prev = n;

		m_size++;
		return index + 1;
	
	}

	return -1;
}

int Sequence::insert(const ItemType& value) {

	//find where to insert
	Node* temp = head;
	int i_to_insert = 0;

	for (; temp != nullptr; temp = temp->next) {
		if (value <= temp->m_elem) {
			break;
		}
		i_to_insert++;
	}

	//pass to other insert function
	insert(i_to_insert, value);

	return i_to_insert;
	
}


// If 0 <= pos < size(), remove the item at position pos from
// the sequence (so that all items that followed that item end up at
// positions one lower than they were at before), and return true.
// Otherwise, leave the sequence unchanged and return false.
bool Sequence::erase(int pos) {

	// check pos
	if (pos < 0 || head == nullptr) {
		return false;
	}
	Node* current = head;
	// traverse the list to the node to be deleted
	for (int i = 0; i < pos && current != nullptr; i++) {
		current = current->next;
	}
	// check if node not found
	if (current == nullptr) { 
		return false;
	}
	//beginning
	if (current->prev != nullptr) {
		current->prev->next = current->next;
	}
	else {
		head = current->next;
	}//middle
	if (current->next != nullptr) {
		current->next->prev = current->prev;
	}//end
	else {
		tail = current->prev;
	}

	delete current;
	m_size--;
	return true;
}

// Erase all items from the sequence that == value.  Return the
// number of items removed (which will be 0 if no item == value).
int Sequence::remove(const ItemType& value) {

	//check for edge cases
	if (m_size == 0) {
		return 0;
	}

	int counter = 0;

	while (find(value)!= -1) {
		erase(find(value));
		counter++;

	}

	return counter;
}

// If 0 <= pos < size(), copy into value the item in position pos
// of the sequence and return true.  Otherwise, leave value unchanged
// and return false.
bool Sequence::get(int pos, ItemType& value) const {

	int index = 0;

	if (pos >= 0 && pos < m_size) {
		for (Node* p = head; p != nullptr; p = p->next){
			if (index == pos) {
				value = p->m_elem;//needs to be changed?
				break;
			}
			index++;
		}
		return true;
	}
	return false;
}


// If 0 <= pos < size(), replace the item at position pos in the
// sequence with value and return true.  Otherwise, leave the sequence
// unchanged and return false.
bool Sequence::set(int pos, const ItemType& value) {

	int index = 0;

	if (pos >= 0 && pos < m_size) {
		for (Node* p = head; p!= nullptr; p = p->next) {
			if (index == pos) {
				p->m_elem = value;//needs to be changed?
				break;
			}
			index++;
		}
		return true;
	}
	return false;

}


// Let p be the smallest integer such that value == the item at
// position p in the sequence; if no such item exists, let p be -1.
// Return p.

int Sequence::find(const ItemType& value) const {

	int index = 0;

	for (Node* p = head; p!= nullptr; p = p->next) {
		if (p->m_elem == value) {
			return index;
		}
		index++;
	}

	return -1;
}


// Exchange the contents of this sequence with the other one.
void Sequence::swap(Sequence& other) {

	//swap size
	int temp = m_size;
	m_size = other.m_size;
	other.m_size = temp;

	//swap head
	Node* temp_h = head;
	head = other.head;
	other.head = temp_h;

	//swap tail
	Node* temp_t = tail;
	tail = other.tail;
	other.tail = temp_t;

}

void Sequence::dump() const {
	Node* node = head;
	while (node != NULL) {
		cerr << node->m_elem << " ";
		node = node->next;
	}
	cerr << endl;
}

int subsequence(const Sequence& seq1, const Sequence& seq2) {
	
	int count = 0;

	for (int i = 0; i < seq1.size(); i++){
		for (int j = 0; j < seq2.size(); j++){

			ItemType a;
			seq1.get(i + j, a);

			ItemType b;
			seq2.get(j, b);

			if (a != b){

				count = 0;
			}
			else
			{
				count++;
			}

		}
		if (count == seq2.size()){

			return i;
		}

		if (i >= seq1.size() - seq2.size()){
			return -1;
		}

	}

	return -1;
	
}

void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result) {
	
	//reverse sequences
	Sequence r1;
	int r1_index = 0;

	for (int i = seq1.size() - 1; i >= 0; i--) {

		ItemType val;
		seq1.get(r1_index, val);
		r1.insert(r1_index, val);
		r1_index++;
	}

	Sequence r2;

	int r2_index = 0;

	for (int i = seq2.size() - 1; i >= 0; i--) {

		ItemType val;
		seq1.get(r2_index, val);
		r2.insert(r2_index, val);
		r2_index++;
	}	

	//combine into result
	result = r1;
	for (int i = 0; i < r2.size(); i++) {
		ItemType val;
		r2.get(i, val);
		result.insert(result.size(), val);
	}
	
}



