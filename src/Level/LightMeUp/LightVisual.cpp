#include "LightVisual.h"

LightVisual::LightVisual()
{
    //ctor
}

LightVisual::~LightVisual()
{
    //dtor
}

void LightVisual::initRing( Light& r_Lt0, unsigned int numLts, float posX, float posY, float radius, float dPosX, float dPosY, sf::Vector2f LtSz )
{
    pLt0 = &r_Lt0;
    this->numLts = numLts;
    vtxVec.resize( 4*numLts );
    
    // Calculate angle between each LED
    float angleStep = 2.0f * M_PI / numLts;
    
    for( unsigned int n = 0; n < numLts; ++n )
    {
        // Calculate position of this LED's center
        float angle = n * angleStep;
        float centerX = posX + radius * cos(angle);
        float centerY = posY + radius * sin(angle);
        
        // Calculate the four corners of the LED square
        // Offset by half the LED size to center it
        float halfWidth = LtSz.x / 2.0f;
        float halfHeight = LtSz.y / 2.0f;
        
        vtxVec[4*n].position.x = centerX - halfWidth;     // up lt
        vtxVec[4*n].position.y = centerY - halfHeight;
        
        vtxVec[4*n+1].position.x = centerX + halfWidth;   // up rt
        vtxVec[4*n+1].position.y = centerY - halfHeight;
        
        vtxVec[4*n+2].position.x = centerX + halfWidth;   // dn rt
        vtxVec[4*n+2].position.y = centerY + halfHeight;
        
        vtxVec[4*n+3].position.x = centerX - halfWidth;   // dn lt
        vtxVec[4*n+3].position.y = centerY + halfHeight;
    }
}

void LightVisual::init( Light& r_Lt0, unsigned int Rows, unsigned int Cols, float posX, float posY, float dPosX, float dPosY, sf::Vector2f LtSz )
{
    pLt0 = &r_Lt0;
    numLts = Rows*Cols;
    vtxVec.resize( 4*numLts );

    for( unsigned int n = 0; n < numLts; ++n )
    {

        vtxVec[4*n].position.x = posX + n%Cols*( LtSz.x + dPosX );// up lt
        vtxVec[4*n].position.y = posY + n/Cols*( LtSz.y + dPosY );

        vtxVec[4*n+1].position.x = vtxVec[4*n].position.x + LtSz.x;// up rt
        vtxVec[4*n+1].position.y = vtxVec[4*n].position.y;

        vtxVec[4*n+2].position.x = vtxVec[4*n+1].position.x;// dn rt
        vtxVec[4*n+2].position.y = vtxVec[4*n].position.y + LtSz.y;

        vtxVec[4*n+3].position.x = vtxVec[4*n].position.x;// dn lt
        vtxVec[4*n+3].position.y = vtxVec[4*n+2].position.y;
    }
}

sf::FloatRect LightVisual::getRect()const
{
    sf::FloatRect retVal;
    retVal.left = vtxVec[0].position.x;
    retVal.top = vtxVec[0].position.y;
    const sf::Vertex& backVtx = vtxVec[ vtxVec.size() - 2 ];// dn rt vtx in last quad
    retVal.width = backVtx.position.x - retVal.left;
    retVal.height = backVtx.position.y - retVal.top;

    return retVal;
}

sf::Vector2f LightVisual::getLtSize()const
{
    float w = vtxVec[1].position.x - vtxVec[0].position.x;
    float h = vtxVec[3].position.y - vtxVec[0].position.y;
    return sf::Vector2f( w, h );
}

bool LightVisual::isOver( float x, float y )const
{
    sf::FloatRect rect( getRect() );
    if( x < rect.left ) return false;
    if( x > rect.left + rect.width ) return false;
    if( y < rect.top ) return false;
    if( y > rect.top + rect.height ) return false;
    return true;
}

void LightVisual::update()
{
    sf::Color LtClr;
    const Light* pLt = pLt0;
    for( unsigned int n = 0; n < numLts; ++n )
    {
        LtClr.r = pLt->r;
        LtClr.g = pLt->g;
        LtClr.b = pLt->b;
        vtxVec[4*n+3].color = vtxVec[4*n+2].color = vtxVec[4*n+1].color = vtxVec[4*n].color = LtClr;
        ++pLt;
    }
}

void LightVisual::draw( sf::RenderTarget& RT ) const
{
    if( vtxVec.empty() ) return;
    RT.draw( &( vtxVec[0] ), vtxVec.size(), sf::Quads );
}

