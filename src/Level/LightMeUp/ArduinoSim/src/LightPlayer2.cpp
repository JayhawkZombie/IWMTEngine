#include "LightPlayer2.h"

void LightPlayer2::init(std::vector<Light>& lights, unsigned int Rows, unsigned int Cols, const patternData& rPattData, unsigned int NumPatterns)
{
    m_lights = &lights;
    rows = Rows;
    cols = Cols;
    numLts = rows*cols;

    stepTimer = 0;
    stepIter = 0;
    patternIter = 0;

    pattData = &rPattData;
    numPatterns = NumPatterns;
}

void LightPlayer2::setStateData(uint8_t* p_StateData, unsigned int DataSz)
{
    pStateData = p_StateData;
    stateDataSz = DataSz;
    BA.init(p_StateData[0], DataSz);
}

void LightPlayer2::update(const Light& onLt, const Light& offLt)
{
    for(unsigned int n = 0; n < numLts; ++n)
    {
        if(getState(n)) (*m_lights)[n] = onLt;
        else (*m_lights)[n] = offLt;
    }

    if(++stepTimer >= pattData[patternIter].stepPause)
    {
        stepTimer = 0;
        if(++stepIter >= getPattLength())
        {
            stepIter = 0;
            if(++patternIter >= numPatterns)
                patternIter = 0;
        }
    }
}

unsigned int LightPlayer2::getPattLength() const
{
    const auto& config = LightPatterns::GetPatternConfig(pattData[patternIter].type);
    
    switch(config.category)
    {
        case LightPatterns::PatternCategory::Basic:
            return 1;
            
        case LightPatterns::PatternCategory::Linear:
            if (config.type == LightPatterns::PatternType::AlternateBlink ||
                config.type == LightPatterns::PatternType::CheckerBlink)
                return pattData[patternIter].param;
            return numLts;
            
        case LightPatterns::PatternCategory::Grid:
            if (config.type == LightPatterns::PatternType::ScrollBoxIn ||
                config.type == LightPatterns::PatternType::ScrollBoxOut)
                return cols/2;
            else if (config.type == LightPatterns::PatternType::ScrollDiagonal)
                return rows + cols;
            else if (config.type == LightPatterns::PatternType::ScrollColumnRight ||
                     config.type == LightPatterns::PatternType::ScrollColumnLeft)
                return cols;
            else
                return rows;
            
        case LightPatterns::PatternCategory::Special:
            if (config.type == LightPatterns::PatternType::CustomBitPattern)
                return BA.bitSize()/numLts;
            return 1;
    }
    return 1;
}

bool LightPlayer2::getState(unsigned int n) const
{
    const auto& pattern = pattData[patternIter];
    const auto& config = LightPatterns::GetPatternConfig(pattern.type);
    
    switch(config.category)
    {
        case LightPatterns::PatternCategory::Basic:
            return false;

        case LightPatterns::PatternCategory::Linear:
            return handleLinearPattern(pattern.type, n, pattern.param);
            
        case LightPatterns::PatternCategory::Grid:
            return handle2DPattern(pattern.type, n, pattern.param);
            
        case LightPatterns::PatternCategory::Special:
            return handleSpecialPattern(pattern.type, n, pattern.param);
    }
    return false;
}

bool LightPlayer2::handleLinearPattern(LightPatterns::PatternType type, unsigned int n, unsigned int param) const
{
    switch(type)
    {
        case LightPatterns::PatternType::ScrollRight:
            return scrollToRight(n, param);
        case LightPatterns::PatternType::ScrollLeft:
            return scrollToLeft(n, param);
        case LightPatterns::PatternType::FillFromRight:
            return fillFromRight(n);
        case LightPatterns::PatternType::FillFromLeft:
            return fillFromLeft(n);
        case LightPatterns::PatternType::CrissCross:
            return crissCross(n, param);
        case LightPatterns::PatternType::AlternateBlink:
            return alternateBlink(n);
        case LightPatterns::PatternType::CheckerBlink:
            return checkerBlink(n);
        default:
            return false;
    }
}

bool LightPlayer2::handle2DPattern(LightPatterns::PatternType type, unsigned int n, unsigned int param) const
{
    switch(type)
    {
        case LightPatterns::PatternType::ScrollColumnRight:
            return scrollColToRight(n, param);
        case LightPatterns::PatternType::ScrollColumnLeft:
            return scrollColToLeft(n, param);
        case LightPatterns::PatternType::ScrollRowBottom:
            return scrollRowToBottom(n, param);
        case LightPatterns::PatternType::ScrollRowTop:
            return scrollRowToTop(n, param);
        case LightPatterns::PatternType::ScrollBoxIn:
            return scrollBoxIn(n);
        case LightPatterns::PatternType::ScrollBoxOut:
            return scrollBoxOut(n);
        case LightPatterns::PatternType::ScrollDiagonal:
            return scrollDiagonal(n);
        default:
            return false;
    }
}

bool LightPlayer2::handleSpecialPattern(LightPatterns::PatternType type, unsigned int n, unsigned int param) const
{
    switch(type)
    {
        case LightPatterns::PatternType::CustomBitPattern:
            if(pStateData) return BA.getBit(stepIter*numLts + n);
            return false;
        default:
            return false;
    }
}

bool LightPlayer2::scrollToRight(unsigned int n, unsigned int numInGroup) const
{ return (n >= stepIter && n < stepIter + numInGroup); }

bool LightPlayer2::scrollToLeft(unsigned int n, unsigned int numInGroup) const
{ return (n <= numLts - 1 - stepIter) && (n + numInGroup > numLts - 1 - stepIter); }

bool LightPlayer2::fillFromRight(unsigned int n) const
{ return (n >= numLts - 1 - stepIter); }

bool LightPlayer2::fillFromLeft(unsigned int n) const
{ return (n <= stepIter); }

bool LightPlayer2::crissCross(unsigned int n, unsigned int numInGroup) const
{
    bool A = (n >= stepIter && n < stepIter + numInGroup);
    bool B = (n <= numLts - 1 - stepIter);
    B = B && (n + numInGroup > numLts - 1 - stepIter);
    return A || B;
}

bool LightPlayer2::alternateBlink(unsigned int n) const
{ return (n + stepIter)%2; }

bool LightPlayer2::checkerBlink(unsigned int n) const
{ return (n + n/cols + stepIter)%2; }

bool LightPlayer2::scrollColToRight(unsigned int n, unsigned int numInGroup) const
{ return stepIter == n%cols; }

bool LightPlayer2::scrollColToLeft(unsigned int n, unsigned int numInGroup) const
{ return stepIter == (cols - 1 - n%cols); }

bool LightPlayer2::scrollRowToBottom(unsigned int n, unsigned int numInGroup) const
{ return stepIter == n/cols; }

bool LightPlayer2::scrollRowToTop(unsigned int n, unsigned int numInGroup) const
{ return stepIter == rows - 1 - n/cols; }

bool LightPlayer2::scrollBoxIn(unsigned int n) const
{
    unsigned int SI = stepIter, SIr = cols - 1 - stepIter;
    unsigned int ndc = n/cols, npc = n%cols;
    bool A = (ndc >= SI) && (ndc <= SIr);
    bool B = (npc >= SI) && (npc <= SIr);
    bool LC = (npc == SI) && A;
    bool RC = (npc == SIr) && A;
    bool TR = (ndc == SI) && B;
    bool BR = (ndc == SIr) && B;
    return LC || RC || TR || BR;
}

bool LightPlayer2::scrollBoxOut(unsigned int n) const
{
    unsigned int SI = cols/2 - 1 - stepIter;
    unsigned int SIr = cols - 1 - SI;
    unsigned int ndc = n/cols, npc = n%cols;
    bool A = (ndc >= SI) && (ndc <= SIr);
    bool B = (npc >= SI) && (npc <= SIr);
    bool LC = (npc == SI) && A;
    bool RC = (npc == SIr) && A;
    bool TR = (ndc == SI) && B;
    bool BR = (ndc == SIr) && B;
    return LC || RC || TR || BR;
}

bool LightPlayer2::scrollDiagonal(unsigned int n) const
{
    if(stepIter >= n/cols) return n%cols == stepIter - n/cols;
    return false;
}
