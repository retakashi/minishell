# minishell

## Overview
Reimplementation of a simple shell script.
![gif](https://github.com/retakashi/minishell/blob/main/minishell.gif)

## Implementation Environment
- **Programming Language**: C
- **Operating Systems**: macOS
- **Compiler**: Apple Clang 15.0.0 (clang-1500.3.9.4), Target: arm64-apple-darwin23.6.0

If necessary, please install the following: [readline](https://formulae.brew.sh/formula/readline)

## Usage
``` bash
git clone ...
cd minishell
make
./minishell
```

## Features
minishell has the following features:
- external commands
- redirections(<, >, <<, >>)
- pipe(| character)
- expansion of environment variables (ex: echo $USER)
- exit status($?)
- ctrl+C, ctrl+D, ctrl+\
- history
- builtin:
  - echo with option -n
  - cd with only a relative or absolute path
  - pwd with no options
  - export with no options
  - unset with no options
  - env with no options or arguments
  - exit with no options
