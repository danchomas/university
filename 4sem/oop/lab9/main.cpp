#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <sstream>
#include <stdexcept>

class Point3D {
private:
    float x, y, z;

public:
    Point3D(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

    float getX() const { return x; }
    float getY() const { return y; }
    float getZ() const { return z; }

    void setX(float val) { x = val; }
    void setY(float val) { y = val; }
    void setZ(float val) { z = val; }
};

class Triangle {
private:
    int v1, v2, v3;

public:
    Triangle(int v1 = 0, int v2 = 0, int v3 = 0) : v1(v1), v2(v2), v3(v3) {}

    int getV1() const { return v1; }
    int getV2() const { return v2; }
    int getV3() const { return v3; }

    void setV1(int val) { v1 = val; }
    void setV2(int val) { v2 = val; }
    void setV3(int val) { v3 = val; }
};

class OBJModel {
private:
    std::list<Point3D> vertices;
    std::list<Triangle> faces;

public:
    bool loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string prefix;
            iss >> prefix;

            if (prefix == "v") {
                float x, y, z;
                if (!(iss >> x >> y >> z)) {
                    throw std::runtime_error("Invalid vertex data in file: " + filename);
                }
                vertices.emplace_back(x, y, z);
            }
            else if (prefix == "f") {
                int v1, v2, v3;
                if (!(iss >> v1 >> v2 >> v3)) {
                    throw std::runtime_error("Invalid face data in file: " + filename);
                }
                if (v1 < 1 || v2 < 1 || v3 < 1 ||
                    v1 > vertices.size() ||
                    v2 > vertices.size() ||
                    v3 > vertices.size()) {
                    throw std::out_of_range("Vertex index out of range in face data");
                }
                faces.emplace_back(v1-1, v2-1, v3-1);
            }
        }

        file.close();
        return true;
    }

    friend OBJModel operator+(const OBJModel& a1, const OBJModel& a2) {
        OBJModel result;
        result.vertices = a1.vertices;
        result.faces = a1.faces;
        size_t baseIdx = a1.vertices.size();
        result.vertices.insert(result.vertices.end(),
                             a2.vertices.begin(),
                             a2.vertices.end());

        for (const auto& f : a2.faces) {
            Triangle newFace = f;
            newFace.setV1(f.getV1() + baseIdx);
            newFace.setV2(f.getV2() + baseIdx);
            newFace.setV3(f.getV3() + baseIdx);
            result.faces.push_back(newFace);
        }

        return result;
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to create file: " + filename);
        }
        for (const auto& vertex : vertices) {
            file << "v " << vertex.getX() << " " << vertex.getY() << " " << vertex.getZ() << "\n";
        }
        for (const auto& face : faces) {
            file << "f " << face.getV1()+1 << " " << face.getV2()+1 << " " << face.getV3()+1 << "\n";
        }

        file.close();
    }

    size_t getVertexCount() const { return vertices.size(); }
    size_t getTriangleCount() const { return faces.size(); }
};

int main() {
    try {
        OBJModel model1, model2, result;

        model1.loadFromFile("model1.obj");
        model2.loadFromFile("model2.obj");

        result = model1 + model2;
        result.saveToFile("result.obj");

        std::cout << "Модель корректно обьединена : "
                  << result.getVertexCount()
                  << ", triangles: " << result.getTriangleCount() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
