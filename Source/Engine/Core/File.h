#pragma once

#include <string>
#include <vector>

namespace Cpain {
    std::string getCurrentDirectory();
    bool setCurrentDirectory(const std::string& path);
    std::string getExtension(const std::string& path);
    std::string getFilename(const std::string& path);
    bool exists(const std::string& path);

    std::vector<std::string> getFilesInDirectory(const std::string& path);
    std::vector<std::string> getDirectoriesIn(const std::string& path);

    bool readTextFile(const std::string& path, std::string& content);
    bool writeTextFile(const std::string& path, const std::string& content, bool append = false);
}