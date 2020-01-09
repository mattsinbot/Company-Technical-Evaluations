#include <iostream>
using namespace std;

struct Node{
	int value;
	Node* next = NULL; 
};

class LinkedList{
public:
	LinkedList(){std::cout << "LinkedList created \n";}
	~LinkedList();
	Node* head = NULL;
	int size = 0;
	int insert(const int& node_val);
	void traverse_display();
	void free_memory(Node* node);
};

int LinkedList::insert(const int& node_val){
	Node* new_node = new Node;
	new_node->value = node_val;
	
	if (head == NULL) {
		head = new_node; 
		return 1;
	}
	
	Node* current_node = head;
	while (current_node->next != NULL){
		current_node = current_node->next;
	}
	current_node->next = new_node;
	return 1;
}

void LinkedList::traverse_display(){
	cout << "Traversing LinkedList: ";
	Node* current_node = head;
	while (current_node != NULL){
		cout << current_node->value << " ";
		current_node = current_node->next;
	}
	cout << "\n";
}

LinkedList::~LinkedList(){
	free_memory(head);
}

void LinkedList::free_memory(Node* node){
	if (node != NULL) {
		free_memory(node->next); 
		delete node;
	}
}

void reverse_LinkedList(LinkedList* ll){
	LinkedList* reversed_LinkedList = new LinkedList();
	Node* current_node = ll->head;
	Node* prev_node = new Node;
	prev_node->value = ll->head->value;
	
	while (current_node->next != NULL) {
		Node* reversed_node = new Node;
		reversed_node->value = (current_node->next)->value;
		reversed_node->next = prev_node;
		prev_node = reversed_node;
		current_node = current_node->next;
		if (current_node->next == NULL){
			reversed_LinkedList->head = reversed_node;
		}
	}
	
	// Traver the reversed linkedlist
	reversed_LinkedList->traverse_display();
	
	delete reversed_LinkedList;
}

int main(){
	// create a linked list
	LinkedList* my_LinkedList = new LinkedList();
	
	// Start inserting values
	my_LinkedList->insert(10);
	my_LinkedList->insert(20);
	my_LinkedList->insert(30);
	my_LinkedList->insert(40);
	my_LinkedList->insert(50);
	my_LinkedList->insert(60);
	my_LinkedList->insert(70);
	
	// Traverse the LinkedList
	my_LinkedList->traverse_display();
	
	// Reverse LinkedList
	reverse_LinkedList(my_LinkedList);
	
	delete my_LinkedList;
	return 0;
}
