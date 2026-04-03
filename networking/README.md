# 🌐 Networking projects

A collection of network tools written in C. This repository contains network analysis and diagnostic utilities, developed using sockets and the ICMP protocol.

> ⚠️Note: These tools are written for Windows.


## 🛠 Projects:

* **pscan (port scanning):** A tool for identifying open ports on a remote host. It uses TCP sockets to attempt to connect to a user-specified port range.
    * **Utility:** Security audit and firewall configuration.

* **lping (ICMP ping tool):** A custom implementation of the ping command. It sends ICMP "Echo Request" packets to an IP address and waits for an "Echo Reply" to verify the host's reachability.
  * **Utility:** Network diagnostics and latency measurement.
  * **⚠️Requirements:** lping **requires Admin privileges**.

## 📚 Libraries & Dependencies:

Both projects are developed for **Windows** systems and use native networking APIs. Note that each project uses a specific subset of these headers.

### Networking Core
* `winsock2.h`: The core library for network programming on Windows. It's required to manage sockets, IP addresses and protocols (TCP/ICMP).
* `ws2tcpip.h`: Winsock2 extension that includes modern definitions for IP address handling (essential for features like getaddrinfo and IPv6 support).

### Standard C Libraries
* `stdio.h` / `stdlib.h`: For managing input/output streams and dynamic memory allocation.
* `unistd.h`: Provides access to POSIX operating system APIs (such as the sleep() function to set a timeout).
* `limits.h`: Defines properties and limits of the various types of variables.
* `string.h`: For manipulating strings and data buffers.


## 🚀 How to compile and run (GCC):

1a. **In Dev-C++, you compile the file first, but you have to link `winsock2` library. Go to compilation options and type this: `-lws2_32`.**

1b. **If you prefer command line type these:**
- For pscan

```bash
    gcc pscan.c -o pscan.exe -lws2_32
```
- For lping

```bash
    gcc lping.c -o lping.exe -lws2_32
```

2. **Then in the command prompt or PowerShell, use this commands:**

- For pscan

```bash
    C://your_path/pscan.exe <IP> <start_port> <end_port>
```

- For lping

```bash
    C://your_path/lping.exe <IP>
```

Both have help commands that are: `?`, `h`, `help`, `-h`, `--help` and `/?`.

---
Alternatively, you can add the folder containing pscan and lping to your `PATH`, which will simplify the command:

```bash
    pscan <IP> <start_port> <end_port>
```

```bash
    lping <IP>
```

## Example:
```bash
    pscan 127.0.0.1 20 80
```

```bash
    lping 8.8.8.8
```

## 🛡️ Windows Smart Screen detection:
Since these programs perform network operations (like port scanning and sending ICMP packets), **Windows Defender** or **SmartScreen** might flag or block the executables.

### How to run:
* **Admin Privileges:** These programs require Administrative privileges to create raw sockets. Run your terminal as Administrator.

* **Bypassing SmartScreen:** If Windows blocks the execution, click on "More info" and then "Run anyway".

* **Digital Signing:** If the program is still blocked, you may need to create a **self-signed** certificate to sign your executables. You can do this using the `New-SelfSignedCertificate` command in PowerShell and the `signtool.exe` utility (Windows SDK). For more information about the creation of a certificate, visit the official [Microsoft Guide on New-SelfSignedCertificate](https://learn.microsoft.com/en-us/powershell/module/pki/new-selfsignedcertificate?view=windowsserver2025-ps).
