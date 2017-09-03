#include "discord.h"

#include "utils.h"

#include <curl/curl.h>

size_t trash_data(void *buffer, size_t size, size_t nmemb, void *userp) {
	return size * nmemb;
}
size_t print_data(void *buffer, size_t size, size_t nmemb, void *userp) {
	printf(buffer);
	return size * nmemb;
}

struct curl_slist *standard_headers(token tok, struct curl_slist *headers) {
	headers = curl_slist_append(headers, "User-Agent: irssi-discord/0.0");
	headers = curl_slist_append(headers, g_strdup_printf("Authorization: %s", tok)); // TODO: better memory allocation
	return headers;
}

void discord_send_message(token tok, chID target, string msg) {
	// user agent... = DiscordBot (https://github.com/mjsir911/irssi-discord,  0.0) irssi-discord/0.0
	//
	curl_global_init(CURL_GLOBAL_ALL);
	CURL *curl = curl_easy_init();
	if(curl) {
		//chunk = curl_slist_append(chunk, "User-Agent: irssi-discord/0.0 DiscordBot (https://github.com/mjsir911/discord-irssi, 0.0)");
		struct curl_slist *headers = NULL;
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, standard_headers(tok, headers));
		curl_easy_setopt(curl, CURLOPT_URL, g_strdup_printf(BASE_API "/channels/%s/messages", target)); // TODO: memory allocation
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, g_strdup_printf("content=%s", msg)); // TODO: memory allocation
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, print_data);

		CURLcode res = curl_easy_perform(curl);
		if(res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));

		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}

#include <jansson.h>

/*
FILE* out = fopen("out.html", "w");
curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)out);
curl_easy_setopt(easyhandle, CURLOPT_WRITEFUNCTION, fwrite);
*/

size_t json_data(void *buffer, size_t size, size_t nmemb, json_t **root) {
	json_error_t error;
	*root = json_loads(buffer, 0, &error);
	return size * nmemb;
}

static json_t *generic_get_request(token tok, string URL) {
	curl_global_init(CURL_GLOBAL_ALL);
	CURL *curl = curl_easy_init();
	json_t *root = NULL;
	if(curl) {
		struct curl_slist *headers = NULL;
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER,    standard_headers(tok, headers));
		curl_easy_setopt(curl, CURLOPT_URL,           URL);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA,     &root);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, json_data);

		CURLcode res = curl_easy_perform(curl);
		if(res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));

		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	return root;
}

json_t *discord_get_channel_info(token tok, chID channel) {
	return generic_get_request(tok, g_strdup_printf(BASE_API "/channels/%s", channel)); // TODO: memory allocation
}
json_t *discord_get_guild_info(token tok, chID guild) {
	return generic_get_request(tok, g_strdup_printf(BASE_API "/guilds/%s", guild)); // TODO: memory allocation
}
