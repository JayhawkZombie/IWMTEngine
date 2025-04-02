#ifndef LIGHTPLAYER2_H
#define LIGHTPLAYER2_H

#include "../../Light.h"
#include "utility/bitArray.h"
#include "../../PatternDefinitions.h"
#include <vector>

struct patternData
{
public:
    LightPatterns::PatternType type = LightPatterns::PatternType::AllOff;
    unsigned int stepPause = 1;
    unsigned int param = 0;
    void init(LightPatterns::PatternType patternType, unsigned int StepPause = 1, unsigned int Param = 0)
    { type = patternType; stepPause = StepPause; param = Param; }
};

class LightPlayer2
{
public:
    // Pattern iteration
    unsigned int numPatterns = 1;  // size of storage arrays
    unsigned int patternIter = 0;  // 0 to numPatterns. This is index into arrays
    
    // Pattern data
    const patternData* pattData = nullptr;
    
    // Custom bit pattern data
    uint8_t* pStateData = nullptr;  // pattern #100: Length = stateDataSz/numLts
    unsigned int stateDataSz = 0;
    bitArray BA;  // for bitwise storage of above stateData
    
    // Pattern state
    unsigned int stepTimer = 0;  // timer for stepIter incrementation
    unsigned int stepIter = 0;  // 0 to patternLength

    // Core functions
    void init(std::vector<Light>& lights, unsigned int Rows, unsigned int Cols, const patternData& rPattData, unsigned int NumPatterns);
    void update(const Light& onLt, const Light& offLt);
    bool getState(unsigned int n) const;
    unsigned int getPattLength() const;
    void setStateData(uint8_t* p_StateData, unsigned int DataSz);

    // Constructor/Destructor
    LightPlayer2() = default;
    ~LightPlayer2() = default;

protected:
    std::vector<Light>* m_lights = nullptr;  // Reference to the lights vector
    unsigned int rows = 1, cols = 1;
    unsigned int numLts = 1;  // numLts = rows*cols

private:
    // Pattern implementation functions
    bool handleLinearPattern(LightPatterns::PatternType type, unsigned int n, unsigned int param) const;
    bool handle2DPattern(LightPatterns::PatternType type, unsigned int n, unsigned int param) const;
    bool handleSpecialPattern(LightPatterns::PatternType type, unsigned int n, unsigned int param) const;

    // Individual pattern implementations
    bool scrollToRight(unsigned int n, unsigned int numInGroup) const;
    bool scrollToLeft(unsigned int n, unsigned int numInGroup) const;
    bool fillFromRight(unsigned int n) const;
    bool fillFromLeft(unsigned int n) const;
    bool crissCross(unsigned int n, unsigned int numInGroup) const;
    bool alternateBlink(unsigned int n) const;
    bool checkerBlink(unsigned int n) const;
    bool scrollColToRight(unsigned int n, unsigned int numInGroup) const;
    bool scrollColToLeft(unsigned int n, unsigned int numInGroup) const;
    bool scrollRowToBottom(unsigned int n, unsigned int numInGroup) const;
    bool scrollRowToTop(unsigned int n, unsigned int numInGroup) const;
    bool scrollBoxIn(unsigned int n) const;
    bool scrollBoxOut(unsigned int n) const;
    bool scrollDiagonal(unsigned int n) const;
};

#endif // LIGHTPLAYER2_H
