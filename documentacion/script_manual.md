# script(1)

## NAME
`script` - make typescript of terminal session.

---

## SYNOPSIS
`script` [options] [file]

---

## DESCRIPTION
`script` makes a typescript of everything on your terminal session. The terminal data are stored in raw form to the log file and information about timing to another (optional) structured log file. The timing log file is necessary to replay the session later by `scriptreplay(1)` and to store additional information about the session.

Since version 2.35, `script` supports multiple streams and allows the logging of input and output to separate files or all the one file. This version also supports a new timing file which records additional information. The command `scriptreplay --summary` then provides all the information.

If the argument `file` or option `--log-out file` is given, `script` saves the dialogue in this file. If no filename is given, the dialogue is saved in the file **typescript**.

**Note**: logging input using `--log-in` or `--log-io` may record security-sensitive information as the log file contains all terminal session input (e.g., passwords) independently of the terminal echo flag setting.

---

## OPTIONS
- **`-a, --append`**
  Append the output to `file` or to `typescript`, retaining the prior contents.
- **`-c, --command command`**
  Run the `command` rather than an interactive shell.
- **`-E, --echo when`**
  This option controls the `ECHO` flag for the slave end of the session’s pseudoterminal. The supported modes are `always`, `never`, or `auto`.
- **`-e, --return`**
  Return the exit status of the child process.
- **`-f, --flush`**
  Flush output after each write.
- **`--force`**
  Allow the default output file `typescript` to be a hard or symbolic link.
- **`-B, --log-io file`**
  Log input and output to the same file.
- **`-I, --log-in file`**
  Log input to the file.
- **`-O, --log-out file`**
  Log output to the file. The default is to log output to the file with name `typescript` if the option `--log-out` or `--log-in` is not given.
- **`-T, --log-timing file`**
  Log timing information to the file.
- **`-m, --logging-format format`**
  Force use of advanced or classic format.
- **`-o, --output-limit size`**
  Limit the size of the typescript and timing files to size and stop the child process after this size is exceeded.
- **`-q, --quiet`**
  Be quiet (do not write start and done messages to standard output).
- **`-t[file], --timing[=file]`**
  Output timing data to standard error, or to `file` when given. **(Deprecated)**
- **`-V, --version`**
  Display version information and exit.
- **`-h, --help`**
  Display help text and exit.

---

## SIGNALS
Upon receiving `SIGUSR1`, `script` immediately flushes the output files.

---

## ENVIRONMENT
- **`SHELL`**
  If the variable `SHELL` exists, the shell forked by `script` will be that shell. If `SHELL` is not set, the Bourne shell is assumed.

---

## NOTES
The `script` ends when the forked shell exits (e.g., a `control-D`).

Certain interactive commands, such as `vi(1)`, create garbage in the typescript file. `script` works best with commands that do not manipulate the screen.

It is not recommended to run `script` in non-interactive shells or in command pipes.

---

## BUGS
- `script` places everything in the log file, including linefeeds and backspaces, which is not what the naive user expects.
- `script` is primarily designed for interactive terminal sessions. When `stdin` is not a terminal, the session can hang.