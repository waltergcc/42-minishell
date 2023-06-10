# minishell

## Evaluation tests

### Check -Wall -Wextra -Werror

| # | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | make -n | show the commands that will be executed |

### Simple Command

| Check | Command | Expected result |
|:-----:|---------|-----------------|
| ☐ | /bin/ls | list files |
| ☐ | date | current date |
| ☐ | ifconfig | network information |
| ☐ | who | who is connected |
| ☐ | | do nothing |
| ☐ | [space] | do nothing |
| ☐ | [tab] | do nothing |

### Command with Arguments

| # | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | touch 1 2 3 | create 3 files |
| ☐ | /bin/ls -l | list files with details |
| ☐ | rm 1 2 3 | remove 3 files |
| ☐ | cat Makefile | content of the Makefile |
| ☐ | cat -e Makefile | content of the Makefile with $ at the end of each line |
| ☐ | wc -l Makefile | count lines in the makefile |

### echo

| # | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | echo | print a new line |
| ☐ | echo This is a test | This is a test |
| ☐ | echo -n Hello World | Hello World without new line|

### exit

| # | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | exit | exit the minishell |
| ☐ | exit 1 | exit the minishell with return code 1 |
| ☐ | exit 42 | exit the minishell with return code 42 |

### Return value of a process

| # | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | echo $? | 0 |
| ☐ | /bin/ls then run echo $? | 0 |
| ☐ | ls notexist then run echo $? | 2 |
| ☐ | /bin/notexist then run echo $? | 127 |
| ☐ | expr $? $? then run cho $? | 2 |

### Signals

| # | Shortcut | mode | Expected result |
|:-:|:--------:|------|-----------|
| ☐ | ctrl-C | empty prompt | display a new line with a new prompt |
| ☐ | ctrl-/ | empty prompt | do nothing |
| ☐ | ctrl-D | empty prompt | quit minishell |
| ☐ | ctrl-C | after write some stuff | display a new line with a new prompt |
| ☐ | ctrl-/ | after write some stuff | do nothing |
| ☐ | ctrl-D | after write some stuff | do nothing |
| ☐ | ctrl-C | in cat without arguments | display a new line with a new prompt |
| ☐ | ctrl-/ | in cat without arguments | display \Quit (core dumped) |
| ☐ | ctrl-D | in cat without arguments | close interactive mode |

### Double Quotes

| # | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | echo "Hello World" | Hello World |
| ☐ | echo "with       spaces" | Hello       World |
| ☐ | echo "test with %specials *chars" | test with %specials *chars |
| ☐ | echo "cat lol.c cat > Iol.c" | cat lol.c cat > Iol.c |
| ☐ | echo " | print a new line |

### Single Quotes

| # | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | echo 'Hello World' | Hello World |
| ☐ | echo 'with       spaces' | Hello       World |
| ☐ | echo '$USER' | $USER |
| ☐ | echo ' | print a new line |
| ☐ | echo '$HOME > home.txt' | $HOME > home.txt |
| ☐ | echo '$?' | $? |

### env

| # | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | env | show the environment variables |

### export
| # | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | export NEW_VAR=42 | create a new environment variable |
| ☐ | export NEW_VAR="A little change" | replace the value of the environment variable |
| ☐ | export NEW_VAR=$USER | replace the value of the environment variable |

### unset

| # | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | unset NEW_VAR | remove the environment variable |

### cd

| # | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | cd . | stay in the same directory |
| ☐ | cd . ls | get an error |
| ☐ | cd .. | go to the parent directory |
| ☐ | cd /usr/bin | go to the /usr/bin directory |
| ☐ | cd | go to the home directory |
| ☐ | cd notexist | get an error |


### pwd

| # | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | pwd | show the current directory |

### Relative Path

| # | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | ./minishell | execute the minishell inside minishell |
| ☐ | ../../../../../../bin/ls | list files |

### Environment path

| # | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | echo $PATH | show environment PATH |
| ☐ | unset PATH | remove the environment variable |
| ☐ | ls | get an error |
| ☐ | export PATH=/bin:/usr/bin | set the environment variable |

### Redirection

| # | Command | Expected result |
|:-:|---------|-----------------|
| ☐ | ls -l > file | create a file with the files list inside |
| ☐ | repeat the last command more times | create a file with the files list inside |
| ☐ | cat Makefile >> file | append the content of the Makefile to the file |
| ☐ | wc -l < file | count lines in the file |
| ☐ | < file \| wc -w > newfile | count words in the file and write the result in a new file |
| ☐ | cat << EOF | print the content until write EOF |
> After here document, the prompt history don't have to show the content of the here document.





### Pipes

- Execute commands with pipes like 'cat file | grep bla | more
- Repeat multiple times with different commands and arguments.
Try some wrong commands like 'ls filethatdoesntexist |grep bla | more'
- Try to mix pipes and redirections.

### Go Crazy and history

- Type a command line, then use ctrl-C and press "Enter". The buffer should be clean and there should be nothing left to execute.
- Can we navigate through history using Up and Down?
- Can we retry some command?
- Execute commands that should not work like 'dsbksdgbksdghsd'. Ensure minishell doesn't crash and prints an error.
- 'cat | cat | ls' should behave in a "normal way".
- Try to execute a long command with a ton of arguments.

### Environment variables

- Execute echo with some environment variables ($variable) as arguments.
- Check that $ is interpreted as an environment variable.
- Check that double quotes interpolate $.
- Check that USER exists. Otherwise, set it,
- echo "$USER" should print the value of the USER variable.
### Used tests
- minishell_tester: https://github.com/kichkiro/minishell_tester