#pragma once

#ifdef EXPORT
#define STL_Importer_API __declspec(dllimport)
#else
#define STL_Importer_API __declspec(dllexport)
#endif //EXPORT

#include <string>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>

class STL_Importer_API STL_Importer
{
public:

	using Point = std::array<float, 3>;
	using Triangle = std::array<int, 3>;

	struct Face
	{
		bool m_hasNormal = false;
		Point m_normal = { 0, 0, 0 };
		Triangle m_triangle;
	};
	STL_Importer();
	STL_Importer(const STL_Importer&) = delete;
	STL_Importer(STL_Importer&&) = delete;
	STL_Importer& operator = (const STL_Importer&) = delete;
	STL_Importer& operator = (STL_Importer&&) = delete;
	void Import(const std::string& i_file_path, std::vector<Face>& o_faces, std::vector<Point>& o_vertexs);	
	~STL_Importer() = default;
private:
	std::string m_name;
};

