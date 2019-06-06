#include "../include/map.hpp"
#include "../include/constants.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stb_image/stb_image.h>
#include <stdio.h>



Map::Map(std::string filePath)
{
	std::string ppmPath;
	
	// TODO read and construct path graph

	std::ifstream file(filePath);
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			if (line.find("@") != std::string::npos) { continue; }
			else if (line.find("#") != std::string::npos) { continue; } // Skip comments
			else if (line.find("carte") != std::string::npos) { ppmPath = line.substr(6, line.size()); }
			else if (line.find("chemin") != std::string::npos) { m_pathColor = getColorFromString(line); }
			else if (line.find("noeud") != std::string::npos) { m_nodeColor = getColorFromString(line); }
			else if (line.find("construct") != std::string::npos) { m_constructColor = getColorFromString(line); }
			else if (line.find("in") != std::string::npos) { m_startColor = getColorFromString(line); }
			else if (line.find("out") != std::string::npos) { m_endColor = getColorFromString(line);}
			else {m_nodeNumber = getNumberFromString(line);}
		}
		file.close();
	}
	else {
		printf("Chemin de fichier invalide ! %s \n", filePath.c_str());
	}

	

	// Read Png file
	int imgWidth, imgHeight, imgChannels;
	unsigned char* image = stbi_load(ppmPath.c_str(), &imgWidth, &imgHeight, &imgChannels, STBI_rgb);
	if (nullptr == image) {
		printf("Echec du chargement de l'image de carte %s", ppmPath);
	}

	m_gridWidth = imgWidth;
	m_gridHeight = imgHeight;
	m_grid.resize(m_gridWidth * m_gridHeight);

	// Fill grid with tiles
	glm::vec3 color = glm::vec3(0);
	for (int y = 0; y < imgHeight; y++) {
		for (int x = 0; x < imgWidth; x++) {
			color = getPixelColorFromImage(image, imgWidth, x, y);
			if (color == m_constructColor) {
				setTile(x, y, MapTile::constructible);
			}
			else if (color == m_pathColor) {
				setTile(x, y, MapTile::path);
			}
			else if (color == m_endColor) {
				setTile(x, y, MapTile::end);
			}
			else if (color == m_nodeColor) {
				setTile(x, y, MapTile::node);
			}
			else if (color == m_startColor) {
				setTile(x, y, MapTile::start);
			}
			else {
				setTile(x, y, MapTile::locked);
			}
		}
	}
}

Map::~Map()
{
}

/* ----------------- READ ITD ------------------ */

glm::vec3 Map::getPixelColorFromImage(unsigned char* image, int imageWidth, int x, int y) {
	glm::vec3 pixel;
	pixel.r = image[3 * (y * imageWidth + x) + 0];
	pixel.g = image[3 * (y * imageWidth + x) + 1];
	pixel.b = image[3 * (y * imageWidth + x) + 2];
	return pixel;
}

float Map::getNumberFromString(std::string line) {
	std::string temp;
	float data;
	std::stringstream ss(line);
	while (!ss.eof()) {
		ss >> temp;
		if (std::stringstream(temp) >> data) {
			return data;
		}
	}

	printf("[ITD] no valid data at %s", line.c_str());
	return 0.0f;
}

glm::vec3 Map::getColorFromString(std::string line) {
	std::string temp;
	float data;
	std::stringstream ss(line);
	std::vector<float> tempData;
	while (!ss.eof()) {
		ss >> temp;
		if (std::stringstream(temp) >> data) {
			tempData.push_back(data);
		}
	}

	// Save temp data
	glm::vec3 color = glm::vec3(0);
	if (tempData.size() == 3) {
		color.r = tempData.at(0);
		color.g = tempData.at(1);
		color.b = tempData.at(2);
	}
	else {
		printf("[ITD] invalid colors at : %s", line.c_str());
	}

	return color;
}

/* ----------------------- Public methods ------------------ */

glm::vec2 Map::windowToGrid(float x, float y) {
    unsigned int tileX = x / (WINDOW_WIDTH - MENU_WIDTH) * m_gridWidth;
    unsigned int tileY = y / WINDOW_HEIGHT * m_gridHeight;
    return glm::vec2(tileX, tileY);
}

glm::vec2 Map::gridToWindow(unsigned int x, unsigned int y) {
	float posX = (WINDOW_WIDTH - MENU_WIDTH) / m_gridWidth * x;
	float posY = WINDOW_HEIGHT / m_gridHeight * y;
	return glm::vec2(posX, posY);
}

MapTile Map::getTile(unsigned int x, unsigned int y) {
    return m_grid.at(y * m_gridHeight + x);
}

void Map::setTile(int x, int y, MapTile type) {
	m_grid.at(y * m_gridHeight + x) = type;
}

void Map::draw() {
	/*/* DRAW GRID *//*
	glColor4f(255, 0, 0, 1);
    for (int x = 0; x < m_gridWidth; x++) {
		glm::vec2 pos = gridToWindow(x, m_gridHeight);
		glBegin(GL_LINES);
			glVertex2f(pos.x, 0);
			glVertex2f(pos.x, pos.y);
		glEnd();
    }

    for (int y = 0; y < m_gridHeight; y++) {
		glm::vec2 pos = gridToWindow(m_gridWidth, y);
		glBegin(GL_LINES);
			glVertex2f(0, pos.y);
			glVertex2f(pos.x, pos.y);
		glEnd();
   }

	/* DRAW TILES */
	glPointSize(50.0f);
	glm::vec2 center = gridToWindow(1, 1);
	center /= 2;
	for (int y = 0; y < m_gridHeight; y++) {
		for (int x = 0; x < m_gridWidth; x++) {
			MapTile tile = getTile(x, y);
			glm::vec2 pos = gridToWindow(x, y);
			pos += center;
			/*switch (tile) {
			case constructible:
				// glColor4f(m_constructColor.r, m_constructColor.g, m_constructColor.b, 1);
				glColor4f(m_constructColor.r, m_constructColor.g, m_constructColor.b, 0);
				glBegin(GL_POINTS);
					glVertex2f(pos.x, pos.y);
				glEnd();
				break;

			/*case path:
				glColor4f(m_pathColor.r, m_pathColor.g, m_pathColor.b, 1);
				glBegin(GL_POINTS);
					glVertex2f(pos.x, pos.y);
				glEnd();
				break;

			case locked:
				glColor4f(255, 255, 0, 1);
				glBegin(GL_POINTS);
					glVertex2f(pos.x, pos.y);
				glEnd();
				break;

			case start:
				glColor4f(m_startColor.r, m_startColor.g, m_startColor.b, 1);
				glBegin(GL_POINTS);
					glVertex2f(pos.x, pos.y);
				glEnd();
				break;

			case end:
				glColor4f(m_endColor.r, m_endColor.g, m_endColor.b, 1);
				glBegin(GL_POINTS);
					glVertex2f(pos.x, pos.y);
				glEnd();
				break;

			case node:
				glColor4f(m_nodeColor.r, m_nodeColor.g, m_nodeColor.b, 1);
				glBegin(GL_POINTS);
					glVertex2f(pos.x, pos.y);
				glEnd();
				break;

			case tower:
				glColor4f(0.99, 0.79, 0.43, 1);
				glBegin(GL_POINTS);
					glVertex2f(pos.x, pos.y);
				glEnd();
				break;

			default:
				break;
			}*/
		}
	}
	glPointSize(1.0f);		
}


