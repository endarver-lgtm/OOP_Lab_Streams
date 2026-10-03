#pragma once
#include <vector>
#include <string>
#include "Product.h"
#include "Order.h"

using namespace std;

class Shop {
    vector<Manufacturer*> manufacturers;
    vector<Product*> products;
    vector<Order*> orders;
    int nextProductId;
    int nextOrderId;

public:
    Shop();
    ~Shop();

    void seedDemoData();

    Manufacturer* addManufacturer(const string& name, const string& country);
    Manufacturer* findManufacturerById(int id);
    void listManufacturers(ostream& out) const;

    Product* addPerfume(const string& name, double volumeMl, double price,
        Manufacturer* manufacturer, const string& fragranceFamily, int longevityHours);
    Product* addCosmetic(const string& name, double volumeMl, double price,
        Manufacturer* manufacturer, const string& skinType);

    bool removeProduct(int id);
    Product* findProductById(int id);
    vector<Product*> findProductsByName(const string& part) const;

    void sortByPrice();
    void sortByName();

    void printCatalog(ostream& out) const;
    void exportCatalogToFile(const string& path) const;

    Order* createOrder(const string& customerName);
    vector<Order*>& getOrders();

    vector<Product*>& getProducts();
};