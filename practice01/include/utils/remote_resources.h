//
// Created by coder on 12/10/25.
//

#pragma once

#include <stdio.h>
#include <string>

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);

int download_file(const std::string& url, const std::string& local_path);
