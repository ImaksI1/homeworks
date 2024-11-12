#include <iostream>
#include <string>

using namespace std;

struct PrintJob {
    int priority;
    string user;
    string document;

    PrintJob(int p, const string& u, const string& d)
        : priority(p), user(u), document(d) {}
};

class PrinterQueue {
private:
    PrintJob* printQueue[100];
    int jobCount = 0;

public:
    void addJob(int priority, const string& user, const string& document) {
        PrintJob* newJob = new PrintJob(priority, user, document);

        int i;
        for (i = jobCount - 1; i >= 0 && printQueue[i]->priority < priority; --i) {
            printQueue[i + 1] = printQueue[i];
        }
        printQueue[i + 1] = newJob;
        jobCount++;

        cout << "Job added: " << document << " from " << user << " with priority " << priority << "\n";
    }

    void processJob() {
        if (jobCount == 0) {
            cout << "Queue is empty.\n";
            return;
        }

        PrintJob* job = printQueue[0];
        cout << "Printing document: " << job->document << " from " << job->user << " (priority: " << job->priority << ")\n";

        for (int i = 0; i < jobCount - 1; ++i) {
            printQueue[i] = printQueue[i + 1];
        }
        jobCount--;

        delete job;
    }

    void showQueue() {
        if (jobCount == 0) {
            cout << "Queue is empty.\n";
            return;
        }

        cout << "Print queue:\n";
        for (int i = 0; i < jobCount; ++i) {
            cout << "Document: " << printQueue[i]->document
                << ", User: " << printQueue[i]->user
                << ", Priority: " << printQueue[i]->priority << "\n";
        }
    }
};

int main() {
    PrinterQueue printerQueue;

    printerQueue.addJob(3, "User1", "Document1");
    printerQueue.addJob(5, "User2", "Document2");
    printerQueue.addJob(1, "User3", "Document3");
    printerQueue.addJob(0, "User4", "Document4");
    printerQueue.addJob(2, "User5", "Document5");

    printerQueue.showQueue();

    printerQueue.processJob();
    printerQueue.processJob();

    printerQueue.showQueue();

    return 0;
}
