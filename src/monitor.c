#include "../include/monitor.h"

// Get current timestamp
void get_timestamp(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", t);
}

// Log event to file
void log_event(const char *event_type, const char *filename) {
    char timestamp[64];
    get_timestamp(timestamp, sizeof(timestamp));

    FILE *log = fopen(LOG_FILE, "a");
    if (log == NULL) {
        perror("Failed to open log file");
        return;
    }

    fprintf(log, "[%s] EVENT: %-12s | FILE: %s\n",
            timestamp, event_type, filename);
    fclose(log);
}

// Print alert to terminal
void print_alert(const char *event_type, const char *filename) {
    char timestamp[64];
    get_timestamp(timestamp, sizeof(timestamp));

    printf("\n🔔 ALERT!\n");
    printf("   Time      : %s\n", timestamp);
    printf("   Event     : %s\n", event_type);
    printf("   File      : %s\n", filename);
    printf("----------------------------------\n");
}

// Core monitoring function
void monitor_directory(const char *path) {
    int fd, wd;
    char buffer[EVENT_BUF_LEN];

    // Initialize inotify
    fd = inotify_init();
    if (fd < 0) {
        perror("inotify_init failed");
        exit(EXIT_FAILURE);
    }

    // Add watch on directory
    wd = inotify_add_watch(fd, path,
         IN_CREATE | IN_MODIFY | IN_DELETE);

    if (wd < 0) {
        perror("inotify_add_watch failed");
        exit(EXIT_FAILURE);
    }

    printf("\n✅ Monitoring started on: %s\n", path);
    printf("   Watching for: CREATE | MODIFY | DELETE\n");
    printf("   Logs saved to: %s\n", LOG_FILE);
    printf("----------------------------------\n");
    printf("Press Ctrl+C to stop.\n\n");

    // Event loop
    while (1) {
        int length = read(fd, buffer, EVENT_BUF_LEN);
        if (length < 0) {
            perror("read failed");
            break;
        }

        int i = 0;
        while (i < length) {
            struct inotify_event *event =
                (struct inotify_event *)&buffer[i];

            if (event->len) {
                if (event->mask & IN_CREATE) {
                    print_alert("CREATED", event->name);
                    log_event("CREATED", event->name);
                }
                if (event->mask & IN_MODIFY) {
                    print_alert("MODIFIED", event->name);
                    log_event("MODIFIED", event->name);
                }
                if (event->mask & IN_DELETE) {
                    print_alert("DELETED", event->name);
                    log_event("DELETED", event->name);
                }
            }

            i += EVENT_SIZE + event->len;
        }
    }

    // Cleanup
    inotify_rm_watch(fd, wd);
    close(fd);
}

// Main entry point
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./monitor <directory_path>\n");
        printf("Example: ./monitor /home/suha/testfolder\n");
        return 1;
    }

    monitor_directory(argv[1]);
    return 0;
}