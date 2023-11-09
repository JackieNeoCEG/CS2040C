#pragma once
#include <iostream>
#include <fstream>
#include <string>
// You can include/import any library/packages
#include <vector>
#include <set>
using namespace std;


void dfs(int student, const vector<set<int>>& friends, vector<bool>& visited, set<int>& attendees) {
    visited[student] = true;
    attendees.insert(student);

    int connectedFriends = 0;
    for (int friendOfStudent : friends[student]) {
        if (!visited[friendOfStudent]) {
            connectedFriends++;
            dfs(friendOfStudent, friends, visited, attendees);
        }
    }

    if (connectedFriends * 2 <= friends[student].size()) {
        attendees.erase(student);
    }
}


void partyGoing(string filename) {
    // Use these cout statments to make sure that your output is the same as our checker.

    cout << "For the file input of \"" << filename << "\"." << endl;
    int A, B, C, D;

    ifstream f(filename);
    if (!f.is_open())
    {
        cout << "File not found!" << endl;
        return;
    }

    f >> A >> B >> C >> D;
    vector<set<int>> friends(A + 1);
    int a, b;
    for (int i = 0; i < B; i++) {
        // reading in the friendship
      
        f >> a >> b;
        friends[a].insert(b);
        friends[b].insert(a);
        cout << "Student " << a << " is a friend of Student " << b << endl; // delete this line for submission
    }
    set<int> attendees;
    vector<bool> visited(A + 1, false);
    dfs(D, friends, visited, attendees);


    if (attendees.find(C) != attendees.end())  // modify this condition
        cout << C << " will go for the party" << endl;
    else 
        cout << C << " will not go for the party" << endl;

    cout << "Classmate(s) who will go to the party is/are:" << endl;
    for (int student : attendees) {
        cout << student << " ";
    }
    cout << endl;

}