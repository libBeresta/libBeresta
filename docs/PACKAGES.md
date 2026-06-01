# Пакеты libbrst

Проект libbrst поддерживает сборку дистрибутивных пакетов для различных операционных систем через CPack.

## Поддерживаемые форматы

| Формат | Система | Команда сборки | Имя файла |
|--------|---------|----------------|-----------|
| `.deb` | Linux (Debian, Ubuntu и производные) | `cpack -G DEB` | `libbrst-dev-1.0.0-amd64.deb` |
| `.pkg` | FreeBSD | `cpack -G FREEBSD` | `libbrst-dev-1.0.0.pkg` |
| `.tar.gz` | HaikuOS / любые Unix-системы | `cpack -G TGZ` | `libbrst-dev-1.0.0-amd64.tar.gz` |

## Состав пакета

Каждый пакет содержит:

- **Библиотека**: `libbrst.so` (с symlink'ами `libbrst.so.1`, `libbrst.so.1.0.0`)
- **Заголовочные файлы**: все `*.h` из директории `include/`
- **Файл pkg-config**: `libbrst.pc` для использования через `pkg-config`

## Требования

Для сборки пакетов необходимы:

- CMake >= 3.10
- Компилятор C (GCC, Clang)
- `zlib` (и `zlib1g-dev` на Debian/Ubuntu)
- `libpng` (и `libpng-dev` на Debian/Ubuntu)

## Сборка

### Все пакеты сразу

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cpack -G DEB -G FREEBSD -G TGZ
```

### Только deb-пакет (Linux)

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cpack -G DEB
```

### Только pkg-пакет (FreeBSD)

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cpack -G FREEBSD
```

### Только tar.gz-архив (HaikuOS / Unix)

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cpack -G TGZ
```

## Установка

### Linux (Debian/Ubuntu)

```bash
sudo dpkg -i libbrst-dev-1.0.0-amd64.deb
```

При возникновении ошибок о зависимостях:

```bash
sudo apt-get install -f
```

### FreeBSD

```bash
sudo pkg add libbrst-dev-1.0.0.pkg
```

### HaikuOS / ручная установка

```bash
tar -xzf libbrst-dev-1.0.0-amd64.tar.gz -C /system
```

## Проверка установки

После установки пакета проверьте, что библиотека доступна через pkg-config:

```bash
pkg-config --cflags --libs libbrst
```

Ожидаемый вывод:

```
-I/usr/include -L/usr/lib -lbrst
```

## Использование в проектах

### Через pkg-config (рекомендуется)

В `Makefile`:

```makefile
CFLAGS  += $(shell pkg-config --cflags libbrst)
LDFLAGS += $(shell pkg-config --libs libbrst)
```

В скрипте сборки:

```bash
gcc $(pkg-config --cflags --libs libbrst) my_program.c -o my_program
```

### Через CMake

```cmake
find_package(PkgConfig)
pkg_check_modules(BRST REQUIRED libbrst)

target_link_libraries(my_target PRIVATE ${BRST_LIBRARIES})
target_include_directories(my_target PRIVATE ${BRST_INCLUDE_DIRS})
```

## Пути установки

| Компонент | Путь |
|-----------|------|
| `libbrst.so` | `/usr/lib/x86_64-linux-gnu/` или `/usr/local/lib/` |
| Заголовочные файлы | `/usr/include/` |
| `libbrst.pc` | `/usr/lib/x86_64-linux-gnu/pkgconfig/` или `/usr/local/lib/pkgconfig/` |