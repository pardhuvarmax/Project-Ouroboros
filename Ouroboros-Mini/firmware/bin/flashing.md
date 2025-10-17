# Firmware Upload Guide for OuroMini (Ouroboros Mini)

The OuroMini (Ouroboros Mini) requires firmware or code to unlock its wireless capabilities. This guide covers three methods to upload firmware: OTA/SD Card, Flash Download Tool, and Arduino IDE. These methods suit both beginners and advanced users working with the mini prototype.

⚠️ **Note:** Always download firmware and sketches from the OuroMini repository.

---

## Method 1: Update Firmware via OTA or SD Card

If your OuroMini is running its main firmware, use the built-in update feature via Over-The-Air (OTA) or SD card. This method is ideal for quick, computer-free updates using the TFT display.

### What You’ll Need
- Working OuroMini with main firmware and functional TFT display.  
- MicroSD card (FAT32 formatted) for SD card updates.  
- `.bin` firmware file from the repository.  
- Wi-Fi credentials for OTA updates.  
- Computer or phone to host the firmware file for OTA.

### Steps for OTA Update

**Get the Firmware File:**
- Download the latest `.bin` file from the OuroMini GitHub repository.  
- Host it on a server or computer and note the URL (e.g., `http://192.168.1.100/firmware.bin`).  

**Connect to Wi-Fi:**
- Power on the OuroMini. Go to Wi-Fi Settings on the TFT display.  
- Select your network, enter the password using the on-screen keyboard, and connect.

**Run the OTA Update:**
- Navigate to Firmware Update menu, select OTA Update, and enter the firmware URL.  
- Press Update to download and flash. The device reboots when done.

**Check the Update:**
- Verify the new firmware version on the TFT display or Serial Monitor (115200 baud).  
- If it fails, check the URL and Wi-Fi stability, then retry.

### Steps for SD Card Update

**Prepare the SD Card:**
- Format a microSD card to FAT32.  
- Download the latest `.bin` file from the repository and rename it to `firmware.bin`.  
- Place `firmware.bin` in the SD card’s root directory and eject safely.

**Insert the SD Card:**
- Power off the OuroMini and insert the SD card.

**Run the SD Card Update:**
- Power on, go to Firmware Update, and select SD Card Update.  
- Select `firmware.bin` and press Update. The device reboots after flashing.

**Check the Update:**
- Confirm the firmware version on the TFT display or Serial Monitor.  
- The file may be renamed (e.g., `firmware.bak`). Remove or reformat the SD card for future use.

**Tips:**
- OTA: Ensure a strong Wi-Fi signal and keep the host online.  
- SD Card: Use a reliable microSD card. Power off before inserting/removing.  
- Troubleshooting: Verify the `.bin` file, ensure FAT32 format, or check Serial Monitor for errors.

---

## Method 2: Flash a `.bin` File with Flash Download Tool

Use the Espressif Flash Download Tool to upload firmware via USB. This is suitable for initial setups or restoring a non-working OuroMini.

### What You’ll Need
- OuroMini with USB-C/micro-USB port.  
- Computer (Windows, macOS, Linux).  
- USB cable.  
- `.bin` firmware file from the OuroMini repository.  
- `.partitions` firmware file from the repository.  
- Espressif Flash Download Tool.

### Steps

**Prepare the Firmware File:**
- Download the `.bin` and `.partitions` files from the repository.

**Install the Flash Download Tool:**  
- Download and install the tool. Run as administrator on Windows.

**Connect the OuroMini:**
- Connect via USB and enter Download Mode:  
  Hold **BOOT** button, press **RESET** briefly, release both.  
- Select the correct COM port in the tool.

**Configure Flash Settings:**
- Select ESP32 chip type and Developer Mode or Download Mode.  
- Load the `.bin` file, set flash offset to `0x10000`.  
- Load the `.partitions` file, set flash offset to `0x8000`.  
- Set SPI Speed to 40 MHz, SPI Mode to DIO.  
- Check the `.bin` and `.partitions` file boxes.

**Flash the Firmware:**
- Click **START**. Wait for “FINISH” or “Download Complete” (1–2 minutes).

**Reset and Verify:**
- Power cycle the OuroMini. Check the TFT display or Serial Monitor for the new firmware version.  
- If it fails, verify COM port, offset, or Download Mode.

**Tips:**
- Install USB-to-serial drivers (e.g., CP2102, CH340) if needed.  
- Verify the `.bin` file matches your hardware.  
- Try a different USB cable/port or lower SPI Speed (20 MHz) if flashing fails.

---

## Method 3: Upload Sketch via Arduino IDE

Compile and upload the OuroMini sketch for customization. This method requires specific setup for the 4MB or 16MB ESP32 versions used in the mini.

### What You’ll Need
- OuroMini with USB-C/micro-USB port.  
- Computer with Arduino IDE (2.x or 1.8.x).  
- USB cable.  
- OuroMini sketch, library ZIP, and `platform.txt` from the repository.

### Steps

**Install Arduino IDE and ESP32 Board Package:**
- Install Arduino IDE.  
- Go to **Tools > Board > Boards Manager**, search “esp32,” and install **esp32 by Espressif Systems** (version 2.0.10).

**Replace platform.txt:**
- Download `platform.txt` from the repository.  
- Replace the file in:  
  - Windows: `C:\Users\<YOUR_USERNAME>\AppData\Local\Arduino15\packages\esp32\hardware\esp32\2.0.10`  
  - macOS: `~/Library/Arduino15/packages/esp32/hardware/esp32\2.0.10`  
  - Linux: `~/.arduino15/packages/esp32/hardware/esp32\2.0.10`  
- Back up the original.

**Replace Library Files:**
- Download the library ZIP from the repository and unzip it.  
- Replace existing library folders in:  
  - Windows: `C:\Users\<YOUR_USERNAME>\Documents\Arduino\libraries`  
  - macOS: `~/Documents/Arduino/libraries`  
  - Linux: `~/Arduino/libraries`  
- Restart the Arduino IDE.

**Download and Open Sketch:**
- Download the `.ino` sketch from the repository and open it in the IDE.

**Configure Arduino IDE Settings:**
- Connect the OuroMini via USB.  
- Select **Tools > Board > ESP32 Dev Module** and the correct Port.  
- Configure based on flash size:  
  - **4MB ESP32:** Partition Scheme: Rainmaker, Huge APP, or Minimal SPIFFS. Flash Size: 4MB.  
  - **16MB ESP32:** Partition Scheme: 16MB Flash (3MB APP/9.9MB FATFS). Flash Size: 16MB.  
- Optional: Set Upload Speed to 921600, CPU Frequency to 240 MHz.

**Compile and Upload:**
- Click **Verify** to compile. Fix any errors.  
- Click **Upload**. Enter Download Mode if prompted (hold **BOOT**, press **RESET**, release both).  
- Wait for “Done uploading.”

**Verify Upload:**
- Check the TFT display or Serial Monitor (115200 baud).  
- If it fails, verify settings, port, or Download Mode.

**Tips:**
- Ensure libraries match the ZIP file to avoid conflicts.  
- Install USB-to-serial drivers if the port isn’t detected.  
- Lower upload speed to 115200 or try another cable/port if needed.

> refer this, or alternatively [ESP32-DIV](https://github.com/cifertech/ESP32-DIV/tree/main) Wiki of **Cifertech**