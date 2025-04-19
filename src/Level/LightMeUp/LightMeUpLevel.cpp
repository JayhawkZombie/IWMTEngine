//
// Created by Kurt Slagle on 3/23/25.
//

#include "LightMeUpLevel.h"

#include <Globals.h>
#include <imgui.h>
#include <fmt/base.h>
#include <random>
#include <Logging/LogFormatting.h>

LightMeUpLevel::LightMeUpLevel()
    : m_starrySky(5) // Initialize with 15 stars per cell
     ,
      m_rng(std::random_device()()) // Initialize RNG with random seed
{
    // InitPatterns();
    // ResetAndResizeLights();
}

void LightMeUpLevel::Init() {
    Level::Init();
    fmt::println("LightMeUpLevel::Init");

    InitPatterns();
    ResetAndResizeLights();
}

void LightMeUpLevel::InitPatterns() {
    std::ifstream file("testdata.txt");
    if (!file) {
        GlobalConsole->Error("No init file testdata.txt for patterns");
        return;
    }

    unsigned int rows, cols;
    file >> rows >> cols;

    float posX, posY, dPosX, dPosY;
    file >> posX >> posY >> dPosX >> dPosY;
    sf::Vector2f lightSize;
    file >> lightSize.x >> lightSize.y;

    m_matrixWidth  = static_cast<int>(cols);
    m_matrixHeight = static_cast<int>(rows);
    m_boxSize      = lightSize;
    m_boxPosition  = sf::Vector2f(posX, posY);
    m_boxSpacing   = sf::Vector2f(dPosX, dPosY);

    unsigned int numPatterns;
    file >> numPatterns;
    m_patternData.reserve(numPatterns);

    patternData pd;
    for (int i = 0; i < numPatterns; ++i) {
        file >> pd.funcIndex >> pd.stepPause >> pd.param;
        m_patternData.push_back(pd);
    }
    ResetAndResizeLights();

    m_lightPlayer2.init(m_lights[0],
                        m_matrixHeight,
                        m_matrixWidth,
                        m_patternData[0],
                        numPatterns);
    m_lightPlayer2.onLt  = Light(0, 255, 255);
    m_lightPlayer2.offLt = Light(255, 0, 255);

    m_lightPlayer2.update();

    InitDataPlayer();
}

void LightMeUpLevel::InitDataPlayer() {
    int rows, cols;
    int row0, col0;
    std::ifstream infile("blueGuy_a16color16x16_data.txt");
    if (!infile) {
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

    m_dataPlayerVisual.init(m_dataPlayerLights[0],
                            rows,
                            cols,
                            static_cast<float>(m_boxPosition.x) + 300.f,
                            static_cast<float>(m_boxPosition.y),
                            m_boxSpacing.x,
                            m_boxSpacing.y,
                            m_boxSize);

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


    /*
     *
     *
     *    DataVec.clear();

    int Rows, Cols;
    int Row0, Col0;
    is >> Rows >> Cols;
    is >> Row0 >> Col0;
    is >> DP.stepPause;
    is >> DP.drawOff;
    is >> DP.fadeAlong;
    unsigned int numColors = 2;
    is >> numColors;

    unsigned int rd, gn, bu;
    for( unsigned int k = 0; k < numColors; ++k )
    {
        is >> rd >> gn >> bu;
        DP.Lt[k].init(rd,gn,bu);
    }

    // the data
    bool dataInBits;
    is >> dataInBits;

    if( dataInBits )
    {
        if( numColors == 16 )
        {
            std::cout << "\n initDataPlay(): 16 colors from dblBits";
            unsigned int numQuadBits;
            is >> numQuadBits;
            std::cout << "\n numQuadBits = " << numQuadBits;

            if( numQuadBits%2 == 0 ) DataVec.resize( numQuadBits/2 );
            else DataVec.resize( numQuadBits/2 + 1 );
            DP.init( rLt0, Rows, Cols, DataVec[0], DataVec.size(), 16 );

            std::cout << "\n DataVec.size() = " << DataVec.size();

            unsigned int inVal = 0;
            DP.BA.Clear();
            for( unsigned int k = 0; k < numQuadBits; ++k )
            {
                is >> inVal;
                DP.BA.pushQuad( inVal );
            }
        }
        else if( numColors == 4 )
        {
            std::cout << "\n initDataPlay(): 4 colors from dblBits";
            unsigned int numDblBits;
            is >> numDblBits;

            if( numDblBits%4 == 0 ) DataVec.resize( numDblBits/4 );
            else DataVec.resize( numDblBits/4 + 1 );
            std::cout << "\n DataVec.size() = " << DataVec.size();

            DP.init( rLt0, Rows, Cols, DataVec[0], DataVec.size(), 4 );

            unsigned int inVal = 0;
            DP.BA.Clear();
            for( unsigned int k = 0; k < numDblBits; ++k )
            {
                is >> inVal;
                DP.BA.push( inVal/2 > 0 );// hi bit
                DP.BA.push( inVal%2 > 0 );// lo bit
            }
        }
        else if( numColors == 2 )
        {
            std::cout << "\n initDataPlay(): 2 colors from bits";
            unsigned int numBits;
            is >> numBits;
            if( numBits%8 == 0 ) DataVec.resize( numBits/8 );
            else DataVec.resize( numBits/8 + 1 );
            DP.init( rLt0, Rows, Cols, DataVec[0], DataVec.size(), 2 );

            bool inVal = 0;
            DP.BA.Clear();
            for( unsigned int k = 0; k < numBits; ++k )
            {
                is >> inVal;
                DP.BA.push( inVal );
            }
        }
    }
    else// data is in whole bytes which may represent 2, 4 or 16 colors
    {
        std::cout << "\n initDataPlay(): " << numColors << " colors from Bytes";
        unsigned int numBytes;
        is >> numBytes;
        DataVec.reserve( numBytes );
        unsigned int inVal = 0;
        for( unsigned int k = 0; k < numBytes; ++k )
        {
            is >> inVal;
            DataVec.push_back( inVal );
        }

        DP.init( rLt0, Rows, Cols, DataVec[0], DataVec.size(), numColors );
    }

    DP.setGridBounds( Row0, Col0, GridRows, GridCols );

    std::cout << "\n initDataPlay(): BA.bitSize() = " << DP.BA.bitSize();

    return true;
    */
    m_dataPlayer.setGridBounds(row0, col0, rows, cols);
    // std::cout << "\n initDataPlay(): BA.bitSize() = " << m_dataPlayer.BA.bitSize();
    GlobalConsole->Debug("initDataPlay(): BA.bitSize() = %u",
                         m_dataPlayer.BA.bitSize());
}


void LightMeUpLevel::Destroy() {
}

void LightMeUpLevel::Tick(double deltaTime) {
    UpdateVisuals(deltaTime);

    // Update star cell visibility and color based on LED states
    for (size_t y = 0; y < 8; ++y) {
        for (size_t x = 0; x < 8; ++x) {
            const auto &light = m_dataPlayerLights[y * 8 + x];
            // Calculate visibility based on average brightness
            float brightness = (light.r + light.g + light.b) / (3.0f * 255.0f);
            m_starrySky.setCellVisibility(x, y, brightness);
            // Set color directly from the LED
            m_starrySky.
                    setCellColor(x, y, sf::Color(light.r, light.g, light.b));
        }
    }
}

void LightMeUpLevel::UpdateVisuals(double delta) {
    m_lightPlayer2.update();
    m_visual.update();
    m_starrySky.update(static_cast<float>(delta));
    m_wavePlayer.update(static_cast<float>(delta));
    m_wavePlayerVisual.update();
    m_pulsePlayer.update(static_cast<float>(delta));
    m_pulsePlayerVisual.update();
    m_dataPlayer.update();
    m_dataPlayerVisual.update();
}


void LightMeUpLevel::Render(sf::RenderTarget &target) {
    // Get the bounds of the light grid
    sf::FloatRect lightBounds = m_visual.getRect();
    // Add some padding around the lights for the starry background

    lightBounds.left += lightBounds.width + 50.f;
    lightBounds.top    = 400.f;
    lightBounds.width  = 300.f;
    lightBounds.height = 300.f;

    // Draw starry sky with background in the light grid area
    m_starrySky.draw(target, lightBounds);
    // Then draw the light visualization on top
    RenderVisuals(target);
}

void LightMeUpLevel::RenderVisuals(sf::RenderTarget &target) const {
    m_visual.draw(target);
    m_pulsePlayerVisual.draw(target);
    m_wavePlayerVisual.draw(target);
    m_dataPlayerVisual.draw(target);
}


sf::Vector2f LightMeUpLevel::GetLEDsPosition() const {
    return m_boxPosition;
}

void LightMeUpLevel::SetLEDsPosition(const sf::Vector2f &pos) {
    m_boxPosition = pos;
    ResetAndResizeLights();
}

void LightMeUpLevel::ResetAndResizeLights() {
    m_lights.resize(m_matrixWidth * m_matrixHeight, Light(125, 125, 125));
    m_pulsePlayerLights.resize(m_matrixWidth * m_matrixHeight,
                               Light(125, 125, 125));
    m_visual.init(m_lights[0],
                  m_matrixHeight,
                  m_matrixWidth,
                  m_boxPosition.x,
                  m_boxPosition.y,
                  m_boxSpacing.x,
                  m_boxSpacing.y,
                  m_boxSize);
    AssignRandomColors();
    m_visual.update();
    m_wavePlayer.init(m_lights[0],
                      m_matrixHeight,
                      m_matrixWidth,
                      Light(255, 255, 255),
                      Light(0, 0, 0));
    m_wavePlayerVisual.init(
                            m_lights[0],
                            m_matrixHeight,
                            m_matrixWidth,
                            m_boxPosition.x + 100.f,
                            m_boxPosition.y,
                            m_boxSpacing.x,
                            m_boxSpacing.y,
                            m_boxSize
                           );
    m_wavePlayer.setWaveData(1.f, 64.f, 64.f, 128.f, 64.f);
    m_wavePlayer.update(0.f);
    m_wavePlayerVisual.update();
    m_pulsePlayerVisual.init(m_pulsePlayerLights[0],
                             m_matrixHeight,
                             m_matrixWidth,
                             m_boxPosition.x + 200.f,
                             m_boxPosition.y,
                             m_boxSpacing.x,
                             m_boxSpacing.y,
                             m_boxSize);
    m_pulsePlayerVisual.update();
    m_pulsePlayer.init(m_pulsePlayerLights[0],
                       m_matrixHeight,
                       m_matrixWidth,
                       Light(125, 125, 0),
                       Light(0, 0, 0),
                       2,
                       5.f,
                       true);
    m_wavePlayer.setSeriesCoeffs(C_Rt, 2, nullptr, 0);

    // m_dataPlayerVisual.update();
    // m_dataPlayerVisual.init(m_dataPlayerLights[0],
    //                         m_dataPlayer.getRows(),
    //                         m_dataPlayer.getCols(),
    //                         static_cast<float>(m_boxPosition.x) + 300.f,
    //                         static_cast<float>(m_boxPosition.y),
    //                         m_boxSpacing.x,
    //                         m_boxSpacing.y,
    //                         m_boxSize);
}

void LightMeUpLevel::AssignRandomColors() {
    std::uniform_int_distribution<uint8_t> colorDist(0, 255);
    for (auto &light: m_lights) {
        light.init(colorDist(m_rng), colorDist(m_rng), colorDist(m_rng));
    }
    for (auto &light: m_pulsePlayerLights) {
        light.init(colorDist(m_rng), colorDist(m_rng), colorDist(m_rng));
    }
}
