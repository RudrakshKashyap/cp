https://stackoverflow.com/questions/8786183/how-to-append-content-to-stringstream-type-object

//istringstream iss(str) //can only read data from it, cant do iss << "something"
//iss >> s1 >> i >> s2 >> d; // Extracting data 


stringstream ss("abcdef");
if we do ss << "xxx" after initializing ss, then it will overwrite the initialization
print(ss.str()) will give "xxxdef"

	
	
string s;
cin >> s;
stringstream t(s);
//cout << t.str();

while(getline(t, s))
{
    cout << s << endl;
}

stringstream ss("4jkla");
char firstChar = ss.get(); // Get first character
cout << firstChar;         // Output: '4'

stringstream ss("4jkla");
char firstChar = ss.peek(); // Look at first character without removing it
cout << firstChar;          // Output: '4'

getline takes input "till" new line, -- not including new line
if it's written "untill" instead of "till" i.e. -- including new line
