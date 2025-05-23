//
// Created by Kurt Slagle on 4/20/25.
//

#include "DataPlayerWrapper.h"
#include <Globals.h>
#include <Console/EngineConsole.h>
#include <fmt/ostream.h>

DataPlayerWrapper::~DataPlayerWrapper() {
}

void DataPlayerWrapper::Tick(double delta) {
    if (!HasInit()) {
        return;
    }
    m_dataPlayer.update();
    GetLightVisual().update();
}

void DataPlayerWrapper::Init() {
    BaseLightPlayerWrapper::Init();
    int rows, cols;
    int row0, col0;
    std::ifstream infile("Boom2_4colorBits16x16_data.txt");
    if (!infile) {
        GlobalConsole->
                Error("Failed to open file Boom2_4colorBits16x16_data.txt");
        return;
    }

    infile >> rows >> cols;
    infile >> row0 >> col0;
    GlobalConsole->Info("%i x %i @(%i,%i)", rows, cols, row0, col0);

    infile >> m_dataPlayer.stepPause >> m_dataPlayer.drawOff >> m_dataPlayer.
            fadeAlong;
    GlobalConsole->Debug("stepPause: %i drawOff: %i fadeAlong %i",
                         m_dataPlayer.stepPause,
                         m_dataPlayer.drawOff,
                         m_dataPlayer.fadeAlong);
    ResizeNumLights(rows * cols, Light(125, 125, 125));
    for (auto &light: GetLights()) {
        light.init(125, 125, 125);
    }
    infile >> m_numColors;
    GlobalConsole->Debug("numColors: %i", m_numColors);

    unsigned int red, green, blue;
    for (int i = 0; i < m_numColors; ++i) {
        infile >> red >> green >> blue;
        GlobalConsole->Debug("red: %i, green: %i, blue: %i", red, green, blue);
        m_dataPlayer.Lt[i].init(red, green, blue);
    }

    const auto pos            = GetPosition();
    const auto realSize       = GetSize();
    const auto spaceForBoxesX = realSize.x - ((cols - 1) * m_boxSpacing.x);
    const auto spaceForBoxesY = realSize.y - ((rows - 1) * m_boxSpacing.y);
    const auto boxSize        = sf::Vector2f(spaceForBoxesX / cols,
                                             spaceForBoxesY / rows);

    bool dataInBits;
    infile >> dataInBits;

    if (dataInBits) {
        GlobalConsole->Debug("Reading data in bits");
        if (m_numColors == 16) {
            GlobalConsole->Debug("initDataPlay(): 16 colors from dlbBits");
            unsigned int numQuadBits;
            infile >> numQuadBits;
            GlobalConsole->Debug("numQuadBits: %i", numQuadBits);

            if (numQuadBits % 2 == 0)
                m_dataPlayerDataVector.
                        resize(numQuadBits / 2);
            else m_dataPlayerDataVector.resize(numQuadBits / 2 + 1);
            m_dataPlayer.init(GetLights()[0],
                              rows,
                              cols,
                              m_dataPlayerDataVector[0],
                              m_dataPlayerDataVector.size(),
                              16);

            GlobalConsole->Debug("DataVec.size(): %lu",
                                 m_dataPlayerDataVector.size());

            unsigned int inVal = 0;
            m_dataPlayer.BA.Clear();
            for (unsigned int k = 0; k < numQuadBits; ++k) {
                infile >> inVal;
                m_dataPlayer.BA.pushQuad(inVal);
            }
        } else if (m_numColors == 4) {
            GlobalConsole->Debug("initDataPlay(): 4 colors from dlbBits");
            unsigned int numDblBits;
            infile >> numDblBits;

            if (numDblBits % 4 == 0)
                m_dataPlayerDataVector.
                        resize(numDblBits / 4);
            else m_dataPlayerDataVector.resize(numDblBits / 4 + 1);
            std::cout << "\n m_dataPlayerDataVector.size() = " <<
                    m_dataPlayerDataVector.size();

            m_dataPlayer.init(GetLights()[0],
                              rows,
                              cols,
                              m_dataPlayerDataVector[0],
                              m_dataPlayerDataVector.size(),
                              4);

            unsigned int inVal = 0;
            m_dataPlayer.BA.Clear();
            for (unsigned int k = 0; k < numDblBits; ++k) {
                infile >> inVal;
                m_dataPlayer.BA.push(inVal / 2 > 0); // hi bit
                m_dataPlayer.BA.push(inVal % 2 > 0); // lo bit
            }
        } else if (m_numColors == 2) {
            std::cout << "\n initDataPlay(): 2 colors from bits";
            unsigned int numBits;
            infile >> numBits;
            if (numBits % 8 == 0) m_dataPlayerDataVector.resize(numBits / 8);
            else m_dataPlayerDataVector.resize(numBits / 8 + 1);
            m_dataPlayer.init(GetLights()[0],
                              rows,
                              cols,
                              m_dataPlayerDataVector[0],
                              m_dataPlayerDataVector.size(),
                              2);

            bool inVal = false;
            m_dataPlayer.BA.Clear();
            for (unsigned int k = 0; k < numBits; ++k) {
                infile >> inVal;
                m_dataPlayer.BA.push(inVal);
            }
        }
    } else {
        GlobalConsole->Debug("Reading data in rgb");
        // data is in whole bytes which may represent 2, 4 or 16 colors

        GlobalConsole->Debug("Reading %u colors", m_numColors);
        unsigned int numBytes;
        infile >> numBytes;
        m_dataPlayerDataVector.reserve(numBytes);
        unsigned int inVal = 0;
        for (unsigned int k = 0; k < numBytes; ++k) {
            infile >> inVal;
            m_dataPlayerDataVector.push_back(inVal);
        }

        m_dataPlayer.init(GetLights()[0],
                          rows,
                          cols,
                          m_dataPlayerDataVector[0],
                          m_dataPlayerDataVector.size(),
                          m_numColors);
    }

    m_visual.init(GetLights()[0],
                            rows,
                            cols,
                            pos.x,
                            pos.y,
                            4.f,
                            4.f,
                            sf::Vector2f(8.f, 8.f)
                           );
    SetHasInit(true);
    m_dataPlayer.setGridBounds(row0, col0, rows, cols);
    GlobalConsole->Debug("initDataPlay(): BA.bitSize() = %u",
                         m_dataPlayer.BA.bitSize());
}

void DataPlayerWrapper::Render(sf::RenderTarget &target) {
    BaseLightPlayerWrapper::Render(target);
}

void DataPlayerWrapper::GenerateCode() {
    std::ofstream file("dataPlayer.txt");
    fmt::println(file, "CRGB arr[{}]", m_dataPlayer.getCols() * m_dataPlayer.getRows());
    // file << "CRGB arr" << m_dataPlayer.getRows() << " * " << m_dataPlayer.getCols() << ";\n";
    GlobalConsole->Debug("CRGB arr[%i * %i];", m_dataPlayer.getRows(), m_dataPlayer.getCols());
    GlobalConsole->Debug("dp.stepPause = %i; dp.drawOff = %i; dp.fadeAlong = %i;", m_dataPlayer.stepPause, m_dataPlayer.drawOff, m_dataPlayer.fadeAlong);
    fmt::println(file, "dp.stepPause = {};", m_dataPlayer.stepPause);
    file << "dp.stepPause = " << m_dataPlayer.stepPause << ";\n";
    fmt::println(file, "dp.drawOff = {};", m_dataPlayer.drawOff);
    file << "dp.drawOff = " << m_dataPlayer.drawOff << ";\n";
    fmt::println(file, "dp.fadeAlong = {};", m_dataPlayer.fadeAlong);
    file << "dp.fadeAlong = " << m_dataPlayer.fadeAlong << ";\n";
    fmt::println(file, "uint8_t dv[{}]", m_dataPlayerDataVector.size());
    file << "uint8_t dv[" << m_dataPlayerDataVector.size() << "];\n";
    BaseLightPlayerWrapper::GenerateCode();
    const auto lights = GetLights();
    for (int i = 0; i < 16; ++i) {
        fmt::println(file, "dp.lt[{}] = {};", i, m_dataPlayer.Lt[i]);
        file << "dp.Lt[" << i << "] = Light(" << (int) m_dataPlayer.Lt[i].r << "," << (int) m_dataPlayer.Lt[i].g << "," << (int) m_dataPlayer.Lt[i].b << ");\n";
    }
    GlobalConsole->Debug("Data vector %lu", m_dataPlayerDataVector.size());
    for (unsigned int k = 0; k < m_dataPlayerDataVector.size(); ++k) {
        GlobalConsole->Debug("\tdv[%u] = %u", k, m_dataPlayerDataVector[k]);
        fmt::println(file, "dv[{}] = ", k, m_dataPlayerDataVector[k]);
        file << "dv[" << k << "] = " << (int) m_dataPlayerDataVector[k] << ";\n";
    }
}

bool DataPlayerWrapper::RenderEditor() {
    bool edited = false;
    if (ImGui::Button("Generate code")) {
        GenerateCode();
        edited = true;
    }
    return edited;
}
