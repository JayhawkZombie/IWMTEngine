#ifndef LIGHTPLAYER2_H
#define LIGHTPLAYER2_H

#include <array>
#include <unordered_map>

#include "Light.h"

/*
*        case 0 : return false;// a "pause" between patterns
case 1 : return scrollToRight( n, param );
case 2 : return scrollToLeft( n, param );
case 3 : return fillFromRight( n );
case 4 : return fillFromLeft( n );
case 5 : return crissCross( n, param );
case 6 : return alternateBlink( n );
case 7 : return checkerBlink( n );
// 2d patterns
case 10 : return scrollColToRight( n );
case 11 : return scrollColToLeft( n );
case 12 : return scrollRowToBottom( n );
case 13 : return scrollRowToTop( n );
case 14 : return scrollBoxIn( n );
case 15 : return scrollBoxOut( n );
case 16 : return scrollDiagonal( n, param );
*/

constexpr const char *PatternNames[] = {
    "pause",
    "scroll-to-right",
    "scroll-to-left",
    "fill-from-right",
    "fill-from-left",
    "criss-cross",
    "alternate-blink",
    "checker-blink",
    "<8>",
    "<9>",
    "scroll-col-right",
    "scroll-col-left",
    "scroll-row-bottom",
    "scroll-row-top",
    "scroll-box-in",
    "scroll-box-out",
    "scroll-diag",
    "<17>",
    "<oops>",
    "<oops>",
    "<20>",
    "<oops>",
    "<oops>",
    "<oops>",
    "<oops>",
    "<oops>",
    "<oops>",
    "<oops>",
    "<oops>",
    "<oops>",
    "<30>",
    "fillColFromTop",
    "unfillColFromTop",
    "fillColFromBottom",
    "unfillColFromBottom",
    "<oops>",
    "<oops>",
    "<oops>",
    "<oops>",
    "<oops>",
    "<oops>",
};

const std::array<unsigned int, 19> AvailableFunctionIndices = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    10,
    11,
    12,
    13,
    14,
    15,
    16,
    31,
    32,
    33,
    34,
};

#include <Reflection/GenReflection.h>

// a player for presenting procedural patterns in a specified order
RENGINE_REFLECTABLE_BEGIN(patternData)

struct patternData // for each pattern in the sequence to be played
{
public:
    RENGINE_REFLECT_PROPERTY(funcIndex);
    unsigned int funcIndex = 0; // which pattern

    RENGINE_REFLECT_PROPERTY(stepPause);
    unsigned int stepPause = 1;
    // between each step in the present pattern. To slow animation

    RENGINE_REFLECT_PROPERTY(param);
    unsigned int param = 0;
    // varying purpose. see notes for each case in getPattLength() and getState()

    // convenient init
    void init(unsigned int fIdx,
              unsigned int StepPause = 1,
              unsigned int Param     = 0) {
        funcIndex = fIdx;
        stepPause = StepPause;
        param     = Param;
    }
};

RENGINE_REFLECTABLE_END(patternData)

class LightPlayer2 {
public:
    // new iteration scheme
    unsigned int numPatterns = 1; // number of patterns in the sequence
    unsigned int patternIter = 0;
    // 0 to numPatterns. This is index into pattData array below

    // 1 instance per pattern in the sequence
    const patternData *pattData = nullptr;
    // array to be provided on Arduino for this data

    unsigned int stepTimer = 0; // timer for stepIter incrementation
    unsigned int stepIter  = 0; // 0 to patternLength
    // new. Lights are members not passed as arguments
    Light onLt, offLt;

    // new. Find pattern length
    unsigned int getPattLength() const; // lookup for each funcIndex

    // Arduino: Lights[NUM_LEDS]  NUM_LEDS = Rows*Cols     patternData[]            patternData size
    void init(Light &r_Lt0,
              int Rows,
              int Cols,
              const patternData &rPattData,
              unsigned int NumPatterns);

    // 1st player draws the off color
    void update();       // assign as desired
    void updateOnOnly(); // writes only to onLt
    // for use as 2nd player in sub rect
    void updateSub(); // draw over background
    void updateSubOnOnly();
    // writes only to onLt. 1st player assign of others stand

    bool getState(unsigned int n) const;
    // of each light (on/off) in the draw of all numLts

    // pattern functions indexed to in switch within getState
    bool scrollToRight(unsigned int n, unsigned int numInGroup) const;
    // returns state assignment
    bool scrollToLeft(unsigned int n, unsigned int numInGroup) const;
    // returns state assignment
    bool fillFromRight(unsigned int n) const;
    bool fillFromLeft(unsigned int n) const;
    bool crissCross(unsigned int n, unsigned int numInGroup) const;
    bool alternateBlink(unsigned int n) const;
    bool checkerBlink(unsigned int n) const; // checker board fill

    // patterns for 2d
    bool scrollColToRight(unsigned int n) const;
    bool scrollColToLeft(unsigned int n) const;
    bool scrollRowToBottom(unsigned int n) const;
    bool scrollRowToTop(unsigned int n) const;
    bool scrollBoxIn(unsigned int n) const;
    bool scrollBoxOut(unsigned int n) const;
    // Mode: 0 = dn rt, 1 = up lt, 2 = dn lt, 3 = up lt
    bool scrollDiagonal(unsigned int n, unsigned int Mode) const;

    // New ones
    bool fillColumnFromTop(unsigned int n,
                           unsigned int colToFill,
                           unsigned int toRow) const;
    bool unfillColumnFromTop(unsigned int n,
                             unsigned int colToFill,
                             unsigned int toRow) const;
    bool fillColumnFromBottom(unsigned int n,
                              unsigned int colToFill,
                              unsigned int toRow) const;
    bool unfillColumnFromBottom(unsigned int n,
                                unsigned int colToFill,
                                unsigned int toRow) const;

    LightPlayer2() {
    }

    ~LightPlayer2() {
    }

    // set the target rectangle within a larger array (Grid)
    void setGridBounds(int Row0, int Col0, int GridRows, int GridCols) {
        row0     = Row0;
        col0     = Col0;
        gridRows = GridRows;
        gridCols = GridCols;
    }

    // useful getters
    int getRows() const { return rows; }

    int getCols() const { return cols; }

    unsigned int getNumLts() const { return numLts; }

    static bool ShowParamUI(unsigned int funcIndex, int &paramValue);
    bool ShowEditor();

protected:                 // new for me. Not everything is public
    Light *pLt0 = nullptr; // to LightArr on Arduino

    //   unsigned int rows = 1, cols = 1;
    int rows     = 1, cols     = 1; // dimensions of this array
    int row0     = 0, col0     = 0; // origin in grid
    int gridCols = 1, gridRows = 1; // bounding grid
    // dependent. For convenience in functions
    unsigned int numLts = 1; // numLts = rows*cols

private:
};

#endif // LIGHTPLAYER2_H
