/********************************
* Linked list which saves the xml
********************************/

#ifndef XML_BUFFER_H
#define XML_BUFFER_H

#include <stdlib.h>
#include <string.h>

typedef struct _buffer_entry{
	struct _buffer_entry *next;
	char *buffer;
	int size;
} buffer_entry;

typedef struct {
	buffer_entry *head;
	buffer_entry *tail;
	int size;
} xml_buffer;

void init_buffer(xml_buffer *buf);

void add_entry(xml_buffer *buf, buffer_entry *entry);

void init_entry(buffer_entry *entry, char *buffer_input, int size);

/**************************************
* @param nmemb: number of memory blocks
**************************************/
int write_to_buffer(char *data, int size, int nmemb, void *buf);

/***************************************
* Concatenate the buffer into one string
***************************************/
char* concat_buffer(xml_buffer *buffer, char *xml_doc);

void free_buffer(xml_buffer *buf);

#endif