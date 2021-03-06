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
//////////////////////////////////////////////////////////////////////////////
///
///                      MY OWEN FUCTION
///
//////////////////////////////////////////////////////////////////////////////
PlaceId findnextCityToAiming (HunterView hv, PlaceId dest, Player name) {
	Round temp = -1;
	// if we have  arrive the dracula trail loc
	// tring to find the next place;
	if (HvGetPlayerLocation(hv, name) == HvGetLastKnownDraculaLocation(hv, &temp)) {
		//return dest;
		int pathLength = -1;
		PlaceId *path = HvWhereCanIGoByType(hv, true, false, false , &pathLength);

		for(int i = pathLength - 1; i >= 0; i--) {
			if(path[i] != HvGetPlayerLocation(hv, 0)
			&& path[i] != HvGetPlayerLocation(hv, 1)
			&& path[i] != HvGetPlayerLocation(hv, 2)
			&& path[i] != HvGetPlayerLocation(hv, 3)){
				PlaceId next = path[i];
				free(path);
				return next;
			}

		}
		PlaceId next = path[0];

		free(path);
		return next;

	}
	// if we have not find the trail of dracula
	// doing research.
	if (HvGetPlayerLocation(hv, name) == dest) {
		//return dest;
		int pathLength = -1;
		PlaceId *path = HvWhereCanIGoByType(hv, true, false, false , &pathLength);

		for(int i = pathLength - 1; i >= 0; i--) {
			if(path[i] != HvGetPlayerLocation(hv, 0)
			&& path[i] != HvGetPlayerLocation(hv, 1)
			&& path[i] != HvGetPlayerLocation(hv, 2)
			&& path[i] != HvGetPlayerLocation(hv, 3)){
				PlaceId next = path[i];
				free(path);
				return next;
			}

		}
		PlaceId next = path[0];
		free(path);
		return next;

	}

	// else, if none above here
	// just find the next city next to dest.
	int pathLength = -1;
	PlaceId *path = HvGetShortestPathTo(hv, name,
										dest, &pathLength);


	PlaceId next = path[0];
	free(path);
	return next;
}


void decideHunterMove(HunterView hv)
{
	// initial all the information we need.
	Round round = HvGetRound(hv);
	Player whose_turn = HvGetPlayer(hv);
	PlaceId me_loc = HvGetPlayerLocation(hv, whose_turn);

	PlaceId decide_loc;
	PlaceId next_loc;
	Round last_know_round = -1;
	PlaceId drac_loc = HvGetLastKnownDraculaLocation(hv, &last_know_round);



	int HP = HvGetHealth(hv, whose_turn);

	// low hp, rest repush hp
	if(HP <= 3) {
		registerBestPlay(placeIdToAbbrev(me_loc), "I AM going to rest.");
		return;
	}

	/*
	PlaceId vam_loc = HvGetVampireLocation(hv);

	if(vam_loc >= MIN_REAL_PLACE && vam_loc <= MAX_REAL_PLACE){

		int shortpath = MAX_REAL_PLACE;
		for (int i = 0; i < 4; i++){
			int pathLength = -1;
			PlaceId *path =
			HvGetShortestPathTo(hv, i, vam_loc, &pathLength);
			if(shortpath > pathLength) {
				shortpath = pathLength;
			}

			free(path);
		}
		int pathLength = -1;
		PlaceId *path = HvGetShortestPathTo(hv, whose_turn, vam_loc, &pathLength);

		free(path);
		if (pathLength == shortpath) {
			decide_loc = vam_loc;
			next_loc = findnextCityToAiming (hv, decide_loc, whose_turn);
			registerBestPlay(placeIdToAbbrev(next_loc), "I am going to find vampire.");
			return;
		}
	}
	*/

	if (drac_loc == NOWHERE
	&& round >= 6) {

		registerBestPlay(placeIdToAbbrev(me_loc), "I AM LOOKING FOREARD YOU!");
		return;
	}
	Round round_diff = round - last_know_round;
	// if the trail has been long time no update, just update it
	if(round_diff >= 10 && round >= 9) {
		registerBestPlay(placeIdToAbbrev(me_loc), "I am going to check where u r  <_>");
		return;
	}




	if(whose_turn == PLAYER_LORD_GODALMING) {
		/*

		if(round == 1 && drac_loc == NOWHERE) {
			registerBestPlay("MN", "I am comming.");
			return;
		}
		if(round == 2 && drac_loc == NOWHERE) {
			registerBestPlay("LO", "I am comming.");
			return;
		}
		if(round == 3 && drac_loc == NOWHERE) {
			registerBestPlay("SW", "I am comming.");
			return;
		}
		if(round == 4 && drac_loc == NOWHERE) {
			registerBestPlay("LV", "I am comming.");
			return;
		}
		*/
		if(round == 0 && me_loc == NOWHERE) {
			registerBestPlay(placeIdToAbbrev(MANCHESTER), "I am comming.");
			return;
		}
		if (drac_loc == NOWHERE
		&& round < 6) {
			decide_loc = STRASBOURG;
			next_loc = findnextCityToAiming (hv, decide_loc, whose_turn);
			registerBestPlay(placeIdToAbbrev(next_loc), "I am waitting you.");
			return;
		}

		if(drac_loc != NOWHERE) {

			decide_loc = drac_loc;
			next_loc = findnextCityToAiming (hv, decide_loc, whose_turn);
			registerBestPlay(placeIdToAbbrev(next_loc), "I am behind you");
			return;
		}


	}

	if(whose_turn == PLAYER_DR_SEWARD) {

		if(round == 0 && me_loc == NOWHERE) {
			registerBestPlay(placeIdToAbbrev(NAPLES), "I am comming.");
			return;

		}

		if (drac_loc == NOWHERE
		&& round < 6) {
			decide_loc = COLOGNE;
			next_loc = findnextCityToAiming (hv, decide_loc, whose_turn);
			registerBestPlay(placeIdToAbbrev(next_loc), "I am waitting you.");
			return;

		}

		/*
		if(round == 0 && me_loc == NOWHERE) {
			registerBestPlay("MA", "I am comming.");
			return;
		}
		if(round == 1 && drac_loc == NOWHERE) {
			registerBestPlay("BO", "I am comming.");
			return;
		}
		if(round == 2 && drac_loc == NOWHERE) {
			registerBestPlay("NA", "I am comming.");
			return;
		}
		if(round == 3 && drac_loc == NOWHERE) {
			registerBestPlay("LE", "I am comming.");
			return;
		}
		if(round == 4 && drac_loc == NOWHERE) {
			registerBestPlay("PA", "I am comming.");
			return;
		}
		*/
		if(drac_loc != NOWHERE) {
			decide_loc = drac_loc;
			next_loc = findnextCityToAiming (hv, decide_loc, whose_turn);
			registerBestPlay(placeIdToAbbrev(next_loc), "I am behind you");
			return;

		}

	}if(whose_turn == PLAYER_VAN_HELSING) {
		
		if(round == 0 && me_loc == NOWHERE) {
			registerBestPlay(placeIdToAbbrev(CASTLE_DRACULA), "I am comming.");
			return;

		}
		if (drac_loc == NOWHERE
		&& round < 6) {
			decide_loc = TOULOUSE;
			next_loc = findnextCityToAiming (hv, decide_loc, whose_turn);
			registerBestPlay(placeIdToAbbrev(next_loc), "I am waitting you.");
			return;

		}
		
		/*
		if(round == 0 && me_loc == NOWHERE) {
			registerBestPlay("RO", "I am comming.");
			return;
		}
		if(round == 1 && drac_loc == NOWHERE) {
			registerBestPlay("MI", "I am comming.");
			return;
		}
		if(round == 2 && drac_loc == NOWHERE) {
			registerBestPlay("ZU", "I am comming.");
			return;
		}
		if(round == 3 && drac_loc == NOWHERE) {
			registerBestPlay("ST", "I am comming.");
			return;
		}
		if(round == 4 && drac_loc == NOWHERE) {
			registerBestPlay("LI", "I am comming.");
			return;
		}
		*/
		if(drac_loc != NOWHERE) {
			decide_loc = drac_loc;
			next_loc = findnextCityToAiming (hv, decide_loc, whose_turn);
			registerBestPlay(placeIdToAbbrev(next_loc), "I am behind you");
			return;

		}


	}if(whose_turn == PLAYER_MINA_HARKER) {
		
		if(round == 0 && me_loc == NOWHERE) {
			registerBestPlay(placeIdToAbbrev(MADRID), "I am comming.");
			return;

		}
		if (drac_loc == NOWHERE
		&& round < 6) {
			decide_loc = BUDAPEST;
			next_loc = findnextCityToAiming (hv, decide_loc, whose_turn);
			registerBestPlay(placeIdToAbbrev(next_loc), "I am waitting you.");
			return;

		}
		
	/*
		if(round == 0 && me_loc == NOWHERE) {
			registerBestPlay("GA", "I am comming.");
			return;
		}
		if(round == 1 && drac_loc == NOWHERE) {
			registerBestPlay("CD", "I am comming.");
			return;
		}
		if(round == 2 && drac_loc == NOWHERE) {
			registerBestPlay("KL", "I am comming.");
			return;
		}
		if(round == 3 && drac_loc == NOWHERE) {
			registerBestPlay("BE", "I am comming.");
			return;
		}
		if(round == 4 && drac_loc == NOWHERE) {
			registerBestPlay("BD", "I am comming.");
			return;
		}
		*/
		if(drac_loc != NOWHERE) {
			decide_loc = drac_loc;
			next_loc = findnextCityToAiming (hv, decide_loc, whose_turn);
			registerBestPlay(placeIdToAbbrev(next_loc), "I am behind you");
			return;

		}
	}




}
