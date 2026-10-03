#pragma once
#include <vector>
#include <iostream>
#include "Product.h"

using namespace std;

class OrderLine {
    Product* product;
    int quantity;
public:
    OrderLine();
    OrderLine(Product* product, int quantity);
    Product* getProduct() const;
    int getQuantity() const;
    void setQuantity(int value);
    double getLineTotal() const;
    void printRow(ostream& out) const;
};

class Order {
    int id;
    string customerName;
    vector<OrderLine> lines;
public:
    Order();
    Order(int id, const string& customerName);
    int getId() const;
    string getCustomerName() const;
    vector<OrderLine>& getLines();
    void addLine(Product* product, int quantity);
    bool removeLine(int productId);
    double getTotal() const;
    void printReceipt(ostream& out) const;
};