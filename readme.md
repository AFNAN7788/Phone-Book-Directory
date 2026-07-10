Phone Book Directory (C++ Console Application)

Project Description

This project implements a simple console-based Phone Book Directory application using C++. It allows users to manage contacts by adding, displaying, searching, updating, and deleting entries. The application utilizes a linked list data structure to store contact information and persists data to a contacts.txt file, ensuring that contact details are saved between sessions. Contacts are automatically sorted alphabetically by name using a bubble sort algorithm after any modification (add, delete, update).

Features


1. Add New Contact: Users can add new contacts with name, phone number, email (optional), and address (optional). Input validation is performed for name, number, and email.


2. Display All Contacts: View a list of all stored contacts, sorted alphabetically by name.


3. Search Contact: Find a specific contact by name and display their details.


4. Update Contact: Modify existing contact details (name, number, email, address) by searching for the contact's name.


5. Delete Contact: Remove a contact from the directory by name.


6. Data Persistence: Contacts are automatically saved to and loaded from contacts.txt.


7. Input Validation: Ensures valid names, phone numbers (digits only), and email formats.


8. Sorted Display: Contacts are maintained and displayed in alphabetical order by name.

How to Compile and Run

This project is a C++ console application and can be compiled using a standard C++ compiler like g++.

Prerequisites

A C++ compiler (e.g., g++, MinGW, MSVC)

Compilation Steps

1. Save the source code in your desired project directory.


2. Open a terminal or command prompt.


3. Navigate to the project directory where your main.cpp file is located.


4. Compile the code using your C++ compiler. For g++, use the following command:

g++ main.cpp -o phonebook

Running the Application

After successful compilation, you can run the application from the terminal:

On Linux/macOS:

./phonebook

On Windows:

.\phonebook.exe


The application will then present a menu-driven interface in the console.


        DIGITAL PHONE BOOK DIRECTORY
        1) Add a New Contact.
        2) Display all Contacts.
        3) Search Contact.
        4) Update Contact.
        5) Delete Contact.
        6) Exit.
        Enter Choice: 






License

This project is open-source and available under the MIT License.

