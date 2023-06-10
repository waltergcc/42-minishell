# minishell

# Minishell Evaluation Page

## Compile

- Use "make -n" to see if compilation use "-Wall -Wextra -Werror". If not, select the "invalid compilation' flag.

## Simple Command & global variables

- Execute a simple command with an absolute path like /bin/ls, or any other command without any options.
```
input : [/bin/ls]
output: [files and folders of current folder]
```
```
input : [date]
output: [current date]
```
```
input : [echo Hello]
output: [Hello]
```
```
input : [pwd]
output: [current path]
```
- Test an empty command.
```
input : []
output: []
```
- Test only spaces or tabs.

```
input : [ ]
output: []
```
```
input : [    ]
output: []
```
- How many global variables are used? Why? Ask the evaluated student to give you a concrete example of why it feels mandatory or logical.



## Arguments

- Execute a simple command with an absolute path like /bin/ls, or any other command with arguments but without any quotes or double quotes.
- Repeat multiple times with different commands and arguments.

## echo

- Execute the echo command with or without arguments, or the option.
- Repeat multiple times with different arguments.

## exit

- Execute exit command with or without arguments.
- Repeat multiple times with different arguments.
- Don't forget to relaunch the minishell

## Return value of a process

- Execute a simple command with an absolute path like /bin/Is, or any other command with arguments but without any quotes and double quotes. Then execute echo $?
- Check the printed value. You can do the same in bash in order to compare the results.
- Repeat multiple times with different commands and arguments. Try some wrong commands like'/bin/Is filethatdoesntexistl
- Try anything like expr $? $?

## Signals

- ctrl-C in an empty prompt should display a new line with a new prompt.
- ctrl-/ in an empty prompt should not do anything.
- ctrl-D in an empty prompt should quit minishell --> RELAUNCH!
- ctrl-C in a prompt after you wrote some stuff should display a new line with a new prompt.
- The buffer should be clean too. Press "Enter' to make sure nothing from the previous line is executed.
- ctrl-D in a prompt after you wrote some stuff should not do anything.
- ctrl-\ in a prompt after you wrote some stuff should not do anything.
- Try ctrl-C after running a blocking command like cat without arguments or grep "something".
- Try ctrl-/ after running a blocking command like cat without arguments or grep "something".
- Try ctrl-D after running a blocking command like cat without arguments or grep "something".
- Repeat multiple times using different commands.

## Double Quotes

- Execute a simple command with arguments and, this time, use also double quotes (you should try to include whitespaces too).
- Try a command like : echo ''cat lol.c cat > Iol.c"
- Try anything except $.

## Single Quotes

- Execute commands with single quotes as arguments.
- Try empty arguments.
- Try environment variables, whitespaces, pipes, redirection in the single quotes.
- echo '$USER' must print "$USER".
- Nothing should be interpreted.

## env

- Check if env shows you the current environment variables. Yes X No
export

## export
- Export environment variables, create new ones and replace old ones.

## unset

- Export environment variables, create new ones and replace old ones.
- Use unset to remove some of them.
- Check the result with env.

## cd
- Use the command cd to move the working directory and check if you are in the right directory with /bin/ls
- Repeat multiple times with working and not working cd
- Also, try '.' and as arguments.

## pwd

- Use the command pwd.
- Repeat multiple times in different directories.

## Relative Path

- Execute commands but this time use a relative path.
- Repeat multiple times in different directories with a complex relative path (lots of ..).

## Environment path

- Execute commands but this time without any path (ls, wc, awk and so forth).
- Unset the $PATH and ensure commands are not working anymore.
- Set the $PATH to a multiple directory value (directoryl:directory2) and ensure that directories are checked in order from left to right.

## Redirection

- Execute commands with redirections < and/or >
- Repeat multiple times with different commands and arguments and sometimes change > with >>
- Check if multiple tries of the same redirections fail.
- Test << redirection (it doesn't have to update the history).

## Pipes

- Execute commands with pipes like 'cat file | grep bla | more
- Repeat multiple times with different commands and arguments.
Try some wrong commands like 'ls filethatdoesntexist |grep bla | more'
- Try to mix pipes and redirections.

## Go Crazy and history

- Type a command line, then use ctrl-C and press "Enter". The buffer should be clean and there should be nothing left to execute.
- Can we navigate through history using Up and Down?
- Can we retry some command?
- Execute commands that should not work like 'dsbksdgbksdghsd'. Ensure minishell doesn't crash and prints an error.
- 'cat | cat | ls' should behave in a "normal way".
- Try to execute a long command with a ton of arguments.

## Environment variables

- Execute echo with some environment variables ($variable) as arguments.
- Check that $ is interpreted as an environment variable.
- Check that double quotes interpolate $.
- Check that USER exists. Otherwise, set it,
- echo "$USER" should print the value of the USER variable.
## Used tests
- minishell_tester: https://github.com/kichkiro/minishell_tester