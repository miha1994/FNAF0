#include "camera.h"

void camera_another_opening (rooms *rm) {
	//FREDDY
	if (rm->time > (20 - rm->AI_level[FREDDY])*18 && rand1 > 0.3) {
		freddy_room = ___tmp____[rand()%5];
	} else {
		freddy_room = 7;
	}
	//BONNIE
	if (freddy_room == 7 && (rm->time > (20 - rm->AI_level[BONNIE]) * 18) && (rand1 < 0.45)) {
		if (rand1 < 0.5) {
			bonnie_room = 0;
		} else {
			bonnie_room = 1;
		}
	} else {
		int bon_r;

		do {
			if (freddy_room != 7) {
				bon_r = 1;
				break;
			}
			if (rand1 > 0.8) {
				bon_r = 2;
			} else {
				if (rm->AI_level[BONNIE] < 5 && rm->time < 150) {
					bon_r = 2;
				} else {
					bon_r = 1;
				}
			}
		} while (0);

		if (bon_r == 1) {
			do {
				bonnie_room = 4 + (rand ()%3);
			} while (bonnie_room == freddy_room);
		} else if (bon_r == 2) {
			bonnie_room = 7;
		}
	}
	//CHICA
	if (freddy_room == 7 && (rm->time > (20 - rm->AI_level[CHICA]) * 18) && (bonnie_room > 1) && (rand1 < 0.6)) {
		if (rand1 < 0.5) {
			chica_room = 2;
		} else {
			chica_room = 3;
		}
	} else {
		int ch_r;
		do {
			if (freddy_room != 7) {
				ch_r = 1;
				break;
			}
			if (rand1 > 0.8) {
				ch_r = 2;
			} else {
				if (rm->AI_level[CHICA] < 5 && rm->time < 100) {
					ch_r = 2;
				} else {
				    ch_r = 1;
                }
			}
		} while (0);

		if (ch_r == 1) {
			do {
				chica_room = ___tmp0____[rand()%3];
			} while (chica_room == bonnie_room || chica_room == freddy_room);
		} else if (ch_r == 2) {
			chica_room = 7;
		}
	}
	//FOXY
	if (rm->time > (20 - rm->AI_level[FOXY]) * 18) {
		foxy_is_active = rand1 > 0.6f;
	}
	//SAVE
	FOR (i, 11) {
		num_of_pic_4_room[i] = number_of_png (rm, i);
	}
	//SOUNDS
#define sir rm->cam->sounds_in_room
#define make_full_sound(sir_i)	if (rand () % 8 < 3) {sir_i[0] = rand ()%3;} else {sir_i[0] = 21 + rand () % 5;} sir_i[1] = 3 + rand () % 3;sir_i[2] = 6 + rand () % 3;
	FOR (i, 11) {
		FOR (j, 3) {
			sir[i][j] = -1;
		}
	}
	make_full_sound(sir[bonnie_room]);
	if (chica_room != 9) {
		make_full_sound(sir[chica_room]);
	} else {
		sir[9][2] = 13 + rand () % 2;
		sir[9][1] = 15 + rand () % 2;
	}
	if (freddy_room != 7) {
		sir[freddy_room][0] = 10 + rand() % 3;
	}
	int ai_sum = 0;
	int ai_max = 0;
	FOR (i, 5) {
		ai_sum += rm->AI_level[i];
		if (rm->AI_level[i] > ai_max) {
			ai_max = rm->AI_level[i];
		}
	}

	FOR (i, 10) {
		if (sir[i][0] == -1 && sir[i][1] == -1 && sir[i][2] == -1) {
			if (ai_sum/5 < 4 && rm->time < 230) {
				if (rand1 > 0.9) {
					if(rand ()%14 < 9) {
						sir[i][1] = rand () % 9;
					} else {
						sir[i][1] = 21 + rand ()%5;
					}
				}
			} else if (ai_max < 10) {
				if (rand1 > 0.6) {
					sir[i][0] = 3 + rand () % 6;
				}
				if (rand1 > 0.7) {
					if (rand() % 8 < 3) {
						sir[i][2] = rand() % 3;
					} else {
						sir[i][2] = 21 + rand ()%5;
					}
				}
			} else {
				if (rand1 > 0.5) {
					sir[i][1] = 3 + rand () % 3;
					if (rand1 > 0.5) {
						sir[i][2] = (rand()%2) * 6 + rand () % 3;
					} else {
						sir[i][2] = 21 + rand () % 5;
					}
				}
			}
		}
	}
	FOR (j, 3) {
		sir[0][j] = -1;
		sir[2][j] = -1;
	}

#undef sir
	rm->cam->sounds_in_room_time[0] = -2.0 - rand1;
	rm->cam->sounds_in_room_time[1] = - rand1*2;
	rm->cam->sounds_in_room_time[2] = -3.0 - rand1;
	FOR (z, 3) {
		rm->cam->play[z] = false;
	}
	//TOTC
	rm->cam->totc_time = 0.0f;
	rm->cam->totc_stat = 0;
	//
	rm->cam->fg.great = false;
}