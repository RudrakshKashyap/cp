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
* Non-static data members cannot be initialized directly in the class definition.
* Use the member initializer list in the constructor to initialize non-static data members.
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
