#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <ctime>
#include <iomanip>
#include <fstream>


// Product class for inventory management
class Product {
    std::string id;
    std::string name;
    double price;
    int stock;
    time_t expiryDate;

public:
    Product(const std::string& id, const std::string& name, double price, int stock, time_t expiry)
        : id(id), name(name), price(price), stock(stock), expiryDate(expiry) {}

    const std::string& getId() const { return id; }
    const std::string& getName() const { return name; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }
    void setStock(int quantity) { stock = quantity; }
    void reduceStock(int quantity) { stock -= quantity; }

    bool isLowStock() const { return stock < 10; }
};

// Admin functionalities
class AdminSystem {
    std::vector<Product> inventory;
    double totalSales = 0.0;
    int totalTransactions = 0;

public:

     AdminSystem() {
        inventory.emplace_back("001", "Mie Instan", 3000.0, 50, 0);
        inventory.emplace_back("002", "Kopi", 5000.0, 30, 0);
    }

    void addProduct() {
        std::string id, name;
        double price;
        int stock;

        std::cout << "Enter product code (3 digits): ";
        std::cin >> id;
        std::cout << "Enter product name: ";
        std::cin.ignore();
        std::getline(std::cin, name);
        std::cout << "Enter selling price: ";
        std::cin >> price;
        std::cout << "Enter initial stock: ";
        std::cin >> stock;

        Product product(id, name, price, stock, 0);
        inventory.push_back(product);
        std::cout << "Product added successfully!\n";
    }

    void viewProducts() {
        std::cout << "\nProduct List:\n";
        for (const auto& product : inventory) {
            std::cout << "ID: " << product.getId() << ", Name: " << product.getName() 
                      << ", Price: " << product.getPrice() << ", Stock: " << product.getStock() << "\n";
        }
    }

    void updateStock() {
        std::string productId;
        int stock;

        std::cout << "Enter product code to update stock: ";
        std::cin >> productId;
        std::cout << "Enter stock to add: ";
        std::cin >> stock;

        for (auto& product : inventory) {
            if (product.getId() == productId) {
                product.setStock(product.getStock() + stock);
                std::cout << "Stock updated successfully!\n";
                return;
            }
        }

        std::cout << "Product not found!\n";
    }

void generateReport() {
    std::cout << "\nDaily Sales Report:\n";
    std::cout << "Total Transactions: " << totalTransactions << "\n";
    std::cout << "Total Revenue: " << std::fixed << std::setprecision(2) << totalSales << "\n";

    // Save report to file
    std::ofstream reportFile("daily_report.txt");
    if (reportFile.is_open()) {
        reportFile << "Daily Sales Report\n";
        reportFile << "===================\n";
        reportFile << "Total Transactions: " << totalTransactions << "\n";
        reportFile << "Total Revenue: " << std::fixed << std::setprecision(2) << totalSales << "\n";
        reportFile.close();
        std::cout << "Report has been saved to 'daily_report.txt'.\n";
    } else {
        std::cout << "Failed to save the report to file.\n";
    }
}


    void recordSale(double amount) {
        totalSales += amount;
        ++totalTransactions;
    }

    std::vector<Product>& getInventory() { return inventory; }
};

// Staff functionalities
class StaffSystem {
    AdminSystem& admin;
    std::vector<Product>& inventory;

public:
    StaffSystem(AdminSystem& admin, std::vector<Product>& inventory) : admin(admin), inventory(inventory) {}

   void processSale() {
    std::string productId;
    int quantity;
    double total = 0.0;

    // Tampilkan daftar produk
    std::cout << "\nAvailable Products:\n";
    for (const auto& product : inventory) {
        std::cout << "ID: " << product.getId()
                  << ", Name: " << product.getName()
                  << ", Price: " << product.getPrice()
                  << ", Stock: " << product.getStock() << "\n";
    }

    // Input kode produk
    std::cout << "\nEnter product code: ";
    std::cin >> productId;
    std::cout << "Enter quantity: ";
    std::cin >> quantity;

    // Proses penjualan
    for (auto& product : inventory) {
        if (product.getId() == productId) {
            if (product.getStock() < quantity) {
                std::cout << "Not enough stock available!\n";
                return;
            }

            product.reduceStock(quantity);
            total = product.getPrice() * quantity;
            admin.recordSale(total);

            std::cout << "Sale processed successfully!\n";
            std::cout << "Total: " << total << "\n";
            printReceipt(product.getName(), quantity, total);
            return;
        }
    }

    std::cout << "Product not found!\n";
}


    void checkPrice() {
        std::string productId;

        std::cout << "Enter product code to check price: ";
        std::cin >> productId;

        for (const auto& product : inventory) {
            if (product.getId() == productId) {
                std::cout << "Price of " << product.getName() << ": " << product.getPrice() << "\n";
                return;
            }
        }

        std::cout << "Product not found!\n";
    }

    void checkStock() {
        std::string productId;

        std::cout << "Enter product code to check stock: ";
        std::cin >> productId;

        for (const auto& product : inventory) {
            if (product.getId() == productId) {
                std::cout << "Stock of " << product.getName() << ": " << product.getStock() << "\n";
                return;
            }
        }

        std::cout << "Product not found!\n";
    }

    void updateOutgoingStock() {
        std::string productId;
        int quantity;

        std::cout << "Enter product code: ";
        std::cin >> productId;
        std::cout << "Enter quantity to remove: ";
        std::cin >> quantity;

        for (auto& product : inventory) {
            if (product.getId() == productId) {
                if (product.getStock() < quantity) {
                    std::cout << "Not enough stock available to remove!\n";
                    return;
                }

                product.reduceStock(quantity);
                std::cout << "Stock updated successfully!\n";
                return;
            }
        }

        std::cout << "Product not found!\n";
    }

    void viewLowStock() {
        std::cout << "\nLow Stock Products:\n";
        for (const auto& product : inventory) {
            if (product.isLowStock()) {
                std::cout << "ID: " << product.getId() << ", Name: " << product.getName() << ", Stock: " << product.getStock() << "\n";
            }
        }
    }

    void reportToAdmin() {
        std::cout << "Low stock report sent to admin!\n";
    }

private:
    void printReceipt(const std::string& productName, int quantity, double total) {
        std::string receiptFileName = "receipt.txt";
        std::ofstream receiptFile(receiptFileName);

        if (receiptFile.is_open()) {
            receiptFile << "Receipt\n";
            receiptFile << "====================\n";
            receiptFile << "Product: " << productName << "\n";
            receiptFile << "Quantity: " << quantity << "\n";
            receiptFile << "Total: " << std::fixed << std::setprecision(2) << total << "\n";
            receiptFile << "Thank you for your purchase!\n";
            receiptFile.close();
            std::cout << "\nReceipt has been saved to '" << receiptFileName << "'\n";
        } else {
            std::cout << "Failed to save the receipt to file.\n";
        }

        // Print to console as well
        std::cout << "\nReceipt:\n";
        std::cout << "Product: " << productName << "\n";
        std::cout << "Quantity: " << quantity << "\n";
        std::cout << "Total: " << total << "\n";
        std::cout << "Thank you for your purchase!\n\n";
    }
};

int main() {
    AdminSystem admin;
    std::vector<Product>& inventory = admin.getInventory();
    StaffSystem staff(admin, inventory);

    int userType;
    do {
        std::cout << "\nWelcome!\n1. Admin\n2. Staff\n0. Exit\nChoose your role: ";
        std::cin >> userType;

        if (userType == 1) {
            int choice;
            do {
                std::cout << "\nAdmin Menu:\n";
                std::cout << "1. Add Product\n2. View Products\n3. Update Stock\n4. Generate Report\n0. Back to Main Menu\n";
                std::cout << "Enter your choice: ";
                std::cin >> choice;

                switch (choice) {
                    case 1:
                        admin.addProduct();
                        break;
                    case 2:
                        admin.viewProducts();
                        break;
                    case 3:
                        admin.updateStock();
                        break;
                    case 4:
                        admin.generateReport();
                        break;
                    case 0:
                        std::cout << "Returning to Main Menu...\n";
                        break;
                    default:
                        std::cout << "Invalid choice!\n";
                        break;
                }
            } while (choice != 0);
        } else if (userType == 2) {
            int choice;
            do {
                std::cout << "\nStaff Menu:\n";
                std::cout << "1. Process Sale\n2. Check Product Price\n3. Check Product Stock\n4. Update Outgoing Stock\n5. View Low Stock Products\n6. Report Low Stock to Admin\n0. Back to Main Menu\n";
                std::cout << "Enter your choice: ";
                std::cin >> choice;

                switch (choice) {
                    case 1:
                        staff.processSale();
                        break;
                    case 2:
                        staff.checkPrice();
                        break;
                    case 3:
                        staff.checkStock();
                        break;
                    case 4:
                        staff.updateOutgoingStock();
                        break;
                    case 5:
                        staff.viewLowStock();
                        break;
                    case 6:
                        staff.reportToAdmin();
                        break;
                    case 0:
                        std::cout << "Returning to Main Menu...\n";
                        break;
                    default:
                        std::cout << "Invalid choice!\n";
                        break;
                }
            } while (choice != 0);
        } else if (userType == 0) {
            std::cout << "Exiting the program...\n";
        } else {
            std::cout << "Invalid role! Please choose again.\n";
        }
    } while (userType != 0);

    return 0;
}

