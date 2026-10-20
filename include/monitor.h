#ifndef MONITOR_H
#define MONITOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <time.h>

// Constants
#define EVENT_SIZE      (sizeof(struct inotify_event))
#define EVENT_BUF_LEN   (1024 * (EVENT_SIZE + 16))
#define LOG_FILE        "logs/monitor.log"

// Function declarations
void monitor_directory(const char *path);
void log_event(const char *event_type, const char *filename);
void print_alert(const char *event_type, const char *filename);
void get_timestamp(char *buffer, size_t size);

#endif // MONITOR_H