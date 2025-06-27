# libBeresta

libBeresta — free, open-source, cross-platform library for generating PDF files.

![Beresta](img/beresta.png)

Русскоязычное описание содержится в [`README.md`](README.md)

Library Capabilities:

* Creation of PDF files using lines, text and images;
* Ability to add various types of annotations into the documents;
* Support for document compression;
* Insertion of PNG, JPEG, and TIFF (Raw) format images into documents;
* Creation of encrypted files;
* Use of different encodings including UTF-8 and Asian ones such as:
  * Traditional Chinese
  * Simplified Chinese
  * Korean
  * Japanese

The library allows creating PDF documents without requiring an understanding of the internal structure of the Portable Document Format.

Programming Language: ANSI C


## Name and History

Beresta is a material that refers us back to ancient Russian writings.

Birchbark letters are monuments of Old Russian writing, records made on tree bark. 
One of the most popular materials used for writing in the 11th–15th centuries.

The word “beresta” comes from the same root as “birch.” Literally it means “white tree.” 
The term “birchbark” was coined because birch bark was most commonly used for their creation.

## Development Principles

* Development language: ANSI C;
* Documentation, code, and communication in Russian (English is welcome as well);
* Public API documentation;
* Clear separation between exported and private parts both in headers and source code;
* Modularity according to PDF standards and supported features;
* Spelling checks for code and documentation;
* Unit testing of library functions;
* Testing documented error states (such as `BRST_INVALID_DOCUMENT`);
* Preparation of the library for future generation of bindings;
* Examples covering all library functions;
* Examples illustrating each section of supported PDF standards. 

This library is a deep rework of the `libHaru` project.

Several reasons motivated this development effort:

* Practically stalled development of the libHaru library (patch responses could take several months);
* Inability to use the library piecemeal (difficulties excluding annotations, text generation, image embedding or PDF/A support);
* Mixed-up functions in libHaru—exported and non-exported functions appear intermingled in both header files and implementation;
* Lack of any form of documentation;
* Unclear compliance with PDF standards by libHaru;
* Absence of tests;
* Limited number of examples;
* Inconsistencies and errors in function names. 

## License 
The library is developed and distributed under the MIT license. The full text of the license can be found in the file [`ЛИЦЕНЗИЯ`](ЛИЦЕНЗИЯ).

The original libHaru library's license text is located in the [`LICENSE.libHaru`](LICENSE.libHaru) file.
