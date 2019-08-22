#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <array>

class STL_Importer
{
public:

	using Point = std::array<float, 3>;
	using Triangle = std::array<Point, 3>;

	struct Face
	{
		bool m_hasNormal = false;
		Point m_normal = { 0, 0, 0 };
		Triangle m_triangle;
	};
	STL_Importer();
	void Import(const std::string& i_file_path, std::vector<Face>& o_vector);	
	~STL_Importer() = default;
private:
	std::string m_name;
	std::vector<Face> m_faces;
};

