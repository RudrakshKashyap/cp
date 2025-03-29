## Definition for singly-linked list.
```cpp
 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}		//default constructor
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
```

* If you do not define any constructors, the compiler generates a default constructor.
* If you define any constructor, the compiler does not generate a default constructor.
* If a class has members without default constructors, the compiler cannot generate a default constructor for the class.

## Default Initialization

* Default initialization occurs when a variable is declared without an explicit initializer.
	* The behavior of default initialization depends on:
		* The type of the variable (fundamental type, class type, etc.).
		* The storage duration of the variable (automatic, static, dynamic, etc.).
    
 ###  Default Initialization for Fundamental Types
 The value after default initialization depends on the storage duration of the variable.
1. Automatic Storage Duration (Local Variables) - These variables are not initialized by default. Their values are indeterminate (garbage values).
2. Static Storage Duration (Global/Static Variables) - These variables are zero-initialized by default.

### Default Initialization for Class Types
* If the class does not have a default constructor, you must explicitly initialize the object:
  ```cpp
  struct MyClass {
		int x;
		MyClass(int val) : x(val) {} // No default constructor
	};
	
	void foo() {
	    // MyClass obj; // Error: No default constructor
	    MyClass obj(10); // OK: Explicit initialization
	}
  ```
* However, since C++11, you can provide default member initializers directly in the class definition.

* Check this code
  ```cpp
  #include <unordered_map>

	struct Node {
	    int key, val;
	    Node *next;
	    Node(int k, int v) : key(k), val(v), next(nullptr) {} // Constructor 1
	    Node(int k, int v, Node *next) : key(k), val(v), next(next) {} // Constructor 2
	};
	
	class LRUCache {
	    int sz, n;
	    std::unordered_map<int, Node*> mp; // key, prevNode
	    Node head(-1, -1); // ERROR
	    Node head; // Member 'head' of type Node	-- no default constructor, so you have to explicit initiazlit it later
	    Node *tail;
	
	public:
	    // Initialize 'head' in the member initializer list
	    LRUCache(int capacity) : sz(0), n(capacity), head(-1, -1) {
	        tail = &head;
	    }
	};
  ```
  ### Problem
  ```cpp
  Node head(-1, -1); // ERROR
  ```
	- This line tries to call a constructor directly in the class definition, which is not allowed for non-static members.
	- Default member initialization (since C++11) only allows:
		- = value (assignment-style)
		- {value} (brace initialization)
		- Not direct constructor calls with (args).
  ### Fix 1 - Use Brace Initialization
  ```cpp
  Node head{-1, -1}; // Correct (uses uniform initialization)
  ```
  ### Fix 2 - Initialize in the Constructor's Member Initializer List

# The Problem: Dangling Pointers

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
## Common error
```cpp
map<int, Node> mp;
Node newNode(3);
mp[3] = newNode; //map will store the copy of the newNode, modifying map[3] will not modify newNode
```
* If the key does not exist in the map:
	* mp[key] inserts a new key-value pair into the map.
	* The value is default-constructed (if non pointer type,this is why default constuction is important of struct or class).
	* The size of the map increases by 1.
