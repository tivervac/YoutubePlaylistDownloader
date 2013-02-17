#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>
#include <math.h>
#include <process.h>

#include "curl-7.28.1/curl-7.28.1/include/curl/curl.h"
#include "xml_buffer.h"
#include "xml_processing.h"

#define PREFIX	"http://gdata.youtube.com/feeds/api/playlists/"
#define SUFFIX	"?v=2"
#define MAX_ID_LENGTH	64
#define	PROGRAM	"youtube-dl.exe"

int main();

char* construct_url(char *url, char listID[]);

void send_playlist_request(char *url);

void download_files(video_info *v_info);

void generate_file(video_info *v_info, unsigned int i);

#endif