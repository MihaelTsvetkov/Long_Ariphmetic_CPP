#include "bignumber.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>

void BigNumber::addNode(long long value) {
    Node* newNode = new Node(value);
    if (!newNode) {
        std::cerr << "Memory allocation failed" << std::endl;
        exit(1);
    }
    if (!tail) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void BigNumber::prependNode(long long value) {
    Node* newNode = new Node(value);
    if (!newNode) {
        std::cerr << "Memory allocation failed" << std::endl;
        exit(1);
    }
    if (!head) {
        head = tail = newNode;
    }
    else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

void BigNumber::copy_list(const BigNumber& other) {
    Node* current = other.head;
    while (current) {
        addNode(current->value);
        current = current->next;
    }
}

void BigNumber::delete_list() {
    Node* current = head;
    while (current) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    head = tail = nullptr;
}

BigNumber::BigNumber(const std::string& numStr) : head(nullptr), tail(nullptr) {
    loadFromString(numStr);
}

BigNumber::BigNumber(const BigNumber& other) : head(nullptr), tail(nullptr) {
    copy_list(other);
}

BigNumber& BigNumber::operator=(const BigNumber& other) {
    if (this != &other) {
        delete_list();
        copy_list(other);
    }
    return *this;
}

BigNumber::~BigNumber() {
    delete_list();
}

void BigNumber::loadFromString(const std::string& numStr) {
    int length = numStr.length();
    for (int i = length; i > 0; i -= 5) {
        int start = std::max(0, i - 5);
        int len = i - start;
        long long value = std::stoll(numStr.substr(start, len));
        prependNode(value);
    }
}

std::string BigNumber::toString() const {
    if (!head) return "0";
    std::string result;
    Node* current = head;
    while (current) {
        std::stringstream ss;
        if (current != head) ss << std::setw(5) << std::setfill('0');
        ss << current->value;
        result += ss.str();
        current = current->next;
    }
    while (result.length() > 1 && result[0] == '0') {
        result.erase(0, 1);
    }
    return result;
}

void BigNumber::removeLeadingZeros() {
    while (head && head->value == 0) {
        Node* toDelete = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        }
        else {
            tail = nullptr;
        }
        delete toDelete;
    }
}

void BigNumber::removeTrailingZeros() {
    while (tail && tail->value == 0) {
        Node* toDelete = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        }
        else {
            head = nullptr;
        }
        delete toDelete;
    }
}

BigNumber BigNumber::operator+(const BigNumber& other) const {
    BigNumber result("0");
    Node* n1 = this->tail;
    Node* n2 = other.tail;
    long long carry = 0;
    const long long BASE = 100000;

    while (n1 || n2 || carry) {
        long long value1 = (n1 ? n1->value : 0);
        long long value2 = (n2 ? n2->value : 0);
        long long sum = value1 + value2 + carry;
        carry = sum / BASE;
        result.prependNode(sum % BASE);
        if (n1) n1 = n1->prev;
        if (n2) n2 = n2->prev;
    }

    result.removeLeadingZeros();
    result.removeTrailingZeros();
    return result;
}

BigNumber BigNumber::operator-(const BigNumber& other) const {
    BigNumber result("0");
    Node* n1 = this->tail;
    Node* n2 = other.tail;
    long long borrow = 0;
    const long long BASE = 100000;

    while (n1 || n2) {
        long long value1 = (n1 ? n1->value : 0);
        long long value2 = (n2 ? n2->value : 0) + borrow;
        long long diff = value1 - value2;
        if (diff < 0) {
            diff += BASE;
            borrow = 1;
        }
        else {
            borrow = 0;
        }
        result.prependNode(diff);
        if (n1) n1 = n1->prev;
        if (n2) n2 = n2->prev;
    }

    result.removeLeadingZeros();
    result.removeTrailingZeros();
    return result;
}

BigNumber BigNumber::operator*(const BigNumber& other) const {
    const long long BASE = 100000;
    BigNumber result("0");

   
    int totalLength = 0;
    for (Node* n1 = head; n1 != nullptr; n1 = n1->next) {
        for (Node* n2 = other.head; n2 != nullptr; n2 = n2->next) {
            totalLength++;
        }
    }

    
    for (int i = 0; i < totalLength; i++) {
        result.addNode(0);
    }

    Node* resultNode = result.tail;
    for (Node* n1 = tail; n1 != nullptr; n1 = n1->prev) {
        Node* tempNode = resultNode;
        for (Node* n2 = other.tail; n2 != nullptr; n2 = n2->prev) {
            long long mul = n1->value * n2->value + tempNode->value;
            tempNode->value = mul % BASE;
            long long carry = mul / BASE;

            
            Node* carryNode = tempNode->prev;
            while (carry > 0) {
                if (carryNode == nullptr) {
                    result.prependNode(carry % BASE);
                    carry /= BASE;
                }
                else {
                    carryNode->value += carry % BASE;
                    carry = carryNode->value / BASE;
                    carryNode->value %= BASE;
                    carryNode = carryNode->prev;
                }
            }

            tempNode = tempNode->prev;
        }
        resultNode = resultNode->prev;
    }

    result.removeLeadingZeros();
    return result;
}
