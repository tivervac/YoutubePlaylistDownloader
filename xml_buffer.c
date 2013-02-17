#include "xml_buffer.h"

void init_buffer(xml_buffer *buf){
	buf->size = sizeof(char); //To include the '\0'
	buf->head = buf->tail = NULL;
}

void add_entry(xml_buffer *buf, buffer_entry *entry){
	if (buf->size != sizeof(char)){
		buf->tail->next = entry;
		buf->tail = buf->tail->next;
	} else {
		buf->head = buf->tail = entry;
	}
	buf->size += buf->tail->size;
}

void init_entry(buffer_entry *entry, char* buffer_input, int size){
	entry->buffer = buffer_input;
	entry->next = NULL;
	entry->size = size;
}

int write_to_buffer(char *data, int size, int nmemb, void *buf){
	int len = size * nmemb;
	char* buffer_input = (char*) malloc(len + 1);
	buffer_entry *entry = (buffer_entry*) malloc(sizeof(buffer_entry));
	strncpy(buffer_input, data, len);
	buffer_input[len] = '\0';
	init_entry(entry, buffer_input, len); // len + 1?
	add_entry((xml_buffer*) buf, entry);
	return len;
}

char* concat_buffer(xml_buffer *buffer,char *xml_doc){
	buffer_entry *current_entry = buffer->head;
	xml_doc = (char*) malloc(buffer->size + 1);
	xml_doc[0] = '\0'; //So you can always strcat in the loop
	while (current_entry) {
		strcat(xml_doc, current_entry->buffer);
		current_entry = current_entry->next;
	}
	xml_doc[buffer->size] = '\0';
	free_buffer(buffer);
	return xml_doc;
}

void free_buffer(xml_buffer *buffer){
	buffer_entry *entry = buffer->head;
	while(entry){
		buffer_entry *temp = entry;
		free(entry->buffer);
		entry->buffer = NULL;
		entry = entry->next;
		free(temp);
		temp = NULL;
	}
}