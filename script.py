import serial
import time

# Konfigurasi Serial (Sesuaikan dengan port di VS Code Anda)
PORT = 'COM6' 
BAUD_RATE = 9600

print("==================================================")
print("  MEMULAI STRESS TEST & AUTO-SAVE (C-PURE)        ")
print("  [MODE: MURNI UJI KAPASITAS -> SIMPAN OTOMATIS]  ")
print("==================================================")

try:
    ser = serial.Serial(PORT, BAUD_RATE, timeout=0.5)
    time.sleep(2) # Menunggu Arduino selesai proses booting
    print(f"[OK] Berhasil terhubung ke {PORT}\n")
except Exception as e:
    print(f"[ERROR] Gagal membuka port {PORT}. Pastikan Serial Monitor di VS Code SUDAH DITUTUP!")
    exit()

count = 1
fase_stress_testing = True 

while True:
    try:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8', errors='ignore').strip()
            
            if not line:
                continue

            print(f"[Arduino] {line}")
            
            # --- PENANGANAN MENU UTAMA YANG KETAT ---
            if "Masukkan nomor menu" in line:
                if fase_stress_testing:
                    print(">>> [BOT] Mengetik: 1 (Tambah Barang)")
                    ser.write(b"1\n") 
                else:
                    print(">>> [BOT] Mengetik: 3 (Simpan ke EEPROM)")
                    ser.write(b"3\n") 
            
            # --- FASE 1: STRESS TEST (INPUT DATA) ---
            elif fase_stress_testing:
                if "Masukkan ID Barang" in line:
                    ser.write(f"{count}\n".encode())
                    
                elif "Masukkan Nama Barang" in line:
                    ser.write(f"Komp_{count}\n".encode())
                    
                elif "Masukkan Kategori" in line:
                    ser.write(b"0\n") 
                    
                elif "Masukkan Jumlah Stok" in line:
                    ser.write(b"50\n")
                    
                elif "Masukkan Lokasi Penyimpanan" in line:
                    ser.write(b"Laci_Lab\n") 
                    
                elif "Masukkan Status" in line:
                    ser.write(b"1\n") 
                    
                elif "Masukkan PIC" in line:
                    ser.write(b"Bot\n") 
                    
                elif "Masukkan Pemilik Barang" in line:
                    ser.write(b"Tim_EE\n") 
                    
                elif "berhasil ditambahkan" in line:
                    print(f"---> [SUKSES] Barang ke-{count} masuk ke SRAM!\n")
                    count += 1
                    
                elif "sudah ada" in line:
                    print(f"---> [SKIP] ID {count} sudah ada. Melompat...\n")
                    count += 1 
                    
                # --- DETEKSI PENUH & PINDAH FASE ---
                elif "Kapasitas memori hampir habis" in line or "Tidak dapat menyimpan data lebih dari ini" in line:
                    print("\n[!] BATAS TERCAPAI! MENGUBAH MODE BOT KE AUTO-SAVE...\n")
                    fase_stress_testing = False
                    
                    # PENTING: Bersihkan kabel USB dari sisa tembakan angka sebelumnya (Mencegah Menu 4/5 terpencet)
                    ser.reset_output_buffer() 

            # --- FASE 2: SELESAI ---
            if "tersimpan permanen" in line and not fase_stress_testing:
                print("\n==================================================")
                print("             STRESS TEST SELESAI                  ")
                print("==================================================")
                ser.close()
                break

    except KeyboardInterrupt:
        print("\n[!] Stress test dihentikan secara manual.")
        ser.close()
        break
