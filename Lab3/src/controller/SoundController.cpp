#include "SoundController.hpp"

#include <iostream>
#include <string>
#include <vector>

#include <Factory/FactoryCreator.hpp>
#include <Factory/IFactory.hpp>

#include <converter/includes/FactoryItems.hpp>
#include <converter/includes/Fwd.hpp>
#include <converter/includes/IConverter.hpp>
#include <converter/includes/Tags.hpp>

SoundController::SoundController(std::vector<std::string> args) {
    bool isFirst = true;

    std::string configPath;
    std::string outputPath;
    std::vector<std::string> inputPath;

    for (size_t i = 1; i < args.size(); i++) {
        if (args[i].find(".wav") != std::string::npos && isFirst) {
            outputPath = args[i];
            isFirst = false;
        } else if (args[i].find(".wav") != std::string::npos && !isFirst) {
            inputPath.push_back(args[i]);
        } else if (args[i].find(".txt") != std::string::npos) {
            configPath = args[i];
        }
    }

    m_configFileModel = ConfigFileModel(configPath);

    m_outWavFileModel = WavFileModel(outputPath);
    for (size_t i = 0; i < inputPath.size(); i++) {
        m_vectInWavFileModel.push_back(WavFileModel(inputPath[i]));
    }
}

SoundController::~SoundController() {
}

void SoundController::InitConfConvertors() {
    Factory::FactoryMap factoryMap = Converter::factoryItems();
    Factory::IFactoryPtr factory = Factory::createFactory(std::move(factoryMap));

    m_configFileModel.OpenConfig();

    std::string command;
    while ((command = m_configFileModel.NextCommand()) != "\0") {
        if (command == "mute") {
            auto converterPtr = factory->create(Converter::muteTag);
            converterPtr->putParametrs(m_configFileModel.getPairParametrs());
            m_vectConverters.push_back(converterPtr);
        } else if (command == "mix") {
            std::pair<int, int> param = m_configFileModel.getPairParametrs();

            auto converterPtr = factory->create(Converter::mixTag);
            converterPtr->putParametrs(m_vectInWavFileModel[param.first - 1], param.second);
            m_vectConverters.push_back(converterPtr);
        } else if (command == "change_speed") {
            auto converterPtr = factory->create(Converter::changeSpeedTag);
            converterPtr->putParametrs(m_configFileModel.getTripletParametrs());
            m_vectConverters.push_back(converterPtr);
        }
    }

    m_configFileModel.CloseConfig();
}

void SoundController::Convert() {
    for (size_t i = 0; i < m_vectInWavFileModel.size(); i++) {
        m_vectInWavFileModel[i].OpenForRead();
    }

    m_outWavFileModel.OpenForWrite();

    InitConfConvertors();

    std::vector<unsigned short> samples;
    unsigned int second = 0;
    while (!m_vectInWavFileModel[0].isEnd()) {
        second++;

        samples = m_vectInWavFileModel[0].ReadSecond();
        for (size_t i = 1; i < m_vectInWavFileModel.size(); i++) {
            m_vectInWavFileModel[i].ReadSecond();
        }

        for (const auto &converterPtr : m_vectConverters) {
            samples = converterPtr->UpdateSound(samples, second);
        }

        m_outWavFileModel.WriteSamples(samples);
    }

    m_outWavFileModel.closeWriteFile();
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
        std::cout << "Converter: " << converterPtr->getName() << std::endl;
        std::cout << "Params: " << converterPtr->getParametrs() << std::endl;
        std::cout << "Features: " << converterPtr->getFeatures() << std::endl;
        std::cout << "Syntax in config: " << converterPtr->getSyntax() << std::endl;
        std::cout << "=========================" << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
    }
}