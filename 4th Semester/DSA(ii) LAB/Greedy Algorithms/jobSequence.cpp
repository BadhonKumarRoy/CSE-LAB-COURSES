// #This code greedily selects jobs with maximum profit and schedules them as late as possible to maximize total profit.
// #Idea

// You have jobs.
// Each job:

// --must be finished before its deadline
// --gives you some profit

// You can’t do all jobs, so you must choose wisely.

// #Goal

// Maximize total profit, not number of jobs.

// Strategy (Greedy Thinking)
// 1. Do the most profitable jobs first
// 2. Place them as late as possible

// #Why “late as possible”?

// Because:

// --Early slots are valuable
// --Saving them allows more jobs to fit later

// This is the trick that makes greedy work here.

// #Sort jobs by profit and assign each job to the latest available slot before its deadline to maximize total profit.

#include<iostream>
#include<algorithm>
using namespace std;

struct Job {
    int id;
    int deadline;
    int profit;
};

bool compare(Job a, Job b) {
    return a.profit > b.profit; // Sort in decreasing order of profit
}

void jobSequence(Job jobs[], int n) {
    sort(jobs, jobs + n, compare);
    int maxDeadline = 0;
    for(int i = 0; i < n; i++) {
        if (jobs[i].deadline > maxDeadline) {
            maxDeadline = jobs[i].deadline;
        }
    }
    int slot[100];
    for(int i = 0; i <= maxDeadline; i++) {
        slot[i] = -1; // Initialize all slots to be empty
    }
    int totalProfit = 0;
    for(int i = 0; i < n; i++) {
        for(int j = jobs[i].deadline; j > 0; j--) {
            if (slot[j] == -1) { // If the slot is empty
                slot[j] = jobs[i].id; // Assign the job to this slot
                totalProfit += jobs[i].profit; // Add profit
                break;
            }
        }
    }
    cout << "The selected jobs are: ";
    for(int i = 0; i <= maxDeadline; i++) {
        if (slot[i] != -1) {
            cout << slot[i] << " ";
        }
    }
    cout << "\nTotal profit is: " << totalProfit << endl;
}

int main() {
    int n;
    cout << "Enter the number of jobs: ";
    cin >> n;
    Job jobs[n];
    cout << "Enter the id, deadline and profit of each job:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> jobs[i].id >> jobs[i].deadline >> jobs[i].profit;
    }
    jobSequence(jobs, n);
    return 0;
}