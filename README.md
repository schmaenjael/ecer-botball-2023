1. Trivial Variables: i,n,c,etc... (Only one letter. If one letter isn't clear, then make it a Local Variable)
2. Local Variables: camelCase
3. Global Variables: g_camelCase
4. Const Variables: ALL_CAPS
5. Pointer Variables: add a p* to the prefix. For global variables it would be gp_var, for local variables p_var, for 1. const variables p_VAR. If far pointers are used then use an fp* instead of p\_.
6. Structs: ModulePascalCase (Module = full module name, or a 2-3 letter abbreviation, but still in PascalCase.)
7. Struct Member Variables: camelCase
8. Enums: ModulePascalCase
9. Enum Values: ALL_CAPS
10. Public Functions: ModulePascalCase
11. Private Functions: PascalCase
12. Macros: PascalCase
