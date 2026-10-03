#pragma once
#include <string>
#include <iostream>

using namespace std;

class Manufacturer {
    int id;
    string name;
    string country;
public:
    Manufacturer();
    Manufacturer(int id, const string& name, const string& country);
    int getId() const;
    string getName() const;
    string getCountry() const;
    void print() const;
};

class Product {
protected:
    int id;
    string name;
    double volumeMl;
    double price;
    Manufacturer* manufacturer;
public:
    Product();
    Product(int id, const string& name, double volumeMl, double price, Manufacturer* manufacturer);
    virtual ~Product();

    int getId() const;
    string getName() const;
    double getVolumeMl() const;
    double getPrice() const;
    Manufacturer* getManufacturer() const;

    void setName(const string& value);
    void setVolumeMl(double value);
    void setPrice(double value);
    void setManufacturer(Manufacturer* value);

    virtual string getType() const = 0;
    virtual string getDetails() const = 0;
    virtual void printRow(ostream& out) const;
};

class Perfume : public Product {
    string fragranceFamily;
    int longevityHours;
public:
    Perfume();
    Perfume(int id, const string& name, double volumeMl, double price,
        Manufacturer* manufacturer, const string& fragranceFamily, int longevityHours);
    string getType() const override;
    string getDetails() const override;
    string getFragranceFamily() const;
    int getLongevityHours() const;
    void setFragranceFamily(const string& value);
    void setLongevityHours(int value);
};

class CosmeticItem : public Product {
    string skinType;
public:
    CosmeticItem();
    CosmeticItem(int id, const string& name, double volumeMl, double price,
        Manufacturer* manufacturer, const string& skinType);
    string getType() const override;
    string getDetails() const override;
    string getSkinType() const;
    void setSkinType(const string& value);
};