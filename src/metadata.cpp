#include "metadata.h"

namespace Metadata {

std::unique_ptr<TorrentMetaData> decode_torrent(std::istream& input)
{
//    auto m_decoder = TorrentDecoder::create();
//    auto res = std::make_unique<TorrentMetaData>();
//    std::unique_ptr<tItem> md = m_decoder->decode(input);
//
//
//    return res;
}

std::unique_ptr<TorrentMetaData> decode_torrent(std::string& input)
{



}

std::unique_ptr<tItem> TorrentDecoder::decode(std::istream &input)
{
    switch(input.peek()) {
        case 'd':
//            return std::make_unique<tDict>(decode_dict(input));
            break;
        case 'i':
            return std::make_unique<tInt>(decode_int(input));
            break;
        case 'l':
//            return std::make_unique<tList>(decode_list(input));
            break;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
            auto s = decode_string(input);
            return std::make_unique<tString>(s);
            break;
    }

}

std::unique_ptr<tItem> decode(std::string& input)
{



}

int TorrentDecoder::decode_int(std::istream& input) const
{
    int res = 0;
    int digit;

    digit = input.get();
    //TODO Check digit=='i'
    while (true) {
        digit = input.get();
        if (digit == 'e')
            break;
        if ((digit >= '0') && (digit <= '9')) {
            res = res*10;
            res += digit - '0';
        }
    }
    return res;
}

std::string TorrentDecoder::decode_string(std::istream& input) const
{
    int digit;
    int len = 0;
    std::string result;

    while (true) {
        digit = input.get();
        if (digit == ':')
            break;
        if ((digit >= '0') && (digit <= '9')) {
            len = len*10;
            len += digit - '0';
        }
    }

    for(int i=0; i< len; i++ )
        result.push_back(static_cast<char>(input.get()));

    return result;
}

std::map<std::string, std::string> TorrentDecoder::decode_dictionary(std::istream& input) const
{


}

std::vector<std::unique_ptr<tItem>> TorrentDecoder::decode_list(std::istream& input) const
{
//    std::vector<std::unique_ptr<tItem>> res;
//    int digit;
//
//    digit = input.get();
//    //TODO Check digit == 'l'
//
//    while (input.peek() != 'e') {
//        auto res = decode(input);
//        res.push_back(res);
//    }
//    input.get(); //Flush final e
//    return res;
}

//Constructor from input stream
TorrentMetaData::TorrentMetaData(std::istream& input)
{


}

std::unique_ptr<tItem> decode(std::istream& input)
{
    auto m_decoder = TorrentDecoder::create();
    return m_decoder->decode(input);
}

std::unique_ptr<TorrentDecoder> TorrentDecoder::create()
{
    return std::unique_ptr<TorrentDecoder>(new TorrentDecoder());
}

} //namespace Metadata
