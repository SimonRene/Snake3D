#pragma once

#include <vector>
//#include <math.h>

#include <glm/glm.hpp>

#include "CubeObject.h"

class SnakePart {

public:
    SnakePart(float _x, float _y, glm::vec3 worldPos)
    : m_worldPosition(worldPos)
    {
        x = _x;
        y = _y;

        m_worldPosition = worldPos;
    }

    void draw(CubeObject& obj)
    {
        obj.setPosition(m_worldPosition);
        obj.setColor(0.0f, 1.0f, 0.0f);
        obj.draw();
    }

    float x, y;
    glm::vec3 m_worldPosition;

};

struct Food {
    unsigned int x;
    unsigned int y;
};

enum Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST,
    NONE,
};

class Snake {

public:

    Snake(unsigned int size, CubeObject& cube) : m_food({1,1}), m_fieldSize(0), m_cube(cube) {
        m_fieldSize = size;
        m_positions = new glm::vec3[size * size];

        for (int x = 0; x < size; ++x) {
            for (int y = 0; y < size; ++y) {
                glm::vec3 pos((float)(x), 0.0f, -((float)(y)));
                m_positions[size * y + x] = pos;

                std::cout << "Pos (" << x << ", " << y << ") : (" << pos.x << ", " << pos.y << ", " << pos.z << ")" << std::endl;
            }
        }
        
        m_food = {rand()%size, rand()%size};
        m_cube.setColor(0.0f, 1.0f, 0.0f);

        int startX = size/2;
        int startY = size/2;

        SnakePart head(startX, startY, m_positions[(startY * size) + startX]);
        
        m_snakeParts.push_back(head);
    }

    void setDir(Direction newDir) {
        m_currentDir = newDir;
    }

    glm::vec3 getWorldPos(int x, int y) {
        return m_positions[y * m_fieldSize + x];
    }

    bool move() {
        int currentHeadX = m_snakeParts[0].x;
        int currentHeadY = m_snakeParts[0].y;
        int newHeadX = currentHeadX + getVelX();
        int newHeadY = currentHeadY + getVelY();

        if (newHeadX >= static_cast<int>(m_fieldSize)) {
            newHeadX = 0;
        }
        else if (newHeadX < 0) {
            newHeadX = m_fieldSize - 1;
        }

        if (newHeadY >= static_cast<int>(m_fieldSize)) {
            newHeadY = 0;
        }
        else if (newHeadY < 0) {
            newHeadY = m_fieldSize - 1;
        }

        std::cout << "currentHeadX " << currentHeadX << " currentHeadY  " << currentHeadY << std::endl;
        std::cout << "newHeadX " << newHeadX << " newHeadY" << newHeadY << std::endl;
        std::cout << "getVelX() " << getVelX() << " getVelY()" << getVelX() << std::endl;

        bool lostGame = !checkPos(newHeadX, newHeadY);

        int snakeEndX = m_snakeParts[m_snakeParts.size()-1].x;
        int snakeEndY = m_snakeParts[m_snakeParts.size()-1].y;

        for (int i = m_snakeParts.size() - 1; i > 0; --i) {
            m_snakeParts[i].x = m_snakeParts[i-1].x;
            m_snakeParts[i].y = m_snakeParts[i-1].y;
            m_snakeParts[i].m_worldPosition = m_snakeParts[i-1].m_worldPosition;
        }

        m_snakeParts[0].x = newHeadX;
        m_snakeParts[0].y = newHeadY;
        //std::cout << "Moved to " << newHeadX << " - " << newHeadY << std::endl;
        if(!lostGame) {
            m_snakeParts[0].m_worldPosition = m_positions[newHeadY*m_fieldSize + newHeadX];
            if (checkFood(newHeadX, newHeadY)) {
                SnakePart addPart(snakeEndX, snakeEndY, m_positions[(snakeEndY * m_fieldSize) + snakeEndX]);
                m_snakeParts.push_back(addPart);
                m_food.x = rand()%m_fieldSize;
                m_food.y = rand()%m_fieldSize;
            }
        }
        return !lostGame; 
    }

    void draw()
    {
        GLcheck();
        m_cube.setColor(0.0f, 9.0f, 0.0f);
        for (int i = 0; i < m_snakeParts.size(); ++i) {
            m_snakeParts[i].draw(m_cube);
        }
        GLcheck();

        m_cube.setColor(1.0f, 0.0f, 0.0f);

        int index = (m_food.y * m_fieldSize) + m_food.x;
        m_cube.setPosition(m_positions[index]);
        m_cube.draw();

        

        for (int i = 0; i < (m_fieldSize * m_fieldSize); ++i) {
            glm::vec3 pos = m_positions[i];
            // std::cout << "floor at: " << pos.x << " - " << pos.y << " - " << pos.z << std::endl;
            m_cube.setPosition(pos.x, -1.0f, pos.z);
            
            float r = 0.0f;//(rand()%100)/100.0f;
            float g = 0.0f;//(rand()%100)/100.0f;
            float b = 0.8f;//(rand()%100)/100.0f;

            m_cube.setColor(r, g, b);
            m_cube.draw();
        }

        GLcheck();
    }

    int getVelX() {
        switch (m_currentDir)
        {
        case Direction::NORTH:
        case Direction::SOUTH:
            return 0;
            break;
        case Direction::EAST:
            return 1;
            break;
        case Direction::WEST:
            return -1;
            break;
        
        default:
            return 0;
            break;
        }
    }
    int getVelY() {
        switch (m_currentDir)
        {
        case Direction::EAST:
        case Direction::WEST:
            return 0;
            break;
        case Direction::NORTH:
            return 1;
            break;
        case Direction::SOUTH:
            return -1;
            break;
        
        default:
            return 0;
            break;
        }
    }

    bool checkPos(int x, int y) {
        if (m_currentDir == Direction::NONE)
            return true;

        for (int i = 1; i < m_snakeParts.size(); ++i) {
            SnakePart& part = m_snakeParts[i];
            if (part.x == x && part.y == y) {
                std::cout << "hit tail " << i << " . " << part.y << " = " << y << " -- " << part.x << " = " << x << std::endl;
                return false;
            } 
        }

        return true;
    }

    bool checkFood(int x, int y) {
        if (x == m_food.x && y == m_food.y)
            return true;

        return false;
    }

private:
    std::vector<SnakePart> m_snakeParts;
    Food m_food;
    Direction m_currentDir = Direction::NONE;

    unsigned int m_fieldSize;

    // array that contains the 3d world positions of every position the snake can move to on the field
    glm::vec3 * m_positions = nullptr;

    CubeObject m_cube;

};