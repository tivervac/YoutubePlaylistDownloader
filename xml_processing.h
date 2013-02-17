#ifndef XML_PROCESSING_H
#define XML_PROCESSING_H

#include <string.h>

#include "libxml/parser.h"
#include "libxml/tree.h"
#include "libxml/xpath.h"

typedef struct _video_info {
	char** id;
	unsigned int amount;
	char** titles;
} video_info;

video_info* parse_xml(char *xml);

void free_video_info(video_info *v_info);

#endif