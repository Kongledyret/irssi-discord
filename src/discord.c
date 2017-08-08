#include <curl/curl.h>
#include <stdlib.h>
#include <jansson.h>
#include <string.h>

#include "discord.h"

size_t writefunc(void *ptr, size_t size, size_t nmemb, char **data) {
	//https://stackoverflow.com/questions/2329571/c-libcurl-get-output-into-a-string
	*data = malloc(nmemb * size); // Do I need safety? // yes, yes I do
	strcpy(*data, ptr); // hmm sometimes theres just a seg fault for no reason

	return size * nmemb;
}

size_t json_write_func(void *ptr, size_t size, size_t nmemb, json_t **root_ptr) {

	//*root_ptr = malloc(0); // Do I need safety?
	json_error_t error;
	*root_ptr = json_loads(ptr, 0, &error);
	//printf("error: %s\n", error.text);
	return size * nmemb;
}

#define BASEURL "https://discordapp.com/api/v7"

#define DISCORD_GET_GATEWAY_LINK BASEURL "/gateway"
const char *get_gateway(void) {
	CURL *curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, DISCORD_GET_GATEWAY_LINK);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.42.0");

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, json_write_func);
	} else {
		printf("curl error\n");
	}
	json_t **root_ptr = malloc(0);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, root_ptr);
	curl_easy_perform(curl); // TODO: check return val
	const char *gateway = json_string_value(json_object_get(*root_ptr, "url"));
	return gateway; // TODO: implement safety
}

CURL *authenticate(char *token) {
	curl_global_init(CURL_GLOBAL_DEFAULT);
	CURL *curl = curl_easy_init();
	if (curl) {
		struct curl_slist *chunk = NULL;
		const char *auth_header_beginning = "Authorization: ";
		char auth_header[strlen(auth_header_beginning) + strlen(token)];
		strcpy(auth_header, auth_header_beginning);
		strcat(auth_header, token);
		chunk = curl_slist_append(chunk, auth_header);
		chunk = curl_slist_append(chunk, "Content-Type: application/json");

		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
		//curl_easy_setopt(curl, CURLOPT_URL, BASEURL "/users/@me");
		//curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
		//curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
	}
	return curl;
}

void handle_authentication(CURL *curl, CURLcode res) {
	if(res == CURLE_OK) {
		long response_code;
		curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &response_code);
		switch(response_code) {
			case 200 :
				//printf("authorized\n");
				break;
			case 201 ... 299 :
			case 401 :
				printf("Token rejected\n");
				break;
			case 402 ... 499 :
				printf("unknown error\n");
			default :
				printf("unknown response: %li\n", response_code);
		}
	} else {
		fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));
	}
}

#include "secret.h"
//group_ID get_gId_from_user(user_ID uID) {
group_ID get_gID_from_uID(void) {

	CURL *curl = authenticate(MYTOKEN);

	#define PRIVMSG_HEADER "{'recipient_id': 5639}"
	curl_easy_setopt(curl, CURLOPT_URL, BASEURL "/users/@me/channels");
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, PRIVMSG_HEADER);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
	char *data = NULL;
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);

	CURLcode res = curl_easy_perform(curl);
	handle_authentication(curl, res);
	/* always cleanup */ 

	json_error_t error;
	json_t *root = json_loads(data, 0, &error);
	curl_easy_cleanup(curl);

	json_t *id_json = json_object_get(root, "id");
	const char *tid = json_string_value(id_json);
	char *eptr = (char *)tid + strlen(tid) + 1; // Is this valid I wonder?
	group_ID id = 0;
	if (tid == NULL) {
		printf("ERROR\n");
	} else {
		id = strtoll(tid, &eptr, 10);
	}
	return id;
	//group_ID id = strtoll(json_string_value(json_object_get(root, "id")));
	

	//printf("%llu", id);


}

void discord_send_message(group_ID id, string message) {
	CURL *curl = authenticate(MYTOKEN);

	#define SEND_HEADER_1 "/channels/"
	#define SEND_HEADER_2 "/messages"
	//https://stackoverflow.com/questions/2709713/how-to-convert-unsigned-long-to-string
	char buf[256];
	sprintf(buf, "%llu", id);
	char header[strlen(BASEURL) + strlen(SEND_HEADER_1) + strlen(buf) + strlen(SEND_HEADER_2)];
	strcpy(header, BASEURL);
	strcat(header, SEND_HEADER_1);
	strcat(header, buf);
	strcat(header, SEND_HEADER_2);
	//printf("%s\n", header);
	curl_easy_setopt(curl, CURLOPT_URL, header);

	#define SEND_CONTENT_1 "{\"content\": \""
	#define SEND_CONTENT_2 "\"}"

	char payload[strlen(SEND_CONTENT_1) + strlen(message) + strlen(SEND_CONTENT_2)];
	strcpy(payload, "");
	strcat(payload, SEND_CONTENT_1);
	strcat(payload, message);
	strcat(payload, SEND_CONTENT_2);

	//printf("%s\n", payload);
	//printf("%s\n", PRIVMSG_HEADER);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
	char *data = NULL;
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);

	CURLcode res = curl_easy_perform(curl);
	handle_authentication(curl, res);
	/* always cleanup */ 

	//printf("%s\n", data);
	curl_easy_cleanup(curl);
}

int main() {
	//token_privmsg(MYTOKEN);
	//discord_send_message(get_gID_from_uID(), "hello this is C");
	//printf("%s\n", get_gateway());
	//discord_send_message(343599756821397504, "Turns out it just doesnt like single quotes");
	//authorize();
}
