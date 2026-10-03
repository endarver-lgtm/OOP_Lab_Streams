#include "Order.h"
#include <iomanip>
#include <algorithm>

OrderLine::OrderLine() : product(nullptr), quantity(0) {}

OrderLine::OrderLine(Product* product, int quantity) : product(product), quantity(quantity) {}

Product* OrderLine::getProduct() const { return product; }
int OrderLine::getQuantity() const { return quantity; }
void OrderLine::setQuantity(int value) { quantity = value; }

double OrderLine::getLineTotal() const {
    return product ? product->getPrice() * quantity : 0.0;
}

void OrderLine::printRow(std::ostream& out) const {
    out.setf(std::ios::left, std::ios::adjustfield);
    out << std::setw(26) << (product ? product->getName() : "-");
    out.setf(std::ios::right, std::ios::adjustfield);
    out << std::setw(6) << quantity;
    out.setf(std::ios::fixed, std::ios::floatfield);
    out << std::setw(12) << std::setprecision(2) << getLineTotal() << "\n";
}

Order::Order() : id(0), customerName("") {}

Order::Order(int id, const std::string& customerName) : id(id), customerName(customerName) {}

int Order::getId() const { return id; }
std::string Order::getCustomerName() const { return customerName; }
std::vector<OrderLine>& Order::getLines() { return lines; }

void Order::addLine(Product* product, int quantity) {
    lines.push_back(OrderLine(product, quantity));
}

bool Order::removeLine(int productId) {
    auto it = std::find_if(lines.begin(), lines.end(), [productId](const OrderLine& l) {
        return l.getProduct() && l.getProduct()->getId() == productId;
        });
    if (it == lines.end()) return false;
    lines.erase(it);
    return true;
}

double Order::getTotal() const {
    double sum = 0.0;
    for (const auto& l : lines) sum += l.getLineTotal();
    return sum;
}

void Order::printReceipt(std::ostream& out) const {
    out << "Order #" << id << ", customer: " << customerName << "\n";
    out.setf(std::ios::left, std::ios::adjustfield);
    out << std::setw(26) << "Product";
    out.setf(std::ios::right, std::ios::adjustfield);
    out << std::setw(6) << "Qty" << std::setw(12) << "Total" << "\n";
    for (const auto& l : lines) l.printRow(out);
    out.setf(std::ios::fixed, std::ios::floatfield);
    out << "Order total: " << std::setprecision(2) << getTotal() << "\n";
}
