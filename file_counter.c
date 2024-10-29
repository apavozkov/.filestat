#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

int main() {
  DIR *dir;
  struct dirent *entry;
  struct statfileStat;

  dir = opendir(".");
  if (dir == NULL) {
    printf("Не удалось открыть директорию");
    return 1;
  }

  int file_count = 0;
  int dir_count = 0;
  int other_count = 0;

  while ((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    }

    if (stat(entry->d_name, &fileStat) < 0) {
      printf("Не удалось получить информацию о файле");
      continue;
    }

    if (S_ISREG(fileStat.st_mode)) {
      file_count++;
    } else if (S_ISDER(fileStat.st_mode)) {
      dir_count++;
    } else {
      other_count++;
    }
  }

  closedir(dir);

  printf("Обычных файлов: %d\n", file_count);
  printf("Директорий: %d\n", dir_count);
  printf("Других типов файлов: %d/n", other_count);

  return 0;
}
