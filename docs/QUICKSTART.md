# Quick Start

## Build the Library

The library is built using [CMake](https://cmake.org/) version 3.10 or higher.

```sh
mkdir build
cd build
cmake ..
make
```

The library will be built as a **shared library**, and the file `libbrst.so.1.0.0` will be created.

## Create a File

Below is the minimal source code that creates a PDF document and does *something useful*:

```c
// File: bare_minimum.c


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

## Compile the File (Shared Library)

For convenience, let's assume the `LIBBRST_PATH` environment variable contains the path to the `libBeresta` library folder.

Then, you can compile the binary with the following command:

```sh
/usr/bin/cc ./bare_minimum.c  \
-o ./bare_minimum             \
-I$LIBBRST_PATH/include       \
-I$LIBBRST_PATH/build/include \
-L$LIBBRST_PATH/build/src     \
-lbrst -lm -lz
```

The file `bare_minimum` should be created.

## Run the File (Shared Library)

Now, run the `bare_minimum` file:

```sh
LD_LIBRARY_PATH=$LIBBRST_PATH/build/src/ ./bare_minimum
```

The file `bare_minimum.pdf` should be generated.

The resulting file is an A4-sized, landscape-oriented PDF with a rectangle covering the almost entire page.

The creation of `bare_minimum.pdf` is a sign that the library has been successfully built and can be used in your work.
