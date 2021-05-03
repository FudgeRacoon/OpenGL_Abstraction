#ifndef OBJPARSER_H
#define OBJPARSER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Core/Mesh.h"

class ObjParser
{
private:
    ObjParser() = delete;
    ~ObjParser() = default;

private:
    static std::vector<std::string> SplitString(std::string __string__, char __char__)
    {
        std::vector<std::string> data;
        std::string word = "";

        for(char letter : __string__)
        {
            if(letter == __char__)
            {
                data.push_back(word);
                word = "";
            }
            else
                word += letter;
        }

        data.push_back(word);
        return data;
    }

public:
    static Mesh* LoadObj(const char* filepath)
    {
        std::vector<float> vertices;
        std::vector<float> texCoord;
        std::vector<uint32_t> indices;

        std::fstream file(filepath, std::ios::in);

        std::string line;
        
        while(getline(file, line))
        {
            std::vector<std::string> data;

            if(line.find("v ") != std::string::npos)
            {
                data = SplitString(line, ' ');
                vertices.push_back(strtof(data[1].c_str(), nullptr));
                vertices.push_back(strtof(data[2].c_str(), nullptr));
                vertices.push_back(strtof(data[3].c_str(), nullptr));
                data.clear();
            }
            else if(line.find("vt ") != std::string::npos)
            {
                data = SplitString(line, ' ');
                texCoord.push_back(strtof(data[1].c_str(), nullptr));
                texCoord.push_back(strtof(data[2].c_str(), nullptr));
                data.clear();
            }
            else if(line.find("f ") != std::string::npos)
            {
                data = SplitString(line, ' ');

                for(int i = 1; i <= 3; i++)
                {
                    std::vector<std::string> temp = SplitString(data[i], '/');
                    indices.push_back(atoi(temp[0].c_str()) - 1);    
                }
            }
        }

        uint32_t verticesSize = vertices.size() * sizeof(float);
        uint32_t texCoordSize = texCoord.size() * sizeof(float);
        uint32_t indiciesSize = indices.size() * sizeof(uint32_t);

        float vertices_array[vertices.size()];
        float texCoord_array[texCoord.size()];
        uint32_t indices_array[indices.size()];

        std::copy(vertices.begin(), vertices.end(), vertices_array);
        std::copy(texCoord.begin(), texCoord.end(), texCoord_array);
        std::copy(indices.begin(), indices.end(), indices_array);

        Mesh* mesh = new Mesh(vertices_array, verticesSize, texCoord_array, texCoordSize, indices_array, indiciesSize);
        return mesh;
    }
};

#endif