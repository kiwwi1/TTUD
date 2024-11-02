#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_CALLS 100000

typedef struct {
    char from[11];
    char to[11];
    char date[11];
    char from_time[9];
    char end_time[9];
} Call;

Call calls[MAX_CALLS];
int call_count = 0;

int is_valid_phone_number(char phone[]) {
    if (strlen(phone) != 10) return 0;
    for (int i = 0; i < 10; i++) {
        if (!isdigit(phone[i])) return 0;
    }
    return 1;
}

int time_to_seconds(char time[]) {
    int h, m, s;
    sscanf(time, "%d:%d:%d", &h, &m, &s);
    return h * 3600 + m * 60 + s;
}

void process_queries() {
    char query[256];
    int valid_phone_numbers = 1;  // Flag for ?check_phone_number
    while (scanf("%s", query) != EOF) {
        if (strcmp(query, "#") == 0) break;

        if (strcmp(query, "?check_phone_number") == 0) {
            for (int i = 0; i < call_count; i++) {
                if (!is_valid_phone_number(calls[i].from) || !is_valid_phone_number(calls[i].to)) {
                    valid_phone_numbers = 0;
                    break;
                }
            }
            printf("%d\n", valid_phone_numbers);
        } else if (strcmp(query, "?number_calls_from") == 0) {
            char phone_number[11];
            scanf("%s", phone_number);
            int count = 0;
            for (int i = 0; i < call_count; i++) {
                if (strcmp(calls[i].from, phone_number) == 0) count++;
            }
            printf("%d\n", count);
        } else if (strcmp(query, "?number_total_calls") == 0) {
            printf("%d\n", call_count);
        } else if (strcmp(query, "?count_time_calls_from") == 0) {
            char phone_number[11];
            scanf("%s", phone_number);
            int total_time = 0;
            for (int i = 0; i < call_count; i++) {
                if (strcmp(calls[i].from, phone_number) == 0) {
                    int start_time = time_to_seconds(calls[i].from_time);
                    int end_time = time_to_seconds(calls[i].end_time);
                    total_time += (end_time - start_time);
                }
            }
            printf("%d\n", total_time);
        }
    }
}

int main() {
    char command[256];

    // Read call data
    while (scanf("%s", command) != EOF) {
        if (strcmp(command, "#") == 0) break;

        if (strcmp(command, "call") == 0) {
            Call new_call;
            scanf("%s %s %s %s %s", new_call.from, new_call.to, new_call.date, new_call.from_time, new_call.end_time);
            calls[call_count++] = new_call;
        }
    }

    process_queries();

    return 0;
}
