//
// Created by coder on 12/10/25.
//

#include "utils/remote_resources.h"

#include <QDebug>
#include <QFile>
#include <curl/curl.h>

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int download_file(const std::string& url, const std::string& local_path) {
    try {
        CURL *curl = curl_easy_init();
        if (!curl) throw -1;

        FILE *fp = fopen(local_path.c_str(), "wb");
        if (!fp) {
            curl_easy_cleanup(curl);
            throw -2;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        const CURLcode res = curl_easy_perform(curl);
        fclose(fp);
        curl_easy_cleanup(curl);

        if (res == CURLE_OK) {
            return 0;
        }

        throw static_cast<int>(res);
    } catch (int code) {
        qDebug() << "download_file() failed:" << code;

        QFile file(local_path.c_str());
        file.remove();

        return code;
    }
}