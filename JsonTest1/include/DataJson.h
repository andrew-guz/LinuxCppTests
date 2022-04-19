#ifndef _DATAJSON_H_
#define _DATAJSON_H_

template<typename T>
class DataJson
{
public:
    static std::string ToJson(const T& connectionInfo);

    static T FromJson(const std::string& string);
};

#endif //_DATAJSON_H_
