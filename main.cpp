#include <iostream>
#include <fstream>
#include <cctype>
#include <string>

using namespace std;

// Define the Contact structure
struct Contact {
    string name;
    string email;
    string address;
    string number;
    Contact* next;
};

class AddressBook {
public:
    Contact* head = NULL;

    // Helper function to validate name
    bool isValidName(const string& name) {
        for (char c : name) {
            if (!(isalpha(c) || c == ' ')) {
                return false;
            }
        }
        return !name.empty();
    }

    // Helper function to validate number
    bool isValidNumber(const string& number) {
        for (char c : number) {
            if (!isdigit(c)) {
                return false;
            }
        }
        return !number.empty();
    }

    // Helper function to validate email
    bool isValidEmail(const string& email) {
        return email.find('@') != string::npos && email.find('.') != string::npos;
    }

    // Function to bubble sort the contacts list by name
    void bubbleSort() {
        if (!head || !head->next) return;

        bool swapped;
        do {
            swapped = false;
            Contact* current = head;
            while (current && current->next) {
                if (current->name > current->next->name) {
                    swap(current->name, current->next->name);
                    swap(current->email, current->next->email);
                    swap(current->address, current->next->address);
                    swap(current->number, current->next->number);
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
    }

    // Add a new contact
    void Add(Contact* c) {
        Contact* temp = new Contact;
        temp->name = c->name;
        temp->email = c->email;
        temp->address = c->address;
        temp->number = c->number;
        temp->next = NULL;

        if (head == NULL) {
            head = temp;
        } else {
            Contact* current = head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = temp;
        }

        // Save the contact to file
        ofstream file("contacts.txt", ios::app);
        if (file.is_open()) {
            file << temp->name << endl;
            file << temp->number << endl;
            file << temp->email << endl;
            file << temp->address << endl;
            file << "-----------------------------------\n";
            file.close();
        }

        bubbleSort();  // Sort contacts after addition
    }

    // Display all contacts
    void Display() {
        if (head == NULL) {
            cout << "No Contacts Available.\n";
            return;
        }

        Contact* current = head;
        while (current != NULL) {
            cout << "Name: " << current->name << endl;
            cout << "Number: " << current->number << endl;
            if (!current->email.empty()) 
                cout << "Email: " << current->email << endl;
            if (!current->address.empty()) 
                cout << "Address: " << current->address << endl;
            cout << "-----------------------------------\n";
            current = current->next;
        }
    }

    // Search for a contact
    void Search(const string& name) {
        Contact* current = head;
        while (current != NULL) {
            if (current->name == name) {
                cout << "Contact Found:\n";
                cout << "Name: " << current->name << endl;
                cout << "Number: " << current->number << endl;
                if (!current->email.empty())
                    cout << "Email: " << current->email << endl;
                if (!current->address.empty())
                    cout << "Address: " << current->address << endl;
                return;
            }
            current = current->next;
        }
        cout << "Contact not found.\n";
    }

    // Delete a contact
    void Delete(const string& name) {
        if (head == NULL) {
            cout << "No Contacts Available.\n";
            return;
        }

        Contact* current = head;
        Contact* prev = NULL;

        while (current != NULL) {
            if (current->name == name) {
                if (prev == NULL) { // Deleting the head
                    head = current->next;
                } else { // Deleting a middle or last node
                    prev->next = current->next;
                }
                delete current;
                cout << "Contact deleted successfully.\n";
                bubbleSort();  // Sort contacts after deletion
                return;
            }
            prev = current;
            current = current->next;
        }

        cout << "Contact not found.\n";
    }

    // Update a contact
    void Update(const string& name) {
        Contact* current = head;

        while (current != NULL) {
            if (current->name == name) {
                cout << "Contact Found! Here are the current details:\n";
                cout << "Name: " << current->name << endl;
                cout << "Number: " << current->number << endl;
                if (!current->email.empty())
                    cout << "Email: " << current->email << endl;
                if (!current->address.empty())
                    cout << "Address: " << current->address << endl;

                // Update the name
                cout << "Enter new Name (leave blank to keep current): ";
                cin.ignore();
                string newName;
                getline(cin, newName);
                if (!newName.empty() && isValidName(newName)) {
                    current->name = newName;
                }

                // Update the number
                cout << "Enter new Number (leave blank to keep current): ";
                string number;
                getline(cin, number);
                if (!number.empty() && isValidNumber(number)) {
                    current->number = number;
                }

                // Update the email
                cout << "Enter new Email (leave blank to keep current): ";
                string email;
                getline(cin, email);
                if (!email.empty() && isValidEmail(email)) {
                    current->email = email;
                }

                // Update the address
                cout << "Enter new Address (leave blank to keep current): ";
                string address;
                getline(cin, address);
                if (!address.empty()) {
                    current->address = address;
                }

                cout << "Contact updated successfully.\n";
                bubbleSort();  // Sort contacts after update
                return;
            }
            current = current->next;
        }

        cout << "Contact not found.\n";
    }

    // Load contacts from file when the program starts
    void LoadContacts() {
        ifstream file("contacts.txt");
        if (!file) {
            cout << "No contacts file found.\n";
            return;
        }

        Contact* current = NULL;
        while (!file.eof()) {
            Contact* temp = new Contact;
            getline(file, temp->name);
            getline(file, temp->number);
            getline(file, temp->email);
            getline(file, temp->address);
            file.ignore();  // Skip separator line

            temp->next = NULL;
            if (head == NULL) {
                head = temp;
                current = head;
            } else {
                current->next = temp;
                current = temp;
            }
        }
        file.close();
        bubbleSort();  // Sort contacts after loading from file
    }
};

int main() {
    AddressBook AB;
    AB.LoadContacts();  // Load contacts from file at the start
    int Choice;

    do {
        cout << "\n\n";
        cout << "\tDIGITAL PHONE BOOK DIRECTORY\n";
        cout << "\t1) Add a New Contact.\n";
        cout << "\t2) Display all Contacts.\n";
        cout << "\t3) Search Contact.\n";
        cout << "\t4) Update Contact.\n";
        cout << "\t5) Delete Contact.\n";
        cout << "\t6) Exit.\n";
        cout << "\tEnter Choice: ";
        cin >> Choice;

        switch (Choice) {
        case 1: {
            Contact c1;

            cout << "\tEnter Name: ";
            cin.ignore();
            do {
                getline(cin, c1.name);
                if (!AB.isValidName(c1.name)) {
                    cout << "Invalid name. Please enter a valid name: ";
                }
            } while (!AB.isValidName(c1.name));

            cout << "\tEnter Number: ";
            do {
                getline(cin, c1.number);
                if (!AB.isValidNumber(c1.number)) {
                    cout << "Invalid number. Please enter a valid number: ";
                }
            } while (!AB.isValidNumber(c1.number));

            cout << "\tDo you want to enter Email? (yes/no): ";
            string choice;
            cin >> choice;
            if (choice == "yes") {
                cout << "\tEnter Email: ";
                cin.ignore();
                do {
                    getline(cin, c1.email);
                    if (!AB.isValidEmail(c1.email)) {
                        cout << "Invalid email. Please enter a valid email: ";
                    }
                } while (!AB.isValidEmail(c1.email));
            } else {
                c1.email = "";
            }

            cout << "\tDo you want to enter Address? (yes/no): ";
            cin >> choice;
            if (choice == "yes") {
                cout << "\tEnter Address: ";
                cin.ignore();
                getline(cin, c1.address);
            } else {
                c1.address = "";
            }

            AB.Add(&c1);
            cout << "\tContact Added.\n";
            break;
        }
        case 2:
            AB.Display();
            break;
        case 3: {
            string name;
            cout << "\tEnter the name of the Contact to Search: ";
            cin.ignore();
            getline(cin, name);
            AB.Search(name);
            break;
        }
        case 4: {
            string name;
            cout << "\tEnter the name of the Contact to Update: ";
            cin.ignore();
            getline(cin, name);
            AB.Update(name);
            break;
        }
        case 5: {
            string name;
            cout << "\tEnter the name of the Contact to Delete: ";
            cin.ignore();
            getline(cin, name);
            AB.Delete(name);
            break;
        }
        case 6:
            cout << "Exiting program. Goodbye!\n";
            return 0;
        default:
            cout << "\tInvalid Choice Entered.\n";
        }
    } while (true);

    return 0;
}
