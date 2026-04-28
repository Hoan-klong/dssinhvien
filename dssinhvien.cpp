#include <iostream>
#include <cstring>
using namespace std;

//================= KHAI BAO STRUCT =================
struct Ngay {
    int ngay, thang, nam;
};

struct SinhVien {
    char maSV[8];
    char hoTen[50];
    int gioiTinh;
    Ngay ngaySinh;
    char diaChi[100];
    char lop[12];
    char khoa[7];
};

struct Node {
    SinhVien data;
    Node *link;
};

struct List {
    Node *first;
    Node *last;
};

//================= KHOI TAO DS =================
void initList(List &l) {
    l.first = l.last = NULL;
}

//================= TAO NODE =================
Node* taoNode(SinhVien x) {
    Node *p = new Node;
    p->data = x;
    p->link = NULL;
    return p;
}

//================= THEM CUOI =================
void themCuoi(List &l, SinhVien x) {
    Node *p = taoNode(x);

    if (l.first == NULL) {
        l.first = l.last = p;
    } else {
        l.last->link = p;
        l.last = p;
    }
}

//================= NHAP 1 SV =================
void nhap1SV(SinhVien &sv) {
    cin.ignore();

    cout << "Ma SV: ";
    cin.getline(sv.maSV, 8);

    cout << "Ho ten: ";
    cin.getline(sv.hoTen, 50);

    cout << "Gioi tinh (1-Nam,0-Nu): ";
    cin >> sv.gioiTinh;

    cout << "Ngay sinh (dd mm yyyy): ";
    cin >> sv.ngaySinh.ngay >> sv.ngaySinh.thang >> sv.ngaySinh.nam;

    cin.ignore();

    cout << "Dia chi: ";
    cin.getline(sv.diaChi, 100);

    cout << "Lop: ";
    cin.getline(sv.lop, 12);

    cout << "Khoa: ";
    cin.getline(sv.khoa, 7);
}

//================= NHAP DANH SACH =================
void nhapDS(List &l, int n) {
    SinhVien sv;
    for (int i = 0; i < n; i++) {
        cout << "\nNhap sinh vien thu " << i + 1 << ":\n";
        nhap1SV(sv);
        themCuoi(l, sv);
    }
}

//================= XUAT 1 SV =================
void xuat1SV(SinhVien sv) {
    cout << sv.maSV << " | "
         << sv.hoTen << " | "
         << (sv.gioiTinh ? "Nam" : "Nu") << " | "
         << sv.ngaySinh.ngay << "/"
         << sv.ngaySinh.thang << "/"
         << sv.ngaySinh.nam << " | "
         << sv.diaChi << " | "
         << sv.lop << " | "
         << sv.khoa << endl;
}

//================= XUAT DS =================
void xuatDS(List l) {
    Node *p = l.first;
    while (p != NULL) {
        xuat1SV(p->data);
        p = p->link;
    }
}

//================= SAP XEP MSSV =================
void sapXepMaSV(List &l) {
    for (Node *p = l.first; p != NULL; p = p->link) {
        for (Node *q = p->link; q != NULL; q = q->link) {
            if (strcmp(p->data.maSV, q->data.maSV) > 0) {
                SinhVien temp = p->data;
                p->data = q->data;
                q->data = temp;
            }
        }
    }
}

//================= CHEN CO THU TU =================
void chenCoThuTu(List &l, SinhVien x) {
    Node *p = taoNode(x);

    if (l.first == NULL) {
        l.first = l.last = p;
        return;
    }

    if (strcmp(x.maSV, l.first->data.maSV) < 0) {
        p->link = l.first;
        l.first = p;
        return;
    }

    Node *q = l.first;
    while (q->link != NULL &&
           strcmp(q->link->data.maSV, x.maSV) < 0) {
        q = q->link;
    }

    p->link = q->link;
    q->link = p;

    if (p->link == NULL)
        l.last = p;
}

//================= SO SANH NGAY =================
bool trungNgay(Ngay a, Ngay b) {
    return (a.ngay == b.ngay &&
            a.thang == b.thang &&
            a.nam == b.nam);
}

//================= IN SV CUNG NGAY SINH =================
void inTrungNgaySinh(List l) {
    bool found = false;

    for (Node *p = l.first; p != NULL; p = p->link) {
        int dem = 0;

        for (Node *q = l.first; q != NULL; q = q->link) {
            if (trungNgay(p->data.ngaySinh, q->data.ngaySinh))
                dem++;
        }

        if (dem > 1) {
            xuat1SV(p->data);
            found = true;
        }
    }

    if (!found)
        cout << "Khong tim thay sinh vien cung ngay sinh!\n";
}

//================= XOA NODE SAU q =================
void xoaSauQ(List &l, Node *q) {
    Node *p;

    if (q == NULL) {
        p = l.first;
        l.first = l.first->link;
    } else {
        p = q->link;
        q->link = p->link;
    }

    if (p == l.last)
        l.last = q;

    delete p;
}

//================= XOA SV TRUNG NGAY SINH =================
void xoaTrungNgaySinh(List &l) {
    Node *p = l.first;
    Node *prev = NULL;

    while (p != NULL) {
        int dem = 0;

        for (Node *q = l.first; q != NULL; q = q->link) {
            if (trungNgay(p->data.ngaySinh, q->data.ngaySinh))
                dem++;
        }

        if (dem > 1) {
            xoaSauQ(l, prev);
            if (prev == NULL)
                p = l.first;
            else
                p = prev->link;
        } else {
            prev = p;
            p = p->link;
        }
    }
}

//================= MENU =================
int main() {
    List l;
    initList(l);

    int n, chon;
    SinhVien sv;

    do {
        cout << "\n========= MENU =========\n";
        cout << "1. Nhap danh sach\n";
        cout << "2. Sap xep tang theo ma SV\n";
        cout << "3. Them sinh vien moi\n";
        cout << "4. In sinh vien trung ngay sinh\n";
        cout << "5. Xoa sinh vien trung ngay sinh\n";
        cout << "6. Xuat danh sach\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";
        cin >> chon;

        switch (chon) {
        case 1:
            cout << "Nhap so luong sinh vien: ";
            cin >> n;
            nhapDS(l, n);
            break;

        case 2:
            sapXepMaSV(l);
            cout << "Da sap xep!\n";
            break;

        case 3:
            cout << "Nhap sinh vien can them:\n";
            nhap1SV(sv);
            chenCoThuTu(l, sv);
            break;

        case 4:
            inTrungNgaySinh(l);
            break;

        case 5:
            xoaTrungNgaySinh(l);
            cout << "Da xoa!\n";
            break;

        case 6:
            xuatDS(l);
            break;
        }

    } while (chon != 0);

    return 0;
}