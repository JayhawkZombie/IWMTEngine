#ifndef LIGHTVISUAL_H
#define LIGHTVISUAL_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Light.h"

// graphical rep. of 1 LightGrid. each Light = 1 sf::Quad
class LightVisual
{
public:
    const Light* pLt0 = nullptr;// use for an array
    std::vector<sf::Vertex> vtxVec;// for entire group
    unsigned int numLts = 0;// useful in methods

    // group is entire grid. Rectangular layout
    void init( Light* r_Lt0, unsigned int Rows, unsigned int Cols, float posX, float posY, float dPosX, float dPosY, sf::Vector2f LtSz );
    LightVisual( Light* r_Lt0, unsigned int Rows, unsigned int Cols, float posX, float posY, float dPosX, float dPosY, sf::Vector2f LtSz )
    { init( r_Lt0, Rows, Cols, posX, posY, dPosX, dPosY, LtSz ); }

    LightVisual();
    ~LightVisual();

    sf::FloatRect getRect()const;
    sf::Vector2f getLtSize()const;
    bool isOver( float x, float y )const;

    void RenderEditor();
    void RenderLightsEditor();
    void RenderEditorForSingleLight(const Light *lt);

    void update();
    void draw( sf::RenderTarget& RT ) const;

    protected:

    private:
};

#include <Reflection/GenReflection.h>
RENGINE_REFLECT_CLASS_BEGIN(LightVisual)
RENGINE_REFLECT_CLASS_MEMBER(LightVisual, numLts, "numLights")
RENGINE_REFLECT_CLASS_END(LightVisual)

#endif // LIGHTVISUAL_H
