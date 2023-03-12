#pragma once
#ifndef STAR_READ_HPP
#define STAR_READ_HPP

#include <string_view>
#include <fstream>
#include <string>
#include <regex>
#include <map>
#include <unordered_map>
#include <iostream>

namespace star::file {
    class ini {
    public:
        ini() = default;

        explicit ini(const std::string_view &name) {
            this->load(name);
        }

        bool load(const std::string_view &name) {
            this->file.open(name.data(), std::ios::in | std::ios::out);
            if (!this->file.is_open()) {
                return false;
            }

            std::string line;
            std::string section;
            std::smatch result;
            while (getline(this->file, line)) {
                size_t pos = std::min(line.find('#'), line.find(';'));
                if (pos == 0) {
                    continue;
                }

                if (pos != std::string::npos) {
                    line.erase(pos);
                }

                std::string_view line_view = line;
                size_t equal_pos = line_view.find('='); // 寻找"="对应的pos

                // re查找，结果保存在result，如果不是[]中这样的sections名字，就把key和value存到map[result[1]]
                static std::regex rule("\\[(.*?)\\]");
                if (equal_pos == std::string_view::npos) {
                    if (std::regex_search(line, result, rule)) {
                        section = result[1].str();
                        continue;
                    }

                    // 非sections，也非key，value，返回false
                    return false;
                }

                std::string key{line_view.substr(0, equal_pos)};
                std::string value{line_view.substr(equal_pos + 1)};
                this->map[section][key] = value;
            }

            return true;
        }

        std::string get_value(const std::string &sections, const std::string &key) noexcept {
            auto &&section_iterator = this->map.find(sections);
            if (section_iterator == this->map.end()) {
                return {};
            }

            auto &&parameter_iterator = section_iterator->second.find(key);
            if (parameter_iterator == section_iterator->second.end()) {
                return {};
            }
            return parameter_iterator->second;
        }

        std::vector<std::string> get_section() noexcept {
            std::vector<std::string> sections;
            for (auto &section: map) {
                sections.emplace_back(section.first);
            }

            return sections;
        }

        std::map<std::string, std::string> get_parameter(const std::string &s) noexcept {
            auto &&section_iterator = this->map.find(s);
            if (section_iterator == this->map.end()) {
                return {};
            }

            return section_iterator->second;
        }

        void clear() {
            this->file.close();
            this->map.clear();
        }

        ~ini() {
            this->clear();
        }

    private:
        std::ifstream file;
        std::map<std::string, std::map<std::string, std::string> > map;
    };
}

#endif //STAR_READ_HPP
