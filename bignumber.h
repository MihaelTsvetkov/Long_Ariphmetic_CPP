#ifndef BIGNUMBER_H
#define BIGNUMBER_H

#include <string>

class Node {
public:
    long long value;
    Node* prev;
    Node* next;

    Node(long long val) : value(val), prev(nullptr), next(nullptr) {}
    ~Node() {}
};

class BigNumber {
private:
    Node* head;
    Node* tail;

    void addNode(long long value);
    void prependNode(long long value);
    void copy_list(const BigNumber& other);
    void delete_list();

public:
    BigNumber(const std::string& numStr);
    BigNumber(const BigNumber& other);
    BigNumber& operator=(const BigNumber& other);
    ~BigNumber();

    void loadFromString(const std::string& numStr);
    std::string toString() const;
    void removeLeadingZeros();
    void removeTrailingZeros();

    BigNumber operator+(const BigNumber& other) const;
    BigNumber operator-(const BigNumber& other) const;
    BigNumber operator*(const BigNumber& other) const;
};

#endif // BIGNUMBER_H
