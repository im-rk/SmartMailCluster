#include "Graph.h"
#include "Cluster.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
    int numUsers;
    cout << "Enter number of users: ";
    cin >> numUsers;

    Graph g(numUsers);
    Cluster cluster;

    // Step 1: Register users
    cout << "\nRegister Users (ID -> Email Address)\n";
    for (int i = 1; i <= numUsers; i++) {
        string email;
        cout << "Enter email for user " << i << ": ";
        cin >> email;
        g.addUserAddress(i, email);
    }

    int choice;
    do {
        cout << "\n--- Email System Menu ---\n";
        cout << "1. Send Email\n";
        cout << "2. Reply Email\n";
        cout << "3. Forward Email\n";
        cout << "4. View Thread\n";
        cout << "5. Cluster Emails\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int from, to;
            string subject, body;
            cout << "From (User ID): "; cin >> from;
            cout << "To (User ID): "; cin >> to;
            cin.ignore();
            cout << "Subject: "; getline(cin, subject);
            cout << "Body: "; getline(cin, body);
            g.sendEmail(from, to, subject, body);

        } else if (choice == 2) {
            int email_id, from, to;
            string body;
            cout << "Reply to Email ID: "; cin >> email_id;
            cout << "From (User ID): "; cin >> from;
            cout << "To (User ID): "; cin >> to;
            cin.ignore();
            cout << "Reply Body: "; getline(cin, body);
            g.replyEmail(email_id, from, to, body);

        } else if (choice == 3) {
            int email_id, from, to;
            string body;
            cout << "Forward Email ID: "; cin >> email_id;
            cout << "From (User ID): "; cin >> from;
            cout << "To (User ID): "; cin >> to;
            cin.ignore();
            cout << "Forward Body (optional): "; getline(cin, body);
            g.forwardEmail(email_id, from, to, body);

        } else if (choice == 4) {
            int email_id;
            cout << "Enter Root Email ID: ";
            cin >> email_id;
            g.viewThread(email_id);

        } else if (choice == 5) {
            cluster.clusterEmails(g);

        } else if (choice == 6) {
            cout << "Exiting...\n";

        } else {
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 6);

    return 0;
}
