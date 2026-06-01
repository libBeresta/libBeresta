# Пакеты libbrst

Проект libbrst поддерживает сборку дистрибутивных пакетов для различных операционных систем через CPack.

## Поддерживаемые форматы

| Формат | Система | Команда сборки | Имя файла |
|--------|---------|----------------|-----------|
| `.deb` | Linux (Debian, Ubuntu и производные) | `cpack -G DEB` | `libbrst-dev-1.0.0-amd64.deb` |
| `.pkg` | FreeBSD | `cpack -G FREEBSD` | `libbrst-dev-1.0.0.pkg` |
| `.tar.gz` | HaikuOS / любые Unix-системы | `cpack -G TGZ` | `libbrst-dev-1.0.0-amd64.tar.gz` |
| `.exe` | Windows (NSIS-инсталлятор) | `cpack -G NSIS` | `libbrst-dev-1.0.0-amd64.exe` |

## Состав пакета

### Linux / FreeBSD / HaikuOS

- **Библиотека**: `libbrst.so` (с symlink'ами `libbrst.so.1`, `libbrst.so.1.0.0`)
- **Заголовочные файлы**: все `*.h` из директории `include/`
- **Файл pkg-config**: `libbrst.pc` для использования через `pkg-config`

### Windows

- **Библиотека**: `libbrst.dll` (и `libbrst.lib` для линковки)
- **Заголовочные файлы**: все `*.h` из директории `include/`
- Инсталлятор добавляет путь к библиотеке в `PATH`

## Требования

### Для всех платформ

- CMake >= 3.10
- Компилятор C (GCC, Clang, MSVC)
- `zlib` (и `zlib1g-dev` на Debian/Ubuntu)
- `libpng` (и `libpng-dev` на Debian/Ubuntu)

### Для Windows (NSIS)

- [NSIS](https://nsis.sourceforge.io/) (Nullsoft Scriptable Install System) должен быть установлен и доступен в `PATH`

## Сборка

### Все пакеты сразу

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cpack -G DEB -G FREEBSD -G TGZ -G NSIS
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

### Только NSIS-инсталлятор (Windows)

```cmd
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cpack -G NSIS
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

### Windows

Запустите `libbrst-dev-1.0.0-amd64.exe` и следуйте инструкциям мастера установки.
Инсталлятор предложит добавить путь к библиотеке в системную переменную `PATH`.

## Проверка установки

### Linux / FreeBSD / HaikuOS

После установки пакета проверьте, что библиотека доступна через pkg-config:

```bash
pkg-config --cflags --libs libbrst
```

Ожидаемый вывод:

```
-I/usr/include -L/usr/lib -lbrst
```

### Windows

Проверьте, что DLL доступна:

```cmd
where libbrst.dll
```

## Использование в проектах

### Через pkg-config (Unix-системы, рекомендуется)

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

### Windows (Visual Studio)

После установки через NSIS-инсталлятор укажите в настройках проекта:

- **C/C++ → Общие → Дополнительные каталоги включаемых файлов**: `C:\Program Files\libBeresta\include`
- **Компоновщик → Общие → Дополнительные каталоги библиотек**: `C:\Program Files\libBeresta\lib`
- **Компоновщик → Ввод → Дополнительные зависимости**: `libbrst.lib`

## Пути установки

### Unix-системы (Linux, FreeBSD, HaikuOS)

| Компонент | Путь |
|-----------|------|
| `libbrst.so` | `/usr/lib/x86_64-linux-gnu/` или `/usr/local/lib/` |
| Заголовочные файлы | `/usr/include/` |
| `libbrst.pc` | `/usr/lib/x86_64-linux-gnu/pkgconfig/` или `/usr/local/lib/pkgconfig/` |

### Windows

| Компонент | Путь |
|-----------|------|
| `libbrst.dll` | `C:\Program Files\libBeresta\bin\` |
| `libbrst.lib` | `C:\Program Files\libBeresta\lib\` |
| Заголовочные файлы | `C:\Program Files\libBeresta\include\` |