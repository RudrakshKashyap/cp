### Definition
In C++, a class definition is a blueprint for creating objects. 
It encapsulates data (member variables) and functions (member functions) that operate on that data. 

## Struct vs Class

|Feature  				| `struct`	    			| `class`					 |
|-----------------------|---------------------------|----------------------------|
| Default Access	    | public					| private					 |	
| Default Inheritance	| public (if not specified)	| private (if not specified) |

- If you're writing C-style POD (Plain Old Data), use struct.
- If you're doing full OOP (encapsulation, polymorphism), prefer class.
- But technically, you can use either interchangeably by adjusting access modifiers.

### Here’s a breakdown of what you can include in a class definition
| Feature               | Example Usage |
|-----------------------|---------------|
| Member Variables      | `int x;` |
| Member Functions      | `void print();` |
| Constructors/Destructor | `MyClass(); ~MyClass();` |
| Access Specifiers     | `public:`, `private:` |
| Operator Overloading  | `MyClass operator+();` |
| Friend Functions      | `friend void func();` |
| Nested Classes        | `class Inner {};` |
| Inheritance           | `class Derived : public Base {};` |
| Virtual Functions     | `virtual void f();` |
| Static Members        | `static int count;` |
| `const`/`mutable`     | `const int x; mutable int y;` |
| Templates             | `template <typename T> class Box {};` |


## OOPS
Object-oriented programming aims to implement real-world entities like inheritance, hiding, polymorphism, etc. in programming. 

### The Four Pillars of OOP
1. **Encapsulation**
   - Bundling data (attributes) and methods (functions) that operate on that data into a single unit (class)
   - Restricting direct access to some of an object's components (data hiding)
   ```cpp
	   	class BankAccount {
		private:
			double balance;  // Hidden data
		};
   ```
2. **Abstraction**
   - Showing only essential features while hiding implementation details
    ```cpp
	class Car {
	private:
	    // Complex engine implementation details hidden
	    void igniteFuel() { /* ... */ }
	    void rotateCrankshaft() { /* ... */ }
	
	public:
	    void start() {  // Simple interface
	        igniteFuel();
	        rotateCrankshaft();
	        // ...
	    }
	};
	```

3. **Inheritance**
   - Creating new classes (child/derived) from existing ones (parent/base)
     
4. **Polymorphism**
	- Same interface with different underlying implementations (you can basically override functions)
	- Example: A `draw()` method that behaves differently for Circle vs Square objects
	```cpp
	class Shape {
	public:
	    virtual void draw() {  // Virtual function enables polymorphism
	        cout << "Drawing a shape\n";
	    }
	};
	
	class Circle : public Shape {
	public:
	    void draw() override {
	        cout << "Drawing a circle\n";
	    }
	};
	
	class Square : public Shape {
	public:
	    void draw() override {
	        cout << "Drawing a square\n";
	    }
	};
	```
