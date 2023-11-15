Title : Student Management System
Team Members (SRN Name): Princia D’souza (PES2UG22CS416) 
                         Raahithya Jayaram (PES2UG22CS421)
                         Raashi Bafna (PES2UG22CS422)
                         Rachana R Aithal (PES2UG22CS424)




SYNOPSIS:

In this project we are creating a Student Management System. It allows users to perform various operations on a list of student records, such as adding students, displaying their information, searching for students, modifying student records, deleting students, and performing statistics and sorting operations. 

1) Header Files: The code includes standard C libraries :stdio.h, stdlib.h, string.h, math.h .


2) Constants:
USERNAME: Defines the expected username for authentication.
MAX_PASSWORD_LENGTH: Maximum length of the password.

3) Structure Definition:
RollNumber: Student's roll number
name: Student's name (up to 50 characters).
marks: Student's marks.
mb_no: Student's mobile number.
next: Pointer to a structure of the same type i.e.,linking it to other students.

4) Function Definitions:
createStudent: Creates a new student node with roll number, name, mobile number, and marks.
addStudent: Adds a new student to the linked list, checking for valid input and duplicate roll numbers.
read_file: Reads student records from a CSV file and adds them to the linked list.
displayStudents: Displays all student records in the linked list.
modifyStudent: Modifies a student's details, including name, mobile number, and marks.
deleteStudent: Deletes a student by roll number.
calculateStatistics: Calculates and displays various statistics, including average, highest, and lowest marks, median, standard deviation, grade ranges, mode, variance, and interquartile range.
searchStudent: Searches for a student by roll number and displays their details.
searchStudentByMobile: Searches for a student by mobile number and displays their details.
searchStudentByName: Searches for a student by name and displays their details.
compareStudents and sortStudents: Sorts students by roll number in ascending order.
compareStudentsByName and sortStudentsByName: Sorts students by name in ascending order.
compareStudentsByMarks and sortStudentsByMarks: Sorts students by marks in ascending order.
reverseStudents: Reverses the order of students in the linked list.
copyStudents: Creates a copy of the linked list.
filterTopStudents: Filters and displays the top 'n' students by marks.
filterBottomStudents: Filters and displays the bottom 'n' students by marks.
savePassword : Save the system password to a text file.
loadPassword: Load the system password from a text file.
login : Functions for verifying username and password to enter the student management system.
modifyPassword: Allows the user to modify the password.
verifyPassword: Functions for verifying current password.
downloadToFile: Downloads student records to a CSV file based on user choice.
freeStudents: Frees the memory allocated for the linked list.

Main Function:
Begins with user login using a predefined username and a password.
Initializes an empty student records linked list.
Provides a menu to perform various operations, such as adding, displaying, searching, modifying, deleting students, calculating statistics, sorting students, reading and writing to files and changing the system password.
The program runs in an infinite loop, allowing the user to choose from the menu until they choose to exit.

5)  Files used
classA.csv
classB.csv
password.txt


ADT Definitions of Data Structures used:

Singly Linked List:

A singly linked list is a linear data structure that consists of a sequence of nodes. It is an ordered collection of elements where each element is composed of two parts: data and a pointer to the next node.. The ADT for a singly linked list can be defined as follows:

Characteristics:

Node Structure:
Elements are represented as nodes.
Each node has data and a link to the next node.
Head:
Access starts from a head pointer, which points to the first node.
Head is NULL for an empty list.
Dynamic Size:
Grows or shrinks dynamically.
Memory Efficiency:
Memory-efficient due to non-contiguous storage.
Access Time:
Access time is less efficient compared to arrays.
No Fixed Size:
Size can change during runtime.
Implementation Complexity:
Simpler implementation than doubly linked lists.
Reversal:
Reversing involves changing pointer directions.

Operations (a few examples) :

Create(): Creates an empty singly linked list.
Insert(data, position): Inserts a new element with the given data at the specified position in the list.
Delete(position): Removes the element at the specified position from the list.
GetElement(position):  Retrieves the data of the element at the specified position.
Search(data): Searches for an element with the given data and returns its position.
IsEmpty(): Checks if the list is empty.
Size(): Returns the number of elements in the list.
Traverse():  Visits each element of the list in order.
Delete(): Deallocates memory and destroys the list.


Array:

An array is a static, contiguous data structure that holds a fixed number of elements of the same data type.It is a finite, ordered collection of elements of the same data type and each element can be accessed by an index .

Characteristics:

Ordered Collection:
Elements are stored in a sequential order.
Fixed Size:
Has a predetermined size set during initialization.
Direct Access:
Elements are accessed directly using an index.
Homogeneous Data:
Contains elements of the same data type.
Contiguous Memory:
Occupies a contiguous block of memory.
Random Access Time:
Provides constant time access to any element.
Static Structure:
Size and structure remain static during execution.
Efficient for Retrieval:
Efficient for retrieving elements by index.
Memory Efficiency:
Can be memory-efficient for certain operations.
Declaration:
Declared with a specific data type and size.
Compile-Time Allocation:
Memory is allocated during compile time.
Sequential Storage:
Data elements are stored sequentially in memory.

Operations ( a few examples) :
Create(size): Creates an array of a specified size.
Access(index): Retrieves the element at the specified index.
Modify(index, value): Changes the value of the element at the specified index.
Length(): Returns the number of elements in the aray.
Resize(newSize): Changes the size of the array to the specified size. This may involve copying the existing elements to a new array.
Search(value): Searches for an element with the given value and returns its index.
IsEmpty(): Checks if the array is empty (has no elements).
IsFull(): Checks if the array is full (no more elements can be added).



