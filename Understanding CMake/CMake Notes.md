CMake is used to generate Makefile that builds your C++ Project. Remember it doesn't explicitly build the project.
It has  a very basic template. Every construct is a command that matches the pattern `_name_(_args_)`

```CMake
cmake_minimum_required(VERSION 3.20.0)
project(HelloWorld)
add_executable(my_executable HelloWorld.cpp)
```

In CMake, all variables are of string data-types. Wrapping a variable in `${}` dereferences it and results in a literal substitution of the name for the value. Following example deals with variables declaration and dereferencing:

```Cmake
set(var_name var1)
set(${var_name} foo) # same as "set(var1 foo)"
set(${${var_name}}_var bar) # same as "set(foo_var bar)"
```
Dereferencing an unset variable results in an empty expansion. For instance:

```
if(APPLE)
  set(extra_sources Apple.cpp)
endif()
add_executable(HelloWorld HelloWorld.cpp ${extra_sources})
```

In CMake, lists are semicolon-delimited strings, and it is strongly advised that you avoid using semicolons in lists; it doesn’t go smoothly. A few examples of defining lists:

```CMake
# Creates a list with members a, b, c, and d
set(my_list a b c d) # Recommended to use this one
set(my_list "a;b;c;d")

# Creates a string "a b c d"
set(my_string "a b c d")
```

The CMake set command provides two scope-related options. `PARENT_SCOPE` sets a variable into the parent scope, and not the current scope. The `CACHE` option sets the variable in the CMakeCache, which results in it being set in all scopes. The `CACHE` option will not set a variable that already exists in the `CACHE` unless the `FORCE` option is specified.

### Control flow in CMake
In general, CMake `if` blocks work the way you’d expect:

```
if(<condition>)
  message("do stuff")
elseif(<condition>)
  message("do other stuff")
else()
  message("do other other stuff")
endif()
```
Remember that CMake’s `if` blocks coming from a C background is that they do not have their own scope.

### Loops in CMake

```
foreach(var foo bar baz)
  message(${var})
endforeach()
# prints:
#  foo
#  bar
#  baz

set(my_list 1 2 3)
foreach(var ${my_list})
  message(${var})
endforeach()
# prints:
#  1
#  2
#  3

foreach(var ${my_list} out_of_bounds)
  message(${var})
endforeach()
# prints:
#  1
#  2
#  3
#  out_of_bounds
```

### Argument Handling
When a command is invoked with extra arguments (beyond the named ones) CMake will store the full list of arguments (both named and unnamed) in a list named `ARGV`, and the sublist of unnamed arguments in `ARGN`

```
function(add_deps target)
  add_dependencies(${target} ${ARGN})
endfunction()
```

Functions and Macros look very similar in how they are used, but there is one fundamental difference between the two. Functions have their own scope, and macros don’t. This means variables set in macros will bleed out into the calling scope. That makes macros suitable for defining very small bits of functionality only.

The other difference between CMake functions and macros is how arguments are passed. Arguments to macros are not set as variables, instead dereferences to the parameters are resolved across the macro before executing it. This can result in some unexpected behavior if using unreferenced variables. For example:

```
macro(print_list my_list)
  foreach(var IN LISTS my_list)
    message("${var}")
  endforeach()
endmacro()

set(my_list a b c d)
set(my_list_of_numbers 1 2 3 4)
print_list(my_list_of_numbers)
# prints:
# a
# b
# c
# d
```

## Structure of a CMake file

```cmake
cmake_minimum_required(VERSION 3.15...4.4)
project(MyProject VERSION 1.0
                  DESCRIPTION "Very nice project"
                  LANGUAGES CXX)
                  
# Making an executable
add_executable(one two.cpp three.h)

# Making a library
add_library(one STATIC two.cpp three.h)
```

`MyProject` is the name of the project
one is the name of the executable
You get to pick a type of library, STATIC, SHARED, or MODULE. If you leave this choice off, the value of `BUILD_SHARED_LIBS` will be used to pick between STATIC and SHARED.

## Building the project

```
cmake -B build -S . 
cmake --build build
```
