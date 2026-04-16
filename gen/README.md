# Language Bindings Generator

The `gen` folder contains files intended for creating language bindings.
The generation is based on generator data files in the format of
[S-expressions](https://en.wikipedia.org/wiki/S-expression).

Historically, the *libBeresta* project grew out of the need to output *.pdf* files in a project
written in *Common Lisp*, so the choice of this format was a logical consequence of the work.

As the list of functions accumulated and language bindings for [ECL](https://ecl.common-lisp.dev/)
were generated from them, it became clear that this representation is very convenient, both for editing
and for further use as a basis for generation.

The generator data files (`*.lsp`) are directly used to generate the ECL bindings
(see [brst-binding-ecl](https://github.com/libBeresta/brst-binding-ecl)),
however, the use of S-expressions may not be very convenient in languages
outside the Lisp family.

To generate bindings using other languages from data files with
S-expressions, files in *JSON* and *YAML* formats have been created,
containing the same information as the data files, but in
*JSON* and *YAML* formats respectively.

## Updating JSON and YAML Files

As the library develops, the generator data files will evolve and change.
To keep the *JSON* and *YAML* files up to date, the build system (*CMake*)
has been enhanced with a mechanism to update these files.

When configuring the project, you must specify the parameter `-DLIBBRST_JSON_YAML=ON`,
which will add the build targets `json` and `yaml` to the project.

After that, it will be possible to call `make json` and `make yaml`,
which will regenerate the files in the *JSON* and *YAML* formats respectively.

The `yaml` target depends on the `json` target.

For the mechanism to work correctly, it is necessary to install the utility [`yq`](https://github.com/mikefarah/yq) version
4.52 or higher and make it available in the `$PATH` variable.

# Coverage statistics

See [stats.md](../doc/STATS.md).