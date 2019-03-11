#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

char **character_name_completion(const char *, int, int);
char *character_name_generator(const char *, int);

char *character_names[] = {
    "Arthur Dent",
    "Ford Prefect",
    "Tricia McMillan",
    "Zaphod Beeblebrox",
    NULL
};


char *character_names2[] = {
    "arthur Dent",
	"armor"
    "ford Prefect",
    "tricia McMillan",
    "zaphod Beeblebrox",
    NULL
};

char **
character_name_completion(const char *text, int start, int end)
{
    rl_attempted_completion_over = 1;
    return rl_completion_matches(text, character_name_generator);
}

char *
character_name_generator(const char *text, int state)
{
    static int list_index, len;
    char *name, **options = character_names;

    if (!state) {
        list_index = 0;
        len = strlen(text);
    }
	if (strncmp("show", rl_line_buffer, 4) == 0)
		options = character_names2;

    while ((name = options[list_index++])) {
        if (strncmp(name, text, len) == 0) {
			/*printf("\nname: %s",rl_line_buffer);*/
			return strdup(name);
        }
    }

    return NULL;
}

int main()
{
    char* input, shell_prompt[100];

    // Configure readline to auto-complete paths when the tab key is hit.
    rl_bind_key('\t', rl_complete);
	rl_attempted_completion_function = character_name_completion;

    for(;;) {
        // Create prompt string from user name and current working directory.
        snprintf(shell_prompt, sizeof(shell_prompt), "%s:%s $ ", getenv("USER"), getcwd(NULL, 1024));

        // Display prompt and read input (NB: input must be freed after use)...
        input = readline(shell_prompt);

        // Check for EOF.
        if (!input)
            break;

        // Add input to history.
        add_history(input);

        // Do stuff...
		printf("ras-%s", input);
		 //rl_redisplay (shell_prompt);
		 rl_forced_update_display ();
        // Free input.
        free(input);
    }
    return 0;
}
