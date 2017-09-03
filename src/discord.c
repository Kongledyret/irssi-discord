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

void discord_send_message(token tok, string target, string msg) {
	// user agent... = DiscordBot (https://github.com/mjsir911/irssi-discord,  0.0) irssi-discord/0.0
	printf("token = %s\ntarget = %s\n msg = %s\n", tok, target, msg);

	/* In windows, this will init the winsock stuff */ 
	curl_global_init(CURL_GLOBAL_ALL);

	/* get a curl handle */ 
	CURL *curl = curl_easy_init();
	if(curl) {
		struct curl_slist *headers = NULL;
		//chunk = curl_slist_append(chunk, "User-Agent: irssi-discord/0.0 DiscordBot (https://github.com/mjsir911/discord-irssi, 0.0)");
		headers = curl_slist_append(headers, "User-Agent: irssi-discord/0.0");
		headers = curl_slist_append(headers, g_strdup_printf("Authorization: %s", tok)); // TODO: better memory allocation
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_URL, g_strdup_printf(BASE_API "/channels/%s/messages", target)); // TODO: memory allocation
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, g_strdup_printf("content=%s", msg)); // TODO: memory allocation
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, print_data);

		/* Perform the request, res will get the return code */ 
		CURLcode res = curl_easy_perform(curl);
		/* Check for errors */ 
		if(res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));

		/* always cleanup */ 
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	printf(BASE_API);
}
