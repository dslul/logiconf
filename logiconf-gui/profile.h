#ifndef PROFILE_H
#define PROFILE_H

#include <vector>
#include <cinttypes>

class Profile
{
public:
    Profile(std::vector<uint8_t> data);
    int getReportRate();
private:
    std::vector<uint8_t> data;
    int report_rate;
};

#endif // PROFILE_H
