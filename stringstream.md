# **C++ StringStream Detailed Notes**

## **1. Introduction to StringStream**
StringStream classes (in `<sstream>` header) allow you to treat strings as streams, enabling easy parsing and formatting.

**Types:**
- `istringstream` - Input string stream (read-only)
- `ostringstream` - Output string stream (write-only)  
- `stringstream` - Bidirectional string stream (read/write)

---

## **2. Basic Usage Examples**

### **Extracting Data (>> operator)**
```cpp
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

stringstream ss("John 25 95.5");
string name;
int age;
double score;

ss >> name >> age >> score;
cout << name << " " << age << " " << score << endl;
// Output: John 25 95.5
```

### **Inserting Data (<< operator)**
```cpp
stringstream ss;
ss << "Age: " << 25 << " Score: " << 95.5;
cout << ss.str() << endl;
// Output: Age: 25 Score: 95.5
```

---

## **3. Important Methods & Properties**

### **.str() - Get/Set String Content**
```cpp
stringstream ss("Initial");
cout << ss.str() << endl;  // Get: "Initial"

ss.str("New Content");     // Set new content
cout << ss.str() << endl;  // "New Content"
```

### **.clear() - Clear Error States**
```cpp
stringstream ss("100");
int num;
ss >> num;                 // Successfully reads 100

ss >> num;                 // Fails, sets failbit
if (ss.fail()) {
    ss.clear();            // Clear error state
    ss.str("200");         // Reset content
    ss >> num;             // Now works
}
```

### **Overwriting Behavior** ⚠️
```cpp
stringstream ss("abcdef");
ss << "xxx";              // Overwrites from beginning
cout << ss.str() << endl; // Output: "xxxdef"

ss.str("");               // Clear completely
ss << "new";
cout << ss.str() << endl; // Output: "new"
```

---

## **4. Character-Level Operations**

### **.get() - Extract Single Character**
```cpp
stringstream ss("45aaaa");
char c = ss.get();        // Extracts '4'
cout << c << endl;        // Output: '4'

cout << ss.str() << endl; // Content remains "45aaaa"

c = ss.get();        // Extracts '5'
cout << c << endl;        // Output: '5'
```

```
Initial:     [4][5][a][a][a][a]
             ↑ (position 0)

After get(): [4][5][a][a][a][a]
                ↑ (position 1)

After >>:    [4][5][a][a][a][a]
                   ↑ (position 2)
```

```cpp
stringstream ss("45aaaa");
cout << "Position: " << ss.tellg() << endl; // 0
ss.get();
cout << "Position: " << ss.tellg() << endl; // 1
ss.seekg(0); // Reset to beginning
cout << "Position: " << ss.tellg() << endl; // 0
```


### **.peek() - Look Ahead Without Extracting**
```cpp
stringstream ss("45aaaa");
char c = ss.peek();                 // Returns '4' without removing
cout << c << endl;                  // Output: '4'

int single_digit = ss.get() - '0';  // Now actually extracts '4'
cout << single_digit << endl;       // Output: '4'
```

### **.putback() - Return Character to Stream**
```cpp
stringstream ss("abc");
char c = ss.get();        // c = 'a'
ss.putback(c);            // Put 'a' back
c = ss.get();             // c = 'a' again
```

---

## **5. Parsing Techniques**

### **Type Conversion**
```cpp
// String to number
stringstream ss1("42");
int num;
ss1 >> num;               // num = 42

// Number to string  
stringstream ss2;
ss2 << 3.14;
string pi_str = ss2.str(); // pi_str = "3.14"
```

### **Handling Multiple Values**
```cpp
string data = "Apple 5 2.99 Banana 3 1.50";
stringstream ss(data);
string fruit;
int quantity;
double price;

while (ss >> fruit >> quantity >> price) {
    cout << fruit << ": " << quantity * price << endl;
}
// Output: Apple: 14.95 Banana: 4.5
```

### **Error Handling**
```cpp
stringstream ss("123 abc");
int num;
string text;

ss >> num;                // Success: num = 123
if (ss.fail()) {
    cout << "Failed to read number" << endl;
}

ss >> text;               // Success: text = "abc"
```

---

## ------------------------- **6. Advanced Usage** --------------------------

### **With getline() for CSV Parsing**
- It extracts and discards the newline character from the stream
- The delimiter `=` in `getline(line_ss, key, '=')` is also discarded
```cpp
string csv = "John,Doe,25\nJane,Smith,30";
stringstream ss(csv);
string line, token;

while (getline(ss, line)) {       // Read each line
    stringstream line_ss(line);
    while (getline(line_ss, token, ',')) { // Split by comma
        cout << token << " | ";
    }
    cout << endl;
}
// Output: John | Doe | 25 | 
//         Jane | Smith | 30 |
```

### **Resetting a StringStream**
```cpp
stringstream ss;
ss << "First: " << 100;
cout << ss.str() << endl;  // "First: 100"

// To reuse completely:
ss.str("");                // Clear content
ss.clear();                // Clear error flags
ss << "Second: " << 200;
cout << ss.str() << endl;  // "Second: 200"
```

### **Binary Data Handling**
```cpp
stringstream ss;
int num = 255;
ss.write(reinterpret_cast<char*>(&num), sizeof(num));

int read_num;
ss.read(reinterpret_cast<char*>(&read_num), sizeof(read_num));
cout << read_num << endl;  // Output: 255
```

---

## **7. Common Pitfalls & Solutions**

### **Pitfall 1: Mixed Extraction Failing**
```cpp
stringstream ss("100abc");
int num;
ss >> num;                 // Reads 100, stops at 'a'
// ss now has "abc" remaining
```

### **Pitfall 2: Forgetting to Clear**
```cpp
stringstream ss("100");
int num1, num2;
ss >> num1;                // num1 = 100
ss >> num2;                // Fails! Need to clear()
```

### **Solution: Robust Parsing**
```cpp
string input = "100abc200";
stringstream ss(input);
int num;
char c;

while (ss) {
    if (isdigit(ss.peek())) {
        ss >> num;
        cout << "Number: " << num << endl;
    } else {
        ss >> c;
        cout << "Char: " << c << endl;
    }
}
```

---

## **8. Performance Considerations**

- **Reuse stringstream objects** instead of creating new ones
- **Use .str("") and .clear()** for resetting
- **Pre-allocate memory** if known size:
```cpp
stringstream ss;
ss.rdbuf()->pubsetbuf(nullptr, 1024); // Pre-allocate 1KB
```

---

## **9. Real-World Examples**

### **Configuration File Parser**
```cpp
string config = "width=800\nheight=600\ntitle=My App";
stringstream ss(config);
string line;

while (getline(ss, line)) {
    stringstream line_ss(line);
    string key, value;
    getline(line_ss, key, '=');
    getline(line_ss, value);
    cout << key << ": " << value << endl;
}
```



StringStream is incredibly versatile for parsing, formatting, and data conversion tasks in C++!
