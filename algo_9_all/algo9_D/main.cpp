#include <iostream>
#include <vector>

using namespace std;

class queue {
public:
    queue() {
        head = nullptr;
        tail = nullptr;
    }
    class Node {
    public:
        int number;
        Node* next;
    };
    Node* tail;
    Node* head;
    void add(int number) {
        Node* adding = new Node;
        adding->number = number;
        adding->next = nullptr;
        if (head == nullptr) {
            head = adding;
            tail = adding;
        } else {
            tail->next = adding;
            tail = adding;
        }
    }
    void take() {
        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
        } else {
            Node *remember = head;
            head = head->next;
            delete remember;
        }
    }
};

class way_and_visit {
public:
    way_and_visit() {
        way = 0;
        visit = false;
    }
    int way;
    bool visit;
};

int main() {
    int places;
    int bridge;
    cin >> places;
    cin >> bridge;
    vector<vector<int>> list(places);

    for (int i = 0; i < bridge; i++) {
        int first;
        int second;
        cin >> first;
        cin >> second;
        list[first - 1].emplace_back(second - 1);
        list[second - 1].emplace_back(first - 1);
    }

    int shlepa;
    int hotel;
    cin >> shlepa;
    cin >> hotel;

    vector<way_and_visit> info(places);
    queue remember_queue;
    remember_queue.add(shlepa - 1);
    info[shlepa - 1].visit = true;

    while (remember_queue.head != nullptr) {
        int number = remember_queue.head->number;
        remember_queue.take();
        for (int i = 0; i < list[number].size(); i++) {
            if (!info[list[number][i]].visit) {
                info[list[number][i]].visit = true;
                info[list[number][i]].way = info[number].way + 1;
                remember_queue.add(list[number][i]);
            }
        }
    }

    if (info[hotel - 1].way == 0 and hotel != shlepa) {
        cout << -1;
    } else {
        cout << info[hotel - 1].way;
    }

    return 0;
}