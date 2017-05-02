# test_scikit_in_csharp
i) Execute: export LD_LIBRARY_PATH="$(pwd)" in order to tell the compiler where to find the dynamic libraries that you'll be using

ii) Execute: gcc -fPIC -shared libtest.c -o libtest.so -lpython2.7 -Xlinker -export-dynamic in order to compile the c code into a dynamic library

iii) Run the code (dotnet build and dotnet run, as usual)
