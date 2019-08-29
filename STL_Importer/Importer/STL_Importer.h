#pragma once

#ifdef STL_Importer_API_EXPORT
#define STL_Importer_API __declspec(dllexport)
#else
#define STL_Importer_API __declspec(dllimport)
#endif //STL_Importer_API_EXPORT

#include <algorithm>
#include <array>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class STL_Importer
{
public:

  using Vertex = std::array<double, 3>;
  using Triangle = std::array<int32_t, 3>;

  struct Face
  {
    bool m_has_normal = false;
    Vertex m_normal = { 0, 0, 0 };
    Triangle m_triangle;
  };

  STL_Importer_API STL_Importer();

  STL_Importer_API void Import(const std::string& i_utf8_file_path);

  STL_Importer_API std::vector<Face>& GetFaces() { return m_faces; };
  STL_Importer_API std::vector<Vertex>& GetVertexes() { return m_vertexes; };

  STL_Importer(const STL_Importer& other) = delete;
  STL_Importer(STL_Importer&& other) = delete;
  STL_Importer& operator = (const STL_Importer& other) = delete;
  STL_Importer& operator = (STL_Importer&& other) = delete;

  STL_Importer_API ~STL_Importer() = default;

private:
  std::string m_part_name;
  std::vector<Face> m_faces;
  std::vector<Vertex> m_vertexes;
};

