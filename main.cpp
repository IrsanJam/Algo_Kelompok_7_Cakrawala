#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Struktur produk
struct Product {
    string name;
    double price;
    int stock;
};

// Fungsi untuk menampilkan produk
void displayProducts(const vector<Product>& products) {
    cout << "\n=== Daftar Produk ===\n";
    for (size_t i = 0; i < products.size(); ++i) {
        cout << i + 1 << ". " << products[i].name << " - Rp" << products[i].price 
             << " (Stok: " << products[i].stock << ")\n";
    }
}

// Fungsi untuk memilih produk untuk dipublikasikan
void publishToECommerce(const vector<Product>& products) {
    int choice;
    cout << "\nMasukkan nomor produk yang ingin dipublikasikan: ";
    cin >> choice;

    if (choice < 1 || choice > products.size()) {
        cout << "Pilihan tidak valid.\n";
        return;
    }

    cout << "\n=== Pilih Platform E-Commerce ===\n";
    cout << "1. Tokopedia\n2. Shopee\n3. Bukalapak\n4. Lazada\n";
    int platformChoice;
    cout << "Pilih platform: ";
    cin >> platformChoice;

    string platform;
    switch (platformChoice) {
        case 1: platform = "Tokopedia"; break;
        case 2: platform = "Shopee"; break;
        case 3: platform = "Bukalapak"; break;
        case 4: platform = "Lazada"; break;
        default: cout << "Platform tidak valid.\n"; return;
    }

    cout << "\nProduk \"" << products[choice - 1].name << "\" berhasil dipublikasikan ke " << platform << ".\n";
}

// Fungsi untuk memilih metode pembayaran
void choosePaymentMethod() {
    cout << "\n=== Metode Pembayaran ===\n";
    cout << "1. QRIS\n2. GoPay\n3. OVO\n4. Dana\n";
    int paymentChoice;
    cout << "Pilih metode pembayaran: ";
    cin >> paymentChoice;

    switch (paymentChoice) {
        case 1: cout << "Anda memilih pembayaran melalui QRIS.\n"; break;
        case 2: cout << "Anda memilih pembayaran melalui GoPay.\n"; break;
        case 3: cout << "Anda memilih pembayaran melalui OVO.\n"; break;
        case 4: cout << "Anda memilih pembayaran melalui Dana.\n"; break;
        default: cout << "Metode pembayaran tidak valid.\n";
    }
}

// Fungsi untuk memesan produk
void orderProduct(vector<Product>& products) {
    int choice, quantity;
    cout << "\nMasukkan nomor produk yang ingin Anda beli: ";
    cin >> choice;

    if (choice < 1 || choice > products.size()) {
        cout << "Pilihan tidak valid.\n";
        return;
    }

    cout << "Masukkan jumlah yang ingin dibeli: ";
    cin >> quantity;

    if (quantity > products[choice - 1].stock) {
        cout << "Stok tidak mencukupi. Stok tersedia: " << products[choice - 1].stock << "\n";
    } else {
        products[choice - 1].stock -= quantity;
        cout << "Anda telah memesan " << quantity << " unit " << products[choice - 1].name << "\n";
        if (products[choice - 1].stock < 5) {
            cout << "Peringatan: Stok produk \"" << products[choice - 1].name << "\" hampir habis!\n";
        }
        choosePaymentMethod(); // Memilih metode pembayaran setelah memesan produk
    }
}

// Fungsi untuk menampilkan inventaris
void displayInventory(const vector<Product>& products) {
    cout << "\n=== Inventaris Produk ===\n";
    for (const auto& product : products) {
        cout << "Produk: " << product.name 
             << ", Stok: " << product.stock 
             << ", Harga: Rp" << product.price << "\n";
    }
}

// Fungsi untuk mengecek stok rendah
void checkLowStock(const vector<Product>& products) {
    cout << "\n=== Peringatan Stok Rendah ===\n";
    for (const auto& product : products) {
        if (product.stock < 5) {
            cout << product.name << " hanya tersisa " << product.stock << " unit.\n";
        }
    }
}

int main() {
    // Daftar produk
   vector<Product> products = {
        {"Beras", 50000, 10},
        {"Mie", 75000, 3},
        {"Kopi", 100000, 1},
        {"Susu", 100000, 1}
    };


    int choice;
    do {
        cout << "\n=== Menu Utama ===\n";
        cout << "1. Lihat Produk\n2. Pesan Produk\n3. Pilih Metode Pembayaran\n";
        cout << "4. Lihat Inventaris\n5. Cek Stok Rendah\n6. Publikasi ke E-Commerce\n0. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> choice;

        switch (choice) {
            case 1: displayProducts(products); break;
            case 2: orderProduct(products); break;
            case 3: choosePaymentMethod(); break;
            case 4: displayInventory(products); break;
            case 5: checkLowStock(products); break;
            case 6: publishToECommerce(products); break;
            case 0: cout << "Keluar dari program.\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (choice != 0);

    return 0;
}


