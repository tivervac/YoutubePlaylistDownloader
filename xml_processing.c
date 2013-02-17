#include "xml_processing.h"

//Only the chars 25 to 36 are important
#define LENGTH 11
#define OFFSET 25

video_info* parse_xml(char *xml){
	int i = 0;
	xmlNode *current;
	xmlDocPtr doc = xmlParseDoc((xmlChar*) xml);
	xmlNode *root = xmlDocGetRootElement(doc);
	video_info *v_info = (video_info*) malloc(sizeof(video_info));
	v_info->id = (char**) malloc(sizeof(char*));
	v_info->titles = (char**) malloc(sizeof(char*));

	for(current = root->children;current;current = current->next){
		if(!strcmp((char*) current->name, "entry")){
			xmlNode *current_node;
			for(current_node = current->children;current_node;current_node = current_node->next){
				if(!strcmp((char*) current_node->name, "title")){
					int length = strlen((char*) current_node->children->content);
					v_info->titles = (char**) realloc(v_info->titles, sizeof(char*) * (i + 1));
					v_info->titles[i] = (char*) malloc(sizeof(char) * (length + 1));
					//strncpy to prevent overflow
					strncpy(v_info->titles[i], (char*) current_node->children->content, length);
					v_info->titles[i][length] = '\0';
				}
				if(!strcmp((char*) current_node->name, "content")){
					v_info->id = (char**) realloc(v_info->id, sizeof(char*) * (i + 1));
					v_info->id[i] = (char*) malloc(sizeof(char) * (LENGTH + 1));
					//strncpy to prevent overflow
					strncpy(v_info->id[i], (char*) current_node->properties->next->children->content + OFFSET, LENGTH);
					v_info->id[i][LENGTH] = '\0';
					i++;
				}
			}
		}
	}

	xmlFreeDoc(doc);
	v_info->amount = i;
	return v_info;
}

void free_video_info(video_info *v_info){
	unsigned int i;
	for (i = 0; i < v_info->amount;i++){
		free(v_info->id[i]);
		v_info->id[i] = NULL;
		free(v_info->titles[i]);
		v_info->titles[i] = NULL;
	}
	free(v_info->id);
	v_info->id = NULL;
	free(v_info->titles);
	v_info->titles = NULL;
	free(v_info);
	v_info = NULL;
}