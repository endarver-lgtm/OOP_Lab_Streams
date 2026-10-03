#include "Product.h"
#include <iomanip>

Manufacturer::Manufacturer() : id(0), name(""), country("") {}

Manufacturer::Manufacturer(int id, const std::string& name, const std::string& country)
    : id(id), name(name), country(country) {
}

int Manufacturer::getId() const { return id; }
std::string Manufacturer::getName() const { return name; }
std::string Manufacturer::getCountry() const { return country; }

void Manufacturer::print() const {
    std::cout << std::setw(4) << id << std::setw(20) << name << std::setw(15) << country << "\n";
}

Product::Product() : id(0), name(""), volumeMl(0.0), price(0.0), manufacturer(nullptr) {}

Product::Product(int id, const std::string& name, double volumeMl, double price, Manufacturer* manufacturer)
    : id(id), name(name), volumeMl(volumeMl), price(price), manufacturer(manufacturer) {
}

Product::~Product() {}

int Product::getId() const { return id; }
std::string Product::getName() const { return name; }
double Product::getVolumeMl() const { return volumeMl; }
double Product::getPrice() const { return price; }
Manufacturer* Product::getManufacturer() const { return manufacturer; }

void Product::setName(const std::string& value) { name = value; }
void Product::setVolumeMl(double value) { volumeMl = value; }
void Product::setPrice(double value) { price = value; }
void Product::setManufacturer(Manufacturer* value) { manufacturer = value; }

void Product::printRow(std::ostream& out) const {
    out.setf(std::ios::left, std::ios::adjustfield);
    out << std::setw(4) << id << std::setw(9) << getType() << std::setw(22) << name;
    out.setf(std::ios::right, std::ios::adjustfield);
    out.setf(std::ios::fixed, std::ios::floatfield);
    out << std::setw(8) << std::setprecision(1) << volumeMl;
    out.setf(std::ios::showpoint);
    out << std::setw(10) << std::setprecision(2) << price;
    out.unsetf(std::ios::showpoint);
    out << "  " << std::setw(14) << (manufacturer ? manufacturer->getName() : "-");
    out << std::setw(20) << getDetails() << "\n";
}

Perfume::Perfume() : Product(), fragranceFamily(""), longevityHours(0) {}

Perfume::Perfume(int id, const std::string& name, double volumeMl, double price,
    Manufacturer* manufacturer, const std::string& fragranceFamily, int longevityHours)
    : Product(id, name, volumeMl, price, manufacturer),
    fragranceFamily(fragranceFamily), longevityHours(longevityHours) {
}

std::string Perfume::getType() const { return "Perfume"; }

std::string Perfume::getDetails() const {
    return fragranceFamily + ", " + std::to_string(longevityHours) + "h";
}

std::string Perfume::getFragranceFamily() const { return fragranceFamily; }
int Perfume::getLongevityHours() const { return longevityHours; }
void Perfume::setFragranceFamily(const std::string& value) { fragranceFamily = value; }
void Perfume::setLongevityHours(int value) { longevityHours = value; }

CosmeticItem::CosmeticItem() : Product(), skinType("") {}

CosmeticItem::CosmeticItem(int id, const std::string& name, double volumeMl, double price,
    Manufacturer* manufacturer, const std::string& skinType)
    : Product(id, name, volumeMl, price, manufacturer), skinType(skinType) {
}

std::string CosmeticItem::getType() const { return "Cosmetic"; }
std::string CosmeticItem::getDetails() const { return "skin: " + skinType; }
std::string CosmeticItem::getSkinType() const { return skinType; }
void CosmeticItem::setSkinType(const std::string& value) { skinType = value; }
