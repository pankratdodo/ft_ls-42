# ft_ls

As simple as listing the files in a directory.

## About
The ls command is one of the first commands you have learned to use with shell. It is
also one you are using the most. Perhaps you have already asked yourself how is this
function coded? Thanks to this project, you will soon find out.
To Recode ls and some of its options will allow you to find out how to interact with
the file system using C. After all, you already know how to open, read, write and close a
file. But, what about the directories? Special files? Rights, dates or sizes of the files?

## Installation
1. Download/Clone this repo
```
git clone https://github.com/pankratdodo/ft_ls-42.git
```
2. `cd` into directrory and run `make`
```
make
./ft_ls
```
## Main project instructions
#### General Instructions
- Project must be written in C in accordance with [the Norm](https://github.com/R4meau/minishell/blob/master/norme.en.pdf).
- Program cannot have memory leaks.
- No Segmentation fault, bus error, double free, etc.
- Recode the system’s command ls.
- Its behavior must be identical to the original ls command with the following variations:
  - Amongst the numerous options available, we are asking you to create the following: `-l`, `-R`, `-a`, `-r` and `-t`.
  - Do not have to deal with the multiple column format for the exit when the option `-l` isn’t in the arguments.
  - You are not required to deal with ACL and extended attributes.
  - The overall display, depending on each option, must stay as identical as possible to the system command. Will be cordial when grading either the padding or the pagination, but no information can be missing.
- Check:
`man ls`
- Allowed to use the following functions:
  - *write*
  - *opendir, readdir, closedir*
  - *stat, lstat*
  - *getpwuid, getgrgid, listxattr, getxattr*
  - *time, ctime*
  - *readlink*
  - *malloc, free*
  - *perror, strerror*
  - *exit*
#### Bonus Part
  - Management of views in colors (Similar to option `-G`).
  - Management of options `-1`, `f`.
