#include <iostream>
#include <vector>

using namespace std;

struct Qnode {
    int value;
    Qnode* next;
    Qnode(int val) {
        value = val;
        next = nullptr;
    }
};

struct Queue {
    Qnode *head;
    Qnode *tail;

    Queue() { head = tail = nullptr; }

    void push(int x) {
        Qnode *tmp = new Qnode(x);
        if (tail == nullptr) {
            head = tail = tmp;
            return;
        }
        tail->next = tmp;
        tail = tmp;
    }
    void pop() {
        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
        } else {
            Qnode *tmp = head;
            head = head->next;
            delete tmp;
        }
    }
};

struct way_visited {
    int way;
    bool visited;
    way_visited() {
        way = 0;
        visited = false;
    }
};

int main() {
    Queue q;

    int places;
    int bridge;
    cin >> places >> bridge;
    vector<vector<int>> list(places);

    for (int i = 0; i < bridge; i++) {
        int source;
        int destination;
        cin >> source;
        cin >> destination;
        list[source - 1].emplace_back(destination - 1);
        list[destination - 1].emplace_back(source - 1);
    }

    int boy_shlepa;
    int hotel;
    cin >> boy_shlepa >> hotel;


    q.push(boy_shlepa - 1);
    vector<way_visited> info(places);
    info[boy_shlepa - 1].visited = true;

    while (q.head != nullptr) { // BFS
        int number = q.head->value;
        q.pop();
        for (int i = 0; i < list[number].size(); i++) {
            if (!info[list[number][i]].visited) {
                info[list[number][i]].visited = true;
                info[list[number][i]].way = info[number].way + 1;
                q.push(list[number][i]);
            }
        }
    }

    if (info[hotel - 1].way == 0 and hotel != boy_shlepa) {
        cout << -1;
    } else {
        cout << info[hotel - 1].way;
    }


    return 0;
}