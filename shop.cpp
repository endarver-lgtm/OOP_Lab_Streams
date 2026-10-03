#include "Shop.h"
#include <algorithm>
#include <fstream>
#include <iomanip>

Shop::Shop() : nextProductId(1), nextOrderId(1) {}

Shop::~Shop() {
    for (auto m : manufacturers) delete m;
    for (auto p : products) delete p;
    for (auto o : orders) delete o;
}

void Shop::seedDemoData() {
    Manufacturer* chanel = addManufacturer("Chanel", "France");
    Manufacturer* nivea = addManufacturer("Nivea", "Germany");
    Manufacturer* dior = addManufacturer("Dior", "France");
    Manufacturer* loreal = addManufacturer("L'Oreal", "France");

    addPerfume("Chanel No.5", 50.0, 120.50, chanel, "Floral", 8);
    addPerfume("Bleu de Chanel", 100.0, 95.00, chanel, "Woody", 6);
    addPerfume("Coco Mademoiselle", 75.0, 110.00, chanel, "Oriental", 4);

    addPerfume("Sauvage", 100.0, 99.90, dior, "Fresh", 7);
    addPerfume("J'adore", 50.0, 130.00, dior, "Floral", 5);
    addPerfume("Miss Dior", 75.0, 115.75, dior, "Floral", 3);

    addPerfume("L'Oreal Men Expert", 50.0, 45.00, loreal, "Woody", 9);
    addPerfume("Elseve Fragrance", 30.0, 25.50, loreal, "Fruity", 12);

    addCosmetic("Nivea Day Cream", 75.0, 12.30, nivea, "Dry");
    addCosmetic("Nivea Soft Moisturizer", 50.0, 8.90, nivea, "All");
    addCosmetic("Nivea Men Face Wash", 100.0, 9.50, nivea, "Oily");

    addCosmetic("L'Oreal Revitalift", 50.0, 18.70, loreal, "Anti-Age");
}

Manufacturer* Shop::addManufacturer(const std::string& name, const std::string& country) {
    int id = static_cast<int>(manufacturers.size()) + 1;
    Manufacturer* m = new Manufacturer(id, name, country);
    manufacturers.push_back(m);
    return m;
}

Manufacturer* Shop::findManufacturerById(int id) {
    for (auto m : manufacturers) if (m->getId() == id) return m;
    return nullptr;
}

void Shop::listManufacturers(std::ostream& out) const {
    out << std::setw(4) << "ID" << std::setw(20) << "Name" << std::setw(15) << "Country" << "\n";
    for (auto m : manufacturers) m->print();
}

Product* Shop::addPerfume(const std::string& name, double volumeMl, double price,
    Manufacturer* manufacturer, const std::string& fragranceFamily, int longevityHours) {
    Product* p = new Perfume(nextProductId++, name, volumeMl, price, manufacturer, fragranceFamily, longevityHours);
    products.push_back(p);
    return p;
}

Product* Shop::addCosmetic(const std::string& name, double volumeMl, double price,
    Manufacturer* manufacturer, const std::string& skinType) {
    Product* p = new CosmeticItem(nextProductId++, name, volumeMl, price, manufacturer, skinType);
    products.push_back(p);
    return p;
}

bool Shop::removeProduct(int id) {
    auto it = std::find_if(products.begin(), products.end(), [id](Product* p) { return p->getId() == id; });
    if (it == products.end()) return false;
    delete* it;
    products.erase(it);
    return true;
}

Product* Shop::findProductById(int id) {
    for (auto p : products) if (p->getId() == id) return p;
    return nullptr;
}

std::vector<Product*> Shop::findProductsByName(const std::string& part) const {
    std::vector<Product*> result;
    for (auto p : products) {
        std::string name = p->getName();
        std::string lowerName = name;
        std::string lowerPart = part;
        std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
        std::transform(lowerPart.begin(), lowerPart.end(), lowerPart.begin(), ::tolower);
        if (lowerName.find(lowerPart) != std::string::npos) result.push_back(p);
    }
    return result;
}

void Shop::sortByPrice() {
    std::sort(products.begin(), products.end(), [](Product* a, Product* b) {
        return a->getPrice() < b->getPrice();
        });
}

void Shop::sortByName() {
    std::sort(products.begin(), products.end(), [](Product* a, Product* b) {
        return a->getName() < b->getName();
        });
}

void Shop::printCatalog(std::ostream& out) const {
    out.setf(std::ios::left, std::ios::adjustfield);
    out << std::setw(4) << "ID" << std::setw(9) << "Type" << std::setw(22) << "Name";
    out.setf(std::ios::right, std::ios::adjustfield);
    out << std::setw(8) << "Vol,ml" << std::setw(10) << "Price";
    out << "  " << std::setw(14) << "Manufacturer" << std::setw(20) << "Details" << "\n";
    for (auto p : products) p->printRow(out);
}

void Shop::exportCatalogToFile(const std::string& path) const {
    std::ofstream file(path);
    if (!file.good()) {
        std::cout << "Failed to open file for writing: " << path << "\n";
        return;
    }
    printCatalog(file);
    file.close();
}

Order* Shop::createOrder(const std::string& customerName) {
    Order* o = new Order(nextOrderId++, customerName);
    orders.push_back(o);
    return o;
}

std::vector<Order*>& Shop::getOrders() { return orders; }
std::vector<Product*>& Shop::getProducts() { return products; }
