#include <iostream>

using namespace std;

struct Node {
	int data = 0;
	Node* next = nullptr;
	Node* previous = nullptr;
};

class DoublyLinkedList {
	private:
		Node* head;
		Node* tail;
	
	public:
		DoublyLinkedList(){
			head = nullptr;
			tail = nullptr;
	}
		
		//copy constructor
		DoublyLinkedList(const DoublyLinkedList & objCopy){
			head = nullptr;
			tail = nullptr;
			for (int i = 0; i < objCopy.size(); i++) {
				push(objCopy.at(i));
			}
		}
		//copy assignment operator
		void operator=(const DoublyLinkedList objCopy) {
			while (size() > 0) {
				pop();
			}
			for (int i = 0; i < objCopy.size(); i++) {
				push(objCopy.at(i));
			}
		}

		int size() const {
			if (head == nullptr) {
				return 0;
			}

			int numElements = 1;
			Node* currentPos = head;

			while (currentPos->next != nullptr) {
				currentPos = currentPos->next;
				numElements++;
			}
			return numElements;
		}

		//destructor
		~DoublyLinkedList() {
			while (size() > 0) {
				pop();
			}
		}

		void push(int data) {
			//empty list
			if (head == nullptr) {
				head = new Node;
				head->data = data;
				head->next = nullptr;
				head->previous = nullptr;
			}
			//searches for last element and inserts
			else {
				Node* currentPosition = head;

				while (currentPosition->next != nullptr){
					currentPosition = currentPosition->next;
				}
				currentPosition->next = new Node;
				tail = currentPosition->next;
				(currentPosition->next)->data = data;
				tail->previous = currentPosition;
				tail->next = nullptr;
			}
		}

		void pop() {
			//checks for empty list
			if (head == nullptr) {
				cout << "Connot Delete Empty List";
				return;
			}
			//checks to see if only one element
			Node* currentPos = head;
			if (currentPos->next == nullptr) {
				delete currentPos;
				head = nullptr;
				tail = nullptr;
				return;
			}

			Node* temp = tail->previous;
			delete tail;
			tail = temp;
			if (tail == nullptr)
				head = nullptr;

			else 
				tail->next = nullptr;	
		}

		void print() const{
			//checks for empty list
			if (head == nullptr) {
				cout << "Nothing Here; Empty List" << endl;
				return;
			}
			//runs through  until null pointer is found
			Node* currentPos = head;
			while (currentPos != nullptr) {
				cout << currentPos->data;
				currentPos = currentPos->next;
			}
		}

		int at(int idx) const {
			Node* currentPos = head;
			for (int i = 0; i < idx; i++)
				currentPos = currentPos;

			return currentPos->data;
		}

		void insert(int data, int pos) {

			if (pos == 0) {
				Node* temp = new Node;
				temp->data = data;
				temp->next = head;
				temp->previous = nullptr;
				temp->next->previous = temp;
				head = temp;
			}
		
			else {
				Node* currentPos = head;
				for (int i = 0; i < pos - 1; i++) {
					currentPos = currentPos->next;
				}
				if (currentPos->next->next == nullptr) {
					Node* temp = new Node;
					temp->data = data;
					temp->next = nullptr;
					temp->previous = tail;
					temp->previous->next = temp;
					tail = temp;	
				}
				else {
					Node* temp = currentPos->next;
					currentPos->next = new Node;
					currentPos->next->data = data;
					currentPos->next->previous = currentPos;
					currentPos->next->next = temp;
				}
			}
		}
		void remove(int pos) {
			if (pos == 0) {
				Node* currentPos = head->next;
				delete head;
				head = currentPos;
			}
			
			else {
				Node* currentPos = head;
				for (int i = 0; i < pos+1; i++) {
					currentPos = currentPos->next;
				}
				if (currentPos == nullptr) {
					Node* temp = tail->previous;
					delete tail;
					tail = temp;
					tail->next = nullptr;
				}
				else {
					currentPos->previous->next = currentPos->next;
					currentPos->next->previous = currentPos->previous;
					delete currentPos;
				}
			}
		}	
};

void test() {
	DoublyLinkedList dll;

	dll.push(1);
	dll.push(2);
	dll.push(3);

	DoublyLinkedList dllCopy = dll;

	dllCopy.push(4);
	dllCopy.remove(1);
	dllCopy.remove(0);
	dllCopy.insert(5, 1);

	dll.print();
	dllCopy.print();

	dll = dllCopy;
	dll.print();
}

int main() {
	test();
	return 0;
}