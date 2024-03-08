#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

void listHiddenFiles(const char *dir_path) {
    DIR *directory;
    struct dirent *entry;

    // Buka direktori
    directory = opendir(dir_path);
    if (directory == NULL) {
        perror("Error opening directory");
        return;
    }

    // Baca setiap entri di dalam direktori
    while ((entry = readdir(directory)) != NULL) {
        // Periksa jika nama file dimulai dengan "."
        if (entry->d_name[0] == '.' && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            printf("Hidden file: %s/%s\n", dir_path, entry->d_name);
        }

        // Jika ini adalah direktori dan bukan "." atau "..", rekursif masuk ke dalamnya
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            char path[1024];
            snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);
            listHiddenFiles(path);
        }
    }

    // Tutup direktori
    closedir(directory);
}

int main() {
    listHiddenFiles("/");
    return EXIT_SUCCESS;
}
