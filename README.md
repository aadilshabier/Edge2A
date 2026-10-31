# Edge2A

Short for Edge2ANode. The best Graph Database Managment System of our times[^1]

[^1]: trust me bro

# Instructions
Make sure you have the following dependencies installed before building:

## Dependencies
* **CMake** (version 3.22 or higher)
* **GCC / Clang** (with C++20 support)
* **FLEX** (Fast Lexical Analyzer)
* **BISON** (GNU Parser Generator)

## Dev Dependencies
* **clang-format** (code formater)
* **cppcheck** & **clang-tidy** (linter)
* **pre-commit** (py tool for Git hooks)

### Installing Dependencies

``` shell
sudo apt update
sudo apt install -y build-essential cmake flex bison clang-format clang-tidy cppcheck pre-commit
```

## Build, Test, and Run

### 1. Build

``` shell
cd build
cmake ..
make
```

### 2. Test

``` shell
ctest
```

### 3. Run

``` shell
./edge2a
```
## Local Development

### Git Hooks

Enable pre-commit hooks once in your repository root to automatically run `clang-format` and `cppcheck` before every commit:

```shell
pre-commit install # enable
pre-commit run --all-files # run manually
```

### Code Formatting

```shell
clang-format -i $(find src -name '*.cpp' -o -name '*.hpp' 2>/dev/null)
```

### Linting

```shell
cppcheck --enable=all --suppress=missingIncludeSystem --inline-suppr src/

cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
clang-tidy -p build -header-filter='src/.*' --warnings-as-errors='*' $(find src -name '*.cpp')
```

## Demo
This is a simple demo application which uses graphDB populated with the movies dataset.
It fetches movies according to filters provided by the user.

`Frontend:  React`
`Backend:   C++`

Install node dependencies as
```
cd ./demo/frontend/
npm install
```

Run the application using
```
npm start
```
