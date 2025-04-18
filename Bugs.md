
# Dangling Pointers

* When you create a local variable (like last), it is allocated on the stack. Stack memory is automatically reclaimed when the function exits, and the object is destroyed.
* Storing a pointer to a stack-allocated object outside its scope (e.g., in a linked list or a map) is unsafe because the object will no longer exist after the function exits.
	```cpp
	void put(int key, int value) {
	    Node newNode(key, value);	//Will be allocated on stack and gets deleted after function return
	    mp[key] = *tail;
	    tail->next = &newNode; // Link the new node to the list
	    tail = tail->next; // Update tail to the new node
	}
	```
* Correct Approach (this is also wrong check below for common error) -> 

	```cpp
	void put(int key, int value) {
	    Node* newNode = new Node(key, value); // Allocate on the heap
	    mp[key] = *tail; // Store the previous tail in the map
	    tail->next = newNode; // Link the new node to the list
	    tail = tail->next; // Update tail to the new node
	}
	```
# CAUTION when using Map
```cpp
map<int, Node> mp;
Node newNode(3);
mp[3] = newNode; //map will store the copy of the newNode, modifying map[3] will not modify newNode
```
* If the key does not exist in the map:
	* mp[key] inserts a new key-value pair into the map.
	* The value is default-constructed (if non pointer type,this is why default constuction is important of struct or class).
	* The size of the map increases by 1.
   	* calling [] operator frequently will keep on increasing memory, resulting in MLE or runtime error
   	* The find method does not modify the map. It returns an iterator to the element if the key is found, otherwise it returns end().
