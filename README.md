# WinIns – Windows 11 HDD Installer Creator

**WinIns** is a simple helper tool to create a fast, bootable Windows 11 installer directly on a hard drive or SSD from Linux. No USB drive required — everything runs from your internal drives, making installations much faster.

---

## Features

- Creates a GPT partition and formats it as NTFS.
- Mounts the Windows 11 ISO and copies all files to the device.
- Makes the device bootable using `ms-sys`.
- Fully automated with colored terminal messages.
- Optional custom partition size.

---

## Requirements

- Linux (tested on Arch Linux)
- `sudo` privileges
- `parted`, `ntfs-3g` (for NTFS formatting)
- A valid Windows 11 ISO file

---

## Installation

### Clone this repository if you haven't
```bash
git clone https://github.com/darkyboys/winins
cd winins
```

### 1. Build `ms-sys` automatically
The helper CLI can clone and build `ms-sys`:

```bash
git clone https://github.com/darkyboys/ms-sys
cd ms-sys
make
sudo mv ms-sys/bin/ms-sys /usr/local/bin/winins-ms-sys
````

### 2. Build WinIns

```bash
g++ winins.cpp -o winins -std=c++17 -lstdc++fs
sudo mv winins /usr/local/bin/
```

> Note: If you alreadty have the gdbs build system installed then the commands should simply be `gdbs -mkms-sys` , `gdbs .` and `gdbs -install`.
---

## Usage

```bash
winins /path/to/Windows11.iso <device> [partition_size]
```

* `/path/to/Windows11.iso` – Path to your Windows 11 ISO file.
* `<device>` – Target device (e.g., `sdb`) to create the installer on.
* `[partition_size]` – Optional. Default: `100%` (partition occupies the full disk, Feel free to write size in GiB).

**Example:**

```bash
sudo winins ~/Downloads/Win11.iso sdb 16GiB
```

---

## Notes & Warnings

* **All data on the target device will be erased.** Make sure you choose the correct device.
* Mount points `/mnt/win11` and `/mnt/iso` are used; ensure they are free.
* Works best on internal HDDs or SSDs for faster installation speeds compared to USB drives.

---

## License

This project is open-source under the MIT License.
`ms-sys` is GPL-licensed.

---

## Author

Created by ghgltggamer
