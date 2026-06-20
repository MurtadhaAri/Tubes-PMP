import serial
import time

# Konfigurasi Serial (Sesuaikan dengan port di VS Code Anda)
PORT = 'COM6' 
BAUD_RATE = 9600

print("======================================================")
print("  MEMULAI AUTOMATED LOGICAL EDGE CASE TESTING (C-PURE)")
print("======================================================")

try:
    ser = serial.Serial(PORT, BAUD_RATE, timeout=1)
    time.sleep(2) # Menunggu Arduino selesai proses booting (Reset)
    print(f"[OK] Berhasil terhubung ke {PORT}\n")
except Exception as e:
    print(f"[ERROR] Gagal membuka port {PORT}. Pastikan Serial Monitor DITUTUP!")
    exit()

# Daftar skenario ekstrem (Tuple: Nama Skenario, List Input berurutan)
scenarios = [
    ("TC-1: Tambah Barang Normal (ID 1)", 
     ["1", "1", "Komp_A", "0", "1", "10", "Laci1", "TimA", "LabEE"]),
    
    ("TC-2: Duplicate ID Rejection (Memaksa masuk ID 1 lagi)", 
     ["1", "1"]),
    
    ("TC-3: Status Habis (ID 2, Status 0) - Cek apakah sistem sadar untuk tidak minta stok?", 
     ["1", "2", "Komp_B", "1", "0", "Laci2", "TimB", "LabEE"]),
    
    ("TC-4: Underflow Stok Negatif (Menu 4 -> ID 1 -> Tambah Stok -> Input -5)", 
     ["4", "1", "1", "-5"]),
    
    ("TC-5: Hapus Barang Gaib (Hapus ID 99 yang tidak ada)", 
     ["6", "99"]),
    
    ("TC-6: Input Menu Karakter Teks (Ketik 'abc' di menu angka)", 
     ["abc"]),
    
    ("TC-7: Menu Out of Bounds (Pilih menu angka 9)", 
     ["9"]),
    
    ("TC-8: Cari Barang (Menu 7 -> Cek ID 1)", 
     ["7", "1"]),
    
    ("TC-9: Tampilkan Semua Barang (Verifikasi Kerusakan Data)", 
     ["2"]),
    
    ("TC-10: Keluar dan Save", 
     ["8"])
]

# Eksekusi berurutan
for name, inputs in scenarios:
    print(f"\n>>> MENJALANKAN: {name}")
    print("-" * 50)
    for val in inputs:
        # Baca respon Arduino sebelumnya
        time.sleep(0.4)
        while ser.in_waiting > 0:
            line = ser.readline().decode('utf-8', errors='ignore').strip()
            if line: print(f"[Arduino] {line}")

        # Kirim input jahat
        print(f"[Python] ---> Mengirim: {val}")
        ser.write(f"{val}\n".encode())
        time.sleep(0.4) 

# Tarik sisa output terakhir sebelum ditutup
time.sleep(1)
while ser.in_waiting > 0:
    line = ser.readline().decode('utf-8', errors='ignore').strip()
    if line: print(f"[Arduino] {line}")

ser.close()
print("\n======================================================")
print("                 PENGUJIAN SELESAI                    ")
print("======================================================")