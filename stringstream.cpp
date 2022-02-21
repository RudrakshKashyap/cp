https://stackoverflow.com/questions/8786183/how-to-append-content-to-stringstream-type-object

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
