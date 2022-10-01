# Pipex
The aim of this project is to reproduce the UNIX tool `pipe` ('|').
A pipe is a form of redirection (transfer of standard output to some other destination) that is used in Linux and other Unix-like operating systems to send the output of one command/program/process to another command/program/process for further processing. 
The Unix/Linux systems allow stdout of a command to be connected to stdin of another command. 
You can make it do so by using the pipe character '|'. 

Pipe is used to combine two or more commands, and in this, the output of one command acts as input to another command, and this command’s output may act as input to the next command and so on. 
It can also be visualized as a temporary connection between two or more commands/ programs/ processes. The command line programs that do the further processing are referred to as filters. 

This direct connection between commands/ programs/ processes allows them to operate simultaneously and permits data to be transferred between them continuously rather than having to pass it through temporary text files or through the display screen. 
Pipes are unidirectional i.e data flows from left to right through the pipeline.

### Discription of mandatory part
The program `pipex` should repeat the behaviour of the shell command
```bash
$> < file1 cmd1 | cmd2 > file2
```
and looks like:
```bash
$> ./pipex file1 cmd1 cmd2 file2
```
All errors like wrong commands,  permission to files and etc should be handled.
