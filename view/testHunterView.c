////////////////////////////////////////////////////////////////////////
// COMP2521 20T2 ... the Fury of Dracula
// testHunterView.c: test the HunterView ADT
//
// As supplied, these are very simple tests.  You should write more!
// Don't forget to be rigorous and thorough while writing tests.
//
// 2014-07-01	v1.0	Team Dracula <cs2521@cse.unsw.edu.au>
// 2017-12-02	v1.1	Team Dracula <cs2521@cse.unsw.edu.au>
// 2018-12-31	v2.0	Team Dracula <cs2521@cse.unsw.edu.au>
// 2020-07-10	v3.0	Team Dracula <cs2521@cse.unsw.edu.au>
//
////////////////////////////////////////////////////////////////////////

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Game.h"
#include "HunterView.h"
#include "Places.h"
#include "testUtils.h"

int main(void)
{
	{///////////////////////////////////////////////////////////////////
	
		printf("Basic initialisation\n");
		
		char *trail = "";
		Message messages[] = {};
		HunterView hv = HvNew(trail, messages);

		assert(HvGetRound(hv) == 0);
		assert(HvGetPlayer(hv) == PLAYER_LORD_GODALMING);
		assert(HvGetScore(hv) == GAME_START_SCORE);
		assert(HvGetHealth(hv, PLAYER_LORD_GODALMING) == GAME_START_HUNTER_LIFE_POINTS);
		assert(HvGetHealth(hv, PLAYER_DRACULA) == GAME_START_BLOOD_POINTS);
		assert(HvGetVampireLocation(hv) == NOWHERE);

		HvFree(hv);
		printf("Test passed\n");
	}

	{///////////////////////////////////////////////////////////////////
	
		printf("After Lord Godalming's turn\n");

		char *trail =
			"GST....";
		
		Message messages[1] = {};
		HunterView hv = HvNew(trail, messages);

		assert(HvGetRound(hv) == 0);
		assert(HvGetPlayer(hv) == PLAYER_DR_SEWARD);
		assert(HvGetScore(hv) == GAME_START_SCORE);
		assert(HvGetPlayerLocation(hv, PLAYER_LORD_GODALMING) == STRASBOURG);
		assert(HvGetPlayerLocation(hv, PLAYER_DR_SEWARD) == NOWHERE);

		HvFree(hv);
		printf("Test passed!\n");
	}
	
	{///////////////////////////////////////////////////////////////////
	
		printf("After Van Helsing's turn\n");

		char *trail =
			"GST.... SAO.... HZU....";
		
		Message messages[3] = {};
		HunterView hv = HvNew(trail, messages);

		assert(HvGetRound(hv) == 0);
		assert(HvGetPlayer(hv) == PLAYER_MINA_HARKER);
		assert(HvGetScore(hv) == GAME_START_SCORE);
		assert(HvGetPlayerLocation(hv, PLAYER_LORD_GODALMING) == STRASBOURG);
		assert(HvGetPlayerLocation(hv, PLAYER_DR_SEWARD) == ATLANTIC_OCEAN);
		assert(HvGetPlayerLocation(hv, PLAYER_VAN_HELSING) == ZURICH);
		assert(HvGetPlayerLocation(hv, PLAYER_MINA_HARKER) == NOWHERE);
		assert(HvGetPlayerLocation(hv, PLAYER_DRACULA) == NOWHERE);
		
		HvFree(hv);
		printf("Test passed!\n");
	}
	
	{///////////////////////////////////////////////////////////////////
	
		printf("After Dracula's turn\n");

		char *trail =
			"GST.... SAO.... HZU.... MBB.... DC?.V..";
		
		Message messages[] = {
			"Hello", "Goodbye", "Stuff", "...", "Mwahahahaha"
		};
		
		HunterView hv = HvNew(trail, messages);

		assert(HvGetRound(hv) == 1);
		assert(HvGetPlayer(hv) == PLAYER_LORD_GODALMING);
		assert(HvGetScore(hv) == GAME_START_SCORE - SCORE_LOSS_DRACULA_TURN);
		assert(HvGetHealth(hv, PLAYER_DRACULA) == GAME_START_BLOOD_POINTS);
		assert(HvGetPlayerLocation(hv, PLAYER_LORD_GODALMING) == STRASBOURG);
		assert(HvGetPlayerLocation(hv, PLAYER_DR_SEWARD) == ATLANTIC_OCEAN);
		assert(HvGetPlayerLocation(hv, PLAYER_VAN_HELSING) == ZURICH);
		assert(HvGetPlayerLocation(hv, PLAYER_MINA_HARKER) == BAY_OF_BISCAY);
		assert(HvGetPlayerLocation(hv, PLAYER_DRACULA) == CITY_UNKNOWN);
		assert(HvGetVampireLocation(hv) == CITY_UNKNOWN);
		Round round = -1;
		assert(HvGetLastKnownDraculaLocation(hv, &round) == NOWHERE);

		HvFree(hv);
		printf("Test passed!\n");
	}
	
	{///////////////////////////////////////////////////////////////////
	
		printf("Encountering Dracula\n");

		char *trail =
			"GST.... SAO.... HCD.... MAO.... DGE.V.. "
			"GGEVD..";
		
		Message messages[] = {
			"Hello", "Goodbye", "Stuff", "...", "Mwahahahaha",
			"Aha!"
		};
		
		HunterView hv = HvNew(trail, messages);
		
		assert(HvGetHealth(hv, PLAYER_LORD_GODALMING) ==
				GAME_START_HUNTER_LIFE_POINTS - LIFE_LOSS_DRACULA_ENCOUNTER);
		assert(HvGetHealth(hv, PLAYER_DRACULA) ==
				GAME_START_BLOOD_POINTS - LIFE_LOSS_HUNTER_ENCOUNTER);
		assert(HvGetPlayerLocation(hv, PLAYER_LORD_GODALMING) == GENEVA);
		assert(HvGetPlayerLocation(hv, PLAYER_DRACULA) == GENEVA);
		assert(HvGetVampireLocation(hv) == NOWHERE);
		Round round = -1;
		assert(HvGetLastKnownDraculaLocation(hv, &round) == GENEVA);
		assert(round == 0);

		HvFree(hv);
		printf("Test passed\n");
	}

	{///////////////////////////////////////////////////////////////////
	
		printf("Test for Dracula doubling back at sea, "
			   "and losing blood points\n");

		char *trail =
			"GGE.... SGE.... HGE.... MGE.... DS?.... "
			"GST.... SST.... HST.... MST.... DD1....";
		
		Message messages[] = {
			"Party at Geneva", "Okay", "Sure", "Let's go", "Mwahahahaha",
			"", "", "", "", "Back I go"
		};
		
		HunterView hv = HvNew(trail, messages);

		assert(HvGetRound(hv) == 2);
		assert(HvGetPlayer(hv) == PLAYER_LORD_GODALMING);
		assert(HvGetScore(hv) == GAME_START_SCORE - 2 * SCORE_LOSS_DRACULA_TURN);
		assert(HvGetHealth(hv, PLAYER_DRACULA) ==
				GAME_START_BLOOD_POINTS - (2 * LIFE_LOSS_SEA));
		assert(HvGetPlayerLocation(hv, PLAYER_DRACULA) == SEA_UNKNOWN);

		HvFree(hv);
		printf("Test passed!\n");
	}

	{///////////////////////////////////////////////////////////////////
	
		printf("Testing a hunter 'dying'\n");
		
		char *trail =
			"GGE.... SGE.... HGE.... MGE.... DC?.V.. "
			"GGE.... SGE.... HGE.... MGE.... DSTT... "
			"GGE.... SGE.... HGE.... MGE.... DHIT... "
			"GGE.... SGE.... HGE.... MGE.... DD1T... "
			"GSTTTTD";
		
		Message messages[21] = {};
		HunterView hv = HvNew(trail, messages);
		
		assert(HvGetScore(hv) == GAME_START_SCORE
		                         - 4 * SCORE_LOSS_DRACULA_TURN
		                         - SCORE_LOSS_HUNTER_HOSPITAL);
		assert(HvGetHealth(hv, PLAYER_LORD_GODALMING) == 0);
		assert(HvGetPlayerLocation(hv, PLAYER_LORD_GODALMING) == HOSPITAL_PLACE);
		assert(HvGetPlayerLocation(hv, PLAYER_DRACULA) == STRASBOURG);
		
		HvFree(hv);
		printf("Test passed!\n");
	}

	{///////////////////////////////////////////////////////////////////
	
		printf("Testing Dracula doubling back to Castle Dracula\n");
		
		char *trail =
			"GGE.... SGE.... HGE.... MGE.... DCD.V.. "
			"GGE.... SGE.... HGE.... MGE.... DD1T...";
		
		Message messages[10] = {};
		HunterView hv = HvNew(trail, messages);
		
		assert(HvGetHealth(hv, PLAYER_DRACULA) ==
				GAME_START_BLOOD_POINTS + (2 * LIFE_GAIN_CASTLE_DRACULA));
		assert(HvGetPlayerLocation(hv, PLAYER_DRACULA) == CASTLE_DRACULA);
		
		HvFree(hv);
		printf("Test passed!\n");
	}
	
	{///////////////////////////////////////////////////////////////////
	
		printf("Testing vampire location\n");
		
		char *trail =
			"GVI.... SGE.... HGE.... MGE.... DCD.V.. "
			"GBD.... SGE.... HGE.... MGE.... DC?T... "
			"GSZ.... SGE.... HGE.... MGE.... DC?T... "
			"GSZ.... SGE.... HGE....";
		
		Message messages[18] = {};
		HunterView hv = HvNew(trail, messages);
		
		assert(HvGetPlayerLocation(hv, PLAYER_DRACULA) == CITY_UNKNOWN);
		assert(HvGetVampireLocation(hv) == CASTLE_DRACULA);
		
		HvFree(hv);
		printf("Test passed!\n");
	}
	
	{///////////////////////////////////////////////////////////////////
	
		printf("Testing a vampire maturing\n");
		
		char *trail =
			"GGE.... SGE.... HGE.... MGE.... DC?.V.. "
			"GGE.... SGE.... HGE.... MGE.... DC?T... "
			"GGE.... SGE.... HGE.... MGE.... DC?T... "
			"GGE.... SGE.... HGE.... MGE.... DC?T... "
			"GGE.... SGE.... HGE.... MGE.... DC?T... "
			"GGE.... SGE.... HGE.... MGE.... DC?T... "
			"GGE.... SGE.... HGE.... MGE.... DC?T.V.";
		
		Message messages[35] = {};
		HunterView hv = HvNew(trail, messages);
		
		assert(HvGetScore(hv) == GAME_START_SCORE
		                         - 7 * SCORE_LOSS_DRACULA_TURN
		                         - SCORE_LOSS_VAMPIRE_MATURES);
		assert(HvGetPlayerLocation(hv, PLAYER_DRACULA) == CITY_UNKNOWN);
		assert(HvGetVampireLocation(hv) == NOWHERE);
		
		HvFree(hv);
		printf("Test passed!\n");
	}
	
	{///////////////////////////////////////////////////////////////////
	
		printf("Testing Dracula's last known location 1\n");
		
		char *trail =
			"GGE.... SGE.... HVI.... MGE.... DCD.V.. "
			"GGE.... SGE.... HBD.... MGE.... DKLT... "
			"GGE.... SGE.... HSZ.... MGE.... DC?T... "
			"GGE.... SGE.... HKLT... MGE.... DC?T... "
			"GGE.... SGE.... HCDV... MGE.... DD1T...";
	
		Message messages[25] = {};
		HunterView hv = HvNew(trail, messages);
		
		assert(HvGetPlayerLocation(hv, PLAYER_DRACULA) == CITY_UNKNOWN);
		Round round = -1;

		assert(HvGetLastKnownDraculaLocation(hv, &round) == KLAUSENBURG);
		assert(round == 1);
		
		HvFree(hv);
		printf("Test passed!\n");
	}
	
	{///////////////////////////////////////////////////////////////////
		
		printf("Testing shortest path 1\n");
		
		char *trail =
			"GLS.... SLS.... HSW.... MMR.... DCD.V..";
		
		Message messages[5] = {};
		HunterView hv = HvNew(trail, messages);
		
		{
			printf("\tLisbon -> Barcelona (Lord Godalming, Round 1)\n");
			int pathLength = -1;
			PlaceId *path = HvGetShortestPathTo(hv, PLAYER_LORD_GODALMING,
			                                    BARCELONA, &pathLength);
			assert(pathLength == 2);
			assert(path[0] == MADRID);
			assert(path[1] == BARCELONA);
			free(path);
		}
		
		{
			printf("\tLisbon -> Cologne (Lord Godalming, Round 1)\n");
			int pathLength = -1;
			PlaceId *path = HvGetShortestPathTo(hv, PLAYER_LORD_GODALMING,
			                                    COLOGNE, &pathLength);
			assert(pathLength == 3);
			assert(path[0] == MADRID);
			assert(path[1] == BORDEAUX);
			assert(path[2] == COLOGNE);
			free(path);
		}
		
		{
			printf("\tSwansea -> Hamburg (Van Helsing, Round 1)\n");
			int pathLength = -1;
			PlaceId *path = HvGetShortestPathTo(hv, PLAYER_VAN_HELSING,
			                                    HAMBURG, &pathLength);
			assert(pathLength == 3);
			assert(path[0] == EDINBURGH);
			assert(path[1] == NORTH_SEA);
			assert(path[2] == HAMBURG);
			free(path);
		}
		
		{
			printf("\tMarseilles -> Constanta (Mina Harker, Round 1)\n");
			int pathLength = -1;
			PlaceId *path = HvGetShortestPathTo(hv, PLAYER_MINA_HARKER,
			                                    CONSTANTA, &pathLength);
			assert(pathLength == 4);
			assert(path[0] == GENOA || path[0] == MILAN);
			assert(path[1] == VENICE);
			assert(path[2] == BUDAPEST);
			assert(path[3] == CONSTANTA);
			free(path);
		}
		
		{
			printf("\tLisbon -> Castle Dracula (Dr. Seward, Round 1)\n");
			int pathLength = -1;
			PlaceId *path = HvGetShortestPathTo(hv, PLAYER_DR_SEWARD,
			                                    CASTLE_DRACULA, &pathLength);
			assert(pathLength == 7);
			assert(path[0] == SARAGOSSA);
			assert(path[1] == MARSEILLES);
			assert(path[2] == GENOA || path[2] == MILAN);
			assert(path[3] == VENICE);
			assert(path[4] == BUDAPEST);
			assert(path[5] == GALATZ || path[5] == KLAUSENBURG);
			assert(path[6] == CASTLE_DRACULA);
			free(path);
		}
		
		HvFree(hv);
		printf("Test passed!\n");
	}
	
	{///////////////////////////////////////////////////////////////////
	
		printf("Checking Galatz road connections "
		       "(Lord Godalming, Round 1)\n");
		
		char *trail = "GGA....";
		Message messages[1] = {};
		HunterView hv = HvNew(trail, messages);
		
		int numLocs = -1;
		PlaceId *locs = HvWhereCanTheyGoByType(hv, PLAYER_LORD_GODALMING,
		                                       true, false, false, &numLocs);
		
		
		assert(numLocs == 5);
		sortPlaces(locs, numLocs);
		assert(locs[0] == BUCHAREST);
		assert(locs[1] == CASTLE_DRACULA);
		assert(locs[2] == CONSTANTA);
		assert(locs[3] == GALATZ);
		assert(locs[4] == KLAUSENBURG);
		free(locs);
		
		HvFree(hv);
		printf("Test passed!\n");
	}
	
	{///////////////////////////////////////////////////////////////////
	
		printf("Checking Paris rail connections "
		       "(Lord Godalming, Round 1)\n");
		
		char *trail = "GPA....";
		Message messages[1] = {};
		HunterView hv = HvNew(trail, messages);
		
		int numLocs = -1;
		PlaceId *locs = HvWhereCanTheyGoByType(hv, PLAYER_LORD_GODALMING,
		                                       false, true, false, &numLocs);

		assert(numLocs == 5);
		sortPlaces(locs, numLocs);
		assert(locs[0] == BORDEAUX);
		assert(locs[1] == BRUSSELS);
		assert(locs[2] == LE_HAVRE);
		assert(locs[3] == MARSEILLES);
		assert(locs[4] == PARIS);
		free(locs);
		
		HvFree(hv);
		printf("Test passed!\n");
	}
	{///////////////////////////////////////////////////////////////////
	
		printf("Testing Dracula's last known location case 2\n");
		
		char *trail =
			"GRO.... SGE.... HGE.... MGE.... DST.V.. "
			"GRO.... SGE.... HGE.... MGE.... DC?T... "
			"GRO.... SGE.... HGE.... MGE.... DC?T... "
			"GRO.... SGE.... HGE.... MGE.... DD3T... "
			"GRO.... SGE.... HGE.... MGE.... DHIT... "
			"GRO.... SGE.... HGE.... MGE.... DC?T... "
			"GRO.... SSTTTV.";
	
		Message messages[32] = {};
		HunterView hv = HvNew(trail, messages);
		
		assert(HvGetPlayerLocation(hv, PLAYER_DRACULA) == CITY_UNKNOWN);
		Round round = -1;
		assert(HvGetLastKnownDraculaLocation(hv, &round) == STRASBOURG);
		
		assert(round == 4);

		HvFree(hv);
		printf("Test passed!\n");
	}
	
	{///////////////////////////////////////////////////////////////////
	
		printf("Checking Adriatic Sea boat connections "
		       "(Lord Godalming, Round 1)\n");
		
		char *trail = "GAS....";
		Message messages[1] = {};
		HunterView hv = HvNew(trail, messages);
		
		int numLocs = -1;
		PlaceId *locs = HvWhereCanTheyGoByType(hv, PLAYER_LORD_GODALMING,
		                                       false, false, true, &numLocs);
		
		assert(numLocs == 4);
		sortPlaces(locs, numLocs);
		assert(locs[0] == ADRIATIC_SEA);
		assert(locs[1] == BARI);
		assert(locs[2] == IONIAN_SEA);
		assert(locs[3] == VENICE);
		free(locs);
		
		HvFree(hv);
		printf("Test passed!\n");
	}
	
	{///////////////////////////////////////////////////////////////////
	
		printf("Checking Szeged road connections "
		       "(Dracula, Round 1)\n");
		
		char *trail =
			"GSZ.... SGE.... HGE.... MGE.... DSZ.V..";
		
		Message messages[5] = {};
		HunterView hv = HvNew(trail, messages);
		
		int numLocs = -1;
		PlaceId *locs = HvWhereCanTheyGoByType(hv, PLAYER_DRACULA,
		                                       true, false, false, &numLocs);
		assert(numLocs == 5);
		sortPlaces(locs, numLocs);
		assert(locs[0] == BELGRADE);
		assert(locs[1] == BUDAPEST);
		assert(locs[2] == KLAUSENBURG);
		assert(locs[3] == SZEGED);
		assert(locs[4] == ZAGREB);
		free(locs);
		
		HvFree(hv);
		printf("Test passed!\n");	
	} 
	{
			
		
		char *trail =
			"GSZ....";
		
		Message messages[1] = {};
		HunterView hv = HvNew(trail, messages);
		{
			printf("Checking for no movs by type"
				"(PLAYER_DR_SEWARD, Round 1)\n");
			int numLocs = -1;
			PlaceId *locs = HvWhereCanTheyGoByType(hv, PLAYER_DR_SEWARD,
												true, false, false, &numLocs);
			assert(numLocs == 0);
			assert(locs == NULL);
			
		
			free(locs);
		}
		printf("Test passed!\n");
		{
			printf("Checking for no movs by type"
			"(player_dracula, Round 2)\n");
			int numLocs = -1;
			PlaceId *locs = HvWhereCanTheyGoByType(hv, PLAYER_DRACULA,
												true, false, false, &numLocs);
			assert(numLocs == 0);
			assert(locs == NULL);
			
		
			free(locs);
			printf("Test passed!\n");
		}
		{
			printf("Checking for no movs for curr play by type"
			"(Round 3)\n");
			int numLocs = -1;
			PlaceId *locs = HvWhereCanIGoByType(hv, true, false, false, &numLocs);
			assert(numLocs == 0);
			assert(locs == NULL);
			
		
			free(locs);
			printf("Test passed!\n");

		}
		{
			printf("Checking for WhereCanIGo no movs "
				"( Round 4)\n");
			int numLocs = -1;
			PlaceId *locs = HvWhereCanIGo(hv, &numLocs);
			assert(numLocs == 0);
			assert(locs == NULL);
			
		
			free(locs);
			printf("Test passed!\n");
		}
		
		{
			printf("Checking for WhereCanTheyGO no movs "
				"(play_decular, Round 4)\n");
			int numLocs = -1;
			PlaceId *locs = HvWhereCanTheyGo(hv, PLAYER_DRACULA, &numLocs);
			assert(numLocs == 0);
			assert(locs == NULL);
			
		
			free(locs);
			printf("Test passed!\n");
		}
		
		
		HvFree(hv);
		printf("Test passed!\n");


	}
	{///////////////////////////////////////////////////////////////////
	
		printf("Checking HvWhereCanIGoByType for Lord Godalming \n");
		
		char *trail = "GLI.... SRO.... HGE.... MRO.... DST.V.. "
					  "GLO.... SRO.... HRO.... MGE.... DST.V.. "
					  "GFR.... SRO.... HGE.... MRO.... DC?T... ";

		Message messages[15] = {};
		HunterView hv = HvNew(trail, messages);
		
		int numLocs = -1;
		PlaceId *locs = HvWhereCanIGoByType(hv, false, true, false, &numLocs);

		assert(numLocs == 13);
		sortPlaces(locs, numLocs);
		assert(locs[0] == BERLIN);
		assert(locs[1] == BRUSSELS);
		assert(locs[2] == COLOGNE);
		assert(locs[3] == FRANKFURT);
		assert(locs[4] == HAMBURG);
		assert(locs[5] == LEIPZIG);
		assert(locs[6] == MILAN);
		assert(locs[7] == MUNICH);
		assert(locs[8] == NUREMBURG);
		assert(locs[9] == PARIS);
		assert(locs[10] == PRAGUE);
		assert(locs[11] == STRASBOURG);
		assert(locs[11] == STRASBOURG);
		assert(locs[11] == STRASBOURG);
		assert(locs[12] == ZURICH);
		free(locs);

		HvFree(hv);
		printf("Test passed!\n");
	}
	{///////////////////////////////////////////////////////////////////
	
		printf("Checking current HvWhereCanIGoByType for Lord Godalming, Round 2)\n");
		
		char *trail = "GBR.... SBR.... HGE.... MSA.... DST.V.. "
					  "GPA.... SRO.... HPA.... MGE.... DSAT... ";

		Message messages[10] = {};
		HunterView hv = HvNew(trail, messages);
		
		int numLocs = -1;
		PlaceId *locs = HvWhereCanIGoByType(hv, false, true, false, &numLocs);

		assert(numLocs == 7);
		sortPlaces(locs, numLocs);
		assert(locs[0] == BORDEAUX);
		assert(locs[1] == BRUSSELS);
		assert(locs[2] == COLOGNE);
		assert(locs[3] == LE_HAVRE);
		assert(locs[4] == MARSEILLES);
		assert(locs[5] == PARIS);
		assert(locs[6] == SARAGOSSA);
		free(locs);

		HvFree(hv);
		printf("Test passed!\n");
	}
	{///////////////////////////////////////////////////////////////////
		{
			char *trail = "GSZ.... SRO....";
		
			Message messages[2] = {};
			HunterView hv = HvNew(trail, messages);
			printf("\tChecking Rome raod, rail and boat connections "
			       "(Dr Seward, Round 1)\n");
			int numLocs = -1;
			
			PlaceId *locs = HvWhereCanTheyGoByType(hv, PLAYER_DR_SEWARD,
													true, true, true, &numLocs);
			
			
			assert(numLocs == 6);
			sortPlaces(locs, numLocs);			
			assert(locs[0] == BARI);
			assert(locs[1] == FLORENCE);
			assert(locs[2] == MILAN);
			assert(locs[3] == NAPLES);
			assert(locs[4] == ROME);
			assert(locs[5] == TYRRHENIAN_SEA);			
			free(locs);
			
			HvFree(hv);
			printf("Test passed!\n");
		}


		{
			char *trail = "GLS.... SLS.... HSW.... MMR.... DCD.V.. "
			"GPA.... SGE.... HGE.... MGE.... DSZ.V..";
		
			Message messages[10] = {};
			HunterView hv = HvNew(trail, messages);
			printf("\tChecking Paris rail connections "
			       "(Lord Godalming, Round 2)\n");
			
			int numLocs = -1;

			PlaceId *locs = HvWhereCanIGoByType(hv, false, true,
			                                     false, &numLocs);

			assert(numLocs == 7);
			sortPlaces(locs, numLocs);
			assert(locs[0] == BORDEAUX);
			assert(locs[1] == BRUSSELS);
			assert(locs[2] == COLOGNE);
			assert(locs[3] == LE_HAVRE);
			assert(locs[4] == MARSEILLES);
			assert(locs[5] == PARIS);
			assert(locs[6] == SARAGOSSA);
			printf("Test passed!\n");
			free(locs);
			
			HvFree(hv);
			
		}
		{///////////////////////////////////////////////////////////////////
	
		printf("Checking HvWhereCanIGoByType FOR Mina Harker, Round 8)\n");
		
		char *trail = "GLO.... SRO.... HBU.... MCN.... DST.V.. "
					  "GLO.... SRO.... HGE.... MGA.... DC?T... "
					  "GLO.... SRO.... HGA.... MVA.... DC?T... "
					  "GVA.... SBU.... HGE.... MGA.... DC?T... "
					  "GLO.... SRO.... HGE.... MSZ.... DC?T... "
					  "GLO.... SRO.... HBE.... MSZ.... DC?T... "
					  "GSA.... SRO.... HGE.... MBU.... DC?T... "
					  "GLO.... SBE.... HVA.... MCN.... DC?T... "
					  "GLO.... SRO.... HGE....";

		Message messages[43] = {};
		HunterView hv = HvNew(trail, messages);
		
		int numLocs = -1;
		PlaceId *locs = HvWhereCanIGoByType(hv, true, true, true, &numLocs);

		assert(numLocs == 8);
		sortPlaces(locs, numLocs);			
		assert(locs[0] == BELGRADE);
		assert(locs[1] == BLACK_SEA);
		assert(locs[2] == BUCHAREST);
		assert(locs[3] == BUDAPEST);
		assert(locs[4] == CONSTANTA);
		assert(locs[5] == GALATZ);	
		assert(locs[6] == SZEGED);
		assert(locs[7] == VARNA);				
		free(locs);

		HvFree(hv);
		printf("Test passed!\n");
	}

		{
			char *trail = "GLS.... SLS.... HSW.... MMR.... DCD.V.. "
			"GPA.... SGE.... HGE.... MGE.... DSZ.V.. "
			"GBA.... SLS.... HSW.... MMR.... DCD.V..";
		
			Message messages[15] = {};
			HunterView hv = HvNew(trail, messages);
			printf("\tChecking Paris rail connections "
			       "(Lord Godalming, Round 2)\n");
			
			int numLocs = -1;

			PlaceId *locs = HvWhereCanIGo(hv, &numLocs);
		
			assert(numLocs == 10);
			sortPlaces(locs, numLocs);
			assert(locs[0] == ALICANTE);
			assert(locs[1] == BARCELONA);
			assert(locs[2] == BORDEAUX);
			assert(locs[3] == LISBON);
			assert(locs[4] == MADRID);
			assert(locs[5] == MEDITERRANEAN_SEA);
			assert(locs[6] == PARIS);
			assert(locs[7] == SANTANDER);
			assert(locs[8] == SARAGOSSA);
			assert(locs[9] == TOULOUSE);
			printf("Test passed!\n");
			free(locs);
			
			HvFree(hv);
			
		}
		
		
	}
	printf("Test passed!\n");
	{///////////////////////////////////////////////////////////////////
	
		printf("Checking HvWhereCanTheyGo for Dr Seward, Round 1\n");
		
		char *trail = "GTY.... SRO.... HLS....";
		Message messages[3] = {};
		HunterView hv = HvNew(trail, messages);
		
		int numLocs = -1;
		PlaceId *locs = HvWhereCanTheyGo(hv, PLAYER_DR_SEWARD, &numLocs);

		assert(numLocs == 6);
		sortPlaces(locs, numLocs);			
		assert(locs[0] == BARI);
		assert(locs[1] == FLORENCE);
		assert(locs[2] == MILAN);
		assert(locs[3] == NAPLES);
		assert(locs[4] == ROME);
		assert(locs[5] == TYRRHENIAN_SEA);			
		free(locs);
		
		HvFree(hv);
		printf("Test passed!\n");
	}

	
	return EXIT_SUCCESS;
}
