import serial
import time

# ==========================================
# KONFIGURASI
# ==========================================
PORT = 'COM6'  # Sesuaikan dengan port Arduino Anda
BAUD_RATE = 9600

print("======================================================")
print("  MEMULAI AUTOMATED QA & EDGE CASE TESTING (C-PURE)   ")
print("======================================================")

try:
    ser = serial.Serial(PORT, BAUD_RATE, timeout=1)
    time.sleep(2) # Tunggu Arduino Reset
    print(f"[OK] Berhasil terhubung ke {PORT}\n")
except Exception as e:
    print(f"[ERROR] Gagal membuka {PORT}. Tutup Serial Monitor!")
    exit()

# ==========================================
# DAFTAR SKENARIO TEST CASE (TC)
# Format: ("Nama Skenario", ["Input1", "Input2", ...])
# ==========================================
scenarios = [
    # --- PENGUJIAN UI & STATE KOSONG ---
    ("TC-01 [UI]: Input Karakter di Menu Angka (Mencegah Infinite Loop)", ["x"]),
    ("TC-02 [UI]: Pilihan Menu Out-of-Bounds (Pilih menu 9)", ["9"]),
    ("TC-03 [DELETE]: Menghapus saat database kosong", ["6", "1"]),
    ("TC-04 [FIND]: Mencari saat database kosong", ["7", "1"]),

    # --- PENGUJIAN MENU 1: TAMBAH BARANG ---
    ("TC-05 [ADD]: Tambah Barang Normal (ID:1, Tersedia)", 
     ["1", "1", "Resistor", "0", "1", "100", "LaciA", "TimA", "LabEE"]),
    
    ("TC-06 [ADD]: Tambah Barang dengan Status Habis (Cek bypass stok)", 
     ["1", "2", "Kapasitor", "0", "0", "LaciB", "TimB", "LabEE"]),
     
    ("TC-07 [ADD]: Penolakan ID Duplikat (Memaksa masuk ID 1 lagi)", 
     ["1", "1"]),

    # --- PENGUJIAN MENU 2 & 3: DISPLAY ---
    ("TC-08 [DISPLAY ALL]: Tampilkan Seluruh Data (Verifikasi memory alignment)", 
     ["2"]),
    
    ("TC-09 [DISPLAY FILTER]: Kategori Out-of-Bounds (Pilih Kategori 5)", 
     ["3", "5"]),
     
    ("TC-10 [DISPLAY FILTER]: Kategori Valid Tapi Kosong (Cari kategori 1/Alat)", 
     ["3", "1"]),

    # --- PENGUJIAN MENU 4: UPDATE STOK ---
    ("TC-11 [STOCK]: Update ID yang tidak ada di sistem (ID 99)", 
     ["4", "99"]),
     
    ("TC-12 [STOCK]: Kurangi stok melebihi jumlah saat ini (ID 1, Kurang 500)", 
     ["4", "1", "2", "500"]),
     
    ("TC-13 [STOCK]: Eksploitasi Underflow Negatif (ID 1, Tambah -5)", 
     ["4", "1", "1", "-5"]),

    # --- PENGUJIAN MENU 5: UPDATE STATUS ---
    ("TC-14 [STATUS]: Update ID yang tidak ada (ID 99)", 
     ["5", "99"]),
     
    ("TC-15 [STATUS]: Masukkan status Out-of-Bounds (Status 9 lalu 2)", 
     ["5", "1", "9", "2"]),

    # --- PENGUJIAN MENU 6 & 7: DELETE & FIND ---
    ("TC-16 [FIND]: Verifikasi data sebelum dihapus (Cari ID 2)", 
     ["7", "2"]),
     
    ("TC-17 [DELETE]: Menghapus Head/Node (Hapus ID 2)", 
     ["6", "2"]),
     
    ("TC-18 [FIND]: Cari Barang (ID 2) yang baru saja dihapus", 
     ["7", "2"]),

    # --- PENGUJIAN MENU 8: SAVE & EXIT ---
    ("TC-19 [EXIT]: Keluar sistem dan memicu Save EEPROM", 
     ["8"])
]

# ==========================================
# MESIN EKSEKUSI
# ==========================================
for name, inputs in scenarios:
    print(f"\n>>> MENJALANKAN: {name}")
    print("-" * 50)
    for val in inputs:
        time.sleep(0.4)
        while ser.in_waiting > 0:
            line = ser.readline().decode('utf-8', errors='ignore').strip()
            if line: print(f"[Arduino] {line}")

        print(f"[Python] ---> Mengirim: {val}")
        ser.write(f"{val}\n".encode())
        time.sleep(0.4) 

time.sleep(1)
while ser.in_waiting > 0:
    line = ser.readline().decode('utf-8', errors='ignore').strip()
    if line: print(f"[Arduino] {line}")

ser.close()
print("\n======================================================")
print("                 PENGUJIAN SELESAI                    ")
print("======================================================")