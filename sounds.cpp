
#include <stdio.h>
#ifdef _WIN32
#include <SDL.h>
#include <SDL_mixer.h>
#endif
extern bool nosound;

void start_sound_system(){
    #ifdef _WIN32
	if(!nosound){
		printf("Starting SDL audio system:");
	//	Inilialize SDL_mixer , exit if fail
		if( SDL_Init(SDL_INIT_AUDIO) < 0 ){
			printf("failed\n");
			exit(1);
		}else printf("loaded\n");
	//	 Setup audio mode

		Mix_OpenAudio(22050,AUDIO_S16SYS,2,640);

	}
	#endif
}
#ifdef _WIN32
Mix_Music *mus=0;
int music_loaded=0;

Mix_Chunk *wav=0;
int sound_loaded=0;
#endif

void close_sound_system(){
//	while(Mix_Playing(channel) != 0);
#ifdef _WIN32
	Mix_FreeChunk(wav);
	Mix_FreeMusic(mus);
	Mix_CloseAudio();
	SDL_Quit();
	#endif

}

void play_music(char *name){
#ifdef _WIN32
	if(name){
		if(!nosound){
			if(!music_loaded){
				mus=Mix_LoadMUS(name);
				if(!mus) {
				printf("Mix_LoadMUS(\"%s\"): %s\n",name, Mix_GetError());			music_loaded=1;
				}Mix_PlayMusic(mus,10);

			}else{
				if(mus){
					Mix_FreeMusic(mus);
				}
				mus=Mix_LoadMUS(name);
				if(!mus) {
				printf("Mix_LoadMUS(\"%s\"): %s\n",name, Mix_GetError());			music_loaded=1;
				}
				music_loaded=1;
				Mix_PlayMusic(mus,10);
			}
		}
	}else{
		printf("no music name received...\n");
	}
	#endif
}


void play_sound(char *name){
#ifdef _WIN32
	if(!nosound){
		if(!sound_loaded){
			sound_loaded=1;
			wav=Mix_LoadWAV(name);
			Mix_PlayChannel(0,wav,0);

		}else{
			sound_loaded=1;
			if(wav)Mix_FreeChunk(wav);
			wav=Mix_LoadWAV(name);
			Mix_PlayChannel(0,wav,0);
		}
	}
#endif
}
