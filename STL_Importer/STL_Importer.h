#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <array>

class STL_Importer
{
public:
	struct Face
	{
		bool m_hasNormal = false;
		std::array<float, 3> m_normal = { 0, 0, 0 };
		std::array<std::array<float, 3>, 3> m_vertexs;
	};
	STL_Importer();
	void Import(const std::string& i_file_path);	
	const std::vector<Face>& GetFaces() const;
	std::vector<Face>& GetFaces();
	~STL_Importer();
private:
	std::string m_name;
	std::vector<Face> m_faces;
};

