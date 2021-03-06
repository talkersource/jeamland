/* An example calculator module written using the jlm library.
 * (c) Andy Fiddaman 1996.
 * JeamLand copyright applies.
 */
#include <stdio.h>
#include <string.h>
#include "jlm.h"

int
main()
{
	struct line *l;

	register_ident("Calculator jlm (c) A. Fiddaman");
	claim_command("calc");

	for(;;)
	{
		FILE *fp;
		char buf[0x100];

		fflush(stdout);
		if ((l = read_line()) == (struct line *)NULL)
			continue;

		if (l->action != T_CMD ||
		    l->user == (char *)NULL ||
		    l->cmd == (char *)NULL)
		{
			free_line(l);
			continue;
		}

		if (l->text == (char *)NULL)
		{
			write_user(l->user, "Syntax: calc <sum>.");
			free_line(l);
			continue;
		}

		if (strlen(l->text) > sizeof(buf) - 1)
		{
			write_user(l->user, "Sum too long!.");
			free_line(l);
			continue;
		}

		sprintf(buf, "echo '%s' | bc", l->text);
		if ((fp = popen(buf, "r")) == (FILE *)NULL)
		{
			write_user(l->user, "Cannot run bc.");
			free_line(l);
			continue;
		}

		fgets(buf, sizeof(buf), fp);
		pclose(fp);

		chattr(l->user, "d");
		write_user(l->user, "C calculator tells you: %s", buf);
		chattr(l->user, "z");
		free_line(l);
	}
	return 0;
}

