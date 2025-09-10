Get-ChildItem -Recurse -Include *.cpp, *.h |
ForEach-Object { clang-format.exe -style=file $_.FullName }