# logic-optimization-tool
The program is capable of reading pla files, printing metrics, and performing a simplified version of the espresso logic optimization heuristic. All the following commands are case sensitive.

help – Lists all available commands.

quit – Exits the program.

read_pla <file_name> – Reads the pla file. The file must be in the same directory as the executable and must not contain a file name extension.

write_eqn – writes the contents of the most recently read pla file to the terminal.

print_stats – writes the number of inputs, outputs, product terms, and literals of the most recently read pla file.

time – times the next command sent to program

espresso – performs the simplified espresso logic optimization heuristic on the last read pla file.

