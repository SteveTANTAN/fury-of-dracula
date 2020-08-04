////////////////////////////////////////////////////////////////////////
// COMP2521 20T2 ... the Fury of Dracula
// hunter.c: your "Fury of Dracula" hunter AI.
//
// 2014-07-01	v1.0	Team Dracula <cs2521@cse.unsw.edu.au>
// 2017-12-01	v1.1	Team Dracula <cs2521@cse.unsw.edu.au>
// 2018-12-31	v2.0	Team Dracula <cs2521@cse.unsw.edu.au>
// 2020-07-10	v3.0	Team Dracula <cs2521@cse.unsw.edu.au>
//
////////////////////////////////////////////////////////////////////////

#include "Game.h"
#include "hunter.h"
#include "HunterView.h"
#include "Places.h"

PlaceId findnextCityToAiming (HunterView hv, PlaceId dest, Player name) {
	
	if (HvGetPlayerLocation(hv, name) == dest) {
		return dest;
	}
	

	int pathLength = -1;
	PlaceId *path = HvGetShortestPathTo(hv, name,
										dest, &pathLength);
	
	
	PlaceId next = path[0];
	free(path);
	return next;
}

void decideHunterMove(HunterView hv)
{
	// TODO: Replace this with something better!
	//registerBestPlay("TO", "Have we nothing Toulouse?");
	
	
	
	Round round = HvGetRound(hv);
	Player whose_turn = HvGetPlayer(hv);
	PlaceId me_loc = HvGetPlayerLocation(hv, whose_turn);

	PlaceId decide_loc;
	PlaceId next_loc;
	Round temp;
	PlaceId drac_loc = HvGetLastKnownDraculaLocation(hv, &temp);
	
	if(whose_turn == PLAYER_LORD_GODALMING) {
		if (drac_loc == NOWHERE 
		&& round < 6) {
			decide_loc = BRUSSELS;
			next_loc = findnextCityToAiming (hv, BRUSSELS, whose_turn);
			registerBestPlay(placeIdToAbbrev(next_loc), "I am waitting you.");
		}
		if (drac_loc == NOWHERE 
		&& round >= 6) {
			
			registerBestPlay(placeIdToAbbrev(me_loc), "I AM LOOKING FOREARD YOU!");
			return;
		}
		if(drac_loc != NOWHERE) {
			decide_loc = drac_loc;
			next_loc = findnextCityToAiming (hv, decide_loc, whose_turn);
			registerBestPlay(placeIdToAbbrev(next_loc), "I am behind you");
		}

	}
	
	if(whose_turn == PLAYER_DR_SEWARD) {
		if (drac_loc == NOWHERE 
		&& round < 6) {
			decide_loc = STRASBOURG;
			next_loc = findnextCityToAiming (hv, BRUSSELS, whose_turn);
			registerBestPlay(placeIdToAbbrev(next_loc), "I am waitting you.");
		}
		if (drac_loc == NOWHERE 
		&& round >= 6) {
			
			registerBestPlay(placeIdToAbbrev(me_loc), "I AM LOOKING FOREARD YOU!");
			return;
		}
		if(drac_loc != NOWHERE) {
			decide_loc = drac_loc;
			next_loc = findnextCityToAiming (hv, decide_loc, whose_turn);
			registerBestPlay(placeIdToAbbrev(next_loc), "I am behind you");
		}
	
	}if(whose_turn == PLAYER_VAN_HELSING) {
		if (drac_loc == NOWHERE 
		&& round < 6) {
			decide_loc = FRANKFURT;
			next_loc = findnextCityToAiming (hv, BRUSSELS, whose_turn);
			registerBestPlay(placeIdToAbbrev(next_loc), "I am waitting you.");
		}
		if (drac_loc == NOWHERE 
		&& round >= 6) {
			
			registerBestPlay(placeIdToAbbrev(me_loc), "I AM LOOKING FOREARD YOU!");
			return;
		}
		if(drac_loc != NOWHERE) {
			decide_loc = drac_loc;
			next_loc = findnextCityToAiming (hv, decide_loc, whose_turn);
			registerBestPlay(placeIdToAbbrev(next_loc), "I am behind you");
		}
	

	}if(whose_turn == PLAYER_MINA_HARKER) {
		if (drac_loc == NOWHERE 
		&& round < 6) {
			decide_loc = NUREMBURG;
			next_loc = findnextCityToAiming (hv, BRUSSELS, whose_turn);
			registerBestPlay(placeIdToAbbrev(next_loc), "I am waitting you.");
		}
		if (drac_loc == NOWHERE 
		&& round >= 6) {
			
			registerBestPlay(placeIdToAbbrev(me_loc), "I AM LOOKING FOREARD YOU!");
			return;
		}
		if(drac_loc != NOWHERE) {
			decide_loc = drac_loc;
			next_loc = findnextCityToAiming (hv, decide_loc, whose_turn);
			registerBestPlay(placeIdToAbbrev(next_loc), "I am behind you");
		}
	}




}