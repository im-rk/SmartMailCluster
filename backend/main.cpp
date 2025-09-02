#include "Graph.h"
#include "Cluster.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

int main() {
    int numUsers;
    cout << "Enter number of users in the dataset: ";
    cin >> numUsers;

    Graph g(numUsers);
    Cluster cluster;

    // ================= Load dataset =================
    ifstream file("email_dataset_20.csv");  
    if (!file.is_open()) {
        cout << "Error: Could not open dataset file!" << endl;
        return 1;
    }

    string line;
    getline(file, line); // skip header line

    while (getline(file, line)) {
        stringstream ss(line);

        string from_str, to_str, from_email, to_email;
        string subject, body, type, parent_id_str;

        // Read each field according to dataset columns
        getline(ss, from_str, ',');       // from
        getline(ss, to_str, ',');         // to
        getline(ss, from_email, ',');     // from_email
        getline(ss, to_email, ',');       // to_email
        getline(ss, subject, ',');        // subject
        getline(ss, body, ',');           // body
        getline(ss, type, ',');           // type
        getline(ss, parent_id_str, ',');  // parent_email_id

        if (from_str.empty() || to_str.empty()) {
            cout << "⚠️ Skipping invalid row: " << line << endl;
            continue;
        }

        int from = stoi(from_str);
        int to = stoi(to_str);

        int parent_id = -1;
        if (!parent_id_str.empty() && parent_id_str != "-") {
            parent_id = stoi(parent_id_str);
        }

        // Call graph methods
        if (type == "original") {
            g.sendEmail(from, to, subject, body);
        } 
        else if (type == "reply") {
            g.replyEmail(parent_id, from, to, body);
        } 
        else if (type == "forward") {
            g.forwardEmail(parent_id, from, to, body);
        }
    }

    file.close();
    cout << "\n✅ Dataset loaded successfully!\n";

    // ================== Menu ==================
    int choice;
    do {
        cout << "\n========= Dataset Email System =========\n";
        cout << "1. View a Thread\n";
        cout << "2. Cluster Emails\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int email_id;
            cout << "Enter email ID to view its thread: ";
            cin >> email_id;
            g.viewThread(email_id);

        } else if (choice == 2) {
            cluster.clusterEmails(g);

        } else if (choice == 3) {
            cout << "Exiting...\n";
        } else {
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 3);

    return 0;
}
