#include "../backend/include/Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    int numUsers;
    cout << "Enter number of users in the system: ";
    cin >> numUsers;

    Graph mailSystem(numUsers);

    //==================Load email id's for every user=======
    
    // ================= Load dataset =================
    ifstream file("email_datasets_10.csv");  // <-- dataset file
    if (!file.is_open()) {
        cout << "Error: Could not open dataset file!" << endl;
        return 1;
    }

    string line;
    getline(file, line); // skip header
    


    while (getline(file, line)) {
        
        stringstream ss(line);
        string from_str, to_str, subject, body, type, parent_id_str;

        getline(ss, from_str, ',');
        getline(ss, to_str, ',');
        getline(ss, subject, ',');
        getline(ss, body, ',');
        getline(ss, type, ',');
        getline(ss, parent_id_str, ',');

        int from = stoi(from_str);
        int to = stoi(to_str);
        int parent_id;
        if (parent_id_str == "-" || parent_id_str.empty()) {
            parent_id = -1;  // means no parent (original mail)
        } else {
            parent_id = stoi(parent_id_str);  // convert to integer normally
        }
        
        if (type == "original") {
            mailSystem.sendEmail(from, to, subject, body);

        } else if (type == "reply") {
            mailSystem.replyEmail(parent_id, from, to, body);

        } else if (type == "forward") {
            mailSystem.forwardEmail(parent_id, from, to, body);
        }
    }

    file.close();
    cout << "\n All dataset emails loaded successfully!\n";

    // ================== Menu ==================
    int choice;
    do {
        cout << "\n========= Smart Mail Cluster =========\n";
        cout << "1. View a Thread\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int email_id;
            cout << "Enter email ID to view its thread: ";
            cin >> email_id;
            mailSystem.viewThread(email_id);

        } else if (choice == 2) {
            cout << "Exiting... Goodbye!\n";
        } else {
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 2);

    return 0;
}
