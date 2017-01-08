/**********************************************************************
 * The JeamLand talker system
 * (c) Andy Fiddaman, 1994-96
 *
 * File:	mbs.h
 * Function:
 **********************************************************************/

struct mbs {
	char *id;
	char *room;
	char *desc;
	time_t last;
	struct mbs *next;
	};

struct umbs {
	char *id;
	time_t last;
	struct umbs *next;
	};

