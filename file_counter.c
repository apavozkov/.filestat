#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

int main() {
  DIR *dir; // Определяем указатели на структуры для сбора инфы
  struct dirent *entry;
  struct statfileStat;

  dir = opendir("."); // Открываем текущую директорию
  if (dir == NULL) {
    printf("Не удалось открыть директорию"); // Если не удалось открыть, то выбить с ошибкой
    return 1;
  }

  // Делаем счётчики
  int file_count = 0;
  int dir_count = 0;
  int other_count = 0;

  while ((entry = readdir(dir)) != NULL) { // Перебираем все записи в директории, пока они есть
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) { // Игнорируем текущую и родительскую директории
      continue;
    }

    if (stat(entry->d_name, &fileStat) < 0) { // Получаем информацию об указанной записи
      printf("Не удалось получить информацию о файле"); 
      continue;
    }

    // Через макросы sys/stat классифицируем содержимое
    if (S_ISREG(fileStat.st_mode)) { // Проверяем, является ли файлом
      file_count++;
    } else if (S_ISDER(fileStat.st_mode)) { // Проверяем, является ли директорией
      dir_count++;
    } else { // Записываем, если не является обычным файлом или директорией
      other_count++;
    }
  }

  closedir(dir); 

  // Выводим результат
  printf("Обычных файлов: %d\n", file_count);
  printf("Директорий: %d\n", dir_count);
  printf("Других типов файлов: %d/n", other_count);

  return 0;
}
