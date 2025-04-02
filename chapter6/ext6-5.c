/*Exercise 6-5. Write a function undef that will remove a name and definition 
 from the table maintained by lookup and install.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_TABLE_SIZE (101)
#define TABLE_ENTRY_COUNT (10)

//table entry
struct entry {
        struct entry *next; // pointer to the next entry in the chain
        char *key;
        char *value;
};

//pointer table
static struct entry *hash_table[HASH_TABLE_SIZE];

//hash: compute hash value for a given string str
unsigned compute_hash(char *str) {
        unsigned hash_value = 0;

        while (*str != '\0') {
                hash_value = *str + 31 * hash_value;
                str++;
        }

        return (hash_value % HASH_TABLE_SIZE); // modulo for table size
}

//duplicate_string: create a duplicate of the given string str
char *duplicate_string(char *str) {
        char *dup = (char *)malloc(strlen(str) + 1); // +1 for null terminator

        if (dup != NULL) {
                strcpy(dup, str); // Copy string to allocated memory
        }

        return dup;
}

//search_entry: Search for an entry in the hash table by its key `key`.
struct entry *search_entry(char *key) {
        struct entry *current;

        // Traverse the linked list at the hashed index
        for (current = hash_table[compute_hash(key)];
                current != NULL;
                current = current->next) {
                if (strcmp(key, current->key) == 0) {
                        return current; // Key found
                }
        }

        return NULL; // Key not found
}

//add_entry: Add or update a key-value pair in the hash table.
struct entry *add_entry(char *key, char *value) {
        struct entry *current;
        unsigned hash_value;

        if ((current = search_entry(key)) == NULL) { 
                current = (struct entry *)malloc(sizeof(*current));
                if (current == NULL || 
                (current->key = duplicate_string(key)) == NULL) {
                        return NULL; // memory allocation failed
                }

                hash_value = compute_hash(key);
                current->next = hash_table[hash_value]; // insert
                hash_table[hash_value] = current;
        } else {
                free((void *)current->value); // free old value
        }

        if ((current->value = duplicate_string(value)) == NULL) {
                return NULL; // memory allocation failed
        }

        return current;
}

//remove_entry: Remove a key-value pair from the hash table by its key `key`.
struct entry *remove_entry(char *key) {
        struct entry *current, *prev = NULL;
        unsigned hash_value = compute_hash(key);

        // raverse the list at the hashed index
        for (current = hash_table[hash_value];
                current != NULL;
                current = current->next) {
                if (strcmp(key, current->key) == 0) { // Key found
                        if (prev == NULL) {
                                hash_table[hash_value] = current->next;
                        } else {
                                prev->next = current->next; // bypass
                        }
                        free(current->key);
                        free(current->value);
                        free(current);
                        return NULL;
                }
                prev = current;
        }

        return NULL; // key not found
}

//print_all_entries: Print all entries in the hash table.
void print_all_entries() {
    struct entry *current;
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        current = hash_table[i];
        while (current != NULL) {
            printf("%s -> %s\n", current->key, current->value);
            current = current->next;
        }
    }
}

int main(void)
{
        int i;

        struct entry *entries[TABLE_ENTRY_COUNT] = {
            (add_entry("Chatgpt", "ai")),
            (add_entry("X", "social media")),
            (add_entry("Purgg", "game")),
            (add_entry("Drive", "storage")),
            (add_entry("GrandTheft", "game")),
            (add_entry("Speed", "twitch streamer"))};

        for (i = 0; i < TABLE_ENTRY_COUNT && entries[i] != NULL; i++) {
                printf("%s -> %s\n", entries[i]->key, entries[i]->value);
        }

        printf("\nRemoving Drive...\n");
        remove_entry("Drive");

        printf("\n");
        if (search_entry("Drive") != NULL) {
                printf("Error: Key still exists in the table\n");
        } else {
                printf("Success: Key removed from table\n");
                print_all_entries(); 
        }

        return 0;
}
