# minishell

## Evaluation tests

### Check -Wall -Wextra -Werror

| # | Command | Expected result |
|:-:|---------|-----------------|
| [x] | make -n | show the commands that will be executed |

### Simple Command

| Check | Command | Expected result |
|:-----:|---------|-----------------|
| [x] | /bin/ls | list files |
| [x] | date | current date |
| [x] | ifconfig | network information |
| [x] | who | who is connected |
| [x] | [empty] | do nothing |
| [x] | [space] | do nothing |
| [x] | [tab] | do nothing |

### Command with Arguments

| # | Command | Expected result |
|:-:|---------|-----------------|
| [x] | touch 1 2 3 | create 3 files |
| [x] | /bin/ls -l | list files with details |
| [x] | rm 1 2 3 | remove 3 files |
| [x] | cat Makefile | content of the Makefile |
| [x] | cat -e Makefile | content of the Makefile with $ at the end of each line |
| [x] | wc -l Makefile | count lines in the makefile |

### echo

| # | Command | Expected result |
|:-:|---------|-----------------|
| [x] | echo | print a new line |
| [x] | echo This is a test | This is a test |
| [x] | echo -n Hello World | Hello World without new line|

### exit

| # | Command | Expected result |
|:-:|---------|-----------------|
| [x] | exit | exit the minishell |
| [x] | exit 1 | exit the minishell with return code 1 |
| [x] | exit 42 | exit the minishell with return code 42 |

### Return value of a process

| # | Command | Expected result |
|:-:|---------|-----------------|
| [x] | echo $? | 0 |
| [x] | /bin/ls then run echo $? | 0 |
| [x] | ls notexist then run echo $? | 2 |
| [x] | /bin/notexist then run echo $? | 127 |
| [x] | expr $? $? then run cho $? | 2 |

### Signals

| # | Shortcut | mode | Expected result |
|:-:|:--------:|------|-----------|
| [x] | ctrl-C | empty prompt | display a new line with a new prompt |
| [x] | ctrl-\ | empty prompt | do nothing |
| [x] | ctrl-D | empty prompt | quit minishell |
| [x] | ctrl-C | after write some stuff | display a new line with a new prompt |
| [x] | ctrl-\ | after write some stuff | do nothing |
| [x] | ctrl-D | after write some stuff | do nothing |
| [x] | ctrl-C | in cat without arguments | display a new line with a new prompt |
| [x] | ctrl-\ | in cat without arguments | display \Quit (core dumped) |
| [x] | ctrl-D | in cat without arguments | close interactive mode |

### Double Quotes

| # | Command | Expected result |
|:-:|---------|-----------------|
| [x] | echo "Hello World" | Hello World |
| [x] | echo "with       spaces" | Hello       World |
| [x] | echo "test with %specials *chars" | test with %specials *chars |
| [x] | echo "cat lol.c cat > Iol.c" | cat lol.c cat > Iol.c |
| [x] | echo " | print a new line |

### Single Quotes

| # | Command | Expected result |
|:-:|---------|-----------------|
| [x] | echo 'Hello World' | Hello World |
| [x] | echo 'with       spaces' | Hello       World |
| [x] | echo '$USER' | $USER |
| [x] | echo ' | print a new line |
| [x] | echo '$HOME > home.txt' | $HOME > home.txt |
| [x] | echo '$?' | $? |

### env

| # | Command | Expected result |
|:-:|---------|-----------------|
| [x] | env | show the environment variables |

### export
| # | Command | Expected result |
|:-:|---------|-----------------|
| [x] | export NEW_VAR=42 | create a new environment variable |
| [x] | export NEW_VAR="A little change" | replace the value of the environment variable |
| [x] | export NEW_VAR=$USER | replace the value of the environment variable |

### unset

| # | Command | Expected result |
|:-:|---------|-----------------|
| [x] | unset NEW_VAR | remove the environment variable |

### cd

| # | Command | Expected result |
|:-:|---------|-----------------|
| [x] | cd . | stay in the same directory |
| [x] | cd . ls | get an error |
| [x] | cd .. | go to the parent directory |
| [x] | cd /usr/bin | go to the /usr/bin directory |
| [x] | cd | go to the home directory |
| [x] | cd notexist | get an error |


### pwd

| # | Command | Expected result |
|:-:|---------|-----------------|
| [x] | pwd | show the current directory |

### Relative Path

| # | Command | Expected result |
|:-:|---------|-----------------|
| [x] | ./minishell | execute the minishell inside minishell |
| [x] | ../../../../../../bin/ls | list files |

### Environment path

| # | Command | Expected result |
|:-:|---------|-----------------|
| [x] | echo $PATH | show environment PATH |
| [x] | unset PATH | remove the environment variable |
| [x] | ls | get an error |
| [x] | export PATH=/bin:/usr/bin | set the environment variable |

### Redirection

| # | Command | Expected result |
|:-:|---------|-----------------|
| [x] | ls -l > test | create a file with the files list inside |
| [x] | repeat the last command more times | create a file with the files list inside |
| [x] | cat Makefile >> test | append the content of the Makefile to the file |
| [x] | wc -l < test | count lines in the file |
| [x] | wc -c < test > test_out | count words in the file and write the result in a new file |
| [x] | cat << EOF | print the content until write EOF |
> After here document, the prompt history don't have to show the content of the here document.

### Pipes

| # | Command | Expected result |
|:-:|---------|-----------------|
| [x] | cat Makefile \| grep NAME \| wc -l | count the number of lines with NAME in the Makefile |
| [x] | cat notexist \| wc -l | get an error |
### Go Crazy and history

| # | Command | Expected result |
|:-:|---------|-----------------|
| [x] | type, Ctrl-C the enter | buffer should be clean |
| [x] | Up, Down | navigate through history |
| [x] | Retry some command | execute the command |
| [x] | dsfdfdfd | get an error |
| [x] | wc -l < /etc/passwd > file1 > file2 > file3 > file4 | count lines in the file and write the result in the last redirection |
| [] | cat \| cat \| ls | behave in a normal way |

### Environment variables

| # | Command | Expected result |
|:-:|---------|-----------------|
| [x] | echo $USER | print the username |
| [x] | echo $notexist | print nothing |
| [x] | echo "$HOME" | print the home directory |

### Used tests
- minishell_tester: https://github.com/kichkiro/minishell_tester