# number of elements
n = int(input("Enter number of elements : "))

# Below line read inputs from user using map() function
a = list( map( int, input("\nEnter the numbers : ").strip().split()  ) ) [:n]   

lst1 = [int(item) for item in input("Enter the list items : ").split()]

for x, y in thisdict.items():
  print(x, y)
  
for num1, num2 in zip(sorted(n, reverse = True), sorted(n)):
        new_n += str(ord(num1) - ord(num2))


dir() is a powerful inbuilt function in Python3, which returns list of the attributes and methods of any object (say functions , modules, strings, lists, dictionaries etc.)
dir(object)
help(object)

global x
nonlocal x


// xrange, genreators



//////////////////////////////////////////////////////////

class Employee:

    num_of_emps = 0
    raise_amt = 1.04

    def __init__(self, first, last, pay):
        self.first = first
        self.last = last
        self.email = first + '.' + last + '@email.com'
        self.pay = pay

        Employee.num_of_emps += 1

    def fullname(self):
        return '{} {}'.format(self.first, self.last)

    def apply_raise(self):
        self.pay = int(self.pay * self.raise_amt)

    @classmethod
    def set_raise_amt(cls, amount):
        cls.raise_amt = amount

    @classmethod                                #method of class, takes cls as first argument
    def from_string(cls, emp_str):
        first, last, pay = emp_str.split('-')
        return cls(first, last, pay)

    @staticmethod                               #doesnt care about class
    def is_workday(day):
        if day.weekday() == 5 or day.weekday() == 6:
            return False
        return True
    
    
    def __repr__(self): #special method of representation, useful when we print(emp_1), otherwite it would print <__main__ Emloy object at 483902x832>
        return "Employee('{}', '{}', {})".format(self.first, self.last, self.pay)

    def __str__(self): #for ease of read for end user, same as repr
        return '{} - {}'.format(self.fullname(), self.email)

    def __add__(self, other):   #arthmetic special operators, there are many like this
        return self.pay + other.pay

    def __len__(self):
        return len(self.fullname())


emp_1 = Employee('Corey', 'Schafer', 50000)
emp_2 = Employee('Test', 'Employee', 60000)

Employee.set_raise_amt(1.05)

print(Employee.raise_amt)
print(emp_1.raise_amt)
print(emp_2.raise_amt)

emp_str_1 = 'John-Doe-70000'
emp_str_2 = 'Steve-Smith-30000'
emp_str_3 = 'Jane-Doe-90000'

first, last, pay = emp_str_1.split('-')

#new_emp_1 = Employee(first, last, pay)
new_emp_1 = Employee.from_string(emp_str_1)

print(new_emp_1.email)
print(new_emp_1.pay)

import datetime
my_date = datetime.date(2016, 7, 11)

print(Employee.is_workday(my_date))



class Developer(Employee):
    raise_amt = 1.10

    def __init__(self, first, last, pay, prog_lang):
        super().__init__(first, last, pay)
        self.prog_lang = prog_lang


class Manager(Employee):

    def __init__(self, first, last, pay, employees=None):
        super().__init__(first, last, pay)
        if employees is None:
            self.employees = []
        else:
            self.employees = employees

    def add_emp(self, emp):
        if emp not in self.employees:
            self.employees.append(emp)

    def remove_emp(self, emp):
        if emp in self.employees:
            self.employees.remove(emp)

    def print_emps(self):
        for emp in self.employees:
            print('-->', emp.fullname())


dev_1 = Developer('Corey', 'Schafer', 50000, 'Python')
dev_2 = Developer('Test', 'Employee', 60000, 'Java')

mgr_1 = Manager('Sue', 'Smith', 90000, [dev_1])

print(mgr_1.email)

mgr_1.add_emp(dev_2)
mgr_1.remove_emp(dev_2)

mgr_1.print_emps()




#property decorators, Getters, Setters, and Deleters
class Employee:

    def __init__(self, first, last):
        self.first = first
        self.last = last

    @property           #now you can call email by print(emp.email) like an attribute, otherwith you would write like this print(emp.email()), which could've be a problem if otherpeople already using the class, then they have to change thier code for printing
    def email(self):
        return '{}.{}@email.com'.format(self.first, self.last)

    @property
    def fullname(self):
        return '{} {}'.format(self.first, self.last)
    
    @fullname.setter        # so that you can write like  emp.fullname = 'blah blah' , notice you are not passing, you are setting
    def fullname(self, name):
        first, last = name.split(' ')
        self.first = first
        self.last = last
        
        
    @fullname.deleter
    def fullname(self):
        print('Delete Name!')
        self.first = None
        self.last = None


emp_1 = Employee('John', 'Smith')
emp_1.fullname = "Corey Schafer"

print(emp_1.first)
print(emp_1.email)
print(emp_1.fullname)

del emp_1.fullname



///////////////////////////////////////////////////////////////////////////////////////////////////////////
shallow copy # only copy 1 level deep

        l1                  l2
        0 --->['a', 'b']<--- 0
        0 --->['a', 'b']<--- 0
        0 --->['a', 'b']<--- 0
        0 --->['a', 'b']<--- 0
        0 --->['a', 'b']<--- 0

after performin l2[1] = ['c', 'd']
        
        l1                  l2
        0 --->['a', 'b']<--- 0
        0 --->['a', 'b']     0 --->['c', 'd']
        0 --->['a', 'b']<--- 0
        0 --->['a', 'b']<--- 0
        0 --->['a', 'b']<--- 0
        
 but if we perform l2[1][1] (accesing 2 level deep) then it will follow the pointer and change both list
        l1                  l2
        0 --->['a', 'b']<--- 0
        0 --->['a', 'c']<--- 0
        0 --->['a', 'b']<--- 0
        0 --->['a', 'b']<--- 0
        0 --->['a', 'b']<--- 0
        
# importing copy module
import copy
  
# initializing list 1 
li1 = [1, 2, [3,5], 4]
  
  
# using copy for shallow copy  
li2 = copy.copy(li1)         li2 = li1.copy()       lst2 = lst1[:]
  
# using deepcopy for deepcopy  
li3 = copy.deepcopy(li1) 
