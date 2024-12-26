# Gunakan image GCC sebagai base
FROM gcc:latest

# Set folder kerja di dalam container
WORKDIR /app

# Copy semua file dari folder proyek ke dalam container
COPY . .

# Compile kode C++ menggunakan g++
RUN g++ -o program main.cpp

# Tentukan perintah default saat container dijalankan
CMD ["./program"]
