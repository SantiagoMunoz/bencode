#ifndef __METADATA_H_
#define __METADATA_H_

#include <iostream>
#include <vector>
#include <map>
#include <optional>
#include <ctime>
#include <memory>

#include "types.h"
#include<optional>

namespace Metadata {

    struct TorrentMetaData {
        struct TorrentInfo {
            struct FileInfo {
                std::string name;
                int length;
                std::optional<std::string> md5;
            };

            int piece_length;
            std::vector<std::array<char,20>> pieces;
            std::optional<int> priv;

            std::vector<FileInfo> files;
        };

        TorrentMetaData(std::istream& input);

        TorrentInfo info;
        std::string announce;

        std::optional<std::vector<std::vector<std::string>>> announce_list;
        std::optional<std::time_t> creation_date;
        std::optional<std::string> comment;
        std::optional<std::string> created_by;
        std::optional<std::string> encoding;
    };

    class TorrentDecoder {
        public:
        std::unique_ptr<tItem> decode(std::istream& input);
        std::unique_ptr<tItem> decode(std::string& input);
        static std::unique_ptr<TorrentDecoder> create();

        protected:
        TorrentDecoder() = default;

        private:
        int decode_int(std::istream& input) const;
        std::string decode_string(std::istream& input) const;
        std::map<std::string, std::string> decode_dictionary(std::istream& input) const;
        std::vector<std::unique_ptr<tItem>> decode_list(std::istream& input) const;
        std::map<std::string, std::string> decode_dict(std::istream& input) const;
    };

    std::unique_ptr<TorrentMetaData> decode_torrent(std::istream& input);
    std::unique_ptr<TorrentMetaData> decode_torrent(std::string& input);
    std::unique_ptr<tItem> decode(std::istream& input);

}

#endif /* __METADATA_H_ */
