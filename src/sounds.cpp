#include "sounds.h"

Sounds::Sounds():
	munch_toggle(true){
	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 4096;
	 
	if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
		fprintf(stderr, "Unable to initialize audio: %s\n", Mix_GetError());
		exit(1);
	}
	sound_munch_a = Mix_LoadWAV("/usr/local/share/pacman/sounds/munch_a.wav");
	if(sound_munch_a == NULL) {
		fprintf(stderr, "Unable to load WAV file: %s\n", Mix_GetError());
	}
	sound_munch_b = Mix_LoadWAV("/usr/local/share/pacman/sounds/munch_b.wav");
	if(sound_munch_a == NULL) {
		fprintf(stderr, "Unable to load WAV file: %s\n", Mix_GetError());
	}	
}

Sounds::~Sounds() {
	Mix_HaltChannel(-1);
	Mix_FreeChunk(sound_munch_a);
	Mix_FreeChunk(sound_munch_b);
	Mix_CloseAudio();
}

void Sounds::munch() {
	Mix_HaltChannel(channel_munch);
	if(munch_toggle) {
		munch_toggle = false;
		channel_munch = Mix_PlayChannel(-1, sound_munch_a, 0);
	} else {
		munch_toggle = true;
		channel_munch = Mix_PlayChannel(-1, sound_munch_b, 0);
	}
		
	if(channel_munch == -1) {
		fprintf(stderr, "Unable to play WAV file: %s\n", Mix_GetError());
	}
}