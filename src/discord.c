#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>

size_t writefunc(void *ptr, size_t size, size_t nmemb, char **data) {
	//https://stackoverflow.com/questions/2329571/c-libcurl-get-output-into-a-string
	//*data = calloc(nmemb, size); // Do I need safety?
	strcpy(*data, ptr);

	return size * nmemb;
}

int authorize(void) {
	curl_global_init(CURL_GLOBAL_DEFAULT);
	CURL *curl = curl_easy_init();
	if (curl) {
		char *data;

		curl_easy_setopt(curl, CURLOPT_URL, "https://discordapp.com:443/api/v7/gateway");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
		CURLcode res = curl_easy_perform(curl);
		if(res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
			        curl_easy_strerror(res));
		}
		printf("%s\n", data);
		/* always cleanup */ 
		curl_easy_cleanup(curl);
	}
	return 1;
}
