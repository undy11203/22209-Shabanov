#include "SoundController.hpp"

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include <Factory/FactoryCreator.hpp>
#include <Factory/Fwd.hpp>
#include <Factory/IFactory.hpp>
#include <Factory/Tag.hpp>

#include <converter/includes/FactoryItems.hpp>
#include <converter/includes/Fwd.hpp>
#include <converter/includes/IConverter.hpp>
#include <converter/includes/Parametrs.hpp>
#include <converter/includes/Tags.hpp>

#include <FormatExceptions.hpp>
#include <UncorrectConfig.hpp>

namespace {
    std::unordered_map<std::string, const Factory::Tag<Converter::IConverterPtr>> convertor = {{"mute", Converter::muteTag},
                                                                                               {"mix", Converter::mixTag},
                                                                                               {"change_speed", Converter::changeSpeedTag}};
} // namespace

SoundController::SoundController(std::vector<std::string> args) {

    bool isFirst = true;

    std::string configPath;
    std::string outputPath;
    std::vector<std::string> inputPath;

    if (args.size() >= 3 && args[2].find(".txt") == std::string::npos) {
        throw FormatExceptions("Need other format for config file, not" + args[3]);
    } else if (args.size() >= 3) {
        configPath = args[2];
    }

    for (size_t i = 3; i < args.size(); i++) {
        if (args[i].find(".wav") != std::string::npos && isFirst) {
            outputPath = args[i];
            isFirst = false;
        } else if (args[i].find(".wav") != std::string::npos && !isFirst) {
            inputPath.push_back(args[i]);
        } else {
            throw FormatExceptions("WAV file ends in .wav format, not " + args[i]);
            break;
        }
    }

    m_configFileModel = ConfigFileModel(configPath);

    m_outWavFileModel = WavFileModel(outputPath);
    for (size_t i = 0; i < inputPath.size(); i++) {
        m_vectInWavFileModel.push_back(WavFileModel(inputPath[i]));
    }
}

bool SoundController::InitConfConvertors() {
    bool isCorrectComplete = true;
    Factory::FactoryMap factoryMap = Converter::factoryItems();
    Factory::IFactoryPtr factory = Factory::createFactory(std::move(factoryMap));

    m_configFileModel.OpenConfig();

    std::vector<Params> params;
    std::unordered_map<std::string,
                       std::function<bool()>>
        parseParams = {{"mix", [this, &params] { return m_configFileModel.GetTimePointAndAdditional(params, m_vectInWavFileModel); }},
                       {"mute", [this, &params] { return m_configFileModel.GetDuration(params); }},
                       {"change_speed", [this, &params] { return m_configFileModel.GetDurationAndModifier(params); }}};

    std::string command;
    while ((command = m_configFileModel.NextCommand()) != "\0") {
        if (parseParams.find(command) == parseParams.end()) {
            throw UncorrectConfig("Undefined command " + command);
            m_configFileModel.CloseConfig();
            return false;
        }
        auto converterPtr = factory->create(convertor.at(command));
        if (!parseParams.at(command)()) {
            isCorrectComplete = false;
            break;
        }

        converterPtr->PutParameters(params);
        m_vectConverters.push_back(converterPtr);
        params.clear();
    }

    m_configFileModel.CloseConfig();
    return true;
}

void SoundController::Convert() {
    for (size_t i = 0; i < m_vectInWavFileModel.size(); i++) {
        m_vectInWavFileModel[i].OpenForRead();
    }

    m_outWavFileModel.OpenForWrite();

    if (!InitConfConvertors())
        return;

    std::vector<short> samples;
    unsigned int second = 0;

    while (!m_vectInWavFileModel[0].IsEnd()) {
        second++;

        samples = m_vectInWavFileModel[0].ReadSecond();

        for (const auto &converterPtr : m_vectConverters) {
            samples = converterPtr->UpdateSound(samples, second);
        }

        m_outWavFileModel.WriteSamples(samples);
    }

    m_outWavFileModel.CloseWriteFile();
}

void SoundController::InitForHelpListConvertors() {
    Factory::FactoryMap factoryMap = Converter::factoryItems();
    Factory::IFactoryPtr factory = Factory::createFactory(std::move(factoryMap));

    auto converterPtr = factory->create(Converter::muteTag);
    m_vectConverters.push_back(converterPtr);
    converterPtr = factory->create(Converter::mixTag);
    m_vectConverters.push_back(converterPtr);
    converterPtr = factory->create(Converter::changeSpeedTag);
    m_vectConverters.push_back(converterPtr);
}

void SoundController::PrintHelpList() {
    InitForHelpListConvertors();

    std::cout << "HelpList" << std::endl;
    for (const auto &converterPtr : m_vectConverters) {
        std::cout << "=========================" << std::endl;
        std::cout << "Converter: " << converterPtr->GetName() << std::endl;
        std::cout << "Params: " << converterPtr->GetParametrs() << std::endl;
        std::cout << "Features: " << converterPtr->GetFeatures() << std::endl;
        std::cout << "Syntax in config: " << converterPtr->GetSyntax() << std::endl;
        std::cout << "=========================" << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
    }
}