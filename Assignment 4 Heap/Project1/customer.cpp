#include "customer.h"
#include "heap.h"
#include <iostream>
using namespace std;
int comparisonWay = 0; // 0 for arrival time, 1 for processing time


bool Customer::operator>(const Customer& c) {
	return comparisonWay ? (processing_time < c.processing_time) : (arrival_time < c.arrival_time); // a customer is "greater" if his time is shorter
};


void customerQueueTest(int n_cust) {
	int current_time = 0;
	int totalWaitingTime = 0;
	int i;
	int WT = 0; // waiting time for each customer

	Heap<Customer> queue;

	Customer* custList = new Customer[n_cust];
	cout << endl << endl << "Setup" << endl;
	cout << "List of customers and their arrival and processing times" << endl;
	for (i = 0; i<n_cust; i++)
	{
		custList[i].setAT(i);
		custList[i].setPT((n_cust - i) % (n_cust / 2) + 1 + (i % 2)*(n_cust / 2));
		cout << "Customer " << i << " will arrive at time " << custList[i].AT() << " with PT=" << custList[i].PT() << endl;
	}
	cout << endl;


	for (int round = 0; round<2; round++) {
		cout << endl << endl;
		cout << "Test Round " << round + 1 << endl;
		cout << (round == 0 ? "First come first serve" : "Customer with the least PT served first") << endl;
		comparisonWay = (round == 0) ? 0 : 1; // 0 for arrival time, 1 for processing time
		current_time = 0;
		totalWaitingTime = 0;

		for (int i = 0; i < n_cust; i++) {
			queue.insert(custList[i]);
				cout << "Customer arrives at time " << custList[i].AT() << " with PT=" << custList[i].PT() << endl;
				if (current_time <= custList[i].AT()) {
					cout << "Customer arrives when no one is waiting" << endl;
					cout << "Customer is served at time " << current_time << " with AT=" << custList[i].AT() << " and PT=" << custList[i].PT() << " after waiting for 0 min." << endl;
					current_time += custList[i].PT();
					queue.extractMax();
				}
			
		}
		
		while (!queue.empty()) {
			Customer c = queue.extractMax();
			WT = current_time - c.AT();
					
			cout << "Customer is served at time " << current_time << " with AT=" << c.AT() << " and PT=" << c.PT() << " after waiting for "
					<< WT << " min." << endl;

			totalWaitingTime += WT;
			current_time += c.PT();
		}
		cout << "Total Waiting Time: " << totalWaitingTime << endl;
		cout << "Average Waiting Time: " << totalWaitingTime / (float)n_cust << endl;
	}
	delete[] custList;
}
