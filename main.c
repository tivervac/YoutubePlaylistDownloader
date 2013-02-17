#include "main.h"

int main(){
	{
		char *listID = (char*) malloc(MAX_ID_LENGTH * sizeof(char));
		char *url = (char *) malloc(strlen(PREFIX) + 1 * sizeof(char));
		strcpy(url, PREFIX);
		url = (char*) realloc(url, strlen(PREFIX) + 1 + 1 * sizeof(char));
		printf("%s", "Enter the listID: ");
		scanf("%s", listID);
		url = construct_url(url, listID);
		send_playlist_request(url);

		free(url);
		printf("All downloads completed!\n");
	}
	_CrtDumpMemoryLeaks();
}

char* construct_url(char *url, char listID[]){
	url = (char*) realloc(url, strlen(PREFIX) + strlen(listID) + 1 * sizeof(char));
	strcat(url, listID);
	url = (char*) realloc(url, strlen(PREFIX) + strlen(listID) + strlen(SUFFIX) + 1 * sizeof(char));
	strcat(url, SUFFIX);
	return url;
}

void send_playlist_request(char *url){
	CURL *curl;
	CURLcode res;
	xml_buffer buffer;
	char *xml_doc = NULL;
	video_info *links;

	init_buffer(&buffer);
	curl = curl_easy_init();

	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &write_to_buffer);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
		res = curl_easy_perform(curl);

		//Check for errors 
		if(res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		} else {
			xml_doc = concat_buffer(&buffer, xml_doc);
			links = parse_xml(xml_doc);
			download_files(links);

			free_video_info(links);
			free(xml_doc);
			xml_doc = NULL;
		}

		//Cleanup curl
		curl_easy_cleanup(curl);
	}
}

void download_files(video_info *v_info){
	unsigned int i;

	for (i = 0; i < v_info->amount; i++){
		generate_file(v_info, i);
	}
}

void generate_file(video_info *v_info, unsigned int i){
	char *rest = "\\Documents\\%(title)s.%(ext)s";
	char *opt = " -o \"";
	int env_len = strlen(getenv("USERPROFILE"));
	char opt_len = strlen(opt);
	int rest_len = strlen(rest);
	//1 extra for the "
	char *file = (char*) malloc((env_len + opt_len + rest_len + 2) * sizeof(char));

	file[0] = '\0';
	strcat(file, opt);
	file[opt_len] = '\0';
	strcat(file, getenv("USERPROFILE"));
	file[env_len + opt_len] = '\0';
	strcat(file, rest);
	file[env_len + rest_len + opt_len] = '\"';
	file[env_len + rest_len + opt_len + 1] = '\0';
	printf("Downloading \"%s\"...\n", v_info->titles[i]);
	_spawnl(P_WAIT, "youtube-dl.exe", file, v_info->id[i], NULL);
	free(file);
	file = NULL;
	printf("Download completed.\n");
}