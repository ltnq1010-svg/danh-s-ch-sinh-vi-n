#include <bits/stdc++.h>
using namespace std;

/* ================= CLASS STUDENT ================= */
class Student {
private:
    string id, name, majors;
    double gpa;

public:
    void input() {
        cout << "Nhap ID: ";
        cin >> id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Nhap ho ten: ";
        getline(cin, name);

        cout << "Nhap nganh hoc: ";
        getline(cin, majors);

        cout << "Nhap GPA: ";
        cin >> gpa;
    }

    void output() const {
        cout << "--------------------------------\n";
        cout << "ID: " << id << endl;
        cout << "Ho ten: " << name << endl;
        cout << "Nganh hoc: " << majors << endl;
        cout << "GPA: " << fixed << setprecision(2) << gpa << endl;
        cout << "--------------------------------\n";
    }

    string getId() const { return id; }
    string getName() const { return name; }
    double getGpa() const { return gpa; }
};

/* ================= CLASS NODE ================= */
class Node {
public:
    Student data;
    Node* next;

    Node(const Student& s) {
        data = s;
        next = NULL;
    }
};

/* ================= LINKED LIST ================= */
class LinkedList {
private:
    Node* head;

public:
    LinkedList() {
        head = NULL;
    }

    bool empty() const {
        return head == NULL;
    }

    int size() const {
        int cnt = 0;
        for (Node* p = head; p != NULL; p = p->next)
            cnt++;
        return cnt;
    }

    /* ===== INSERT ===== */
    void insertFirst() {
        Student s;
        s.input();
        Node* tmp = new Node(s);
        tmp->next = head;
        head = tmp;
    }

    void insertLast() {
        Student s;
        s.input();
        Node* tmp = new Node(s);

        if (head == NULL) {
            head = tmp;
            return;
        }

        Node* p = head;
        while (p->next != NULL)
            p = p->next;

        p->next = tmp;
    }

    void insertMiddle(int pos) {
        int n = size();
        if (pos <= 0 || pos > n + 1) {
            cout << "Vi tri khong hop le!\n";
            return;
        }

        if (pos == 1) {
            insertFirst();
            return;
        }
        if (pos == n + 1) {
            insertLast();
            return;
        }

        Student s;
        s.input();
        Node* tmp = new Node(s);

        Node* p = head;
        for (int i = 1; i < pos - 1; i++)
            p = p->next;

        tmp->next = p->next;
        p->next = tmp;
    }

    /* ===== DELETE ===== */
    void deleteFirst() {
        if (head == NULL) return;
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }

    void deleteLast() {
        if (head == NULL) return;

        if (head->next == NULL) {
            delete head;
            head = NULL;
            return;
        }

        Node* p = head;
        while (p->next->next != NULL)
            p = p->next;

        delete p->next;
        p->next = NULL;
    }

    void deleteMiddle(int pos) {
        int n = size();
        if (pos <= 0 || pos > n) return;

        if (pos == 1) {
            deleteFirst();
            return;
        }

        Node* p = head;
        for (int i = 1; i < pos - 1; i++)
            p = p->next;

        Node* tmp = p->next;
        p->next = tmp->next;
        delete tmp;
    }

    /* ===== DISPLAY ===== */
    void display() const {
        if (head == NULL) {
            cout << "Danh sach rong!\n";
            return;
        }

        cout << "Danh sach sinh vien:\n";
        for (Node* p = head; p != NULL; p = p->next)
            p->data.output();
    }

    /* ===== SORT ===== */
    void sortByGpa() {
        for (Node* p = head; p != NULL; p = p->next) {
            Node* min = p;
            for (Node* q = p->next; q != NULL; q = q->next) {
                if (q->data.getGpa() < min->data.getGpa())
                    min = q;
            }
            swap(p->data, min->data);
        }
    }

    /* ===== SEARCH ===== */
    Node* findById(const string& id) const {
        for (Node* p = head; p != NULL; p = p->next) {
            if (p->data.getId() == id)
                return p;
        }
        return NULL;
    }

    void findByName(const string& name) const {
        bool found = false;
        for (Node* p = head; p != NULL; p = p->next) {
            if (p->data.getName() == name) {
                p->data.output();
                found = true;
            }
        }
        if (!found)
            cout << "Khong tim thay sinh vien!\n";
    }

    Node* findMaxGpa() const {
        if (head == NULL) return NULL;

        Node* max = head;
        for (Node* p = head->next; p != NULL; p = p->next) {
            if (p->data.getGpa() > max->data.getGpa())
                max = p;
        }
        return max;
    }
};

/* ================= MAIN ================= */
int main() {
    LinkedList list;
    while (1) {
        cout << "\n--------- MENU ---------\n";
        cout << "1. Chen sinh vien vao dau\n";
        cout << "2. Chen sinh vien vao cuoi\n";
        cout << "3. Chen sinh vien vao giua\n";
        cout << "4. Xoa dau\n";
        cout << "5. Xoa cuoi\n";
        cout << "6. Xoa giua\n";
        cout << "7. Hien thi danh sach\n";
        cout << "8. Sap xep theo GPA\n";
        cout << "9. Tim sinh vien theo ID\n";
        cout << "10. Tim sinh vien theo ten\n";
        cout << "11. Tim sinh vien GPA cao nhat\n";
        cout << "0. Thoat\n";
        cout << "------------------------\n";
        cout << "Nhap lua chon: ";

        int lc;
        cin >> lc;

        if (lc == 1) list.insertFirst();
        else if (lc == 2) list.insertLast();
        else if (lc == 3) {
            int pos;
            cout << "Nhap vi tri: ";
            cin >> pos;
            list.insertMiddle(pos);
        }
        else if (lc == 4) list.deleteFirst();
        else if (lc == 5) list.deleteLast();
        else if (lc == 6) {
            int pos;
            cout << "Nhap vi tri can xoa: ";
            cin >> pos;
            list.deleteMiddle(pos);
        }
        else if (lc == 7) list.display();
        else if (lc == 8) list.sortByGpa();
        else if (lc == 9) {
            string id;
            cout << "Nhap ID: ";
            cin >> id;
            Node* p = list.findById(id);
            if (p) p->data.output();
            else cout << "Khong tim thay sinh vien!\n";
        }
        else if (lc == 10) {
            cin.ignore();
            string name;
            cout << "Nhap ten: ";
            getline(cin, name);
            list.findByName(name);
        }
        else if (lc == 11) {
            Node* p = list.findMaxGpa();
            if (p) {
                cout << "Sinh vien GPA cao nhat:\n";
                p->data.output();
            } else {
                cout << "Danh sach rong!\n";
            }
        }
        else if (lc == 0) break;
    }
    return 0;
}

