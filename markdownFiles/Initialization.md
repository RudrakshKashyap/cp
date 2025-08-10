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

	struct Node {
	    int key, val;
	    Node *next;
	    Node(int k, int v) : key(k), val(v), next(nullptr) {} // Constructor 1
	    Node(int k, int v, Node *next) : key(k), val(v), next(next) {} // Constructor 2
	};

	bool Compare(Node* p, Node* q)  { 
        return p->val > q->val;
    }
	
	class LRUCache {
	    int sz, n;
	    unordered_map<int, Node*> mp; // key, prevNode
	    Node head(-1, -1); // ERROR
	    Node head; // Member 'head' of type Node	-- no default constructor, OMPILATION ERROR
	    Node *tail;

		// decltype(&Compare) resolves to bool (*)(Node*, Node*)
		// (a function pointer type).
		// you can also create a func pointer and use it
		bool (*comp_func_ptr)(Node*, Node*) = &Compare;
		set<Node*, decltype(&Compare)> s;

	public:
	    // Initialize 'head' in the member initializer list
	    LRUCache(int capacity) : sz(0), n(capacity), head(-1, -1), s(Compare) {
	        tail = &head;
	    }
  		~LRUCache() { delete head; }  //line only for reference, destructor used to clean up memory on heap(malloc, or new keyword)
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
  set<Node*, decltype(&Compare)> s{Compare};
  ```
  ### Fix 2 - Initialize in the Constructor's Member Initializer List

## NOTE
```cpp
class LRUCache {
	int sz;
	sz = 8;  // INVALID: Assignment statement in class definition

	int sz = 8;	// VALID: In-class member initializer (C++11+), NOT an assignment statement
	Node head;
	head.key = -1, head.val = -1;	//This is not valid C++ syntax - you cannot assign to members in the class definition
}
```
Before C++11, you couldn't even do `int sz = 8;` in class definitions - all initialization had to be in constructors. The `in-class initialization` feature was added to simplify common cases while maintaining clear syntax rules.
