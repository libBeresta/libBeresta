# How to contribute to libBeresta

## Short version

Your contribution is welcome in any area that interests you:

* Use the library
* Share information about the library
* Create language bindings for languages other than `C`
* Test the library
* Fix bugs
* Improve code quality
* Propose new features
* Fix security issues
* Translate the library
* Document the library

A list of known tasks can be found on the [milestones](https://github.com/libBeresta/libBeresta/milestones) and [issues](https://github.com/libBeresta/libBeresta/issues) pages.

## Extended version

### Use the library

`libBeresta` is a library for creating PDF files. We would be happy if you use this library in your projects.

Let us know if the library has been useful and helpful to you!
Create an issue in the repository with the prefix `USAGE:` and tell us about your project and how you used the library. We will add your story to the documentation!

### Share information about the library

Give us a star on GitHub, SourceCraft, and other platforms &ndash; this will help more people learn about `libBeresta`.

If you like the library, please write about it on your social networks and blogs. This is very important to us!

### Create language bindings for languages other than `C`

The library is written in plain `C` and was designed with the intention of being used from other languages.

Creating language bindings is a challenging task, and many libraries do nothing to facilitate automatic binding generation.

We have created «generator data files» that can be used as a basis for generating language bindings. For more details, please refer to

[gen/README.md](../gen/README.md).

We are very much looking forward to language bindings for `libBeresta` in your programming languages, especially since you know your own languages much better than we do.

### Test the library

Tests cannot prove the absence of bugs in a program, but they can make it much harder to introduce new ones.

Therefore, we welcome any efforts aimed at testing the library.

Some testing tasks are already known and can be found by the tag [`testing`](https://github.com/libBeresta/libBeresta/issues?q=state%3Aopen%20label%3A%22testing%22).

We would be glad if you added usage examples to the library (the `demo` folder) and test programs (the `tests` folder).

### Fix bugs

We are aware of some bugs, but there may be others we don't know about yet. You can help by either identifying or fixing them.

Known bugs are labeled as [`Bug`](https://github.com/libBeresta/libBeresta/issues?q=is%3Aissue%20state%3Aopen%20type%3ABug).

We would be very grateful if, when creating a `Bug` issue, you also provide a minimal program that reproduces the error.

### Improve code quality

Much of the library was written a long time ago and needs to be reviewed. We will gladly accept any improvements to the existing code &ndash; performance optimizations, better resource usage, and reducing technical debt.

Any changes are welcome!

### Propose new features

The library only supports a subset of the PDF standards and not the full range. However, standard support is not the only important thing.

We want the library to be convenient to use, so we welcome any improvements related to usability, including:

- Adding new image formats
- Adding new supported font formats
- Integrating related projects, such as QR code and DataMatrix generation
- Improving work with library states (`BRST_GMODE_*` constants)
- Supporting PDF 1.7 and 2.0 standards
- Supporting PDF/A 1-4, PDF/E, PDF/UA, PDF/VT, PDF/X standards
- Supporting encryption mechanisms (within the limits allowed by the laws of your country)
- Expanding text handling support
- Deep support for vertical writing
- Support for right-to-left writing
- Support and testing of copy mechanisms (clipboard)
- Creating a logging mechanism and outputting statistical information about generation
- Creating large files
- Creating file groups
- Creating OS packages (Linux `deb`, FreeBSD `pkg`, Windows `nuget` etc.)
- Perhaps something has been missed...

Any enhancements are welcome! You are also invited to join the [discussions](https://github.com/libBeresta/libBeresta/discussions) to talk about improvements from the list above.

### Fix security issues

Much of the library was written decades ago and does not meet modern ideas about secure code.

We are very much looking forward to fixes for security-related bugs, as well as corrections to code that is now considered incorrect or unsafe.

Some of this work has already been started; you can see the [Security and quality](https://github.com/libBeresta/libBeresta/security) section.

Please propose solutions for found problems. You can also suggest what other tools we could use to find vulnerabilities and security issues &ndash; we will gladly consider all proposals.

### Translate the library

Currently, the generator data files in the library contain string descriptions for parts of the library in Russian and English.

This information will be used in the future for website development (see #9).

We would be very grateful for a translation of the library into your language!

### Document the library

You can help by adding to or correcting the library's documentation. The status of documentation strings can be viewed in the document

[STATS.md](STATS.md).

Additionally, we would be very grateful if you wrote or suggested documents such as a tutorial, reference manual, or cookbook.

Best regards,
The `libBeresta` team.