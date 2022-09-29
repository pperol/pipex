# Pipex
The aim of this project is to reproduce the UNIX mechanism `pipe`.

### Discription of mandatory part
The program `pipex` should repeat the behaviour of the shell command
```bash
$> < file1 cmd1 | cmd2 > file2
```
and looks like:
```bash
$> ./pipex file1 cmd1 cmd2 file2
```
All errors like wrong commands,  permission to files and etc, need be handle.
