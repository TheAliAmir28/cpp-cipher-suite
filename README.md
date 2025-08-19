# 🔐 C++ Cipher Suite

![C++](https://img.shields.io/badge/C%2B%2B-17-blue)
![Status](https://img.shields.io/badge/Status-Complete-brightgreen)
![License](https://img.shields.io/badge/License-MIT-green)

## 📌 Overview
A modular, console-based encryption/decryption toolkit implemented in modern C++.  
It features multiple classical ciphers (Atbash, Ong, and Scytale) behind a clean object-oriented interface, with a driver that loads messages from a data file and supports bulk encrypt/decrypt and export.

## ✨ Features
- **Pluggable design** via a `Cipher` base class with virtual `Encrypt`, `Decrypt`, `ToString`, and `FormatOutput` methods.
- **Three ciphers included:**
  - **Atbash** – monoalphabetic substitution using a reversed alphabet.
  - **Ong** – word game style transformation with dashes and “ong” rules.
  - **Scytale** – transposition cipher with a configurable integer key.
- **Batch workflow**: load many messages from a file, display them, encrypt/decrypt all, and export results.
- **Human‑readable I/O** format with a type code, encryption flag, message text, and an optional key for Scytale.

## 🧱 Architecture
- **Cipher (base)**: owns the message, tracks whether it’s encrypted, and defines the virtual API.
- **Atbash / Ong / Scytale**: implement the polymorphic API and provide a `ToString()` for labeling.
- **CipherTool**: loads a data file, maintains a `std::vector<Cipher*>`, presents a menu, and performs batch operations.
- **Driver**: a minimal `main` that instantiates `CipherTool` with a chosen data file and calls `Start()`.

## 📂 Project Structure
```
Atbash.h / Atbash.cpp
Ong.h / Ong.cpp
Scytale.h / Scytale.cpp
Cipher.h / Cipher.cpp
CipherTool.h / CipherTool.cpp
proj4.cpp               # program entry (selects which data file to load)
proj4_data1.txt         # sample data
proj4_data2.txt         # sample data
proj4_data3.txt         # sample data
proj4_data4.txt         # sample data
README.md
```

## 🗃️ Data File Format
Each line encodes one cipher instance using a **pipe** delimiter (`|`):

```
<type>|<isEncrypted>|<message>|<key?>
```

- `<type>`: `"a"` = Atbash, `"o"` = Ong, `"s"` = Scytale  
- `<isEncrypted>`: `"0"` (not encrypted) or `"1"` (encrypted)  
- `<message>`: the text payload (may include punctuation and spaces)  
- `<key?>`: for Scytale only — integer column/key; omitted for others

**Examples**
```text
a|0|If you tell the truth, you don't have to remember anything. (Mark Twain)|
o|1|Pong-e-a-cong-e bong-e-gong-i-nong-song ...|
s|0|The greatest glory in living lies not in never falling, ...|4
```

## 🛠️ Build & Run

### Compile (g++)
```bash
g++ -std=c++17 proj4.cpp CipherTool.cpp Atbash.cpp Ong.cpp Scytale.cpp Cipher.cpp -o cipher_tool
```

### Run
```bash
./cipher_tool
```

> By default, `proj4.cpp` constructs `CipherTool` with `proj4_data2.txt`.  
> To use a different input file, either edit `proj4.cpp` or add simple argument parsing.

## 📖 Program Flow
On launch, you’ll be shown a simple menu:

```
1. Display All Ciphers
2. Encrypt All Ciphers
3. Decrypt All Ciphers
4. Export all Ciphers
5. Quit
```

- **Display**: lists each message and its cipher type label.  
- **Encrypt/Decrypt**: applies the operation to *all* messages that need it.  
- **Export**: writes all items back out using each cipher’s `FormatOutput()` so they can be re‑loaded later.

## ➕ Extending
To add a new cipher:
1. Derive from `Cipher` and implement `Encrypt`, `Decrypt`, `ToString`, and `FormatOutput`.
2. Add a case in `CipherTool::LoadFile()` to construct the new type when its code appears in the data file.
3. Ensure the format stays compatible with `Export()` and your `FormatOutput()`.

## 📜 License
MIT — see `LICENSE` for details.

## 📬 Contact
**Ali Amir**  
GitHub: https://github.com/TheAliAmir28  
Email: codepirate2028@gmail.com
