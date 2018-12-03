edojo
by T Fabiha and Ivan Zhang

Features:
- Forks and executes commands!
- Parses multiple commands on one line!
- Redirects using >, <!
- Guaranteed to regrow hair!
- Can summon a winged unicorn for fast & magical transit!

Attempted:
The following did not end up working, but have been left in the code, commented out.
- Could not get pipes to work
- Tried to implement >>, but it kept overwriting the file
- Looked at replacing ~/ with home directory, got seg faults
- Was unable to have the "puppy" command produce a puppy and eject it from the optical drive.

Bugs:
- Putting two ;'s next to each other will break the parser
- Redirecting to a file that does not exist occasionally does not work.
- Hair regrowth function may result in a seg fault.
- Occasionally, the unicorn command will fail, opening a great chasm in the earth and summoning the demon Beelzebub, who will proceeded to unleash his wrath and begin his reign of terror.
	
Files & Function Headers:

tools.c Handles all commands entered into the shell

	/*======== int run_multiple_cmd() ==========
	Inputs:  char **ary
	Returns: 0 after all commands are run

	Goes through ary and runs each commands
	Determines what to run based what is in the commands (i.e. <, >, |)
	Checks to see if command is 'exit' or 'cd' and executes it accordingly
	====================*/

	/*======== char** parse_args() ==========
	Inputs:  char *line, char c
	Returns: Array of strings where each entry is a token 
	separated by c

	If line contains multiple tokens separated by c, this 
	function will put each token into an array of strings
	====================*/

	/*======== char** parse_args_custom() ==========
	Inputs:  char **args
	Returns: Array of strings where each entry contains the same sign
	(i.e. >, <, |). Example: "tr a-z A-Z < wholist > foo"
	==> args: ["tr", "a-z", "A-z", "<", "wholist", ">", "foo"]
	==> ['tr a-z A-z < wholist', 'wholist > foo']

	If args contains multiple different signs (<, >, |), this fuction puts
	statements with the same sign together (i.e l > l > l, l | l | l, etc.).
	====================*/

	/*======== int count_tokens() ==========
	Inputs:  char **ary
	Returns: Number of *char in ary

	Uses sizeof to determine the number of *char in ary
	====================*/
	
parse.c Handles all line parsing functions
	
	/*======== char* trim() ==========
	Inputs:  char *str

	Returns: String that is trimmed of all extraneous spaces

	Removes all extra spaces, newlines, and tabs in the front, end,
	and in between commands
	====================*/

	/*======== void run_command() ==========
	Inputs:  char **ary 
	Returns: Doesn't return anything :)

	Runs the command in ary.
	Checks to see if command exits.
	====================*/

	/*======== void run_command_custom() ==========
	Inputs:  char **ary, int fd
	Returns: Doesn't return anything :)

	Same as run_command() except when the command is not found,
	fd(STDOUT) is moved to 1. 
	====================*/

	/*======== void redirect_STDIN() ==========
	Inputs:  char *ary
	Returns: Doesn't return anything :)

	Parses and executes STDIN command given in ary.
	Example: ary ==> "ls > ls.txt" or "ls > ls.txt > l.txt"
	====================*/

	/*======== void redirect_STDOUT() ==========
	Inputs:  char *ary
	Returns: Doesn't return anything :)

	Parses and executes STDOUT command given in ary.
	Example: ary ==> "ls < ls.txt" or "ls < ls.txt < l.txt"
	====================*/

	/*======== void redirect_pipes() ==========
	Inputs:  char *ary
	Returns: Doesn't return anything :)

	Handles and runs command line input that contains >, <, |.
	Example: ary ==> "ls | wc > l.txt"
	====================*/
	
	/*======== int check_char_cmd() ==========
	Inputs:  char *ary, char c
	Returns: 1 if c is found, 0 if c is not found

	Checks to see if c exists in ary.
	====================*/

	/*======== int check_char_cmd() ==========
	Inputs:  char *ary, char c
	Returns: 1 if c is found, 0 if c is not found

	Checks to see if c exists in ary.
	====================*/
	
dwsh.c
	Handles the forking an executing of commands...

magical.c
	UNOCORNS!
