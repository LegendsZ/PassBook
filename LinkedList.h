#pragma once

//Linked list class by Akkshai
class LinkedList {

private:

	struct node {
		void* obj;
		node* next;
	};

	node* head = nullptr;
	int cacheNodeCount = 0;

	node* iteration = nullptr;
public:

	/* This function returns a cache int containing how many nodes exist */
	int retNodeCount() const {
		return cacheNodeCount;
	}

	/* This function manually calculates and returns how many nodes are stored as an integer */
	int retManualNodeCount() const {
		node* curr = head;
		int tempIndex = 0;
		while (curr != nullptr) {
			curr = curr->next;
			tempIndex++;
		}
		return tempIndex;
	}

	/* This function returns the object pointer stored in the node as a void pointer using the index */
	void* retPtrByIndex(int index) const {
		int tempIndex = 0;
		node* temp = head;

		while (tempIndex != index && temp != nullptr) {
			temp = temp->next;
			tempIndex++;
		}
		if (temp != nullptr) {
			return temp->obj;
		}
		else {
			return (void*)0x0;
		}
	}

	/* This function returns a pointer to an array of all the void pointers (from the nodes) */
	void** retAllPtrsAsPtr() const {
		void** toRet = new void* [cacheNodeCount];
		int tempIndex = 0;
		node* curr = head;

		while (curr != nullptr) {
			toRet[tempIndex++] = curr->obj;
			curr = curr->next;
		}
		return toRet;
	}

	/* This function returns a pointer to an array of void pointers (from the nodes) (ammount specified by user) */
	void** retSomePtrsAsPtr(int count) const {
		if (count > cacheNodeCount) {
			return nullptr;
		}
		void** toRet = new void* [count];
		int tempIndex = 0;
		node* curr = head;

		while (tempIndex != count) {
			toRet[tempIndex++] = curr->obj;
			curr = curr->next;
		}
		return toRet;
	}

	/* This function returns a pointer to an array of void pointers (substring specified by user) (from the nodes) (ammount specified by user) */
	void** retSubStringPtrsAsPtr(int startIndex, int count)const {
		if (count > cacheNodeCount - startIndex) {
			return nullptr;
		}
		void** toRet = new void* [count];
		int tempIndex = 0;
		node* curr = head;

		while (tempIndex != startIndex + count) {
			if (tempIndex >= startIndex) {
				toRet[tempIndex++] = curr->obj;
			}
			curr = curr->next;
		}
		return toRet;
	}

	/* This function adds a node to the end with the given pointer stored in it returns true/false for success/fail respectively */
	bool addNodeByPtr(void* vPtr) {
		node* n = new node();
		n->obj = vPtr;
		n->next = nullptr;
		node* curr = head;

		if (head != nullptr) {
			while (curr->next != nullptr) {
				curr = curr->next;
			}
			curr->next = n;
		}
		else {
			head = n;
		}
		cacheNodeCount++;
		return true;
	}

	/* This function adds a node to the index given by user with the given pointer stored in it returns true/false for success/fail respectively */
	bool addNodeByIndex(int index, void* vPtr) {
		if (index <= cacheNodeCount) {
			node* n = new node();
			n->next = nullptr;
			n->obj = vPtr;

			int tempIndex = 0;
			node* curr = head;
			node* temp = curr;

			while (tempIndex != index) {
				temp = curr;
				curr = curr->next;
				tempIndex++;
			}
			temp->next = n;
			n->next = curr;

			cacheNodeCount++;
			return true;
		}
		else {
			return false;
		}
	}

	/* This function deletes the first node found that stores the pointer specified by user. Returns true/false if success/fail respectively */
	bool delNodeByPtr(void* vPtr) {
		node* curr = head;
		node* temp = curr;

		while (curr != nullptr && curr->obj != vPtr) {
			temp = curr;
			curr = curr->next;
		}

		if (curr == nullptr) {
			return false;
		}

		if (curr->next != nullptr) {
			temp->next = curr->next;
		}

		delete curr;
		cacheNodeCount--;
		return true;
	}

	/* This function deletes a node based on the index provided by the user. Returns true/false if success/fail respectively */
	bool delNodeByIndex(int index) {
		if (index < cacheNodeCount) {
			int tempIndex = 0;
			node* curr = head;
			node* temp = curr;

			while (tempIndex != index) {
				temp = curr;
				curr = curr->next;
				tempIndex++;
			}
			temp->next = curr->next;

			delete curr;
			cacheNodeCount--;
			return true;
		}
		else {
			return false;
		}
	}

	/* This function deletes a node and its object based on the index provided by the user. Returns true/false if success/fail respectively */
	template <typename T>
	bool delNodeAndObjectByIndex(int index) {
		if (index < cacheNodeCount) {
			int tempIndex = 0;
			node* curr = head;
			node* temp = curr;

			while (tempIndex != index) {
				temp = curr;
				curr = curr->next;
				tempIndex++;
			}
			temp->next = curr->next;

			delete (T*)curr->obj;
			delete curr;
			cacheNodeCount--;
			return true;
		}
		else {
			return false;
		}
	}

	/* This function allows the user to iterate through the list and stores the object into the void ptr. Returns true/false if success/fail respectively */
	bool next(void* ptrStore) {
		if (iteration == nullptr) {
			iteration = head;
			ptrStore = iteration->obj;
		}
		else {
			if (iteration->next != nullptr) {
				iteration = iteration->next;
				ptrStore = iteration->obj;
			}
			else {
				return false;
			}
		}
		return iteration->obj != nullptr ? true : false;
	}

	/* This function resets the iteration status. Returns true/false if success/fail respectively */
	bool iterationClear() {
		iteration = nullptr;
		return true;
	}
};