#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Product {
    string id;
    string name;
    double price;
    int stock;
};

void viewProducts(const vector<Product>& inventory) {
    cout << "\nDaftar Produk:\n";
    cout << "ID\tNama\t\tHarga\tStok\n";
    cout << "----------------------------------\n";
    for (const auto& product : inventory) {
        cout << product.id << "\t" 
             << product.name << "\t\t" 
             << fixed << setprecision(2) << product.price << "\t" 
             << product.stock << endl;
    }
}

void addProduct(vector<Product>& inventory) {
    Product newProduct;
    cout << "Masukkan kode produk (3 digit): ";
    cin >> newProduct.id;
    cout << "Masukkan nama produk: ";
    cin.ignore();
    getline(cin, newProduct.name);
    cout << "Masukkan harga produk: ";
    cin >> newProduct.price;
    cout << "Masukkan jumlah stok awal: ";
    cin >> newProduct.stock;

    inventory.push_back(newProduct);
    cout << "Produk berhasil ditambahkan!\n";
}

void updateStock(vector<Product>& inventory) {
    string productId;
    int stockToAdd;

    cout << "Masukkan kode produk: ";
    cin >> productId;
    cout << "Masukkan jumlah stok masuk: ";
    cin >> stockToAdd;

    for (auto& product : inventory) {
        if (product.id == productId) {
            product.stock += stockToAdd;
            cout << "Stok berhasil diperbarui!\n";
            return;
        }
    }

    cout << "Produk tidak ditemukan!\n";
}

void processSale(vector<Product>& inventory, double& totalSales, int& totalTransactions) {
    string productId;
    int quantity;

    cout << "Masukkan kode produk: ";
    cin >> productId;
    cout << "Masukkan jumlah: ";
    cin >> quantity;

    for (auto& product : inventory) {
        if (product.id == productId) {
            if (product.stock >= quantity) {
                double total = product.price * quantity;
                product.stock -= quantity;
                totalSales += total;
                totalTransactions++;

                cout << "Penjualan berhasil diproses!\n";
                cout << "Total Harga: " << fixed << setprecision(2) << total << endl;

                cout << "\n=== Struk ===\n";
                cout << "Produk: " << product.name << "\n";
                cout << "Jumlah: " << quantity << "\n";
                cout << "Total: " << total << "\n";
                cout << "=============\n";
                return;
            } else {
                cout << "Stok tidak mencukupi!\n";
                return;
            }
        }
    }

    cout << "Produk tidak ditemukan!\n";
}

void checkPrice(const vector<Product>& inventory) {
    string productId;

    cout << "Masukkan kode produk: ";
    cin >> productId;

    for (const auto& product : inventory) {
        if (product.id == productId) {
            cout << "Harga produk " << product.name << ": " << fixed << setprecision(2) << product.price << endl;
            return;
        }
    }

    cout << "Produk tidak ditemukan!\n";
}

void checkStock(const vector<Product>& inventory) {
    string productId;
    cout << "Masukkan kode produk: ";
    cin >> productId;

    for (const auto& product : inventory) {
        if (product.id == productId) {
            cout << "Stok tersedia untuk " << product.name << ": " << product.stock << endl;
            return;
        }
    }

    cout << "Produk tidak ditemukan!\n";
}

void viewLowStock(const vector<Product>& inventory) {
    cout << "\nProduk dengan Stok Menipis (kurang dari 10):\n";
    for (const auto& product : inventory) {
        if (product.stock < 10) {
            cout << "ID: " << product.id << ", Nama: " << product.name << ", Stok: " << product.stock << endl;
        }
    }
}

void printReport(double totalSales, int totalTransactions) {
    cout << "\n=== Laporan Harian ===\n";
    cout << "Total Transaksi: " << totalTransactions << endl;
    cout << "Total Pendapatan: " << fixed << setprecision(2) << totalSales << endl;
    cout << "======================\n";
}

int main() {
    vector<Product> inventory = {
        {"001", "Mie Instan", 3000.0, 50},
        {"002", "Kopi", 5000.0, 30}
    };

    double totalSales = 0.0;
    int totalTransactions = 0;

    int role, choice;
    do {
        cout << "\nPilih Peran:\n1. Admin\n2. Staff\n0. Keluar\nPilih: ";
        cin >> role;

        if (role == 1) { // Admin
            do {
                cout << "\nMenu Admin:\n";
                cout << "1. Tambah Produk\n";
                cout << "2. Lihat Daftar Produk\n";
                cout << "3. Update Stok Masuk\n";
                cout << "4. Cetak Laporan Harian\n";
                cout << "0. Kembali\n";
                cout << "Pilih: ";
                cin >> choice;

                switch (choice) {
                    case 1: addProduct(inventory); break;
                    case 2: viewProducts(inventory); break;
                    case 3: updateStock(inventory); break;
                    case 4: printReport(totalSales, totalTransactions); break;
                    case 0: cout << "Kembali ke menu utama...\n"; break;
                    default: cout << "Pilihan tidak valid!\n"; break;
                }
            } while (choice != 0);
        } else if (role == 2) { // Staff
            do {
                cout << "\nMenu Staff:\n";
                cout << "1. Proses Penjualan\n";
                cout << "2. Cek Harga Produk\n";
                cout << "3. Cek Stok Produk\n";
                cout << "4. Lihat Stok Menipis\n";
                cout << "0. Kembali\n";
                cout << "Pilih: ";
                cin >> choice;

                switch (choice) {
                    case 1: processSale(inventory, totalSales, totalTransactions); break;
                    case 2: checkPrice(inventory); break;
                    case 3: checkStock(inventory); break;
                    case 4: viewLowStock(inventory); break;
                    case 0: cout << "Kembali ke menu utama...\n"; break;
                    default: cout << "Pilihan tidak valid!\n"; break;
                }
            } while (choice != 0);
        } else if (role == 0) {
            cout << "Keluar dari program...\n";
        } else {
            cout << "Pilihan tidak valid!\n";
        }
    } while (role != 0);

    return 0;
}
