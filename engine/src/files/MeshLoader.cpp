#include "files/MeshLoader.h"

namespace Crust {
    Status MeshLoader::loadMesh(const char* p_path, Mesh* p_out_mesh) {
        uint8_t fileNameLen = strlen(p_path);

        if (p_path[fileNameLen - 1] == 'j' && p_path[fileNameLen - 2] == 'b' && p_path[fileNameLen - 3] == 'o' && p_path[fileNameLen - 4] == '.') {
            return loadObj(p_path, p_out_mesh);
        } else {
            ExceptionsHandler::throwWarning("No matching file extension for file: %s - The mesh will not be loaded.", p_path);
            return NOT_SUPPORTED;
        }
    }

    Status MeshLoader::loadObj(const char *p_path, Mesh *p_out_mesh) { // TODO refactor obj loader
        std::ifstream file(p_path);
        if (!file.is_open()) {
            ExceptionsHandler::throwWarning("Failed to open file: %s", p_path);
            return FILE_NOT_FOUND;
        }

        std::string line;
        int lineNum = 0;
        const char *analysed_line;

        char str[256];
        float x = 1.0, y = 1.0, z = 1.0;                   // Points values
        int p1_index = 1, p2_index = 1, p3_index = 1; // Points indexes
        int t1_index = 1, t2_index = 1, t3_index = 1; // Textures indexes
        int n1_index = 1, n2_index = 1, n3_index = 1; // Normals indexes

        std::vector<float> points;

        int currentPoint = 0;
        int currentTri = 0;

        while (std::getline(file, line))
        {
            lineNum++;
            analysed_line = line.c_str();
            if (sscanf(analysed_line, "v %f %f %f", &x, &y, &z) == 3)
            {
                points.push_back(x);
                points.push_back(y);
                points.push_back(z);
            }
            else if (sscanf(analysed_line, "vn %f %f %f", &x, &y, &z) == 3)
            {
                // TODO mesh obj loader - usage for vn data
            }
            else if (sscanf(analysed_line, "vt %f %f %f", &x, &y, &z) == 3)
            {
                // TODO mesh obj loader - usage for vt data
            }
            else if (sscanf(analysed_line, "f %d %d %d", &p1_index, &p2_index, &p3_index) == 3)
            {
                Logger::info("f %d %d %d", p1_index, p2_index, p3_index);
                Triangle* tri = new Triangle();
                tri->setVertex(0, points[(p1_index - 1) * 3], points[(p1_index - 1) * 3 + 1], points[(p1_index - 1) * 3 + 2]);
                tri->setVertex(1, points[(p2_index - 1) * 3], points[(p2_index - 1) * 3 + 1], points[(p2_index - 1) * 3 + 2]);
                tri->setVertex(2, points[(p3_index - 1) * 3], points[(p3_index - 1) * 3 + 1], points[(p3_index - 1) * 3 + 2]);
                p_out_mesh->addPolygon(*tri);
            }
            else if (sscanf(analysed_line, "f %d/%d %d/%d %d/%d", &p1_index, &t1_index, &p2_index, &t2_index, &p3_index, &t3_index) == 6)
            {
                Logger::info("f %d/%d %d/%d %d/%d", p1_index, t1_index, p2_index, t2_index, p3_index, t3_index);
                Triangle* tri = new Triangle();
                tri->setVertex(0, points[(p1_index - 1) * 3], points[(p1_index - 1) * 3 + 1], points[(p1_index - 1) * 3 + 2]);
                tri->setVertex(1, points[(p2_index - 1) * 3], points[(p2_index - 1) * 3 + 1], points[(p2_index - 1) * 3 + 2]);
                tri->setVertex(2, points[(p3_index - 1) * 3], points[(p3_index - 1) * 3 + 1], points[(p3_index - 1) * 3 + 2]);
                p_out_mesh->addPolygon(*tri);
            }
            else if (sscanf(analysed_line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &p1_index, &t1_index, &n1_index, &p2_index, &t2_index, &n2_index, &p3_index, &t3_index, &n3_index) == 9)
            {
                Logger::info("f %d/%d/%d %d/%d/%d %d/%d/%d", p1_index, t1_index, n1_index, p2_index, t2_index, n2_index, p3_index, t3_index, n3_index);
                Triangle* tri = new Triangle();
                tri->setVertex(0, points[(p1_index - 1) * 3], points[(p1_index - 1) * 3 + 1], points[(p1_index - 1) * 3 + 2]);
                tri->setVertex(1, points[(p2_index - 1) * 3], points[(p2_index - 1) * 3 + 1], points[(p2_index - 1) * 3 + 2]);
                tri->setVertex(2, points[(p3_index - 1) * 3], points[(p3_index - 1) * 3 + 1], points[(p3_index - 1) * 3 + 2]);
                p_out_mesh->addPolygon(*tri);
            }
            else if (sscanf(analysed_line, "vt %s", str) == 1)
            {
                static bool vtWarning = false;
                if (!vtWarning)
                {
                    ExceptionsHandler::throwWarning("[NOT IMPLEMENTED] vt not implemented");
                    vtWarning = true;
                }
            }
            else if (sscanf(analysed_line, "usemtl %s", str) == 1)
            {
                static bool usemtlWarning = false;
                if (!usemtlWarning)
                {
                    ExceptionsHandler::throwWarning("[NOT IMPLEMENTED] usemtl not implemented");
                    usemtlWarning = true;
                }
            }
            else if (sscanf(analysed_line, "mtllib %s", str) == 1)
            {
                static bool mtllibWarning = false;
                if (!mtllibWarning)
                {
                    ExceptionsHandler::throwWarning("[NOT IMPLEMENTED] mtllib not implemented");
                    mtllibWarning = true;
                }
            }
            else if (sscanf(analysed_line, "s %s", str) == 1)
            {
                static bool sWarning = false;
                if (!sWarning)
                {
                    ExceptionsHandler::throwWarning("[NOT IMPLEMENTED] s off/on not implemented");
                    sWarning = true;
                }
            }
            else if (sscanf(analysed_line, "o %s", str) == 1)
            {
                p_out_mesh->setName(str);
            }
            else
            {
                ExceptionsHandler::throwWarning("No matching rule for line[%d]: %s in obj's file %s", lineNum, analysed_line, p_path);
            }
        }
        return OK;
    }
}