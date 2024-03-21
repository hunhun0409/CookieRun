#include "Framework.h"

vector<string> Utility::SplitString(string origin, const string& tok)
{
    vector<string> result;

    size_t cutAt = 0;

    while((cutAt = origin.find_first_of(tok)) != origin.npos)
    {
        if (cutAt > 0)
            result.push_back(origin.substr(0, cutAt));

        origin = origin.substr(cutAt + 1);
    }

    if (origin.size() > 0)
        result.push_back(origin);

    return result;
}

string Utility::To_String(wstring text)
{
    string temp;
    temp.assign(text.begin(), text.end());
    return temp;
}

wstring Utility::To_WString(string text)
{
    wstring temp;
    temp.assign(text.begin(), text.end());
    return temp;
}
