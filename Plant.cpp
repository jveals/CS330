/*
 *  Plant.cpp
 *  Game
 *
 *  Created by David Reed, Matt Oldfield, Jeremy Sampson, Andrew Daugherty
 *  and Alex Martishius
 *  Copyright 2011. All rights reserved.
 *
 */


//---------------------------------------------------------

#include "Plant.h"
#include <string>
#include <sstream>

//---------------------------------------------------------

Plant::Plant()
{
	setKillsBottom(true);
	setKillsSide(true);
	setKillsTop(true);
	setPoints(0);
	setXVelocity(0.0);
	setYVelocity(1.0);
    count_ = 120;
    
    sprite();
}

//---------------------------------------------------------

Plant::~Plant()
{
}

//---------------------------------------------------------

void Plant::draw()
{

	glColor3ub(0, 255, 0);
    glBegin(GL_POLYGON);
    glVertex2d(left(),bottom());
    glVertex2d(right(),bottom());
    glVertex2d(right(),top());
    glVertex2d(left(),top());
    glEnd();  
    
    
    
}

//---------------------------------------------------------

void Plant::shootFireball()
{

}

//---------------------------------------------------------

void Plant::updateScene()
{
    // uses the private variable count_ to time the movement of the piranha plant
    // if the count is between 120 and 91 the plant should move upward
    if (count_ >= 91 && count_ <= 120)
    {
        this->setYVelocity(1.0);
    }
    // if the count is between 90 and 61 the plant should stay stationary on top of the block
    else if (count_ >= 61 && count_ <= 90)
    {
        this->setYVelocity(0.0);
    }
    // if the count is between 60 and 31 the plant should be moving back down
    else if (count_ >= 31 && count_ <= 60)
    {
        this->setYVelocity(-1.0);
    }
    // if the count is between 30 and 0 the plant should be stationary and hiding
    else if (count_ >= 0 && count_ <= 30)
    {
        this->setYVelocity(0.0);
        
        // when the count reaches 0 it will reset back to 0
        if (count_ == 0)
        {
            count_ = 120;
        }

    }
    count_--;

}

//---------------------------------------------------------

void Plant::sprite()
{
    texturePos = 0;
    
    // Mac environment variable for home directory
    char *cHomeDir = NULL;
    
    cHomeDir = getenv("HOME");
    
    // I think Windows uses HOMEPATH
    if (!cHomeDir) {
        cHomeDir = getenv("HOMEPATH");
    }
    std::string homeDir = cHomeDir;
    std::string iName;
    homeDir += "/CS330/sprites/plant";
    
    std::string pos;
    std::stringstream out;
    
    for (int i = 0; i<2; ++i) {
        std::stringstream out;
        //Generates Filename
        iName = homeDir;
        out<<i;
        pos = out.str();
        iName += pos;
        iName += ".tex";
        
        FILE *fp = fopen(iName.c_str(), "r");
        unsigned char *texture = new unsigned char[4 * 256 * 256];
        if (fread(texture, sizeof(unsigned char), 4 * 256 * 256, fp)
            != 4* 256 *256) {
            fprintf(stderr, "error reading %s", iName.c_str());
        }
        fclose(fp);
        
        glGenTextures(1, &texture_[i]);
        glBindTexture(GL_TEXTURE_2D, texture_[i]);
        
        glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );        
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                        GL_LINEAR_MIPMAP_NEAREST );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                        GL_LINEAR );        
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                        GL_CLAMP );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                        GL_CLAMP );
        gluBuild2DMipmaps(GL_TEXTURE_2D, 4, 256, 256, GL_RGBA,
                          GL_UNSIGNED_BYTE, texture);
        delete [] texture;
        
    } 
}
