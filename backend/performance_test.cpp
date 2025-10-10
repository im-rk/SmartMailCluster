#include "Graph.h"
#include "Cluster.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace std::chrono;

// helper to measure elapsed time
template <typename Func>
double measureExecutionTime(Func f) {
    auto start = high_resolution_clock::now();
    f();
    auto end = high_resolution_clock::now();
    duration<double, milli> duration = end - start;
    return duration.count(); // milliseconds
}

// function to load dataset rows
struct EmailRecord {
    int from;
    int to;
    string from_email;
    string to_email;
    string subject;
    string body;
    string type;
    int parent_id;
};

vector<EmailRecord> loadDataset(const string &filename) {
    vector<EmailRecord> records;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open " << filename << endl;
        return records;
    }
    //cout<<records.size();
    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        EmailRecord rec;

        string from_str, to_str, parent_id_str;

        getline(ss, from_str, ',');
        getline(ss, to_str, ',');
        getline(ss, rec.from_email, ',');
        getline(ss, rec.to_email, ',');
        getline(ss, rec.subject, ',');
        getline(ss, rec.body, ',');
        getline(ss, rec.type, ',');
        getline(ss, parent_id_str, ',');

        rec.from = stoi(from_str);
        rec.to = stoi(to_str);
        rec.parent_id = (parent_id_str != "-" && !parent_id_str.empty()) ? stoi(parent_id_str) : -1;

        if (rec.from == 0 || rec.to == 0) continue;


        records.push_back(rec);
        //cout<<records.size();
    }

    file.close();
    return records;
}

int main() {
    vector<string> datasets = {
        "email_dataset_40k.csv",
        //"email_dataset_5k.csv",
        //"email_dataset_10k.csv",
        //"email_dataset_50k.csv",
        //"email_dataset_100k.csv"
    };

    ofstream out("results.csv");
    out << "Dataset,NumRecords,Send(ms),Reply(ms),Forward(ms),ViewThread(ms),Cluster(ms)\n";

    for (const string &file : datasets) {
        cout << "\n Processing " << file << " ...\n";

        vector<EmailRecord> data = loadDataset(file);

        if (data.empty()) {
            cout << "Skipping empty or invalid dataset.\n";
            continue;
        }

        int numUsers = 50000;
        Graph g(numUsers);
        Cluster cluster;
        // measure Send Email
        for (auto &rec : data) {
                g.addUserAddress(rec.from, rec.from_email);
                g.addUserAddress(rec.to, rec.to_email);
                
        }
        double sendTime = measureExecutionTime([&]() {
            //cout<<"s";
            for (auto &rec : data) {
                //g.addUserAddress(rec.from, rec.from_email);
                //g.addUserAddress(rec.to, rec.to_email);
                //cout<<"hek";
                if (rec.type == "original")
                    g.sendEmail(rec.from, rec.to, rec.subject, rec.body);
            }
        });

        // measure Reply Email
        double replyTime = measureExecutionTime([&]() {
            for (auto &rec : data) {
                if (rec.type == "reply")
                    g.replyEmail(rec.parent_id, rec.from, rec.to, rec.body);
            }
        });

        // measure Forward Email
        double forwardTime = measureExecutionTime([&]() {
            for (auto &rec : data) {
                if (rec.type == "forward")
                    g.forwardEmail(rec.parent_id, rec.from, rec.to, rec.body);
            }
        });

        // measure View Thread (for 5 sample threads)
        double viewThreadTime = measureExecutionTime([&]() {
            for (int i = 5; i < 10 && i < (int)data.size(); i++)
                g.viewThread(i);
        });

        // measure Clustering
        double clusterTime = measureExecutionTime([&]() {
            cluster.clusterEmails(g);
        });

        cout << fixed << setprecision(3);
        cout << "Results for " << file << ":\n";
        cout << "Send: " << sendTime << " ms | "
             << "Reply: " << replyTime << " ms | "
             << "Forward: " << forwardTime << " ms | "
             << "ViewThread: " << viewThreadTime << " ms | "
             << "Cluster: " << clusterTime << " ms\n";

        out << file << "," << data.size() << ","
            << sendTime << "," << replyTime << "," << forwardTime << ","
            << viewThreadTime << "," << clusterTime << "\n";
    }

    out.close();
    cout << "\nPerformance results saved to results.csv\n";
    return 0;
}
