#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

enum MapTile { 
	constructible,
	path,
	locked,
	start,
	end,
	node,
	tower
};

class Map {
public:
    Map(std::string filePath);
    ~Map();

    glm::vec2 windowToGrid(float x, float y);
    glm::vec2 gridToWindow(unsigned int x, unsigned int y);
    MapTile getTile(unsigned int x, unsigned int y);
	void setTile(int x, int y, MapTile type);

    void draw();

private:
	// Read Itd and PPM
	glm::vec3 getPixelColorFromImage(unsigned char* image, int imageWidth, int x, int y);
	glm::vec3 getColorFromString(std::string line);
	float getNumberFromString(std::string line);

private:
    std::vector<MapTile> m_grid;
    unsigned int m_gridWidth;
    unsigned int m_gridHeight;

	// ITD consts
	glm::vec3 m_pathColor;
	glm::vec3 m_nodeColor;
	glm::vec3 m_startColor;
	glm::vec3 m_endColor;
	glm::vec3 m_constructColor;
	float m_nodeNumber;
};
