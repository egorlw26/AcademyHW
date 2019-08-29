
#include "STL_Importer.h"

STL_Importer::STL_Importer() :
  m_part_name("")
  {
  }

/*Importing STL file into std::vector of 'Face's, where 'Face' is nested structure in STL_Importer*/
void STL_Importer::Import(const std::string& i_utf8_file_path)
  {
  std::ifstream in(i_utf8_file_path);
  if (in.is_open())
    {
    std::string input;
    in >> input;
    if (input != "solid")
      throw std::logic_error("Abort. Supposed to read 'solid'!\n");

    //STL file can include a name for the object, it's empty by default
    std::getline(in, m_part_name);
    m_part_name = m_part_name.substr(1);

    //Starting reading faces
    while (true)
      {
      in >> input;

      if (input == "endsolid")
        break;

      if (in.eof())
        throw std::logic_error("Abort. File ended incorrectly!\n");

      if (input != "facet")
        throw std::logic_error("Abort. Supposed to read 'facet'!\n");
      Face t_face;

      //Can include normal for face
      in >> input;
      if (input != "outer" && input != "\touter" && input != "normal")
        throw std::logic_error("Abort. Something wrong after 'facet'!\n");

      if (input == "normal")
        {
        t_face.m_has_normal = true;
        in >> t_face.m_normal[0] >> t_face.m_normal[1] >> t_face.m_normal[2];
        std::getline(in, input);
        }

      //Reading vertexes
      std::getline(in, input);
      if (input != " loop" && input != "outer loop" && input != "\touter loop")
        throw std::logic_error("Abort. Supposed to read 'outer loop'!\n");

      for (size_t i = 0; i < 3; ++i)
        {
        in >> input;
        if (input != "vertex" && input != "\tvertex")
          throw std::logic_error("Abort. Supposed to read 'vertex'!\n");
        Vertex vertex;
        in >> vertex[0] >> vertex[1] >> vertex[2];
        auto pos = std::find(m_vertexes.begin(), m_vertexes.end(), vertex);
        if (pos != m_vertexes.end())
          t_face.m_triangle[i] = static_cast<int>(pos - m_vertexes.begin());
        else
          {
          m_vertexes.push_back(vertex);
          t_face.m_triangle[i] = m_vertexes.size() - 1;
          }
        }
      in >> input;
      if (input != "endloop" && input != "\tendloop")
        throw std::logic_error("Abort. Supposed to read 'endloop'!\n");
      in >> input;
      if (input != "endfacet")
        throw std::logic_error("Abort. Supposed to read 'endfacet'!\n");
      m_faces.push_back(t_face);
      }
    }
  else
    throw std::logic_error("Wrong file path, check it again, please!\n");
  }
