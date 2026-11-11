# 🐧 Linux File Analysis and Inspection Tool

A menu-driven **Bash shell application** built for the Linux Programming Lab.
Helps users analyze and inspect files efficiently using built-in Linux command-line utilities.

---

## 📋 Features

| # | Feature | Linux Command | What It Does |
|---|---------|--------------|--------------|
| 1 | **Identify File Type** | `file` | Detects the real file type, MIME type, and character encoding |
| 2 | **File Info & Permissions** | `ls -lh`, `stat` | Shows permissions, owner, size, and all timestamps |
| 3 | **Extract Readable Strings** | `strings` | Pulls out human-readable text from any file |
| 4 | **Calculate Hash** | `sha256sum`, `md5sum`, `sha1sum` | Generates SHA-256, MD5, and SHA-1 fingerprints of the file |
| 5 | **Search Text Pattern** | `grep` | Searches inside a file with 4 modes (normal, case-insensitive, line numbers, count) |
| 6 | **Change Loaded File** | — | Switch to a different file without restarting the tool |
| 7 | **Exit** | — | Cleanly exits the program |

---

## ✨ Key Highlights

- **File Memory** — Load a file once and reuse it across all features without retyping the path
- **Smart Prompts** — Shows your current directory and a path example when asking for a file
- **Permission Breakdown** — Explains what each part of `-rwxr-xr--` means in plain English
- **Multiple Hash Algorithms** — SHA-256, MD5, and SHA-1 shown together for comparison
- **4 Search Modes** — Normal, case-insensitive, line numbers, count-only
- **Colored Output** — Color-coded terminal output for easy reading
- **Input Validation** — Checks if the file exists before running any command

---

## 📁 Project Structure

```
file_analysis_tool/
├── file_tool.sh              ← Main script (entire program)
├── README.md                 ← This file
└── sample_files/
    ├── sample.txt            ← Sample plain text file for testing
    └── sample_script.sh      ← Sample shell script file for testing
```

---

## ▶️ How to Run

### Requirements
- Linux OS (Kali, Ubuntu, Fedora, etc.) or WSL on Windows
- Bash shell — pre-installed on all Linux systems
- `strings` command — install it if missing:
  ```bash
  sudo apt install binutils -y      # Kali / Ubuntu / Debian
  sudo yum install binutils -y      # Fedora / RHEL
  ```
- All other tools (`file`, `stat`, `ls`, `grep`) are built into Linux — no install needed

---

### Step 1 — Open a terminal and navigate to the project folder
```bash
cd ~/Desktop/file_analysis_tool
```

### Step 2 — Make the script executable *(one time only)*
```bash
chmod +x file_tool.sh
```

### Step 3 — Run the tool
```bash
./file_tool.sh
```

---

## 🖥️ Menu Preview

```
  ╔══════════════════════════════════════════════╗
  ║    Linux File Analysis & Inspection Tool     ║
  ╠══════════════════════════════════════════════╣
  ║                                              ║
  ║   1.  Identify File Type                     ║
  ║   2.  Display File Info & Permissions        ║
  ║   3.  Extract Readable Strings               ║
  ║   4.  Calculate Hash                         ║
  ║   5.  Search Text Pattern                    ║
  ║   6.  Change Loaded File                     ║
  ║   7.  Exit                                   ║
  ║                                              ║
  ╚══════════════════════════════════════════════╝

  Loaded File : /home/kali/Desktop/sample_files/sample.txt
```

---

## 💡 Usage Tips

- When asked for a file path, always use the **full path**:
  ```
  /home/kali/Desktop/image.png        ✅ Correct
  image.png                           ❌ Wrong (no full path)
  /image.png                          ❌ Wrong (starts from system root)
  ```
- After loading a file, just **press Enter** when prompted to reuse it for the next feature
- Use **Option 4** anytime you want to switch to a different file
- Test the tool using the included sample files in `sample_files/`

---

## 🧪 Sample Files — What They're For

| File | Type | Best for testing |
|------|------|-----------------|
| `sample.txt` | Plain ASCII text | All 3 features — gives clean, readable output |
| `sample_script.sh` | Bash shell script | Feature 1 shows it as "shell script" not just "text" |

---

## 🚀 Phase 2 — Planned Features

| Feature | Tool / Algorithm |
|---------|-----------------|
| AES Encryption | `openssl aes-256-cbc` |
| DES Encryption | `openssl des` |

---

## 👤 Author

**Linux Programming Lab Project**
Built with Bash scripting — using only built-in Linux utilities.

---

## ⚡ Quick Start Commands (Copy & Paste)

Exact commands to get the tool running from scratch on Kali Linux:

```bash
cd ~/Desktop
cd file_analysis_tool
chmod +x file_tool.sh
./file_tool.sh
```
