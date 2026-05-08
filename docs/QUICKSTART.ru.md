# Быстрый запуск

## Соберите библиотеку

Библиотека собирается с помощью программы [CMake](https://cmake.org/) версии не ниже 3.10.

```sh
mkdir build
cd build
cmake ..
make
```

Библиотека соберется в режиме shared library, будет создан файл
`libbrst.so.1.0.0`

## Создайте файл

Минимальный исходный код, который создает PDF-документ и делает _хоть
что-то полезное_, представлен ниже:

```c

// Файл bare_minimum.c

#include "brst.h"

int main(int argc, char** argv)
{
    BRST_Doc pdf;
    BRST_Page page;

    pdf = BRST_Doc_New_Empty();
    if (!pdf) {
        return 1;
    }

    page = BRST_Doc_Page_Add(pdf);
    BRST_Page_SetSize(page, BRST_PAGE_SIZE_A4, BRST_PAGE_ORIENTATION_LANDSCAPE);

    BRST_Page_SetLineWidth(page, 1);

    BRST_Page_Rectangle(
        page,
        50,
        50,
        BRST_Page_Width(page)  - 100,
        BRST_Page_Height(page) - 100
    );

    BRST_Page_Stroke(page);

    BRST_Doc_SaveToFile(pdf, "bare_minimal.pdf");
    BRST_Doc_Free(pdf);

    return 0;
}
```

## Компилируйте файл (shared library)

Предположим для удобства, что переменная `LIBBRST_PATH` содержит путь до
папки с библиотекой `libBeresta`.

Тогда сборка бинарного файла будет выполнена следующей командой:

```sh
/usr/bin/cc ./bare_minimum.c  \
-o ./bare_minimum             \
-I$LIBBRST_PATH/include       \
-I$LIBBRST_PATH/build/include \
-L$LIBBRST_PATH/build/src     \
-lbrst -lm -lz
```

Должен быть создан файл `bare_minimum`

## Запускаете файл (shared library)

Теперь запускаете файл `bare_minimum`:

```sh
LD_LIBRARY_PATH=$LIBBRST_PATH/build/src/ ./bare_minimal
```

Должен сформироваться файл `bare_minimum.pdf`. 

Файл формата А4, портретной ориентации, с&nbsp;прямоугольником на&nbsp;всю 
страницу.

Создание файла `bare_minimum.pdf` &ndash; признак того, что библиотека 
собрана успешно и может использоваться в работе.
