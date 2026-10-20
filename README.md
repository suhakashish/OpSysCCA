# Linux File System Monitoring and Alert System

## Overview
A Linux-based file system monitoring application that watches
a user-selected directory and detects file creation, 
modification, and deletion events in real-time using 
the Linux inotify API.

## Project Structure
file-monitor/
├── src/
│ └── monitor.c # Core monitoring logic
├── include/
│ └── monitor.h # Header file
├── logs/
│ └── monitor.log # Auto-generated event log
├── Makefile # Build configuration
└── README.md # Project documentation

## Requirements
- Linux OS (or WSL on Windows)
- GCC Compiler
- GNU Make

## Installation & Usage

### 1. Compile
```bash
make
```

### 2. Run
```bash
./monitor <directory_path>
```

### 3. Example
```bash
./monitor /home/suha/testfolder
```

## Features
- Real-time file monitoring using inotify
- Detects CREATE, MODIFY, DELETE events
- Terminal alerts with timestamps
- Persistent logging to logs/monitor.log

## Technologies Used
- Language: C
- API: Linux inotify
- Build: GNU Make

## Author
Suha
BMS Institute of Technology & Management
Operating Systems - CCA Project