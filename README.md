# doft
## *Dani's Own Formatting Type*

***

### What is it?

> For the time being it's just a JSON parser written in C, with aims for becoming its very own file format type

To-do's:

+ Change name of the whole thing from 'json' to 'doft'

+ Check that files have the correct extension type (.doft)

+ Add support for boolean data types

+ Change the whole brace-bracket syntax

+ Refactor management of iterators

+ Refactor management of Key-Value lists

### Install & Use

> To install it, simply download the repo and run the `make install` command

```
git clone https://github.com/danibt656/libjson
cd libjson
make install
```

There's a `main.c` file in the `src/` folder. There it lays an example on how to use the parser & iterator, and obtain the contents of the file with a sort-of Object Relational Mapping (ORM).

### Why make your own FT?

> There's no meaning behind it, more than learning more about lexing & parsing in C, then I thought it would be fun to tweak its syntax to my personal liking

*By the way, thanks for checking it out ;-)*
