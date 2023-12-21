#pragma once
struct CLabel
{
    std::string text;
    CLabel(const std::string& string = "Label")
    {
        text = string;
    }
};
