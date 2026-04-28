#include <iostream>
using namespace std;

//================ NODE =================
struct Node {
    int data;
    Node *link;
};

//================ LIST =================
struct List {
    Node *first;
    Node *last;
};

//================ KHOI TAO =================
void initList(List &l) {
    l.first = l.last = NULL;
}

//================ TAO NODE =================
Node* taoNode(int x) {
    Node *p = new Node;
    p->data = x;
    p->link = NULL;
    return p;
}

//================ THEM CUOI =================
void themCuoi(List &l, int x) {
    Node *p = taoNode(x);

    if (l.first == NULL) {
        l.first = l.last = p;
        p->link = p; // tao vong tron
    } else {
        p->link = l.first;
        l.last->link = p;
        l.last = p;
    }
}

//================ TAO VONG TRON N NGUOI =================
void taoDanhSach(List &l, int N) {
    for (int i = 1; i <= N; i++)
        themCuoi(l, i);
}

//================ JOSEPHUS =================
int josephus(int N, int M) {
    List l;
    initList(l);
    taoDanhSach(l, N);

    Node *p = l.first;
    Node *truoc = l.last;

    while (p->link != p) { // con hon 1 nguoi

        // di chuyen den nguoi thu M
        for (int i = 0; i < M; i++) {
            truoc = p;
            p = p->link;
        }

        cout << "Loai: " << p->data << endl;

        // xoa p
        truoc->link = p->link;

        if (p == l.first)
            l.first = p->link;

        if (p == l.last)
            l.last = truoc;

        Node *xoa = p;
        p = p->link;
        delete xoa;
    }

    int winner = p->data;
    delete p;
    return winner;
}

//================ MAIN =================
int main() {
    int N, M;

    cout << "Nhap N: ";
    cin >> N;

    cout << "Nhap M: ";
    cin >> M;

    int win = josephus(N, M);

    cout << "Nguoi chien thang: " << win << endl;

    return 0;
}