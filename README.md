# minishell

This is a shell implementation called Minishell. It is a command-line interpreter that provides a basic shell environment and supports various features such as command execution, input parsing, redirections, pipes, environment variables, built-in commands, and signal handling.

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

|   | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | make -n | show the commands that will be executed |

### Simple Command

|   | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | /bin/ls | list files |
| ☐ | date | current date |
| ☐ | ifconfig | network information |
| ☐ | who | who is connected |
| ☐ | [empty] | do nothing |
| ☐ | [space] | do nothing |
| ☐ | [tab] | do nothing |

### Command with Arguments

|   | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | touch 1 2 3 | create 3 files |
| ☐ | /bin/ls -l | list files with details |
| ☐ | rm 1 2 3 | remove 3 files |
| ☐ | cat Makefile | content of the Makefile |
| ☐ | cat -e Makefile | content of the Makefile with $ at the end of each line |
| ☐ | wc -l Makefile | count lines in the makefile |

### echo

|   | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | echo | print a new line |
| ☐ | echo This is a test | This is a test |
| ☐ | echo -n Hello World | Hello World without new line|

### exit

|   | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | exit | exit the minishell |
| ☐ | exit 1 | exit the minishell with return code 1 |
| ☐ | exit 42 | exit the minishell with return code 42 |
| ☐ | exit 42 10 | get too many args error and not exit|
| ☐ | exit 42scholl | exit and print an error message |

### Return value of a process

|   | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | echo $? | 0 |
| ☐ | /bin/ls then run echo $? | 0 |
| ☐ | ls notexist then run echo $? | 2 |
| ☐ | /bin/notexist then run echo $? | 127 |
| ☐ | expr $? + $? then run cho $? | 2 |

### Signals

|   | Shortcut | mode | Expected result |
|:-:|:--------:|------|-----------|
| ☐ | ctrl-C | empty prompt | display a new line with a new prompt |
| ☐ | ctrl-\ | empty prompt | do nothing |
| ☐ | ctrl-D | empty prompt | quit minishell |
| ☐ | ctrl-C | after write some stuff | display a new line with a new prompt |
| ☐ | ctrl-\ | after write some stuff | do nothing |
| ☐ | ctrl-D | after write some stuff | do nothing |
| ☐ | ctrl-C | in cat without arguments | display a new line with a new prompt |
| ☐ | ctrl-\ | in cat without arguments | display \Quit (core dumped) |
| ☐ | ctrl-D | in cat without arguments | close interactive mode |

### Double Quotes

|   | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | echo "Hello World" | Hello World |
| ☐ | echo "with       spaces" | Hello       World |
| ☐ | echo "test with %specials *chars" | test with %specials *chars |
| ☐ | echo "cat lol.c cat > Iol.c" | cat lol.c cat > Iol.c |
| ☐ | echo " | print a new line |

### Single Quotes

|   | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | echo 'Hello World' | Hello World |
| ☐ | echo 'with       spaces' | Hello       World |
| ☐ | echo '$USER' | $USER |
| ☐ | echo ' | print a new line |
| ☐ | echo '$HOME > home.txt' | $HOME > home.txt |
| ☐ | echo '$?' | $? |

### env

|   | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | env | show the environment variables |

### export
|   | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | export NEW_VAR=42 | create a new environment variable |
| ☐ | export NEW_VAR="A little change" | replace the value of the environment variable |
| ☐ | export NEW_VAR=$USER | replace the value of the environment variable |

### unset

|   | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | unset NEW_VAR | remove the environment variable |

### cd

|   | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | cd . | stay in the same directory |
| ☐ | cd . ls | get an error |
| ☐ | cd .. | go to the parent directory |
| ☐ | cd /usr/bin | go to the /usr/bin directory |
| ☐ | cd | go to the home directory |
| ☐ | cd notexist | get an error |
| ☐ | cd - | go to the previous directory |

### pwd

|   | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | pwd | show the current directory |

### Relative Path

|   | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | ./minishell | execute the minishell inside minishell |
| ☐ | ../../../../../../bin/ls | list files |

### Environment path

|   | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | echo $PATH | show environment PATH |
| ☐ | unset PATH | remove the environment variable |
| ☐ | ls | get an error |
| ☐ | export PATH=/bin:/usr/bin | set the environment variable |

### Redirection

|   | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | ls -l > test | create a file with the files list inside |
| ☐ | repeat the last command more times | create a file with the files list inside |
| ☐ | cat Makefile >> test | append the content of the Makefile to the file |
| ☐ | wc -l < test | count lines in the file |
| ☐ | wc -c < test > test_out | count words in the file and write the result in a new file |
| ☐ | cat << EOF | print the content until write EOF |
> After here document, the prompt history don't have to show the content of the here document.

### Pipes

|   | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | cat Makefile \| grep NAME \| wc -l | count the number of lines with NAME in the Makefile |
| ☐ | cat notexist \| wc -l | get an error |
### Go Crazy and history

|   | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | type, Ctrl-C the enter | buffer should be clean |
| ☐ | Up, Down | navigate through history |
| ☐ | Retry some command | execute the command |
| ☐ | dsfdfdfd | get an error |
| ☐ | wc -l < /etc/passwd > file1 > file2 > file3 > file4 | count lines in the file and write the result in the last redirection |
| ☐ | cat \| cat \| ls | behave in a normal way |

### Environment variables

|   | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | echo $USER | print the username |
| ☐ | echo $notexist | print nothing |
| ☐ | echo "$HOME" | print the home directory |
| ☐ | echo ~ | print the home directory |
| ☐ | echo ~test | ~test |
| ☐ | echo test~ | test~ |
| ☐ | echo ~/test | print the home directory + /test |

### Trouble Cases

|   | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | > | get an error |
| ☐ | < | get an error |
| ☐ | < . | get an error |
| ☐ | >> | get an error |
| ☐ | << | get an error |
| ☐ | \| | get an error |
| ☐ | << EOF | start a here document |
| ☐ | > file | create a file |
| ☐ | >> file | append to a file |
| ☐ | d\| | get an error |
| ☐ | ls \| wc \| | get an error |
| ☐ | ls \| test < | get an error |
| ☐ | ls \| test > | get an error |
| ☐ | ls \| test >> | get an error |
| ☐ | ls \| test << | get an error |
| ☐ | ls \| cat << > \| wc | get an error |
| ☐ | export = | get an error |
| ☐ | export =test | get an error |

### Used tests
- minishell_tester: https://github.com/kichkiro/minishell_tester