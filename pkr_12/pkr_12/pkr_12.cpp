#include <iostream>
using namespace std;

struct Node {
    int coeff;
    int power;
    Node* next;
    Node* prev;
};

void insert(Node** head, int coeff, int power) {
    Node* newNode = new Node;
    newNode->coeff = coeff;
    newNode->power = power;
    newNode->next = *head;
    newNode->prev = nullptr;
    if (*head != nullptr) {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

void printList(Node* node) {
    while (node != nullptr) {
        cout << node->coeff << "x^" << node->power;
        if (node->next != nullptr) {
            cout << " + ";
        }
        node = node->next;
    }
    cout << endl;
}

void sortList(Node* head) {
    Node* i;
    Node* j;
    int swapped;
    for (i = head; i->next != nullptr; i = i->next) {
        swapped = 0;
        for (j = head; j->next != nullptr; j = j->next) {
            if (j->power < j->next->power) {
                int tempCoeff = j->coeff;
                int tempPower = j->power;
                j->coeff = j->next->coeff;
                j->power = j->next->power;
                j->next->coeff = tempCoeff;
                j->next->power = tempPower;
                swapped = 1;
            }
        }
        if (swapped == 0) {
            break;
        }
    }
}

void simplifyList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current->next;
        while (temp != nullptr) {
            if (current->power == temp->power) {
                current->coeff += temp->coeff;
                Node* duplicate = temp;
                temp->prev->next = temp->next;
                if (temp->next != nullptr) {
                    temp->next->prev = temp->prev;
                }
                temp = temp->next;
                delete duplicate;
            }
            else {
                temp = temp->next;
            }
        }
        current = current->next;
    }
}

int main() {
    int numTerms;
    cout << "Enter the number of terms in the polynomial: ";
    cin >> numTerms;
    Node* head = nullptr;
    for (int i = 0; i < numTerms; i++) {
        int coeff, power;
        cout << "Enter the coefficient for term " << i + 1 << ": ";
        cin >> coeff;
        cout << "Enter the power for term " << i + 1 << ": ";
        cin >> power;
        insert(&head, coeff, power);
    }
    cout << "List before simplification: ";
    printList(head);
    sortList(head);
    simplifyList(head);
    cout << "List after simplification: ";
    printList(head);
    return 0;
}
