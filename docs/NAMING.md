# Function Naming System

For ease of use with the library, functions are named according to the following system:

* **Prefix:** All functions must begin with the prefix `BRST_`.
* **`Doc` Parameter:** If a function has a `Doc` parameter, it must be the
  first one. The function name is then supplemented with the prefix `_Doc`.
* **`Page` Parameter:** If a function requires a `Page` parameter, it is
  placed first or second (if a `Doc` parameter is also present). The function
  name is supplemented with the prefix `_Page`.
* **Object:** The name of the object the function operates on follows next,
  such as `_Font` or `_Image`.
* In some cases, an additional suffix may be used if the function's
  logic requires it: `BRST_Doc_Image_Png_LoadFromFile()`.
* **Action:** The final element is the action, if applicable.

The action is represented by a verb or an adjective (e.g., `Add`, `Use`).

An action may consist of multiple words. In this case, they are written in
CamelCase (each subsequent word capitalized).

If the action explicitly sets a property, it must begin with the word `Set`
(e.g., `SetCurrent`).

If it is necessary to retrieve a property (as a counterpart to `Set`),
the word `Get` is not used (e.g., `BRST_Font_FontName()`).
