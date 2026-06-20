import serial
import time
import sys

# ================= KONFIGURASI =================
# Sesuaikan dengan port Arduino di laptop Anda!
SERIAL_PORT = 'COM6' 
BAUD_RATE = 9600
# ===============================================

def read_output(ser, delay=0.5):
    """Membaca output dari buffer serial Arduino."""
    time.sleep(delay)
    output = ""
    while ser.in_waiting > 0:
        try:
            output += ser.read(ser.in_waiting).decode('utf-8', errors='ignore')
        except Exception:
            pass
    return output

def send_command(ser, command):
    """Mengirim input teks ke Arduino diikuti newline."""
    print(f">>> Mengirim: {command}")
    ser.write((command + '\n').encode('utf-8'))

def run_tests():
    try:
        print(f"Membuka {SERIAL_PORT} pada {BAUD_RATE} baud...")
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        
        print("Menunggu Arduino reset (2 detik)...")
        time.sleep(2) 
        
        init_out = read_output(ser, delay=1)
        
        with open("hasil_test_terbaru.txt", "w", encoding="utf-8") as f:
            f.write("=== LOG PENGUJIAN OTOMATIS ARDUINO (VERSI REVISI) ===\n")
            f.write(init_out)
            print(init_out)

            # ================= DEFINISI TESTCASE =================
            test_cases = [
                {
                    "nama": "TC1: Menambah Barang Pertama (Resistor)",
                    # Urutan C: ID -> Nama -> Kategori -> Status -> Lokasi -> PIC -> Pemilik
                    "inputs": ["1", "101", "Resistor", "0", "1", "Rak_A", "Agus", "Lab"]
                },
                {
                    "nama": "TC2: Menampilkan Semua Barang",
                    "inputs": ["2"]
                },
                {
                    "nama": "TC3: Mencari Barang (ID 101)",
                    "inputs": ["7", "101"]
                },
                {
                    "nama": "TC4: Update Stok Barang (ID 101, tambah 20)",
                    # Urutan C: Menu 4 -> ID 101 -> Opsi 1 (Tambah) -> Jumlah 20
                    "inputs": ["4", "101", "1", "20"]
                },
                {
                    "nama": "TC5: Tampilkan Berdasarkan Kategori (Komponen)",
                    "inputs": ["3", "0"]
                },
                {
                    "nama": "TC6: Menambah Barang Kedua (Menguji Linked List)",
                    # Urutan C: ID -> Nama -> Kategori -> Status -> Lokasi -> PIC -> Pemilik
                    "inputs": ["1", "102", "Kapasitor", "0", "1", "Rak_B", "Budi", "Lab"]
                },
                {
                    "nama": "TC7: Tampilkan Semua Barang (Verifikasi 2 barang)",
                    "inputs": ["2"]
                },
                {
                    "nama": "TC8: Hapus Barang (ID 101)",
                    "inputs": ["6", "101"]
                },
                {
                    "nama": "TC9: Keluar dari sistem (Trigger fungsi save)",
                    "inputs": ["8"]
                }
            ]
            # =====================================================

            for tc in test_cases:
                print(f"\n--- Menjalankan {tc['nama']} ---")
                f.write(f"\n\n--- {tc['nama']} ---\n")
                
                for step in tc["inputs"]:
                    send_command(ser, step)
                    
                    # Waktu delay 1 detik per input agar Arduino sempat memproses dan Serial tidak saling tabrak
                    out = read_output(ser, delay=1.0) 
                    
                    print(out, end="")
                    f.write(f">>> Input: {step}\n")
                    f.write(out)
                
                time.sleep(1)

        ser.close()
        print("\n[SUKSES] Pengujian selesai! Port serial ditutup.")
        print("Silakan buka file 'hasil_test_terbaru.txt' dan salin isinya ke saya.")

    except serial.SerialException as e:
        print(f"Error membuka port Serial: {e}")
        print("Pastikan Arduino dicolokkan, port benar, dan Serial Monitor Arduino IDE sedang DITUTUP.")
    except KeyboardInterrupt:
        print("\nPengujian dibatalkan oleh pengguna.")
        if 'ser' in locals() and ser.is_open:
            ser.close()

if __name__ == '__main__':
    run_tests()