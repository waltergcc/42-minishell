# minishell

This is a shell implementation called Minishell. It is a command-line interpreter that provides a basic shell environment and supports various features such as command execution, input parsing, redirections, pipes, environment variables, built-in commands, and signal handling.

This project was developed in colaboration with [teroVF](https://github.com/teroVF).
## Features
	
- **Prompt display:** Minishell displays a prompt when waiting for a new command.
- **Command history:** It has a working history feature that allows navigating and reusing previous commands.
- **Command execution:** Minishell can search and launch the appropriate executable based on the PATH variable or using a relative or absolute path.
- **Quoting:** It handles single quotes `'`, preventing the interpretation of meta-characters within the quoted sequence. Double quotes `"` prevent the interpretation of meta-characters except for the dollar sign `$`.
- **Redirections:** Minishell supports input `<`, output `>` and append output `>>` redirections. It also handles here documents `<<` where input is read until a line containing the specified delimiter.
- **Pipes:** It implements pipes `|` to connect the output of one command to the input of the next command in a pipeline.
- **Environment variables:** Minishell handles the expansion of environment variables (`$` followed by a sequence of characters) to their respective values.
- **Special variables:** It supports the special variable `$?` which expands to the exit status of the most recently executed foreground pipeline.
- **Signal handling:** Minishell handles signals such as `ctrl-C` (SIGINT), `ctrl-D` (EOF), and `ctrl-\` (SIGQUIT) according to the specified behavior in the subject.
- **Built-in commands:** It provides several built-in commands, including `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`, with their respective options and arguments.

## Implementation Details

- The shell uses the readline library to provide line editing capabilities and command history.
- Input parsing is done using a combination of string manipulation and state tracking to handle quotes and command boundaries.
- Command execution is managed through a commands_manager function that handles the execution of commands, including pipe setup and file descriptor management.
- Built-in commands are implemented as separate functions and are executed within the shell process itself.
- Error handling and reporting are done through a combination of error codes, error messages, and signal handling.

## Usage

To compile the Minishell program, use the provided Makefile by running `make` in the project directory. This will generate an executable named `minishell`.

```
make
```

To run the Minishell program, simply execute the generated `minishell` binary.

```
./minishell
```

Once running, you can enter commands and interact with the shell.

## Requirements

- The Libft library is required and provided along with the project files.
- The program was developed and tested on a Unix-based system. Compatibility with other platforms may vary.

## Limitations

- Minishell does not interpret unclosed quotes or special characters that are not required by the subject, such as backslashes `\` or semicolons `;`.
- The readline() function used in Minishell may cause memory leaks, but the code written specifically for this project should not have memory leaks.

## Evaluation tests

### Check -Wall -Wextra -Werror

```bash
make -n
```
> gcc -Wall -Wextra -Werror -c src/main.c -o obj/main.o

### Simple Command

```bash
/bin/ls
```
> include  libft	Makefile  minishell  minishell_tester  src
```bash
date
```
> Wed  7 Jul 2021 11:00:00 AM -03
```bash
ifconfig
```
> network information
```bash
who
```
> wcorrea- tty2         2023-06-20 10:46 (tty2)
```bash
[empty]
```
> print a new line
```bash
[space]
```
> print a new line
```bash
[tab]
```
> do nothing

### Command with Arguments

```bash
touch 1 2 3
```
> create 3 files
```bash
/bin/ls -l
```
> list files with details
```bash
rm 1 2 3
```
> remove 3 files
```bash
cat Makefile
```
> print the content of the Makefile
```bash
cat -e Makefile
```
> print the content of the Makefile with $ at the end of each line
```bash
wc -l Makefile
```
> 55 Makefile


### echo

```bash
echo
```
> print a new line
```bash
echo This is a test
```
> This is a test
```bash
echo -n Hello World
```
> Hello World/home/wcorrea-$

### exit

```bash
exit
```
> exit the minishell
```bash
exit 1
```
> exit the minishell with return code 1
```bash
exit 42
```
> exit the minishell with return code 42
```bash
exit -42
```
> exit the minishell with return code 214
```bash
exit 42 10
```
> minishell: exit: too many arguments
```bash
exit 42scholl
```
> minishell: exit: numeric argument required; then exit with error code 2

### Return value of a process

```bash
echo $?
```
> 0
```bash
/bin/ls
```
> then run echo $?; the return code is 0
```bash
ls notexist
```
> then run echo $?; the return code is 2
```bash
/bin/notexist
```
> then run echo $?; the return code is 127
```bash
expr $? + $?
```
> then run echo $?; the return code is 2

### Signals

`ctrl-C` on empty prompt
> display a new line with a new prompt

`ctrl-\` on empty prompt
> do nothing

`ctrl-D` on empty prompt
> quit minishell

`ctrl-C` after write some stuff
> display a new line with a new prompt

`ctrl-\` after write some stuff
> do nothing

`ctrl-D` after write some stuff
> do nothing

`ctrl-C` in cat without arguments
> ^C

`ctrl-\` in cat without arguments
> \Quit (core dumped)

`ctrl-D` in cat without arguments
> close interactive mode

### Double Quotes

```bash
echo "Hello World"
```
> Hello World
```bash
echo "with       spaces"
```
> Hello       World
```bash
echo "test with %specials *chars"
```
> test with %specials *chars
```bash
echo "cat lol.c cat > Iol.c"
```
> cat lol.c cat > Iol.c
```bash
echo "
```
> minishell: unclosed quotes

### Single Quotes

```bash
echo 'Hello World'
```
> Hello World
```bash
echo 'with       spaces'
```
> Hello       World
```bash
echo '$USER'
```
> $USER
```bash
echo '
```
> minishell: unclosed quotes
```bash
echo '$HOME > home.txt'
```
> $HOME > home.txt
```bash
echo '$?'
```
> $?

### env

```bash
env
```
> print the environment variables

### export

```bash
export NEW_VAR=42
```
> add NEW_VAR with content 42
```bash
export NEW_VAR="A little change"
```
> replace the value of NEW_VAR
```bash
export NEW_VAR=
```
> replace the content of NEW_VAR to empty
```bash
export NEW_VAR=$USER
```
> replace the value of NEW_VAR
```bash
export NEW_VAR="with unclosed quotes
```
> minishell: unclosed quotes
```bash
export -p NEW_VAR
```
> minishell: export: options aren't supported


### unset

```bash
unset NEW_VAR
```
> remove the environment variable
```bash
unset -n NEW_VAR
```
> minishell: unset: options aren't supported

### cd

```bash
cd .
```
> stay in the same directory
```bash
cd . ls
```
> minishell: cd: too many arguments
```bash
cd ..
```
> go to the parent directory
```bash
cd /usr/bin
```
> go to the /usr/bin directory
```bash
cd
```
> go to the home directory
```bash
cd notexist
```
> minishell: cd: notexist: No such file or directory
```bash
cd -
```
> go to the previous directory


### pwd

```bash
pwd
```
> /home/wcorrea-/workplace/common_core/minishell/minishell

```bash
pwd -L
```
> minishell: pwd: options aren't supported

### Relative Path

```bash
./minishell
```
> execute the minishell inside minishell
```bash
../../../../../../bin/ls
```
> include  libft	Makefile  minishell  minishell_tester  src

### Environment path

```bash
echo $PATH
```
> /home/wcorrea-/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/snap/bin
```bash
unset PATH
```
> remove the PATH environment variable
```bash
ls
```
> minishell: ls: command not found
```bash
export PATH=/bin:/usr/bin
```
> set the PATH environment variable with the basic path again

### Redirection

```bash
ls -l > test
```
> create a file with the files list inside
```bash
cat Makefile >> test
```
> append the content of the Makefile to the file
```bash
wc -l < test
```
> 63
```bash
wc -c < test > test_out
```
> test_out receive the number of characters in the file test
```bash
cat << EOF
```
> start the here document

```bash
cat << EOF | wc -l
```
> print the number of lines in the here document

### Pipes

```bash
cat Makefile | grep NAME | wc -l
```
> 5
```bash
cat notexist | wc -l
```
>cat: notexist: No such file or directory
0
```bash
< Makefile grep NAME | wc -l > out
```
> put the result in out

### Go Crazy and history

`up` `down` to navigate in the history

```bash
 dsfdfdfd
```
> minishell: command not found
```bash
wc -l < /etc/passwd > file1 > file2 > file3 > file4
```
> write the result in the last redirection
```bash
cat | cat | ls
```
> print list files and open the interactive mode

### Environment variables

```bash
echo $USER
```
> wcorrea-
```bash
echo $notexist
```
> print an empty line
```bash
echo "$HOME"
```
> /home/wcorrea-
```bash
echo ~
```
> /home/wcorrea-
```bash
echo ~test
```
> ~test
```bash
echo test~
```
> test~
```bash
echo ~/test
```
> /home/wcorrea-/test

### Trouble Cases
```bash
echo -n -n -n -n -n Hello World
```
> Hello World/home/wcorrea-$

```bash
echo $HOME.test
```
> /home/wcorrea-.test

```bash
echo $HOME/test
```
> /home/wcorrea-/test

```bash
;
```
> minishell: no support for operator `;'

```bash
*
```
> minishell: no support for operator `*'

```bash
>
```
> minishell: syntax error near unexpected token `newline'
```bash
<
```
> minishell: syntax error near unexpected token `newline'
```bash
< .
```
> minishell: syntax error near unexpected token `newline'
```bash
>>
```
> minishell: syntax error near unexpected token `newline'
```bash
<<
```
> minishell: syntax error near unexpected token `newline'
```bash
|
```
> minishell: syntax error near unexpected token `|'
```bash
<< EOF
```
> start the here document
```bash
> file
```
> create a file
```bash
>> file
```
> append to a file
```bash
d|
```
> minishell: no support for pipe prompt
```bash
ls | wc |
```
> minishell: no support for pipe prompt
```bash
ls | wc >
```
> minishell: syntax error near unexpected token `newline'
```bash
ls | wc <
```
> minishell: syntax error near unexpected token `newline'
```bash
ls | wc <<
```
> minishell: syntax error near unexpected token `newline'
```bash
ls | wc >>
```
> minishell: syntax error near unexpected token `newline'
```bash
ls | cat << > | wc
```
> minishell: syntax error near unexpected token `<< '
```bash
export =
```
> minishell: export: `=': not a valid identifier
```bash
export =test
```
> minishell: export: `=test': not a valid identifier
```bash
export TEST.=test
```
> minishell: export: `TEST.=test': not a valid identifier

### Crazy export test
```bash
export TEST1="withdouble" TEST2='withsingle' TEST3=wihoutquotes TEST4="with spaces and expand $USER" TEST5="ok, but it has more" TEST6= TEST7='with single $PATH' = TEST8= TEST9 TEST10="" TEST11=too=many=equals TEST.12="    "
```
> define this variables. Check with env
```bash
unset TEST1 TEST2 TEST3 TEST4 TEST5 TEST6 TEST7 TEST8 TEST9 TEST10 TEST11 TEST12
```
> unset all these variables that were valid
### Used tests
- minishell_tester: https://github.com/kichkiro/minishell_tester