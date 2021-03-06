/*aqu4, daughter of pr0t0, half-sister to Johnsbot!
 * Copyright 2014 Subsentient, all rights reserved.
 * Hostname=irc.freenode.net
Nick=aqu42
Admin=*!*@unaffiliated/subsen
Channel=#epoch
Channel=##aqu4bot
 *
 * */
//Test

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include "aqu4.h"

Bool ShowOutput;


static void SigHandler(int Signal)
{
	switch (Signal)
	{
		case SIGINT:
			puts("Caught SIGINT, shutting down.");
			IRC_Quit(NULL);
			IRC_ShutdownChannelTree();
			Auth_ShutdownAdmin();
			CMD_SaveSeenDB();
			Auth_ShutdownBlacklist();
			exit(0);
			break;
		default:
			break;
	}
}

int main(int argc, char **argv)
{
	
	signal(SIGINT, SigHandler);
	
	if (argc == 2)
	{
		if (!strcmp(argv[1], "--verbose"))
		{
			ShowOutput = true;
		}
	}
		
	puts("\033[36maqu4bot " BOT_VERSION " starting up.\033[0m\n");
	
	if (!Config_ReadConfig())
	{
		return 1;
	}

	if (!IRC_Connect())
	{
		return 1;
	}
	
	/*Load the seen command data.*/
	CMD_LoadSeenDB();
	
	/*Load the blacklist data.*/
	Auth_BlacklistLoad();
	
	/*The main IRC loop.*/
	IRC_Loop();
	
	return 0;
}
