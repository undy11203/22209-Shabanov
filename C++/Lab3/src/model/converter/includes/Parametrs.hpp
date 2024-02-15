#pragma once

#include <file/includes/WavFileModel.hpp>
#include <variant>

struct Duration {
    int start;
    int stop;
};

struct TimePoint {
    int sec;
};

struct AdditionalFile {
    WavFileModel &wavFile;
};

struct Modifier {
    float coefficient;
};

using Params = std::variant<Duration, TimePoint, AdditionalFile, Modifier>;