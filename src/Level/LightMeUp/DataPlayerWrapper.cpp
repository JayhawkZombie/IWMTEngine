//
// Created by Kurt Slagle on 4/20/25.
//

#include "DataPlayerWrapper.h"
#include <Globals.h>
#include <Console/EngineConsole.h>

DataPlayerWrapper::~DataPlayerWrapper() {
}

void DataPlayerWrapper::Tick(double delta) {
    if (!m_init) {
        return;
    }
    m_dataPlayer.update();
    m_dataPlayerVisual.update();
}

void DataPlayerWrapper::Init() {
    GameObject::Init();
    int rows, cols;
    int row0, col0;
    std::ifstream infile("blueGuy_a16color16x16_data.dp");
    if (!infile) {
        std::cerr << "Failed to open 16color data player file" << std::endl;
        GlobalConsole->
                Error("Failed to open file blueGuy_a16color16x16_data.txt");
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
    m_dataPlayerLights.resize(rows * cols);
    for (auto &light: m_dataPlayerLights) {
        light.init(125, 125, 125);
    }
    unsigned int numColors = 2;
    infile >> numColors;
    GlobalConsole->Debug("numColors: %i", numColors);

    unsigned int red, green, blue;
    for (int i = 0; i < numColors; ++i) {
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

    // m_dataPlayerVisual.init(m_dataPlayerLights[0],
    //                         rows,
    //                         cols,
    //                         pos.x,
    //                         pos.y,
    //                         spaceForBoxesX,
    //                         spaceForBoxesY,
    //                         // m_boxSpacing.x,
    //                         // m_boxSpacing.y,
    //                         boxSize);

    bool dataInBits;
    infile >> dataInBits;

    if (dataInBits) {
        GlobalConsole->Debug("Reading data in bits");
        if (numColors == 16) {
            GlobalConsole->Debug("initDataPlay(): 16 colors from dlbBits");
            // std::cout << "\n initDataPlay(): 16 colors from dblBits";
            unsigned int numQuadBits;
            infile >> numQuadBits;
            GlobalConsole->Debug("numQuadBits: %i", numQuadBits);
            // std::cout << "\n numQuadBits = " << numQuadBits;

            if (numQuadBits % 2 == 0)
                m_dataPlayerDataVector.
                        resize(numQuadBits / 2);
            else m_dataPlayerDataVector.resize(numQuadBits / 2 + 1);
            m_dataPlayer.init(m_dataPlayerLights[0],
                              rows,
                              cols,
                              m_dataPlayerDataVector[0],
                              m_dataPlayerDataVector.size(),
                              16);

            GlobalConsole->Debug("DataVec.size(): %lu",
                                 m_dataPlayerDataVector.size());
            // std::cout << "\n DataVec.size() = " << m_dataPlayerDataVector.size();

            unsigned int inVal = 0;
            m_dataPlayer.BA.Clear();
            for (unsigned int k = 0; k < numQuadBits; ++k) {
                infile >> inVal;
                m_dataPlayer.BA.pushQuad(inVal);
            }
        } else if (numColors == 4) {
            GlobalConsole->Debug("initDataPlay(): 4 colors from dlbBits");
            unsigned int numDblBits;
            infile >> numDblBits;

            if (numDblBits % 4 == 0)
                m_dataPlayerDataVector.
                        resize(numDblBits / 4);
            else m_dataPlayerDataVector.resize(numDblBits / 4 + 1);
            std::cout << "\n m_dataPlayerDataVector.size() = " <<
                    m_dataPlayerDataVector.size();

            m_dataPlayer.init(m_dataPlayerLights[0],
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
        } else if (numColors == 2) {
            std::cout << "\n initDataPlay(): 2 colors from bits";
            unsigned int numBits;
            infile >> numBits;
            if (numBits % 8 == 0) m_dataPlayerDataVector.resize(numBits / 8);
            else m_dataPlayerDataVector.resize(numBits / 8 + 1);
            m_dataPlayer.init(m_dataPlayerLights[0],
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

        // std::cout << "\n initDataPlay(): " << numColors << " colors from Bytes";
        GlobalConsole->Debug("Reading %u colors", numColors);
        unsigned int numBytes;
        infile >> numBytes;
        m_dataPlayerDataVector.reserve(numBytes);
        unsigned int inVal = 0;
        for (unsigned int k = 0; k < numBytes; ++k) {
            infile >> inVal;
            m_dataPlayerDataVector.push_back(inVal);
        }

        m_dataPlayer.init(m_dataPlayerLights[0],
                          rows,
                          cols,
                          m_dataPlayerDataVector[0],
                          m_dataPlayerDataVector.size(),
                          numColors);
    }

    m_dataPlayerVisual.init(m_dataPlayerLights[0],
                            rows,
                            cols,
                            pos.x,
                            pos.y,
                            4.f,
                            4.f,
                            sf::Vector2f(8.f, 8.f)
                           );
    m_init = true;
    m_dataPlayer.setGridBounds(row0, col0, rows, cols);
    // std::cout << "\n initDataPlay(): BA.bitSize() = " << m_dataPlayer.BA.bitSize();
    GlobalConsole->Debug("initDataPlay(): BA.bitSize() = %u",
                         m_dataPlayer.BA.bitSize());
}

void DataPlayerWrapper::Render(sf::RenderTarget &target) {
    if (!m_init) {
        return;
    }
    GameObject::Render(target);
    m_dataPlayerVisual.draw(target);
}
